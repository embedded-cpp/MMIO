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

#ifndef FIELD_HPP
#define FIELD_HPP

#include <cassert>
#include <cstddef>
#include <type_traits>

#include "mmio/policy/access.hpp"

namespace mmio {
    template <std::size_t Offset, std::size_t Width, typename AccessPolicy, typename Register>
    class Field {
        using value_type                 = typename Register::value_type;
        static constexpr value_type mask = ((value_type(1) << Width) - 1) << Offset;

        template <typename T>
        static constexpr bool dependent_false_v = false;

    public:
        explicit constexpr Field(Register& reg) noexcept : m_reg{reg} {}

        [[nodiscard]] constexpr value_type read() const noexcept {
            if constexpr (std::is_base_of_v<ro, AccessPolicy>) {
                return (*(m_reg.m_raw_ptr) & mask) >> Offset;
            } else {
                static_assert(dependent_false_v<Field>, "Field is not readable.");
            }
        }

        template <value_type val>
        constexpr Register& write(void) noexcept {
            if constexpr (std::is_base_of_v<wo, AccessPolicy>) {
                static_assert(val < (value_type(1) << Width), "Value too large");

                auto tmp = *(m_reg.m_raw_ptr);
                tmp &= ~mask; // Clear field
                tmp |= (val << Offset) & mask; // Set field
                *(m_reg.m_raw_ptr) = tmp;

                return m_reg;
            } else {
                static_assert(dependent_false_v<Field>, "Field is not writable.");
            }
        }

        constexpr Register& set_bit() noexcept {
            static_assert(Width == 1, "set_bit() is only valid for fields of width 1");

            if constexpr (std::is_base_of_v<wo, AccessPolicy>) {
                auto tmp = *(m_reg.m_raw_ptr);
                tmp |= mask;
                *(m_reg.m_raw_ptr) = tmp;

                return m_reg;
            } else {
                static_assert(dependent_false_v<Field>, "Field is not writable.");
            }
        }

        constexpr Register& clear_bit() noexcept {
            static_assert(Width == 1, "clear_bit() is only valid for fields of width 1");

            if constexpr (std::is_base_of_v<wo, AccessPolicy>) {
                auto tmp = *(m_reg.m_raw_ptr);
                tmp &= ~mask;
                *(m_reg.m_raw_ptr) = tmp;

                return m_reg;
            } else {
                static_assert(dependent_false_v<Field>, "Field is not writable.");
            }
        }

    private:
        Register& m_reg;
    };

    template <std::size_t Pos, std::size_t Width, typename AccessPolicy, typename Register>
    constexpr auto make_field(Register& reg) {
        return Field<Pos, Width, AccessPolicy, Register>{reg};
    }
} // namespace mmio
#endif // FIELD_HPP
