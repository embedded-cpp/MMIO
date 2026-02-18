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

//<! Internal
#include "doctest/doctest.h"
//<! External
#include "mmio/mmio.hpp"
//<! System
#include <cstdint>
#include <sys/mman.h>

using namespace mmio;

static constexpr std::uintptr_t MOCK_ADDR = 0x10000U;

struct MmapFixture {
    void* mem;
    MmapFixture() {
        mem = mmap(reinterpret_cast<void*>(MOCK_ADDR), 4096, PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
    }
    ~MmapFixture() {
        if (mem != MAP_FAILED) {
            munmap(mem, 4096);
        }
    }
};

TEST_SUITE("mmio") {
    TEST_CASE_FIXTURE(MmapFixture, "read_write") {
        SUBCASE("reg") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile uint32_t* MOCK_REG = reinterpret_cast<volatile uint32_t*>(MOCK_ADDR);
            using TEST_REG              = reg<MOCK_ADDR, 32, rw>;
            using TEST_FIELD0           = field<TEST_REG, 0, 8>;
            using TEST_FIELD8           = field<TEST_REG, 8, 8>;

            // Check read
            *MOCK_REG = 0xFFFFFFFF;
            CHECK(TEST_REG::read() == 0xFFFFFFFF);

            // Check write
            TEST_REG::write(0xA5A5A5A5);
            CHECK(*MOCK_REG == 0xA5A5A5A5);

            // Check modify
            TEST_REG::modify([](uint32_t& val) { val ^= 0xFFFFFFFF; });
            CHECK(TEST_REG::read() == 0x5A5A5A5A);

            // Check write_set
            TEST_REG::write_set<TEST_FIELD0, TEST_FIELD8>();
            CHECK(*MOCK_REG == 0x0000FFFF);
        }

        SUBCASE("field") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile uint32_t* MOCK_REG = reinterpret_cast<volatile uint32_t*>(MOCK_ADDR);
            using TEST_REG              = reg<MOCK_ADDR, 32, rw>;
            using TEST_FIELD            = field<TEST_REG, 8, 8>;

            // Check read/write
            *MOCK_REG = 0x12345678;
            CHECK(TEST_FIELD::read() == 0x56);
            TEST_FIELD::write(0xAB);
            CHECK(*MOCK_REG == 0x1234AB78);

            // Check modify
            TEST_FIELD::modify([](uint32_t& val) { val ^= 0xFF; });
            CHECK(*MOCK_REG == 0x12345478);
        }

        SUBCASE("bit") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile uint32_t* MOCK_REG = reinterpret_cast<volatile uint32_t*>(MOCK_ADDR);
            using TEST_REG              = reg<MOCK_ADDR, 32, rw>;
            using TEST_BIT              = bit<TEST_REG, 4>;

            // Check set/clear/toggle
            *MOCK_REG = 0x0;
            TEST_BIT::set();
            CHECK(*MOCK_REG == 0x10);
            TEST_BIT::clear();
            CHECK(*MOCK_REG == 0x0);
            TEST_BIT::toggle();
            CHECK(*MOCK_REG == 0x10);
            TEST_BIT::toggle();
            CHECK(*MOCK_REG == 0x0);
        }
    }

    TEST_CASE_FIXTURE(MmapFixture, "read_only") {
        SUBCASE("reg") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile uint32_t* MOCK_REG = reinterpret_cast<volatile uint32_t*>(MOCK_ADDR);
            using TEST_REG              = reg<MOCK_ADDR, 32, ro>;

            // Check read
            *MOCK_REG = 0x5A5A5A5A;
            CHECK(TEST_REG::read() == 0x5A5A5A5A);

            // Check write (should not compile)
            // TEST_REG::write(0xFFFFFFFF); // Ignore - should not compile

            // Check write_set (should not compile)
            // TEST_REG::write_set<TEST_FIELD0, TEST_FIELD8>();
            // CHECK(*MOCK_REG == 0x0000FFFF); // Ignore - should not compile
        }

        SUBCASE("field") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile uint32_t* MOCK_REG = reinterpret_cast<volatile uint32_t*>(MOCK_ADDR);
            using TEST_REG              = reg<MOCK_ADDR, 32, ro>;
            using TEST_FIELD            = field<TEST_REG, 8, 8>;

            // Check read
            *MOCK_REG = 0x12345678;
            CHECK(TEST_FIELD::read() == 0x56);

            // Check write (should not compile)
            // TEST_FIELD::write(0xAB); // Ignore - should not compile
        }

        SUBCASE("bit") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile uint32_t* MOCK_REG = reinterpret_cast<volatile uint32_t*>(MOCK_ADDR);
            using TEST_REG              = reg<MOCK_ADDR, 32, ro>;
            using TEST_BIT              = bit<TEST_REG, 4>;

            // Check read
            *MOCK_REG = 0x10;
            CHECK(TEST_BIT::read() == true);
            *MOCK_REG = 0x0;
            CHECK(TEST_BIT::read() == false);

            // Check set/clear/toggle (should not compile)
            // TEST_BIT::set();    // Ignore - should not compile
            // TEST_BIT::clear();  // Ignore - should not compile
            // TEST_BIT::toggle(); // Ignore - should not compile
        }
    }

    TEST_CASE_FIXTURE(MmapFixture, "write_only") {
        SUBCASE("reg") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile uint32_t* MOCK_REG = reinterpret_cast<volatile uint32_t*>(MOCK_ADDR);
            using TEST_REG              = reg<MOCK_ADDR, 32, wo>;
            using TEST_FIELD0           = field<TEST_REG, 0, 8>;
            using TEST_FIELD8           = field<TEST_REG, 8, 8>;

            // Check write
            *MOCK_REG = 0x0;
            TEST_REG::write(0xDEADBEEF);
            CHECK(*MOCK_REG == 0xDEADBEEF);

            // Check read (should not compile)
            // uint32_t val = TEST_REG::read(); // Ignore - should not compile

            // Check modify (should not compile)
            // TEST_REG::modify([](uint32_t& val) { val ^= 0xFFFFFFFF; }); // Ignore - should not compile

            // Check write_set
            TEST_REG::write_set<TEST_FIELD0, TEST_FIELD8>();
            CHECK(*MOCK_REG == 0x0000FFFF);
        }

        SUBCASE("field") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile uint32_t* MOCK_REG = reinterpret_cast<volatile uint32_t*>(MOCK_ADDR);
            using TEST_REG              = reg<MOCK_ADDR, 32, wo>;
            using TEST_FIELD            = field<TEST_REG, 8, 8>;

            // Check write
            TEST_FIELD::write(0xAB);
            CHECK(*MOCK_REG == 0x0000AB00);

            // Check read (should not compile)
            // uint32_t val = TEST_FIELD::read(); // Ignore - should not compile

            // Check modify (should not compile)
            // TEST_FIELD::modify([](uint32_t& val) { val ^= 0xFF; }); // Ignore - should not compile
        }

        SUBCASE("bit") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile uint32_t* MOCK_REG = reinterpret_cast<volatile uint32_t*>(MOCK_ADDR);
            using TEST_REG              = reg<MOCK_ADDR, 32, wo>;
            using TEST_BIT              = bit<TEST_REG, 0>;

            // Check set
            *MOCK_REG = 0x0;
            TEST_BIT::set();
            CHECK(*MOCK_REG == 0x1);
            TEST_BIT::clear();
            CHECK(*MOCK_REG == 0x0);
            // TEST_BIT::toggle(); // Ignore - should not compile
        }
    }
}
