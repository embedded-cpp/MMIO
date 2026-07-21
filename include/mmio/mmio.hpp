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

// Internal
#include "mmio/policy/access.hpp" // IWYU pragma: export
#include "mmio/traits/size.hpp"   // IWYU pragma: export
// External
// System
#include <concepts>
#include <cstddef>
#include <cstdint>
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
     * @tparam Addr         The physical base address of the register.
     * @tparam BitSize      The width of the register in bits (e.g., 8, 16, 32, 64).
     * @tparam AccessPolicy The access permission policy (ro, wo, rw, etc..).
     */
    template <std::uintptr_t Addr, std::size_t BitSize, access_policy AccessPolicy>
        requires (supported_size<BitSize>)
    class reg {
    public:
        using value_type = size_trait<BitSize>::type; ///< Underlying integer type (e.g., uint32_t)
        using policy     = AccessPolicy;              ///< Access policy alias

        static constexpr std::size_t BIT_SIZE   = BitSize; ///< Register width in bits
        static constexpr std::uintptr_t ADDRESS = Addr;    ///< Physical address

        // Compile-time check to ensure the address is aligned to the register size.
        // Prevents unaligned access faults on architectures like ARM.
        static_assert(
            ADDRESS % (BIT_SIZE / BITS_8) == 0, "MMIO register address is not properly aligned for its data width.");

    private:
        /**
         * @brief Internal helper to get a volatile reference to the hardware address.
         * @return Volatile reference to the register memory.
         */
        static volatile value_type& raw() noexcept {
            return *reinterpret_cast<volatile value_type*>(ADDRESS); // NOLINT(performance-no-int-to-ptr)
        }

        /**
         * @brief Internal trait: true if field F belongs to this register.
         * @tparam F The field type to check.
         * @note This is an internal implementation detail and is not part of the public API.
         */
        template <typename F>
        static constexpr bool BELONGS_TO_THIS_V = requires {
            typename F::register_type;
            requires std::same_as<typename F::register_type, reg>;
        };

    public:
        reg()                      = delete;
        reg(const reg&)            = delete;
        reg(reg&&)                 = delete;
        ~reg()                     = delete;
        reg& operator=(const reg&) = delete;
        reg& operator=(reg&&)      = delete;

        // ================= READ =================

        /**
         * @brief Reads the full value of the register.
         *
         * @note This operation performs a volatile load from memory.
         * @return The current value of the register.
         */
        [[nodiscard]] static value_type read() noexcept
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
         * @param val The value to write.
         */
        static void write(value_type val) noexcept
            requires (writable<AccessPolicy>)
        {
            raw() = val;
        }

        /**
         * @brief Writes a value to the register, clearing bits that are set to 1.
         *
         * @note This operation performs a volatile store to memory.
         * It overwrites the entire content of the register.
         *
         * @warning This method is only meaningful for registers with a Write-1-to-Clear (W1C) policy.
         * Writing a '1' will clear the corresponding bit, while writing '0' has no effect.
         *
         * @param val The value to write.
         */
        static void write(value_type val) noexcept
            requires (writable_1_to_clear<AccessPolicy>)
        {
            raw() = val;
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
         * @pre The register must have a `writable` access policy.
         * @pre All `Fields` must be compatible with the register's `value_type`.
         */
        template <typename... Fields>
            requires (BELONGS_TO_THIS_V<Fields> && ...)
        static void write_set() noexcept
            requires writable<policy>
        {
            static_assert(sizeof...(Fields) > 0, "write_set requires at least one field");
            write((Fields::MASK | ... | value_type{0}));
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
         * @param func  The callable that modifies the value in-place.
         */
        template <typename F>
            requires (readable<AccessPolicy> && writable<AccessPolicy> && std::invocable<F, value_type&>)
        static void modify(F&& func) noexcept(std::is_nothrow_invocable_v<F, value_type&>) {
            value_type tmp = raw();
            std::forward<F>(func)(tmp);
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
        requires (Offset + Width <= Register::BIT_SIZE)
    class field {
    public:
        using value_type    = Register::value_type; ///< Underlying integer type (e.g., uint32_t)
        using policy        = Register::policy;     ///< Access policy alias from the parent register
        using register_type = Register;             ///< Type alias for the parent register

        static constexpr value_type MASK =
            Width == Register::BIT_SIZE ? ~value_type{0} : ((value_type(1) << Width) - 1) << Offset;

        field()                        = delete;
        field(const field&)            = delete;
        field(field&&)                 = delete;
        ~field()                       = delete;
        field& operator=(const field&) = delete;
        field& operator=(field&&)      = delete;

        // ================= READ =================

        /**
         * @brief Reads and extracts the field value.
         *
         * Reads the full register, applies the mask, and shifts the result
         * down to index 0.
         *
         * @return The extracted field value.
         */
        [[nodiscard]] static value_type read() noexcept
            requires (readable<policy>)
        {
            return (Register::read() & MASK) >> Offset;
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
         * @param val The value to write (will be masked and shifted automatically).
         */
        static void write(value_type val) noexcept
            requires (writable<policy> && readable<policy>)
        {
            Register::modify([val](value_type& reg_val) {
                reg_val &= ~MASK;
                reg_val |= (val << Offset) & MASK;
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
         * @param val The value to write (will be masked and shifted automatically).
         */
        static void write(value_type val) noexcept
            requires (writable<policy> && !readable<policy>)
        {
            Register::write((val << Offset) & MASK);
        }

        /**
         * @brief Writes a value to the field (Write-1-to-Clear Policy).
         *
         * For fields that clear on write (W1C), writing a '1' will clear the bit,
         * while writing '0' has no effect. This method allows setting bits to be cleared
         * without affecting other bits in the register.
         *
         * @param val The value to write (only bits set to '1' will be cleared).
         */
        static void write(value_type val) noexcept
            requires (writable_1_to_clear<policy>)
        {
            Register::write((val << Offset) & MASK);
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
         * @param func  The callable that transforms the field value.
         */
        template <typename F>
        static void modify(F&& func) noexcept(std::is_nothrow_invocable_v<F, value_type&>)
            requires (writable<policy> && readable<policy> && std::invocable<F, value_type&>)
        {
            Register::modify([callable = std::forward<F>(func)](value_type& reg_val) mutable {
                value_type tmp = (reg_val & MASK) >> Offset;
                callable(tmp);
                reg_val &= ~MASK;
                reg_val |= (tmp << Offset) & MASK;
            });
        }

        // ================= BIT OPS =================

        /**
         * @brief Sets the bit to 1 (Read-Write Policy).
         * Uses RMW to preserve other bits in the register.
         */
        static void set() noexcept
            requires (writable<policy> && readable<policy> && (Width == 1))
        {
            Register::modify([](value_type& reg_val) { reg_val |= MASK; });
        }

        /**
         * @brief Sets the bit to 1 (Write-Only Policy).
         *
         * @warning **DESTRUCTIVE**: Writes the MASK directly to the register.
         * All other bits become 0.
         */
        static void set() noexcept
            requires (writable<policy> && (!readable<policy>) && (Width == 1))
        {
            Register::write(MASK);
        }

        /**
         * @brief Clears the bit to 0 (Read-Write Policy).
         * Uses RMW to preserve other bits in the register.
         */
        static void clear() noexcept
            requires (writable<policy> && readable<policy> && (Width == 1))
        {
            Register::modify([](value_type& reg_val) { reg_val &= ~MASK; });
        }

        /**
         * @brief Clears the bit to 0 (Write-Only Policy).
         *
         * Writes 0 to the entire register.
         *
         * @warning **DESTRUCTIVE**: effectively resets the whole register to 0.
         */
        static void clear() noexcept
            requires (writable<policy> && !readable<policy> && (Width == 1))
        {
            Register::write(0);
        }

        /**
         * @brief Clears the bit to 0 (Write-1-to-Clear Policy).
         */
        static void clear() noexcept
            requires (writable_1_to_clear<policy> && (Width == 1))
        {
            Register::write(MASK);
        }

        /**
         * @brief Toggles the bit value (0->1 or 1->0).
         *
         * @note Strictly requires Read-Write access, as the new state depends
         * on the previous state.
         */
        static void toggle() noexcept
            requires (writable<policy> && readable<policy> && (Width == 1))
        {
            Register::modify([](value_type& reg_val) { reg_val ^= MASK; });
        }

        /**
         * @brief Check if a bit is set (1)
         *
         * @note Requires Read-Only access.
         * @return true if the bit is set, false otherwise.
         */
        static bool is_set() noexcept
            requires (readable<policy> && (Width == 1))
        {
            return (Register::read() & MASK) != 0;
        }

        /**
         * @brief Check if a bit is clear (0)
         *
         * @note Requires Read-Only access.
         * @return true if the bit is clear, false otherwise.
         */
        static bool is_clear() noexcept
            requires (readable<policy> && (Width == 1))
        {
            return (Register::read() & MASK) == 0;
        }
    };

    /**
     * @brief Convenient alias for a single-bit field.
     */
    template <typename Register, std::size_t Offset>
    using bit = field<Register, Offset, 1>;

} // namespace mmio

#endif // MMIO_HPP
