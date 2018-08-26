// BSD 3-Clause License
//
// Copyright (c) 2018, Gregory Meyer
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproducne the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS AS IS
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <locking/adaptive_mutex.hpp>
#include <locking/spinlock.hpp>
#include <locking/type_traits.hpp>

#include <chrono>
#include <mutex>
#include <shared_mutex>

using namespace locking;

struct BasicLock {
    void lock() { };

    void unlock() { };
};

struct Lock {
    void lock() { };

    bool try_lock() { return true; };

    void unlock() { };
};

struct Mutex {
    Mutex() = default;

    Mutex(const Mutex &other) = delete;

    Mutex(Mutex &&other) = delete;

    Mutex& operator=(const Mutex &other) = delete;

    Mutex& operator=(Mutex &&other) = delete;

    void lock() { };

    bool try_lock() { return true; };

    void unlock() { };
};


// IsBasicLockable
static_assert(IS_BASIC_LOCKABLE<BasicLock>, "BasicLock must be BasicLockable");
static_assert(IS_BASIC_LOCKABLE<Lock>, "Lock must be BasicLockable");
static_assert(IS_BASIC_LOCKABLE<Mutex>, "Mutex must be BasicLockable");
static_assert(IS_BASIC_LOCKABLE<Spinlock>, "Spinlock must be BasicLockable");
static_assert(IS_BASIC_LOCKABLE<AdaptiveMutex<>>,
              "AdaptiveMutex<> must be BasicLockable");
static_assert(IS_BASIC_LOCKABLE<std::mutex>,
              "std::mutex must be BasicLockable");
static_assert(IS_BASIC_LOCKABLE<std::timed_mutex>,
              "std::timed_mutex must be BasicLockable");
static_assert(IS_BASIC_LOCKABLE<std::recursive_mutex>,
              "std::recursive_mutex must be BasicLockable");
static_assert(IS_BASIC_LOCKABLE<std::recursive_timed_mutex>,
              "std::recursive_timed_mutex must be BasicLockable");
static_assert(IS_BASIC_LOCKABLE<std::shared_mutex>,
              "std::shared_mutex must be BasicLockable");
static_assert(IS_BASIC_LOCKABLE<std::shared_timed_mutex>,
              "std::shared_timed_mutex must be BasicLockable");

static_assert(!IS_BASIC_LOCKABLE<void>, "void must not be BasicLockable");
static_assert(!IS_BASIC_LOCKABLE<int>, "int must not be BasicLockable");
static_assert(!IS_BASIC_LOCKABLE<double>, "double must not be BasicLockable");


// IsLockable
static_assert(IS_LOCKABLE<Lock>, "Lock must be Lockable");
static_assert(IS_LOCKABLE<Mutex>, "Mutex must be Lockable");
static_assert(IS_LOCKABLE<Spinlock>, "Spinlock must be Lockable");
static_assert(IS_LOCKABLE<AdaptiveMutex<>>, "AdaptiveMutex<> must be Lockable");
static_assert(IS_LOCKABLE<std::mutex>,
              "std::mutex must be Lockable");
static_assert(IS_LOCKABLE<std::timed_mutex>,
              "std::timed_mutex must be Lockable");
static_assert(IS_LOCKABLE<std::recursive_mutex>,
              "std::recursive_mutex must be Lockable");
static_assert(IS_LOCKABLE<std::recursive_timed_mutex>,
              "std::recursive_timed_mutex must be Lockable");
static_assert(IS_LOCKABLE<std::shared_mutex>,
              "std::shared_mutex must be Lockable");
static_assert(IS_LOCKABLE<std::shared_timed_mutex>,
              "std::shared_timed_mutex must be Lockable");

static_assert(!IS_LOCKABLE<BasicLock>, "BasicLock must not be Lockable");
static_assert(!IS_LOCKABLE<void>, "void must not be Lockable");
static_assert(!IS_LOCKABLE<int>, "int must not be Lockable");
static_assert(!IS_LOCKABLE<double>, "double must not be Lockable");


// IsMutex
static_assert(IS_MUTEX<Mutex>, "Mutex must be a Mutex");
static_assert(IS_MUTEX<Spinlock>, "Spinlock must be a Mutex");
static_assert(IS_MUTEX<AdaptiveMutex<>>, "AdaptiveMutex<> must be a Mutex");
static_assert(IS_MUTEX<std::mutex>,
              "std::mutex must be a Mutex");
