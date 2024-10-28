/**************************************************************************/
/*  cowdata.cpp                                                           */
/**************************************************************************/
/* Copyright (c) 2024 Jordan Schidlowsky, Winterpixel Games.              */
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

void CowBackingData::_backing_unref(bool p_is_trivially_distructable, void(*p_desctructor_func)(void*), size_t p_element_size) {
	if (!_ptr) {
		return;
	}

	SafeNumeric<CowBackingData::USize> *refc = _backing_get_refcount();
	if (refc->decrement() > 0) {
		return; // still in use
	}
	
	// clean up
	if (!p_is_trivially_distructable) {
		CowBackingData::USize current_size = *_backing_get_size();

		for (CowBackingData::USize i = 0; i < current_size; ++i) {
			uint8_t *ptr = (uint8_t *)_ptr;
			p_desctructor_func( (void*)(&(ptr[i*p_element_size])));
		}
	}

	// free mem
	Memory::free_static(((uint8_t *)_ptr) - CowBackingData::DATA_OFFSET, false);
}


CowBackingData::USize CowBackingData::_backing_copy_on_write(bool p_is_trivially_copyable, void(*p_constructor_func)(void*, void*), bool p_is_trivially_distructable, void(*p_desctructor_func)(void*), size_t p_element_size) {
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
				p_constructor_func((void*)(target_ptr), (void*)(&(src_ptr[i*p_element_size])));
			}
		}

		_backing_unref(p_is_trivially_distructable, p_desctructor_func, p_element_size);
		_ptr = _data_ptr;

		rc = 1;
		
	}
	
	return rc;
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