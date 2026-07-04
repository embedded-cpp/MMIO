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

/**
 * @file sonarqube_excluder.cpp
 * @brief This file serves as an anchor for SonarQube to exclude the test_*.cpp files from analysis.
 */
//<! Internal
//<! External
#include "mmio/mmio.hpp" // for field, reg, rw
//<! System
#include <cstdint>    // for uint32_t, uintptr_t
#include <sys/mman.h> // for mmap, munmap, MAP_ANONYMOUS, MAP_FAILED
static constexpr std::uintptr_t mock_addr = 0x10000U;

/**
 * @brief dummy function to anchor SonarQube exclusion of test_*.cpp files
 */
// GCOVR_EXCL_START
void dummy() {
    void* mem = nullptr;
    mem       = mmap(reinterpret_cast<void*>(mock_addr), 4096, PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);

    using TEST_REG   = mmio::reg<mock_addr, 32, mmio::rw>;
    using TEST_FIELD = mmio::field<TEST_REG, 8, 8>;

    TEST_REG::write(0xDEADBEEF);
    uint32_t const val = TEST_REG::read();
    (void) val; // Suppress unused variable warning
    TEST_REG::write(0xA5A5A5A5);

    TEST_FIELD::write(0xAB);
    uint32_t const field_val = TEST_FIELD::read();
    (void) field_val; // Suppress unused variable warning
    TEST_FIELD::write(0xCD);
    if (mem != MAP_FAILED) {
        munmap(mem, 4096);
    }
}
// GCOVR_EXCL_STOP
