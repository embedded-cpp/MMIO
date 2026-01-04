#include <cstdint>
#include <doctest/doctest.h>

#include "mmio.h"

TEST_SUITE("Register Tests - Nominal Cases") {
  static std::uint32_t        dummy_reg = 0;
  static const std::uintptr_t reg_addr  = reinterpret_cast<std::uintptr_t>(&dummy_reg);

  TEST_CASE("ReadWrite Register") {
    // Init
    Register<32, rw> reg{reg_addr};

    // Check read
    dummy_reg = 0xFFFFFFFF;
    CHECK(reg.read() == 0xFFFFFFFF);

    // Check write
    reg.write<0xA5A5A5A5>();
    CHECK(dummy_reg == 0xA5A5A5A5);

    // Check modify
    reg.modify([](auto& val) { val ^= 0xFFFFFFFF; });
    CHECK(reg.read() == 0x5A5A5A5A);

    // Check operators
    reg = 0x12345678;
    CHECK(dummy_reg == 0x12345678);
    std::uint32_t val{reg};
    CHECK(val == 0x12345678);
  }

  TEST_CASE("ReadOnly Register") {
    // Init
    Register<32, ro> reg{reg_addr};

    // Check read
    dummy_reg = 0x5A5A5A5A;
    CHECK(reg.read() == 0x5A5A5A5A);
  }

  TEST_CASE("WriteOnly Register") {
    // Init
    Register<32, wo> reg{reg_addr};

    // Check write
    reg.write<0xFFFFFFFF>();
    CHECK(dummy_reg == 0xFFFFFFFF);

    // Check operator=
    reg = 0x12345678;
    CHECK(dummy_reg == 0x12345678);
  }
}
