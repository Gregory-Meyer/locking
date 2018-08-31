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

#ifndef LOCKING_HYBRID_MUTEX_HPP
#define LOCKING_HYBRID_MUTEX_HPP

#include <locking/type_traits.hpp>

#include <cstddef>

#include <atomic>
#include <mutex>

namespace locking {

template <typename M = std::mutex>
class AdaptiveMutex {
private:
    M mutex_{ };
    std::atomic_intmax_t predictor_ = 0;

public:
    static_assert(IS_MUTEX<M>, "L must be a Mutex type");

    AdaptiveMutex() = default;

    AdaptiveMutex(const AdaptiveMutex &other) = delete;

    AdaptiveMutex(AdaptiveMutex &&other) = delete;

    AdaptiveMutex& operator=(const AdaptiveMutex &other) = delete;

    AdaptiveMutex& operator=(AdaptiveMutex &&other) = delete;

    void lock() {
        std::intmax_t num_spins = 0;

        while (!mutex_.try_lock()) {
            ++num_spins;

            if (num_spins >= 2 * predictor_) {
                mutex_.lock();

                break;
            }
        }

        predictor_ += (num_spins - predictor_) / 8;
    }

    bool try_lock() {
        return mutex_.try_lock();
    }

    void unlock() {
        mutex_.unlock();
    }
};

} // namespace locking

#endif
