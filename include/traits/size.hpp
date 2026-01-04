#pragma once

#include <cstddef>
#include <cstdint>

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