#pragma once

#include <cstddef>

#include "policy/access.hpp"
#include "proxy/field.hpp"
#include "traits/size.hpp"

/**
 * @brief Register class which serves to represent MCU HW register
 *
 * @tparam BitSize: size in bits of a register
 * @tparam read/write policy
 */
template <std::size_t BitSize, typename AccessPolicy>
class Register {
  static_assert(BitSize == 8 || BitSize == 16 || BitSize == 32 || BitSize == 64, "Unsupported register size");

  using value_type = typename SizeTrait<BitSize>::type; //<! Alias of internal_tyoe representing register

  static_assert(std::is_same_v<AccessPolicy, rw> || std::is_same_v<AccessPolicy, ro> || std::is_same_v<AccessPolicy, wo> ||
                    std::is_same_v<AccessPolicy, na>,
                "AccessPolicy must be read-write, read-only, write-only or no-access");

  template <typename T>
  static constexpr bool dependent_false_v = false;

public:
  /**
   * @brief Construct a new Register object: this allow manipulating HW register at given address
   * @param[in] address: address of the HW register to handle
   */
  explicit constexpr Register(std::uintptr_t address) noexcept : m_raw_ptr(reinterpret_cast<volatile value_type*>(address)) { }

  /**
   * @brief Operator to read from the register
   * @details Example: uint32_t reader = reg;
   * @note Available for RW & R registers
   * @return value_type: value read of the register
   */
  [[nodiscard]] constexpr operator value_type() const noexcept {
    if constexpr (std::is_base_of_v<ro, AccessPolicy>) {
      return *m_raw_ptr;
    } else {
      static_assert(dependent_false_v<AccessPolicy>, "Cannot read from write-only register.");
    }
  }

  /**
   * @brief Assignment operator: allow to write the register
   * @param[in] value: value to write to the register
   */
  constexpr Register& operator=(value_type value) noexcept {
    if constexpr (std::is_base_of_v<wo, AccessPolicy>) {
      *m_raw_ptr = value;
      return *this;
    } else {
      static_assert(dependent_false_v<AccessPolicy>, "Cannot modify read-only register.");
    }
  }

  /**
   * @brief Access field proxy by offset and width
   * @param index Bit index [0; BitSize[
   * @return BitProxy proxy object for bit manipulation
   */
  template <std::size_t Pos, std::size_t Width>
  constexpr auto field() {
    return Field<Pos, Width, AccessPolicy, Register>{*this};
  }

  /**
   * @brief Read a register
   * @return The register value
   */
  [[nodiscard]] constexpr value_type read() const noexcept {
    if constexpr (std::is_base_of_v<ro, AccessPolicy>) {
      return *m_raw_ptr;
    } else {
      static_assert(dependent_false_v<AccessPolicy>, "Cannot read from write-only register.");
    }
  }

  /**
   * @brief Write a register
   * @param[in] value: The value to write
   */
  template <value_type value>
  constexpr void write() noexcept {
    if constexpr (std::is_base_of_v<wo, AccessPolicy> && std::is_unsigned_v<value_type>) {
      *m_raw_ptr = value;
    } else {
      static_assert(dependent_false_v<AccessPolicy>, "Cannot write to read-only register.");
    }
  }

  /**
   * @brief Modify the register with a callable (only if read-write)
   * @tparam Func Callable type, callable with signature void(value_type&)
   * @param func Callable to modify the register contents
   */
  template <typename Func>
  void modify(Func&& func) {
    if constexpr (std::is_base_of_v<rw, AccessPolicy>) {
      value_type val = *m_raw_ptr;
      func(val); // The user modifies a copy
      *m_raw_ptr = val;
    } else {
      static_assert(dependent_false_v<AccessPolicy>, "Can only modify read-write registers.");
    }
  }

private:
  volatile value_type* m_raw_ptr; //<! Address of the HW register

  template <std::size_t, std::size_t, typename, typename>
  friend class Field;
};
