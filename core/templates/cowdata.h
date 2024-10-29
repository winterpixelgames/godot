/**************************************************************************/
/*  cowdata.h                                                             */
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

#ifndef COWDATA_H
#define COWDATA_H

#include "core/error/error_macros.h"
#include "core/os/memory.h"
#include "core/templates/safe_refcount.h"

#include <string.h>
#include <type_traits>

template <typename T>
class Vector;
class String;
class Char16String;
class CharString;
template <typename T, typename V>
class VMap;

static_assert(std::is_trivially_destructible_v<std::atomic<uint64_t>>);

// Silence a false positive warning (see GH-52119).
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wplacement-new"
#endif



class CowBackingData {

public:
	typedef int64_t Size;
	typedef uint64_t USize;
	static constexpr USize MAX_INT = INT64_MAX;
	// Function to find the next power of 2 to an integer.
	static USize next_po2(USize x);
	// Alignment:  ↓ max_align_t           ↓ USize          ↓ max_align_t
	//             ┌────────────────────┬──┬─────────────┬──┬───────────...
	//             │ SafeNumeric<USize> │░░│ USize       │░░│ T[]
	//             │ ref. count         │░░│ data size   │░░│ data
	//             └────────────────────┴──┴─────────────┴──┴───────────...
	// Offset:     ↑ REF_COUNT_OFFSET      ↑ SIZE_OFFSET    ↑ DATA_OFFSET

protected:
	mutable void *_ptr = nullptr;

	static constexpr size_t REF_COUNT_OFFSET = 0;
	static constexpr size_t SIZE_OFFSET = ((CowBackingData::REF_COUNT_OFFSET + sizeof(SafeNumeric<CowBackingData::USize>)) % alignof(CowBackingData::USize) == 0) ? (CowBackingData::REF_COUNT_OFFSET + sizeof(SafeNumeric<CowBackingData::USize>)) : ((CowBackingData::REF_COUNT_OFFSET + sizeof(SafeNumeric<CowBackingData::USize>)) + alignof(CowBackingData::USize) - ((CowBackingData::REF_COUNT_OFFSET + sizeof(SafeNumeric<CowBackingData::USize>)) % alignof(CowBackingData::USize)));
	static constexpr size_t DATA_OFFSET = ((CowBackingData::SIZE_OFFSET + sizeof(CowBackingData::USize)) % alignof(max_align_t) == 0) ? (CowBackingData::SIZE_OFFSET + sizeof(CowBackingData::USize)) : ((CowBackingData::SIZE_OFFSET + sizeof(CowBackingData::USize)) + alignof(max_align_t) - ((CowBackingData::SIZE_OFFSET + sizeof(CowBackingData::USize)) % alignof(max_align_t)));

	static _FORCE_INLINE_ SafeNumeric<CowBackingData::USize> *_backing_get_refcount_ptr(uint8_t *p_ptr) {
		return (SafeNumeric<CowBackingData::USize> *)(p_ptr + CowBackingData::REF_COUNT_OFFSET);
	}

	static _FORCE_INLINE_ CowBackingData::USize *_backing_get_size_ptr(uint8_t *p_ptr) {
		return (CowBackingData::USize *)(p_ptr + CowBackingData::SIZE_OFFSET);
	}

	static _FORCE_INLINE_ void *_backing_get_data_ptr(uint8_t *p_ptr) {
		return (void *)(p_ptr + CowBackingData::DATA_OFFSET);
	}

	_FORCE_INLINE_ SafeNumeric<CowBackingData::USize> *_backing_get_refcount() const {
		if (!_ptr) {
			return nullptr;
		}

		return (SafeNumeric<CowBackingData::USize> *)((uint8_t *)_ptr - CowBackingData::DATA_OFFSET + CowBackingData::REF_COUNT_OFFSET);
	}

	_FORCE_INLINE_ CowBackingData::USize *_backing_get_size() const {
		if (!_ptr) {
			return nullptr;
		}

		return (CowBackingData::USize *)((uint8_t *)_ptr - CowBackingData::DATA_OFFSET + CowBackingData::SIZE_OFFSET);
	}

	_FORCE_INLINE_ CowBackingData::USize _backing_get_alloc_size(CowBackingData::USize p_elements, size_t p_element_size) const {
		return CowBackingData::next_po2(p_elements * p_element_size);
	}

