#include "doctest/doctest.h"
#include <cstdint>

#include "mmio/mmio.hpp"

using namespace mmio;

TEST_SUITE("Field Tests - Nominal Cases") {
    static std::uint32_t dummy_reg       = 0;
    static const std::uintptr_t reg_addr = reinterpret_cast<std::uintptr_t>(&dummy_reg);

    TEST_CASE("ReadWrite reg") {
        // Init
        reg<32, rw> reg{reg_addr};

        // Check write
        reg.field<0, 8>().write<0xFF>();
        CHECK(reg.read() == 0xFF);
        CHECK(reg.field<0, 8>().read() == 0xFF);

        // Check clear/set bit
        reg.field<1, 1>().clear_bit();
        CHECK(reg.read() == 0xFD);
        reg.field<1, 1>().set_bit();
        CHECK(reg.read() == 0xFF);
    }

    TEST_CASE("ReadOnly reg") {
        // Init
        reg<32, ro> reg{reg_addr};
        dummy_reg = 0xAA;
        // Check read
        CHECK(reg.field<0, 8>().read() == 0xAA);
    }

    TEST_CASE("WriteOnly reg") {
        // Init
        reg<32, wo> reg{reg_addr};

        // Check write
        reg.field<0, 8>().write<0x55>();
        CHECK(dummy_reg == 0x55);
        // Check set/clear bit
        reg.field<7, 1>().set_bit();
        CHECK(dummy_reg == 0xD5);
        reg.field<7, 1>().clear_bit();
        CHECK(dummy_reg == 0x55);
    }

    TEST_CASE("make_field function") {
        // Init
        reg<32, rw> reg{reg_addr};

        auto field = make_field<4, 4, rw>(reg);

        // Check write
        field.write<0xA>();
        CHECK(reg.read() == 0xA0);
        CHECK(field.read() == 0xA);
    }
}
