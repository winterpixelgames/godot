/**************************************************************************/
/*  cowdata.cpp                                                           */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             PRODOT ENGINE                              */
/**************************************************************************/
/* Copyright (c) 2024-present Prodot Engine contributors (see PRODOT_AUTHORS.md).*/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "cowdata.h"

CowBackingData::USize CowBackingData::next_po2(CowBackingData::USize x) {
	if (x == 0) {
		return 0;
	}

	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	if (sizeof(CowBackingData::USize) == 8) {
		x |= x >> 32;
	}

	return ++x;
}

void CowBackingData::_backing_unref(bool p_is_trivially_destructible, void(*p_destructor_func)(void*), size_t p_element_size) {
	if (!_ptr) {
		return;
	}

	SafeNumeric<CowBackingData::USize> *refc = _backing_get_refcount();
	if (refc->decrement() > 0) {
		return; // still in use
	}
	
	// clean up
	if (!p_is_trivially_destructible) {
		CowBackingData::USize current_size = *_backing_get_size();

		for (CowBackingData::USize i = 0; i < current_size; ++i) {
			uint8_t *ptr = (uint8_t *)_ptr;
			p_destructor_func( (void*)(&(ptr[i*p_element_size])));
		}
	}

	// free mem
	Memory::free_static(((uint8_t *)_ptr) - CowBackingData::DATA_OFFSET, false);
}


CowBackingData::USize CowBackingData::_backing_copy_on_write(bool p_is_trivially_copyable, void(*p_copy_func)(void*, void*), bool p_is_trivially_destructible, void(*p_destructor_func)(void*), size_t p_element_size) {
	if (!_ptr) {
		return 0;
	}

	SafeNumeric<CowBackingData::USize> *refc = _backing_get_refcount();

	CowBackingData::USize rc = refc->get();
	
	if (unlikely(rc > 1)) {
		// in use by more than me
		CowBackingData::USize current_size = *_backing_get_size();

		uint8_t *mem_new = (uint8_t *)Memory::alloc_static(_backing_get_alloc_size(current_size, p_element_size) + CowBackingData::DATA_OFFSET, false);
		ERR_FAIL_NULL_V(mem_new, 0);

		SafeNumeric<CowBackingData::USize> *_refc_ptr = _backing_get_refcount_ptr(mem_new);
		CowBackingData::USize *_size_ptr = _backing_get_size_ptr(mem_new);
		void *_data_ptr = _backing_get_data_ptr(mem_new);

		new (_refc_ptr) SafeNumeric<CowBackingData::USize>(1); //refcount
		*(_size_ptr) = current_size; //size

		
		// initialize new elements
		if (p_is_trivially_copyable) {
			memcpy((uint8_t *)_data_ptr, _ptr, current_size * p_element_size);
		} else {
			for (CowBackingData::USize i = 0; i < current_size; i++) {
				uint8_t *target_ptr = (uint8_t *)_data_ptr;
				target_ptr = &(target_ptr[i*p_element_size]);
				uint8_t *src_ptr = (uint8_t *)_ptr;
				p_copy_func((void*)(target_ptr), (void*)(&(src_ptr[i*p_element_size])));
			}
		}

		_backing_unref(p_is_trivially_destructible, p_destructor_func, p_element_size);
		_ptr = _data_ptr;

		rc = 1;
		
	}
	
	return rc;
}


