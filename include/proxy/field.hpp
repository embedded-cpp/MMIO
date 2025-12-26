#pragma once

#include <cassert>
#include <cstddef>
#include <type_traits>

#include "policy/access.hpp"

template <std::size_t Offset, std::size_t Width, typename AccessPolicy, typename Register>
class Field
{
    using value_type                 = typename Register::value_type;
    static constexpr value_type mask = ((value_type(1) << Width) - 1) << Offset;

    template <typename T>
    static constexpr bool dependent_false_v = false;

  public:
    explicit constexpr Field(Register& reg) : m_reg{reg} { }

    [[nodiscard]] constexpr value_type read() const
    {
        if constexpr (std::is_base_of_v<ro, AccessPolicy>)
        {
            return (*(m_reg.m_raw_ptr) & mask) >> Offset;
        }
        else
        {
            static_assert(dependent_false_v<Field>, "Field is not readable.");
        }
    }

    constexpr Register& write(value_type val)
    {
        if constexpr (std::is_base_of_v<wo, AccessPolicy>)
        {
            value_type max_val = (value_type(1) << Width) - 1;
            assert((val & ~max_val) == 0 && "Value too large for the field width");

            auto tmp = *(m_reg.m_raw_ptr);
            tmp &= ~mask;                  // Clear field
            tmp |= (val << Offset) & mask; // Set field
            *(m_reg.m_raw_ptr) = tmp;

            return m_reg;
        }
        else
        {
            static_assert(dependent_false_v<Field>, "Field is not writable.");
        }
    }

    constexpr Register& set_bit()
    {
        static_assert(Width == 1, "set_bit() is only valid for fields of width 1");

        if constexpr (std::is_base_of_v<wo, AccessPolicy>)
        {
            auto tmp = *(m_reg.m_raw_ptr);
            tmp |= mask;
            *(m_reg.m_raw_ptr) = tmp;

            return m_reg;
        }
        else
        {
            static_assert(dependent_false_v<Field>, "Field is not writable.");
        }
    }

    constexpr Register& clear_bit()
    {
        static_assert(Width == 1, "clear_bit() is only valid for fields of width 1");

        if constexpr (std::is_base_of_v<wo, AccessPolicy>)
        {
            auto tmp = *(m_reg.m_raw_ptr);
            tmp &= ~mask;
            *(m_reg.m_raw_ptr) = tmp;

            return m_reg;
        }
        else
        {
            static_assert(dependent_false_v<Field>, "Field is not writable.");
        }
    }

  private:
    Register& m_reg;
};

template <std::size_t Pos, std::size_t Width, typename AccessPolicy, typename Register>
constexpr auto make_field(Register& reg)
{
    return Field<Pos, Width, AccessPolicy, Register>{reg};
}