	_FORCE_INLINE_ bool _backing_get_alloc_size_checked(CowBackingData::USize p_elements, CowBackingData::USize *out, size_t p_element_size) const {
		if (unlikely(p_elements == 0)) {
			*out = 0;
			return true;
		}
#if defined(__GNUC__) && defined(IS_32_BIT)
		CowBackingData::USize o;
		CowBackingData::USize p;
		if (__builtin_mul_overflow(p_elements, p_element_size, &o)) {
			*out = 0;
			return false;
		}
		*out = CowBackingData::next_po2(o);
		if (__builtin_add_overflow(o, static_cast<CowBackingData::USize>(32), &p)) {
			return false; // No longer allocated here.
		}
#else
		// Speed is more important than correctness here, do the operations unchecked
		// and hope for the best.
		*out = _backing_get_alloc_size(p_elements, p_element_size);
#endif
		return *out;
	}

	_FORCE_INLINE_ CowBackingData::Size _backing_size() const {
		CowBackingData::USize *size = (CowBackingData::USize *)_backing_get_size();
		if (size) {
			return *size;
		} else {
			return 0;
		}
	}

	void _backing_unref(bool p_is_trivially_destructible, void(*p_destructor_func)(void*), size_t p_element_size);

	USize _backing_copy_on_write(bool p_is_trivially_copyable, void(*p_copy_func)(void*, void*), bool p_is_trivially_destructible, void(*p_destructor_func)(void*), size_t p_element_size);

	Error _backing_resize(CowBackingData::Size p_size, bool p_is_zeroed, bool p_is_trivially_copyable, void(*p_copy_func)(void*, void*), bool p_is_trivially_constructible, void(*p_constructor_func)(void*), bool p_is_trivially_destructible, void(*p_destructor_func)(void*), size_t p_element_size);

};

template <typename T>
class CowData : public CowBackingData {
	template <typename TV>
	friend class Vector;
	friend class String;
	friend class Char16String;
	friend class CharString;
	template <typename TV, typename VV>
	friend class VMap;

private:

	static _FORCE_INLINE_ SafeNumeric<CowBackingData::USize> *_get_refcount_ptr(uint8_t *p_ptr) {
		return CowBackingData::_backing_get_refcount_ptr(p_ptr);
	}

	static _FORCE_INLINE_ CowBackingData::USize *_get_size_ptr(uint8_t *p_ptr) {
		return CowBackingData::_backing_get_size_ptr(p_ptr);
	}

	static _FORCE_INLINE_ T *_get_data_ptr(uint8_t *p_ptr) {
		return (T *)CowBackingData::_backing_get_data_ptr(p_ptr);
	}

	_FORCE_INLINE_ SafeNumeric<CowBackingData::USize> *_get_refcount() const {
		return CowBackingData::_backing_get_refcount();
	}

	_FORCE_INLINE_ CowBackingData::USize *_get_size() const {
		return CowBackingData::_backing_get_size();
	}

	_FORCE_INLINE_ CowBackingData::USize _get_alloc_size(CowBackingData::USize p_elements) const {
		return CowBackingData::_backing_get_alloc_size(p_elements, sizeof(T));
	}

	_FORCE_INLINE_ bool _get_alloc_size_checked(CowBackingData::USize p_elements, CowBackingData::USize *out) const {
		return CowBackingData::_backing_get_alloc_size_checked(p_elements, out, sizeof(T));
	}

	void _unref();
	void _ref(const CowData *p_from);
	void _ref(const CowData &p_from);
	CowBackingData::USize _copy_on_write();

public:
	void operator=(const CowData<T> &p_from) { _ref(p_from); }

	_FORCE_INLINE_ T *ptrw() {
		_copy_on_write();
		return (static_cast<T*>(_ptr));
	}

	_FORCE_INLINE_ const T *ptr() const {
		return (static_cast<T*>(_ptr));
	}

	_FORCE_INLINE_ CowBackingData::Size size() const {
		return CowBackingData::_backing_size();
	}

	_FORCE_INLINE_ void clear() { resize(0); }
	_FORCE_INLINE_ bool is_empty() const { return _ptr == nullptr; }

	_FORCE_INLINE_ void set(CowBackingData::Size p_index, const T &p_elem) {
		ERR_FAIL_INDEX(p_index, size());
		_copy_on_write();
		(static_cast<T*>(_ptr))[p_index] = p_elem;
	}

	_FORCE_INLINE_ T &get_m(CowBackingData::Size p_index) {
		CRASH_BAD_INDEX(p_index, size());
		_copy_on_write();
		return (static_cast<T*>(_ptr))[p_index];
	}

	_FORCE_INLINE_ const T &get(CowBackingData::Size p_index) const {
		CRASH_BAD_INDEX(p_index, size());

		return (static_cast<T*>(_ptr))[p_index];
	}

	Error resize(CowBackingData::Size p_size, bool p_is_zeroed=false);