static_assert(IS_MUTEX<std::timed_mutex>,
              "std::timed_mutex must be a Mutex");
static_assert(IS_MUTEX<std::recursive_mutex>,
              "std::recursive_mutex must be a Mutex");
static_assert(IS_MUTEX<std::recursive_timed_mutex>,
              "std::recursive_timed_mutex must be a Mutex");
static_assert(IS_MUTEX<std::shared_mutex>,
              "std::shared_mutex must be a Mutex");
static_assert(IS_MUTEX<std::shared_timed_mutex>,
              "std::shared_timed_mutex must be a Mutex");

static_assert(!IS_MUTEX<BasicLock>, "BasicLock must not be a Mutex");
static_assert(!IS_MUTEX<Lock>, "Lock must not be a Mutex");
static_assert(!IS_MUTEX<void>, "void must not be a Mutex");
static_assert(!IS_MUTEX<int>, "int must not be a Mutex");
static_assert(!IS_MUTEX<double>, "double must not be a Mutex");


// IsArithmetic
static_assert(IS_ARITHMETIC<char>, "char must be Arithmetic");
static_assert(IS_ARITHMETIC<short>, "short must be Arithmetic");
static_assert(IS_ARITHMETIC<int>, "int must be Arithmetic");
static_assert(IS_ARITHMETIC<long>, "long must be Arithmetic");
static_assert(IS_ARITHMETIC<long long>, "long long must be Arithmetic");

static_assert(IS_ARITHMETIC<unsigned char>, "unsigned char must be Arithmetic");
static_assert(IS_ARITHMETIC<unsigned short>,
              "unsigned short must be Arithmetic");
static_assert(IS_ARITHMETIC<unsigned int>, "unsigned int must be Arithmetic");
static_assert(IS_ARITHMETIC<unsigned long>, "unsigned long must be Arithmetic");
static_assert(IS_ARITHMETIC<unsigned long long>,
              "unsigned long long must be Arithmetic");

static_assert(IS_ARITHMETIC<signed char>, "signed char must be Arithmetic");
static_assert(IS_ARITHMETIC<signed short>, "signed short must be Arithmetic");
static_assert(IS_ARITHMETIC<signed int>, "signed int must be Arithmetic");
static_assert(IS_ARITHMETIC<signed long>, "signed long must be Arithmetic");
static_assert(IS_ARITHMETIC<signed long long>,
              "signed long long must be Arithmetic");

static_assert(IS_ARITHMETIC<float>, "float must be Arithmetic");
static_assert(IS_ARITHMETIC<double>, "double must be Arithmetic");
static_assert(IS_ARITHMETIC<long double>, "long double must be Arithmetic");

static_assert(!IS_ARITHMETIC<void*>, "void* must not be Arithmetic");
static_assert(!IS_ARITHMETIC<int*>, "int* must not be Arithmetic");
static_assert(!IS_ARITHMETIC<double*>, "double* must not be Arithmetic");


// IsRatio
static_assert(IS_RATIO<std::ratio<1, 1>>, "std::ratio<1, 1> must be Ratio");
static_assert(IS_RATIO<std::ratio<42, 42>>, "std::ratio<42, 42> must be Ratio");
static_assert(IS_RATIO<std::ratio<1, 42>>, "std::ratio<1, 42> must be Ratio");
static_assert(IS_RATIO<std::ratio<42, 1>>, "std::ratio<42, 1> must be Ratio");

static_assert(!IS_RATIO<void>, "void must not be Ratio");
static_assert(!IS_RATIO<int>, "int must not be Ratio");
static_assert(!IS_RATIO<double>, "double must not be Ratio");


// IsClock
static_assert(IS_CLOCK<std::chrono::high_resolution_clock>,
              "std::chrono::high_resolution_clock must be Clock");
static_assert(IS_CLOCK<std::chrono::system_clock>,
              "std::chrono::system_clock must be Clock");
static_assert(IS_CLOCK<std::chrono::steady_clock>,
              "std::chrono::steady_clock must be Clock");

static_assert(!IS_CLOCK<void>, "void must not be Clock");
static_assert(!IS_CLOCK<int>, "int must not be Clock");
static_assert(!IS_CLOCK<double>, "double must not be Clock");
