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
#include "mmio/policy/access.hpp"
//<! System
#include <cstdint>
#include <sys/mman.h>

using namespace mmio;

static constexpr std::uintptr_t mock_addr = 0x10000U;

struct mmap_fixture {
    void* mem;
    mmap_fixture()
        : mem(mmap(reinterpret_cast<void*>(mock_addr), 4096, PROT_READ | PROT_WRITE,
              MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0)) {}
    ~mmap_fixture() {
        if (mem != MAP_FAILED) {
            munmap(mem, 4096);
        }
    }
};

TEST_SUITE("mmio") {
    TEST_CASE_FIXTURE(mmap_fixture, "read_write") {
        SUBCASE("reg") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile auto* mock_reg = reinterpret_cast<volatile uint32_t*>(mock_addr);
            using TEST_REG          = reg<mock_addr, 32, rw>;
            using TEST_FIELD0       = field<TEST_REG, 0, 8>;
            using TEST_FIELD8       = field<TEST_REG, 8, 8>;

            // Check read
            *mock_reg = 0xFFFFFFFF;
            CHECK(TEST_REG::read() == 0xFFFFFFFF);

            // Check write
            TEST_REG::write(0xA5A5A5A5);
            CHECK(*mock_reg == 0xA5A5A5A5);

            // Check modify
            TEST_REG::modify([](uint32_t& val) { val ^= 0xFFFFFFFF; });
            CHECK(TEST_REG::read() == 0x5A5A5A5A);

            // Check write_set
            TEST_REG::write_set<TEST_FIELD0, TEST_FIELD8>();
            CHECK(*mock_reg == 0x0000FFFF);
        }

        SUBCASE("field") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile auto* mock_reg = reinterpret_cast<volatile uint32_t*>(mock_addr);
            using TEST_REG          = reg<mock_addr, 32, rw>;
            using TEST_FIELD        = field<TEST_REG, 8, 8>;

            // Check read/write
            *mock_reg = 0x12345678;
            CHECK(TEST_FIELD::read() == 0x56);
            TEST_FIELD::write(0xAB);
            CHECK(*mock_reg == 0x1234AB78);

            // Check modify
            TEST_FIELD::modify([](uint32_t& val) { val ^= 0xFF; });
            CHECK(*mock_reg == 0x12345478);
        }

        SUBCASE("bit") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile auto* mock_reg = reinterpret_cast<volatile uint32_t*>(mock_addr);
            using TEST_REG          = reg<mock_addr, 32, rw>;
            using TEST_BIT          = bit<TEST_REG, 4>;

            // Check set/clear/toggle
            *mock_reg = 0x0;
            TEST_BIT::set();
            CHECK(*mock_reg == 0x10);
            CHECK(TEST_BIT::is_set());
            TEST_BIT::clear();
            CHECK(*mock_reg == 0x0);
            CHECK(TEST_BIT::is_clear());
            TEST_BIT::toggle();
            CHECK(*mock_reg == 0x10);
            CHECK(TEST_BIT::is_set());
            TEST_BIT::toggle();
            CHECK(*mock_reg == 0x0);
            CHECK(TEST_BIT::is_clear());
        }
    }

    TEST_CASE_FIXTURE(mmap_fixture, "read_only") {
        SUBCASE("reg") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile auto* mock_reg = reinterpret_cast<volatile uint32_t*>(mock_addr);
            using TEST_REG          = reg<mock_addr, 32, ro>;

            // Check read
            *mock_reg = 0x5A5A5A5A;
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
            volatile auto* mock_reg = reinterpret_cast<volatile uint32_t*>(mock_addr);
            using TEST_REG          = reg<mock_addr, 32, ro>;
            using TEST_FIELD        = field<TEST_REG, 8, 8>;

            // Check read
            *mock_reg = 0x12345678;
            CHECK(TEST_FIELD::read() == 0x56);

            // Check write (should not compile)
            // TEST_FIELD::write(0xAB); // Ignore - should not compile
        }

        SUBCASE("bit") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile auto* mock_reg = reinterpret_cast<volatile uint32_t*>(mock_addr);
            using TEST_REG          = reg<mock_addr, 32, ro>;
            using TEST_BIT          = bit<TEST_REG, 4>;

            // Check read
            *mock_reg = 0x10;
            CHECK(TEST_BIT::read() == true);
            CHECK(TEST_BIT::is_set());
            *mock_reg = 0x0;
            CHECK(TEST_BIT::read() == false);
            CHECK(TEST_BIT::is_clear());

            // Check set/clear/toggle (should not compile)
            // TEST_BIT::set();    // Ignore - should not compile
            // TEST_BIT::clear();  // Ignore - should not compile
            // TEST_BIT::toggle(); // Ignore - should not compile
        }
    }

    TEST_CASE_FIXTURE(mmap_fixture, "write_only") {
        SUBCASE("reg") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile auto* mock_reg = reinterpret_cast<volatile uint32_t*>(mock_addr);
            using TEST_REG          = reg<mock_addr, 32, wo>;
            using TEST_FIELD0       = field<TEST_REG, 0, 8>;
            using TEST_FIELD8       = field<TEST_REG, 8, 8>;

            // Check write
            *mock_reg = 0x0;
            TEST_REG::write(0xDEADBEEF);
            CHECK(*mock_reg == 0xDEADBEEF);

            // Check read (should not compile)
            // uint32_t val = TEST_REG::read(); // Ignore - should not compile

            // Check modify (should not compile)
            // TEST_REG::modify([](uint32_t& val) { val ^= 0xFFFFFFFF; }); // Ignore - should not compile

            // Check write_set
            TEST_REG::write_set<TEST_FIELD0, TEST_FIELD8>();
            CHECK(*mock_reg == 0x0000FFFF);
        }

        SUBCASE("field") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile auto* mock_reg = reinterpret_cast<volatile uint32_t*>(mock_addr);
            using TEST_REG          = reg<mock_addr, 32, wo>;
            using TEST_FIELD        = field<TEST_REG, 8, 8>;

            // Check write
            TEST_FIELD::write(0xAB);
            CHECK(*mock_reg == 0x0000AB00);

            // Check read (should not compile)
            // uint32_t val = TEST_FIELD::read(); // Ignore - should not compile

            // Check modify (should not compile)
            // TEST_FIELD::modify([](uint32_t& val) { val ^= 0xFF; }); // Ignore - should not compile
        }

        SUBCASE("bit") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile auto* mock_reg = reinterpret_cast<volatile uint32_t*>(mock_addr);
            using TEST_REG          = reg<mock_addr, 32, wo>;
            using TEST_BIT          = bit<TEST_REG, 0>;

            // Check set
            *mock_reg = 0x0;
            TEST_BIT::set();
            CHECK(*mock_reg == 0x1);
            TEST_BIT::clear();
            CHECK(*mock_reg == 0x0);
            // TEST_BIT::is_set(); // Ignore - should not compile
            // TEST_BIT::is_clear(); // Ignore - should not compile
            // TEST_BIT::toggle(); // Ignore - should not compile
        }
    }

    TEST_CASE_FIXTURE(mmap_fixture, "write_1_to_clear") {
        SUBCASE("bit") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile auto* mock_reg = reinterpret_cast<volatile uint32_t*>(mock_addr);
            using TEST_REG          = reg<mock_addr, 32, w1c>;
            using TEST_BIT          = bit<TEST_REG, 0>;

            // Check read
            *mock_reg = 0x1;
            CHECK(TEST_BIT::read() == 1);
            CHECK(TEST_BIT::is_set());
            *mock_reg = 0x0;
            CHECK(TEST_BIT::is_clear());

            // Check clear
            *mock_reg = 0x1;
            TEST_BIT::clear();
            CHECK(*mock_reg == 0x1); // Cannot works on host because it does not have real W1C behavior, but should
                                     // compile and call the correct method
            // TEST_BIT::set(); // Ignore - should not compile
        }
    }

    TEST_CASE_FIXTURE(mmap_fixture, "Field corner cases") {
        SUBCASE("field at MSB") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile auto* mock_reg = reinterpret_cast<volatile uint32_t*>(mock_addr);
            using TEST_REG          = reg<mock_addr, 32, rw>;
            using TEST_FIELD        = field<TEST_REG, 31, 1>; // Test MSB field

            // Check read/write
            *mock_reg = 0xFFFFFFFF;
            CHECK(TEST_FIELD::is_set());
            TEST_FIELD::clear();
            CHECK(TEST_FIELD::is_clear());
            CHECK(*mock_reg == 0x7FFFFFFF);
            TEST_FIELD::set();
            CHECK(*mock_reg == 0xFFFFFFFF);
        }

        SUBCASE("full-width field") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile auto* mock_reg = reinterpret_cast<volatile uint32_t*>(mock_addr);
            using TEST_REG          = reg<mock_addr, 32, rw>;
            using TEST_FIELD        = field<TEST_REG, 0, 32>; // Test full-width field

            // Check read/write
            *mock_reg = 0x12345678;
            CHECK(TEST_FIELD::read() == 0x12345678);
            TEST_FIELD::write(0xFFFFFFFF);
            CHECK(*mock_reg == 0xFFFFFFFF);

            // Check modify
            TEST_FIELD::modify([](uint32_t& val) { val ^= 0xFFFFFFFF; });
            CHECK(*mock_reg == 0x00000000);
        }

        SUBCASE("Too large value write") {
            REQUIRE(mem != MAP_FAILED);
            // Init
            volatile auto* mock_reg = reinterpret_cast<volatile uint32_t*>(mock_addr);
            using TEST_REG          = reg<mock_addr, 32, rw>;
            using TEST_FIELD        = field<TEST_REG, 8, 8>;

            // Check read/write with value larger than field width (should be masked)
            TEST_FIELD::write(0xFFF);       // Value larger than 8 bits
            CHECK(*mock_reg == 0x0000FF00); // Should be masked to 8 bits
        }
    }
}