	_FORCE_INLINE_ void remove_at(CowBackingData::Size p_index) {
		ERR_FAIL_INDEX(p_index, size());
		T *p = ptrw();
		CowBackingData::Size len = size();
		for (CowBackingData::Size i = p_index; i < len - 1; i++) {
			p[i] = p[i + 1];
		}

		resize(len - 1);
	}

	Error insert(CowBackingData::Size p_pos, const T &p_val) {
		CowBackingData::Size new_size = size() + 1;
		ERR_FAIL_INDEX_V(p_pos, new_size, ERR_INVALID_PARAMETER);
		Error err = resize(new_size);
		ERR_FAIL_COND_V(err, err);
		T *p = ptrw();
		for (CowBackingData::Size i = new_size - 1; i > p_pos; i--) {
			p[i] = p[i - 1];
		}
		p[p_pos] = p_val;

		return OK;
	}

	CowBackingData::Size find(const T &p_val, CowBackingData::Size p_from = 0) const;
	CowBackingData::Size rfind(const T &p_val, CowBackingData::Size p_from = -1) const;
	CowBackingData::Size count(const T &p_val) const;

	_FORCE_INLINE_ CowData() {}
	_FORCE_INLINE_ ~CowData();
	_FORCE_INLINE_ CowData(CowData<T> &p_from) { _ref(p_from); };
};

template <typename T>
void CowData<T>::_unref() {
	CowBackingData::_backing_unref(std::is_trivially_destructible_v<T>, [](void* p_ptr){
		T *t = static_cast<T*>(p_ptr);
		t->~T();
	}, sizeof(T));
}

template <typename T>
typename CowBackingData::USize CowData<T>::_copy_on_write() {
	return CowBackingData::_backing_copy_on_write(std::is_trivially_copyable_v<T>, [](void* target_ptr, void* src_ptr){
		memnew_placement(static_cast<T*>(target_ptr), T(*(static_cast<T*>(src_ptr))));
	}, std::is_trivially_destructible_v<T>,  [](void* p_ptr){
		T *t = static_cast<T*>(p_ptr);
		t->~T();
	}, sizeof(T));
}

template <typename T>
Error CowData<T>::resize(CowBackingData::Size p_size, bool p_is_zeroed) {
	return CowBackingData::_backing_resize(p_size, p_is_zeroed, std::is_trivially_copyable_v<T>, [](void* target_ptr, void* src_ptr){
		memnew_placement(static_cast<T*>(target_ptr), T(*(static_cast<T*>(src_ptr))));
	}, std::is_trivially_constructible_v<T>, [](void* p_ptr){
		memnew_placement(static_cast<T*>(p_ptr), T);
	}, std::is_trivially_destructible_v<T>,  [](void* p_ptr){
		T *t = static_cast<T*>(p_ptr);
		t->~T();
	}, sizeof(T));
}

template <typename T>
typename CowBackingData::Size CowData<T>::find(const T &p_val, CowBackingData::Size p_from) const {
	CowBackingData::Size ret = -1;

	if (p_from < 0 || size() == 0) {
		return ret;
	}

	for (CowBackingData::Size i = p_from; i < size(); i++) {
		if (get(i) == p_val) {
			ret = i;
			break;
		}
	}

	return ret;
}

template <typename T>
typename CowBackingData::Size CowData<T>::rfind(const T &p_val, CowBackingData::Size p_from) const {
	const CowBackingData::Size s = size();

	if (p_from < 0) {
		p_from = s + p_from;
	}
	if (p_from < 0 || p_from >= s) {
		p_from = s - 1;
	}

	for (CowBackingData::Size i = p_from; i >= 0; i--) {
		if (get(i) == p_val) {
			return i;
		}
	}
	return -1;
}

template <typename T>
typename CowBackingData::Size CowData<T>::count(const T &p_val) const {
	CowBackingData::Size amount = 0;
	for (CowBackingData::Size i = 0; i < size(); i++) {
		if (get(i) == p_val) {
			amount++;
		}
	}
	return amount;
}

template <typename T>
void CowData<T>::_ref(const CowData *p_from) {
	_ref(*p_from);
}

template <typename T>
void CowData<T>::_ref(const CowData &p_from) {
	if (_ptr == p_from._ptr) {
		return; // self assign, do nothing.
	}

	_unref();
	_ptr = nullptr;

	if (!p_from._ptr) {
		return; //nothing to do
	}

	if (p_from._get_refcount()->conditional_increment() > 0) { // could reference
		_ptr = p_from._ptr;
	}
}

template <typename T>
CowData<T>::~CowData() {
	_unref();
}

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif

#endif // COWDATA_H
