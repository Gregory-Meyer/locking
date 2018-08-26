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

#ifndef LOCKING_DETAIL_TYPE_TRAITS_HPP
#define LOCKING_DETAIL_TYPE_TRAITS_HPP

#include <cstdint>

#include <chrono>
#include <ratio>
#include <type_traits>

namespace locking::detail {

template <typename T>
class IsBasicLockableHelper {
private:
    template <
        typename U,
        typename = decltype(std::declval<U&>().lock()),
        typename = decltype(std::declval<U&>().unlock())
    >
    static std::true_type test(std::nullptr_t);

    template <typename U>
    static std::false_type test(...);

public:
    using Type = decltype(test<T>(nullptr));
};

template <typename T>
class IsLockableHelper {
private:
    template <
        typename U,
        typename = std::enable_if_t<IsBasicLockableHelper<U>::Type::value>,
        typename = std::enable_if_t<std::is_same_v<
            decltype((std::declval<U&>().try_lock())),
            bool
        >>
    >
    static std::true_type test(std::nullptr_t);

    template <typename U>
    static std::false_type test(...);

public:
    using Type = decltype(test<T>(nullptr));
};

template <typename T>
class IsMutexHelper {
private:
    template <
        typename U,
        typename = std::enable_if_t<IsLockableHelper<U>::Type::value>,
        typename = std::enable_if_t<std::is_default_constructible_v<U>>,
        typename = std::enable_if_t<std::is_destructible_v<U>>,
        typename = std::enable_if_t<!std::is_copy_constructible_v<U>>,
        typename = std::enable_if_t<!std::is_move_constructible_v<U>>,
        typename = std::enable_if_t<!std::is_copy_assignable_v<U>>,
        typename = std::enable_if_t<!std::is_move_assignable_v<U>>
    >
    static std::true_type test(std::nullptr_t);

    template <typename U>
    static std::false_type test(...);

public:
    using Type = decltype(test<T>(nullptr));
};

template <typename T>
class IsArithmeticHelper {
private:
    template <
        typename U,
        typename = std::enable_if_t<std::is_convertible_v<
            decltype(+std::declval<const U&>()),
            U
        >>,
        typename = std::enable_if_t<std::is_convertible_v<
            decltype(-std::declval<const U&>()),
            U
        >>,
        typename = std::enable_if_t<std::is_convertible_v<
            decltype(std::declval<const U&>() + std::declval<const U&>()),
            U
        >>,
        typename = std::enable_if_t<std::is_convertible_v<
            decltype(std::declval<const U&>() - std::declval<const U&>()),
            U
        >>,
        typename = std::enable_if_t<std::is_convertible_v<
            decltype(std::declval<const U&>() * std::declval<const U&>()),
            U
        >>,
        typename = std::enable_if_t<std::is_convertible_v<
            decltype(std::declval<const U&>() / std::declval<const U&>()),
            U
        >>
    >
    static std::true_type test(std::nullptr_t);

    template <typename U>
    static std::false_type test(...);

public:
    using Type = decltype(test<T>(nullptr));
};

template <typename T>
struct IsArithmetic : detail::IsArithmeticHelper<T>::Type { };

template <typename T>
inline constexpr bool IS_ARITHMETIC = IsArithmetic<T>::value;

template <typename T>
struct IsRatio : std::false_type { };

template <std::intmax_t N, std::intmax_t D>
struct IsRatio<std::ratio<N, D>> : std::true_type { };

template <typename T>
inline constexpr bool IS_RATIO = IsRatio<T>::value;

template <typename T>
class IsClockHelper {
private:
    template <
        typename U,
        typename = std::enable_if_t<IS_ARITHMETIC<typename U::rep>>,
        typename = std::enable_if_t<IS_RATIO<typename U::period>>,
        typename = std::enable_if_t<std::is_same_v<
            std::chrono::duration<typename U::rep, typename U::period>,
            typename U::duration
        >>,
        typename = std::enable_if_t<std::is_same_v<
            std::chrono::time_point<U>,
            typename U::time_point
        >>,
        typename = std::enable_if_t<std::is_convertible_v<
            decltype((U::is_steady)),
            const bool
        >>,
        typename = std::enable_if_t<std::is_same_v<
            typename U::time_point,
            decltype(U::now())
        >>
    >
    static std::true_type test(std::nullptr_t);

    template <typename U>
    static std::false_type test(...);

public:
    using Type = decltype(test<T>(nullptr));
};

} // namespace locking::detail

#endif
