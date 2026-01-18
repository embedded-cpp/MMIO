/*
 * Copyright 2026 embedded-cpp contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SIZE_HPP
#define SIZE_HPP


#include <cstddef>
#include <cstdint>

namespace mmio {


    /**
     * @brief Base trait for the size of the register
     * @tparam BitSize: size in bits of a register
     */
    template <std::size_t BitSize>
    struct SizeTrait {
        static_assert(BitSize == 8U || BitSize == 16U || BitSize == 32U || BitSize == 64U, "Unsupported register size");
    };

    /**
     * @brief Specialization of the base trait for 8-bit register
     */
    template <>
    struct SizeTrait<8U> {
        using type = std::uint8_t;
    };

    /**
     * @brief Specialization of the base trait for 16-bit register
     */
    template <>
    struct SizeTrait<16U> {
        using type = std::uint16_t;
    };

    /**
     * @brief Specialization of the base trait for 32-bit register
     */
    template <>
    struct SizeTrait<32U> {
        using type = std::uint32_t;
    };

    /**
     * @brief Specialization of the base trait for 64-bit register
     */
    template <>
    struct SizeTrait<64U> {
        using type = std::uint64_t;
    };

} // namespace mmio
#endif // SIZE_HPP
