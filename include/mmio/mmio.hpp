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

#ifndef MMIO_HPP
#define MMIO_HPP

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <type_traits>

#include "mmio/policy/access.hpp" // IWYU pragma: export
#include "mmio/traits/size.hpp" // IWYU pragma: export

namespace mmio {

    /**
     * @brief reg class which serves to represent MCU HW reg
     *
     * @tparam Addr: address of the HW reg
     * @tparam BitSize: size in bits of a reg
     * @tparam read/write policy
     */
    template <std::uintptr_t Addr, std::size_t BitSize, access_policy AccessPolicy>
        requires (supported_size<BitSize>)
    class reg {
    public:
        using value_type = typename size_trait<BitSize>::type; //<! Alias of internal_type representing reg
        using policy     = AccessPolicy; //<! Alias of the access policy of the reg

        static constexpr std::size_t bit_size   = BitSize; //<! Size in bits of the reg
        static constexpr std::uintptr_t address = Addr; //<! Address of the reg

    private:
        /**
         * @brief Check at compile time that the register is properly aligned
         */
        static consteval void validate_alignment() {
            static_assert(address % (BitSize / 8) == 0, "MMIO register not properly aligned");
        }

        /**
         * @brief Return a reference to the raw register value
         * @return Reference to the raw register value
         */
        static constexpr volatile value_type& raw() noexcept {
            return *reinterpret_cast<volatile value_type*>(address);
        }

        /**
         * @brief Check alignment at compile time by using a static member that calls the validation function
         */
        static constexpr auto m_alignment_check = (validate_alignment(), 0);

    public:
        // ================= READ =================

        /**
         * @brief Read a reg
         * @return The reg value
         */
        [[nodiscard]] static constexpr value_type read() noexcept
            requires (readable<AccessPolicy>)
        {
            return raw();
        }


        // ================= WRITE =================

        /**
         * @brief Write a reg
         * @param[in] value: The value to write
         */
        static constexpr void write(value_type v) noexcept
            requires (writable<AccessPolicy>)
        {
            raw() = v;
        }

        // ================= MODIF =================
        /**
         * @brief Modify the reg with a callable (only if read-write)
         * @tparam Func Callable type, callable with signature void(value_type&)
         * @param func Callable to modify the reg contents
         */
        template <typename F>
            requires (readable<AccessPolicy> && writable<AccessPolicy> && std::invocable<F, value_type&>)
        static constexpr void modify(F&& f) noexcept {
            value_type tmp = raw();
            std::invoke(f, tmp);
            raw() = tmp;
        }
    };

    template <typename Register, std::size_t Offset, std::size_t Width>
        requires (Offset + Width <= Register::bit_size)
    class field {
        using value_type                 = typename Register::value_type;
        using policy                     = typename Register::policy;
        static constexpr value_type mask = ((value_type(1) << Width) - 1) << Offset;

    public:
        // ================= READ =================

        /**
         * @brief Read the field value
         * @return The field value
         */
        [[nodiscard]] static constexpr value_type read() noexcept
            requires (readable<policy>)
        {
            return (Register::read() & mask) >> Offset;
        }

        // ================= WRITE =================

        /**
         * @brief Write a value to the field
         * @param[in] v The value to write to the field
         */
        static constexpr void write(value_type v) noexcept
            requires (writable<policy> && readable<policy>)
        {
            Register::modify([&](value_type& r) {
                r &= ~mask;
                r |= (v << Offset) & mask;
            });
        }

        /**
         * @brief Write a value to the field
         * @param[in] v The value to write to the field
         */
        static constexpr void write(value_type v) noexcept
            requires (writable<policy> && !readable<policy>)
        {
            Register::write((v << Offset) & mask);
        }

        // ================= MODIF =================
        /**
         * @brief Modify the field with a callable (only if writable)
         * @tparam F field modification function, callable with signature void(value_type&)
         * @param f field modification function, callable with signature void(value_type&)
         */
        template <typename F>
        static constexpr void modify(F&& f) noexcept
            requires (writable<policy> && std::invocable<F, value_type&>)
        {
            Register::modify([&](value_type& r) {
                value_type tmp = (r & mask) >> Offset;

                std::invoke(f, tmp);

                r &= ~mask;
                r |= (tmp << Offset) & mask;
            });
        }

        // ================= BIT OPS =================
        /**
         * @brief Set the field bits (only for single-bit fields)
         */
        static constexpr void set() noexcept
            requires (writable<policy> && readable<policy> && (Width == 1))
        {
            Register::modify([](value_type& r) { r |= mask; });
        }

        /**
         * @brief Set the field bits (only for single-bit fields)
         */
        static constexpr void set() noexcept
            requires (writable<policy> && (!readable<policy>) && (Width == 1))
        {
            Register::write(mask);
        }

        /**
         * @brief Clear the field bits (only for single-bit fields)
         */
        static constexpr void clear() noexcept
            requires (writable<policy> && readable<policy> && (Width == 1))
        {
            Register::modify([](value_type& r) { r &= ~mask; });
        }

        static constexpr void clear() noexcept
            requires (writable<policy> && !readable<policy> && (Width == 1))
        {
            Register::write(0);
        }

        /**
         * @brief Toggle the field bits (only for single-bit fields)
         */
        static constexpr void toggle() noexcept
            requires (writable<policy> && readable<policy> && (Width == 1))
        {
            Register::modify([](value_type& r) { r ^= mask; });
        }
    };

    // Convenient alias for single-bit fields
    template <typename Register, std::size_t Offset>
    using bit = field<Register, Offset, 1>;

} // namespace mmio

#endif // MMIO_HPP