Error CowBackingData::_backing_resize(CowBackingData::Size p_size, bool p_is_zeroed, bool p_is_trivially_copyable, void(*p_copy_func)(void*, void*), bool p_is_trivially_constructible, void(*p_constructor_func)(void*), bool p_is_trivially_destructible, void(*p_destructor_func)(void*), size_t p_element_size) {
	ERR_FAIL_COND_V(p_size < 0, ERR_INVALID_PARAMETER);

	CowBackingData::Size current_size = _backing_size();

	if (p_size == current_size) {
		return OK;
	}

	if (p_size == 0) {
		// wants to clean up
		_backing_unref(p_is_trivially_destructible, p_destructor_func, p_element_size);
		_ptr = nullptr;
		return OK;
	}

	// possibly changing size, copy on write
	CowBackingData::USize rc = _backing_copy_on_write(p_is_trivially_copyable, p_copy_func, p_is_trivially_destructible, p_destructor_func, p_element_size);

	CowBackingData::USize current_alloc_size = _backing_get_alloc_size(current_size, p_element_size);
	CowBackingData::USize alloc_size;
	ERR_FAIL_COND_V(!_backing_get_alloc_size_checked(p_size, &alloc_size, p_element_size), ERR_OUT_OF_MEMORY);

	if (p_size > current_size) {
		if (alloc_size != current_alloc_size) {
			if (current_size == 0) {
				// alloc from scratch
				uint8_t *mem_new = (uint8_t *)Memory::alloc_static(alloc_size + CowBackingData::DATA_OFFSET, false);
				ERR_FAIL_NULL_V(mem_new, ERR_OUT_OF_MEMORY);

				SafeNumeric<CowBackingData::USize> *_refc_ptr = _backing_get_refcount_ptr(mem_new);
				CowBackingData::USize *_size_ptr = _backing_get_size_ptr(mem_new);
				void *_data_ptr = _backing_get_data_ptr(mem_new);

				new (_refc_ptr) SafeNumeric<CowBackingData::USize>(1); //refcount
				*(_size_ptr) = 0; //size, currently none

				_ptr = _data_ptr;

			} else {
				uint8_t *mem_new = (uint8_t *)Memory::realloc_static(((uint8_t *)_ptr) - CowBackingData::DATA_OFFSET, alloc_size + CowBackingData::DATA_OFFSET, false);
				ERR_FAIL_NULL_V(mem_new, ERR_OUT_OF_MEMORY);

				SafeNumeric<CowBackingData::USize> *_refc_ptr = _backing_get_refcount_ptr(mem_new);
				void *_data_ptr = _backing_get_data_ptr(mem_new);

				new (_refc_ptr) SafeNumeric<CowBackingData::USize>(rc); //refcount

				_ptr = _data_ptr;
			}
		}

		// construct the newly created elements
		if (p_is_trivially_constructible) {
			for (CowBackingData::Size i = *_backing_get_size(); i < p_size; i++) {
				uint8_t *src_ptr = (uint8_t *)_ptr;
				p_constructor_func((void*)(&(src_ptr[i*p_element_size])));
			}
		} else if (p_is_zeroed) {

			memset((void *)((static_cast<uint8_t*>(_ptr)) + (current_size*p_element_size)), 0, (p_size - current_size) * p_element_size);
		}

		*_backing_get_size() = p_size;

	} else if (p_size < current_size) {
		if (p_is_trivially_destructible) {
			// deinitialize no longer needed elements
			for (CowBackingData::USize i = p_size; i < *_backing_get_size(); i++) {
				uint8_t *ptr = (uint8_t *)_ptr;
				p_destructor_func( (void*)(&(ptr[i*p_element_size])));
			}
		}

		if (alloc_size != current_alloc_size) {
			uint8_t *mem_new = (uint8_t *)Memory::realloc_static(((uint8_t *)_ptr) - CowBackingData::DATA_OFFSET, alloc_size + CowBackingData::DATA_OFFSET, false);
			ERR_FAIL_NULL_V(mem_new, ERR_OUT_OF_MEMORY);

			SafeNumeric<CowBackingData::USize> *_refc_ptr = _backing_get_refcount_ptr(mem_new);
			void *_data_ptr = _backing_get_data_ptr(mem_new);

			new (_refc_ptr) SafeNumeric<CowBackingData::USize>(rc); //refcount

			_ptr  = _data_ptr;
		}

		*_backing_get_size() = p_size;
	}

	return OK;
}

/*
 void CowData::remove_at(Size p_index) {
	ERR_FAIL_INDEX(p_index, size());
	T *p = ptrw();
	Size len = size();
	for (Size i = p_index; i < len - 1; i++) {
		p[i] = p[i + 1];
	}

	resize(len - 1);
}
*/