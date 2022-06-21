/*************************************************************************/
/*  rw_lock.h                                                            */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef RWLOCK_H
#define RWLOCK_H

#include "core/error_list.h"

#if (!defined(NO_THREADS)) && (!defined(__EMSCRIPTEN__))

#include <shared_mutex>
#include <atomic>

class RWLock {
	mutable std::shared_timed_mutex mutex;

public:
	// Lock the rwlock, block if locked by someone else
	void read_lock() const {
		mutex.lock_shared();
	}

	// Unlock the rwlock, let other threads continue
	void read_unlock() const {
		mutex.unlock_shared();
	}

	// Attempt to lock the rwlock, OK on success, ERR_BUSY means it can't lock.
	Error read_try_lock() const {
		return mutex.try_lock_shared() ? OK : ERR_BUSY;
	}

	// Lock the rwlock, block if locked by someone else
	void write_lock() {
		mutex.lock();
	}

	// Unlock the rwlock, let other thwrites continue
	void write_unlock() {
		mutex.unlock();
	}

	// Attempt to lock the rwlock, OK on success, ERR_BUSY means it can't lock.
	Error write_try_lock() {
		return mutex.try_lock() ? OK : ERR_BUSY;
	}
};

#else

#if defined(NO_THREADS)
class RWLock {
	
public:
	void read_lock() const noexcept { 
	
	}
	void read_unlock() const noexcept { 
		
	 }
	Error read_try_lock() const noexcept { 
		return Error::OK;
	}

	void write_lock() noexcept { 
		
	 }
	void write_unlock() noexcept { 
		
	 }
	Error write_try_lock() noexcept { 
		return Error::OK;
	}
};
#else
// https://rigtorp.se/spinlock/
class RWLock {
	mutable std::atomic<bool> lock_ = {0};
	
public:
	void read_lock() const noexcept { 
		for (;;) {
      // Optimistically assume the lock is free on the first try
      if (!lock_.exchange(true, std::memory_order_acquire)) {
        return;
      }
      // Wait for lock to be released without generating cache misses
      while (lock_.load(std::memory_order_relaxed)) {
        // Issue X86 PAUSE or ARM YIELD instruction to reduce contention between
        // hyper-threads
        //__builtin_ia32_pause();
      }
    }
	 }
	void read_unlock() const noexcept { 
		lock_.store(false, std::memory_order_release);
	 }
	Error read_try_lock() const noexcept { 
		// First do a relaxed load to check if lock is free in order to prevent
    // unnecessary cache misses if someone does while(!try_lock())
    return (Error)(!lock_.load(std::memory_order_relaxed) &&
           !lock_.exchange(true, std::memory_order_acquire));
	}

	void write_lock() noexcept { 
		for (;;) {
      // Optimistically assume the lock is free on the first try
      if (!lock_.exchange(true, std::memory_order_acquire)) {
        return;
      }
      // Wait for lock to be released without generating cache misses
      while (lock_.load(std::memory_order_relaxed)) {
        // Issue X86 PAUSE or ARM YIELD instruction to reduce contention between
        // hyper-threads
        //__builtin_ia32_pause();
      }
    }
	 }
	void write_unlock() noexcept { 
		lock_.store(false, std::memory_order_release);
	 }
	Error write_try_lock() noexcept { 
		// First do a relaxed load to check if lock is free in order to prevent
    // unnecessary cache misses if someone does while(!try_lock())
    return (Error)(!lock_.load(std::memory_order_relaxed) &&
           !lock_.exchange(true, std::memory_order_acquire));
	}
};
#endif
#endif

class RWLockRead {
	const RWLock &lock;

public:
	RWLockRead(const RWLock &p_lock) :
			lock(p_lock) {
		lock.read_lock();
	}
	~RWLockRead() {
		lock.read_unlock();
	}
};

class RWLockWrite {
	RWLock &lock;

public:
	RWLockWrite(RWLock &p_lock) :
			lock(p_lock) {
		lock.write_lock();
	}
	~RWLockWrite() {
		lock.write_unlock();
	}
};

#endif // RWLOCK_H
