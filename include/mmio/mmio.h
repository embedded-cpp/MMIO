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

#ifndef MMIO_H
#define MMIO_H

#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "mmio/policy/access.hpp"
#include "mmio/proxy/field.hpp"
#include "mmio/traits/size.hpp"

namespace mmio {

    /**
     * @brief reg class which serves to represent MCU HW reg
     *
     * @tparam BitSize: size in bits of a reg
     * @tparam read/write policy
     */
    template <std::size_t BitSize, typename AccessPolicy>
    class reg {
        static_assert(BitSize == 8 || BitSize == 16 || BitSize == 32 || BitSize == 64, "Unsupported reg size");

        using value_type = typename SizeTrait<BitSize>::type; //<! Alias of internal_tyoe representing reg

        static_assert(std::is_same_v<AccessPolicy, rw> || std::is_same_v<AccessPolicy, ro>
                          || std::is_same_v<AccessPolicy, wo> || std::is_same_v<AccessPolicy, na>,
            "AccessPolicy must be read-write, read-only, write-only or no-access");

        template <typename T>
        static constexpr bool dependent_false_v = false;

    public:
        /**
         * @brief Construct a new reg object: this allow manipulating HW reg at given address
         * @param[in] address: address of the HW reg to handle
         */
        explicit constexpr reg(std::uintptr_t address) noexcept
            : m_raw_ptr(reinterpret_cast<volatile value_type*>(address)) {}

        /**
         * @brief Operator to read from the reg
         * @details Example: uint32_t reader = reg;
         * @note Available for RW & R regs
         * @return value_type: value read of the reg
         */
        [[nodiscard]] constexpr explicit operator value_type() const noexcept {
            if constexpr (std::is_base_of_v<ro, AccessPolicy>) {
                return *m_raw_ptr;
            } else {
                static_assert(dependent_false_v<AccessPolicy>, "Cannot read from write-only reg.");
            }
        }

        /**
         * @brief Assignment operator: allow to write the reg
         * @param[in] value: value to write to the reg
         */
        constexpr reg& operator=(value_type value) noexcept {
            if constexpr (std::is_base_of_v<wo, AccessPolicy>) {
                *m_raw_ptr = value;
                return *this;
            } else {
                static_assert(dependent_false_v<AccessPolicy>, "Cannot modify read-only reg.");
            }
        }

        /**
         * @brief Access field proxy by offset and width
         * @param index Bit index [0; BitSize[
         * @return BitProxy proxy object for bit manipulation
         */
        template <std::size_t Pos, std::size_t Width>
        [[nodiscard]] constexpr auto field() noexcept {
            return Field<Pos, Width, AccessPolicy, reg>{*this};
        }

        /**
         * @brief Read a reg
         * @return The reg value
         */
        [[nodiscard]] constexpr value_type read() const noexcept {
            if constexpr (std::is_base_of_v<ro, AccessPolicy>) {
                return *m_raw_ptr;
            } else {
                static_assert(dependent_false_v<AccessPolicy>, "Cannot read from write-only reg.");
            }
        }

        /**
         * @brief Write a reg
         * @param[in] value: The value to write
         */
        template <value_type value>
        constexpr void write() noexcept {
            if constexpr (std::is_base_of_v<wo, AccessPolicy> && std::is_unsigned_v<value_type>) {
                *m_raw_ptr = value;
            } else {
                static_assert(dependent_false_v<AccessPolicy>, "Cannot write to read-only reg.");
            }
        }

        /**
         * @brief Modify the reg with a callable (only if read-write)
         * @tparam Func Callable type, callable with signature void(value_type&)
         * @param func Callable to modify the reg contents
         */
        template <typename Func>
        void modify(Func&& func) noexcept {
            if constexpr (std::is_base_of_v<rw, AccessPolicy>) {
                value_type val = *m_raw_ptr;
                func(val); // The user modifies a copy
                *m_raw_ptr = val;
            } else {
                static_assert(dependent_false_v<AccessPolicy>, "Can only modify read-write regs.");
            }
        }

    private:
        volatile value_type* m_raw_ptr; //<! Address of the HW reg

        template <std::size_t, std::size_t, typename, typename>
        friend class Field;
    };

} // namespace mmio

#endif // MMIO_H
