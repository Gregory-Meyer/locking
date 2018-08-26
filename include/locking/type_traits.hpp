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

#ifndef LOCKING_TYPE_TRAITS_HPP
#define LOCKING_TYPE_TRAITS_HPP

#include <locking/detail/type_traits.hpp>

#include <type_traits>

namespace locking {

// https://en.cppreference.com/w/cpp/named_req/BasicLockable
template <typename T>
struct IsBasicLockable : detail::IsBasicLockableHelper<T>::Type { };

template <typename T>
inline constexpr bool IS_BASIC_LOCKABLE = IsBasicLockable<T>::value;

// https://en.cppreference.com/w/cpp/named_req/Lockable
template <typename T>
struct IsLockable : detail::IsLockableHelper<T>::Type { };

template <typename T>
inline constexpr bool IS_LOCKABLE = IsLockable<T>::value;

// https://en.cppreference.com/w/cpp/named_req/Mutex
template <typename T>
struct IsMutex : detail::IsMutexHelper<T>::Type { };

template <typename T>
inline constexpr bool IS_MUTEX = IsMutex<T>::value;

template <typename T>
struct IsArithmetic : detail::IsArithmetic<T> { };

template <typename T>
inline constexpr bool IS_ARITHMETIC = IsArithmetic<T>::value;

template <typename T>
struct IsRatio : detail::IsRatio<T> { };

template <typename T>
inline constexpr bool IS_RATIO = IsRatio<T>::value;

// https://en.cppreference.com/w/cpp/named_req/Clock
template <typename T>
struct IsClock : detail::IsClockHelper<T>::Type { };

template <typename T>
inline constexpr bool IS_CLOCK = IsClock<T>::value;

} // namespace locking

#endif