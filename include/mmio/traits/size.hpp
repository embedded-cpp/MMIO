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

//<! Internal
//<! External
//<! System
#include <cstddef>
#include <cstdint>

namespace mmio {


    /**
     * @brief Base trait for the size of the register
     * @tparam BitSize: size in bits of a register
     */
    template <std::size_t BitSize>
    struct size_trait;

    /**
     * @brief Specialization of the base trait for 8-bit register
     */
    template <>
    struct size_trait<8U> {
        using type = std::uint8_t;
    };

    /**
     * @brief Specialization of the base trait for 16-bit register
     */
    template <>
    struct size_trait<16U> {
        using type = std::uint16_t;
    };

    /**
     * @brief Specialization of the base trait for 32-bit register
     */
    template <>
    struct size_trait<32U> {
        using type = std::uint32_t;
    };

    /**
     * @brief Specialization of the base trait for 64-bit register
     */
    template <>
    struct size_trait<64U> {
        using type = std::uint64_t;
    };

    /**
     * @brief Concept to check if a type is a valid size trait
     * @tparam Bits Type to check
     */
    template <std::size_t Bits>
    concept supported_size = requires { typename size_trait<Bits>::type; };
} // namespace mmio
#endif // SIZE_HPP
