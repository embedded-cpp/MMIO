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

namespace mmio {
    /**
     * @brief Tag type for no access registers
     */
    struct NoAccess {};

    /**
     * @brief Tag type for read-only registers
     */
    struct ReadOnly {};

    /**
     * @brief Tag type for write-only registers
     */
    struct WriteOnly {};

    /**
     * @brief Tag type for read-write registers
     * Inherits from both read_only and write_only
     */
    struct ReadWrite : ReadOnly, WriteOnly {};

    // Convenient aliases
    using ro = ReadOnly;
    using wo = WriteOnly;
    using rw = ReadWrite;
    using na = NoAccess;
} // namespace mmio

#endif // ACCESS_HPP
