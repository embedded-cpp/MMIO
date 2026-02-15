/*
 * Copyright 2026 embedded-cpp contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MMIO_HPP
#define MMIO_HPP

//<! Internal
#include "mmio/policy/access.hpp" // IWYU pragma: export
#include "mmio/traits/size.hpp"   // IWYU pragma: export
//<! External
//<! System
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <type_traits>
#include <utility>


namespace mmio {

    /**
     * @brief Represents a memory-mapped hardware register.
     *
     * This class is a zero-overhead wrapper around a specific memory address.
     * It enforces access policies (Read-Only, Write-Only, Read-Write) and
     * data width constraints at compile time using C++20 concepts.
     *
     * @tparam Addr        The physical base address of the register.
     * @tparam BitSize     The width of the register in bits (e.g., 8, 16, 32, 64).
     * @tparam AccessPolicy The access permission policy (ro, wo, rw).
     */
    template <std::uintptr_t Addr, std::size_t BitSize, access_policy AccessPolicy>
        requires (supported_size<BitSize>)
    class reg {
    public:
        using value_type = typename size_trait<BitSize>::type; ///< Underlying integer type (e.g., uint32_t)
        using policy     = AccessPolicy;                       ///< Access policy alias

        static constexpr std::size_t bit_size   = BitSize; ///< Register width in bits
        static constexpr std::uintptr_t address = Addr;    ///< Physical address

        // Compile-time check to ensure the address is aligned to the register size.
        // Prevents unaligned access faults on architectures like ARM.
        static_assert(Addr % (BitSize / 8) == 0, "MMIO register address is not properly aligned for its data width.");

    private:
        /**
         * @brief Internal helper to get a volatile reference to the hardware address.
         * @return Volatile reference to the register memory.
         */
        static constexpr volatile value_type& raw() noexcept {
            return *reinterpret_cast<volatile value_type*>(address);
        }

    public:
        // ================= READ =================

        /**
         * @brief Reads the full value of the register.
         *
         * @note This operation performs a volatile load from memory.
         * @return The current value of the register.
         */
        [[nodiscard]] static constexpr value_type read() noexcept
            requires (readable<AccessPolicy>)
        {
            return raw();
        }

        // ================= WRITE =================

        /**
         * @brief Writes a value to the register.
         *
         * @note This operation performs a volatile store to memory.
         * It overwrites the entire content of the register.
         *
         * @param v The value to write.
         */
        static constexpr void write(value_type v) noexcept
            requires (writable<AccessPolicy>)
        {
            raw() = v;
        }

        /**
         * @brief Writes multiple bit-fields simultaneously in a single hardware operation.
         *
         * This function leverages Variadic Templates and Fold Expressions (C++17) to calculate
         * a merged global mask at compile-time. It ensures that only a single write
         * instruction (STORE) is generated to configure all specified fields.
         *
         * @tparam Fields A list of `mmio::field` or `mmio::bit` types belonging exclusively
         * to this register.
         *
         * @note **Optimization:** The expression `(Fields::mask | ...)` is entirely resolved by the
         * compiler. The resulting machine code is typically reduced to an immediate constant load
         * followed by a memory transfer, which is the fastest operation possible.
         *
         * @warning **Destructive Behavior:** Since this function calls `write()`,
         * ALL register bits not included in the provided `Fields` types will be
         * cleared to zero (0).
         * - To preserve other bits in the register, use `modify()` (Read-Modify-Write).
         * - For a clean initial configuration (Cold Boot), `write_set` is the ideal choice.
         *
         * @requires The register must have a `writable` access policy.
         * @requires All `Fields` must be compatible with the register's `value_type`.
         */
        template <typename... Fields>
        static constexpr void write_set() noexcept
            requires writable<policy>
        {
            write((Fields::mask | ...));
        }
        // ================= MODIFY =================

        /**
         * @brief Modifies the register value using a Read-Modify-Write (RMW) cycle.
         *
         * This function reads the current value, applies the provided callable transformation,
         * and writes the result back.
         *
         * @note This operation is NOT atomic regarding interrupts or multi-threading.
         * If the register is shared, external locking is required.
         *
         * @tparam F Callable type (e.g., lambda) with signature `void(value_type&)`.
         * @param f  The callable that modifies the value in-place.
         */
        template <typename F>
            requires (readable<AccessPolicy> && writable<AccessPolicy> && std::invocable<F, value_type&>)
        static constexpr void modify(F&& f) noexcept {
            value_type tmp = raw();
            std::invoke(std::forward<F>(f), tmp);
            raw() = tmp;
        }
    };

    /**
     * @brief Represents a specific bit-field within a register.
     *
     * Provides safer manipulation of sub-sections of a register by handling
     * bit-shifting and masking automatically.
     *
     * @tparam Register The parent `reg` class.
     * @tparam Offset   The starting bit position (LSB index) of the field.
     * @tparam Width    The width of the field in bits.
     */
    template <typename Register, std::size_t Offset, std::size_t Width>
        requires (Offset + Width <= Register::bit_size)
    class field {
        using value_type = typename Register::value_type;
        using policy     = typename Register::policy;

    public:
        static constexpr value_type mask = ((value_type(1) << Width) - 1) << Offset;

        // ================= READ =================

        /**
         * @brief Reads and extracts the field value.
         *
         * Reads the full register, applies the mask, and shifts the result
         * down to index 0.
         *
         * @return The extracted field value.
         */
        [[nodiscard]] static constexpr value_type read() noexcept
            requires (readable<policy>)
        {
            return (Register::read() & mask) >> Offset;
        }

        // ================= WRITE =================

        /**
         * @brief Writes a value to the field (Read-Write Policy).
         *
         * Performs a Read-Modify-Write cycle:
         * 1. Reads the register.
         * 2. Clears the bits corresponding to this field.
         * 3. Sets the new value for this field.
         * 4. Writes the result back.
         *
         * @note This preserves the state of all other bits (neighbors) in the register.
         * @param v The value to write (will be masked and shifted automatically).
         */
        static constexpr void write(value_type v) noexcept
            requires (writable<policy> && readable<policy>)
        {
            Register::modify([v](value_type& r) {
                r &= ~mask;
                r |= (v << Offset) & mask;
            });
        }

        /**
         * @brief Writes a value to the field (Write-Only Policy).
         *
         * Performs a Direct Write. Since the register cannot be read,
         * it is impossible to preserve the neighbors.
         *
         * @warning **DESTRUCTIVE OPERATION**: All other bits in the register
         * will be set to 0. This is typically used for command or
         * trigger registers where neighbors are irrelevant or reserved.
         *
         * @param v The value to write (will be masked and shifted automatically).
         */
        static constexpr void write(value_type v) noexcept
            requires (writable<policy> && !readable<policy>)
        {
            Register::write((v << Offset) & mask);
        }

        // ================= MODIFY =================

        /**
         * @brief Modifies the field value in-place.
         *
         * Extracts the current field value, passes it to the user-provided
         * function, and writes the updated value back.
         *
         * @note Requires Read-Write access.
         *
         * @tparam F Callable type with signature `void(value_type&)`.
         * @param f  The callable that transforms the field value.
         */
        template <typename F>
        static constexpr void modify(F&& f) noexcept
            requires (writable<policy> && readable<policy> && std::invocable<F, value_type&>)
        {
            Register::modify([&f](value_type& r) {
                value_type tmp = (r & mask) >> Offset;

                std::invoke(std::forward<F>(f), tmp);

                r &= ~mask;
                r |= (tmp << Offset) & mask;
            });
        }

        // ================= BIT OPS =================

        /**
         * @brief Sets the bit to 1 (Read-Write Policy).
         * Uses RMW to preserve other bits in the register.
         */
        static constexpr void set() noexcept
            requires (writable<policy> && readable<policy> && (Width == 1))
        {
            Register::modify([](value_type& r) { r |= mask; });
        }

        /**
         * @brief Sets the bit to 1 (Write-Only Policy).
         *
         * @warning **DESTRUCTIVE**: Writes the mask directly to the register.
         * All other bits become 0.
         */
        static constexpr void set() noexcept
            requires (writable<policy> && (!readable<policy>) && (Width == 1))
        {
            Register::write(mask);
        }

        /**
         * @brief Clears the bit to 0 (Read-Write Policy).
         * Uses RMW to preserve other bits in the register.
         */
        static constexpr void clear() noexcept
            requires (writable<policy> && readable<policy> && (Width == 1))
        {
            Register::modify([](value_type& r) { r &= ~mask; });
        }

        /**
         * @brief Clears the bit to 0 (Write-Only Policy).
         *
         * Writes 0 to the entire register.
         *
         * @warning **DESTRUCTIVE**: effectively resets the whole register to 0.
         * @note This is NOT for "Write 1 to Clear" (W1C) bits. For W1C bits,
         * use `set()` (which writes 1).
         */
        static constexpr void clear() noexcept
            requires (writable<policy> && !readable<policy> && (Width == 1))
        {
            Register::write(0);
        }

        /**
         * @brief Toggles the bit value (0->1 or 1->0).
         *
         * @note Strictly requires Read-Write access, as the new state depends
         * on the previous state.
         */
        static constexpr void toggle() noexcept
            requires (writable<policy> && readable<policy> && (Width == 1))
        {
            Register::modify([](value_type& r) { r ^= mask; });
        }
    };

    /**
     * @brief Convenient alias for a single-bit field.
     */
    template <typename Register, std::size_t Offset>
    using bit = field<Register, Offset, 1>;

} // namespace mmio

#endif // MMIO_HPP
