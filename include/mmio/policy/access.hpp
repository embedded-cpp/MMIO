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

#ifndef ACCESS_HPP
#define ACCESS_HPP

#include <concepts>

namespace mmio {
    /**
     * @brief Tag type for no access registers
     */
    struct no_access {};

    /**
     * @brief Tag type for read-only registers
     */
    struct read_only {};

    /**
     * @brief Tag type for write-only registers
     */
    struct write_only {};

    /**
     * @brief Tag type for read-write registers
     * Inherits from both read_only and write_only
     */
    struct read_write : read_only, write_only {};

    // Convenient aliases
    using ro = read_only;
    using wo = write_only;
    using rw = read_write;
    using na = no_access;

    /**
     * @brief Concept to check if a type is a valid read access policy
     * @tparam T Type to check
     */
    template <typename T>
    concept readable = std::derived_from<T, read_only>;

    /**
     * @brief Concept to check if a type is a valid write access policy
     * @tparam T Type to check
     */
    template <typename T>
    concept writable = std::derived_from<T, write_only>;

    /**
     * @brief Concept to check if a type is a valid access policy (no_access, readable, or writable)
     * @tparam T Type to check
     */
    template <typename T>
    concept access_policy = std::same_as<T, no_access> || readable<T> || writable<T>;
} // namespace mmio

#endif // ACCESS_HPP
