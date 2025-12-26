#pragma once

#include <cstdint>

/**
 * @brief Base trait for the size of the register
 * @tparam BitSize: size in bits of a register 
 */
template <std::size_t BitSize>
struct SizeTrait
{
    static_assert(BitSize == 8 || BitSize == 16 || BitSize == 32 || BitSize == 64, "Unsupported register size");
};

/**
 * @brief Specialization of the base trait for 8-bit register
 */
template <>
struct SizeTrait<8>
{
    using type = std::uint8_t;
};

/**
 * @brief Specialization of the base trait for 16-bit register
 */
template <>
struct SizeTrait<16>
{
    using type = std::uint16_t;
};

/**
 * @brief Specialization of the base trait for 32-bit register
 */
template <>
struct SizeTrait<32>
{
    using type = std::uint32_t;
};

/**
 * @brief Specialization of the base trait for 64-bit register
 */
template <>
struct SizeTrait<64>
{
    using type = std::uint64_t;
};