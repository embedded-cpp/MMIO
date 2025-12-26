#pragma once

/**
 * @brief Tag type for no access registers
 */
struct NoAccess
{
};

/**
 * @brief Tag type for read-only registers
 */
struct ReadOnly
{
};

/**
 * @brief Tag type for write-only registers
 */
struct WriteOnly
{
};

/**
 * @brief Tag type for read-write registers
 * Inherits from both read_only and write_only
 */
struct ReadWrite : ReadOnly, WriteOnly
{
};

// Convenient aliases
using ro = ReadOnly;
using wo = WriteOnly;
using rw = ReadWrite;
using na = NoAccess;
