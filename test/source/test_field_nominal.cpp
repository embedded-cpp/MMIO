#include <doctest/doctest.h>

#include "mmio.h"

TEST_SUITE("Field Tests - Nominal Cases")
{

  
  static std::uint64_t dummy_reg = 0;
  static std::uint64_t* reg_ptr = &dummy_reg;
  static std::uint64_t reg_addr = reinterpret_cast<std::uintptr_t>(reg_ptr);
  
  TEST_CASE("ReadWrite Register") {
    // Init
    Register<64, rw> reg{reg_addr};
    
    // Check write
    reg.field<0, 8>().write(0XFF);
    CHECK(reg.read() == 0x00000000000000FF);
    CHECK(reg.field<0, 8>().read() == 0xFF);
    
    // Check clear/set bit
    reg.field<1,1>().clear_bit();
    CHECK(reg.read() == 0x00000000000000FD);
    reg.field<1,1>().set_bit();
    CHECK(reg.read() == 0x00000000000000FF);
  }

  TEST_CASE("ReadOnly Register") {
    // Init
    Register<64, ro> reg{reg_addr};
    *reg_ptr = 0x00000000000000AA;
    // Check read
    CHECK(reg.field<0, 8>().read() == 0xAA);
  }
  
  TEST_CASE("WriteOnly Register") {
    // Init
    Register<64, wo> reg{reg_addr};
    
    // Check write
    reg.field<0, 8>().write(0X55);
    CHECK(*reg_ptr == 0x0000000000000055);
    // Check set/clear bit
    reg.field<7,1>().set_bit();
    CHECK(*reg_ptr == 0x00000000000000D5);
    reg.field<7,1>().clear_bit();
    CHECK(*reg_ptr == 0x0000000000000055);
  }
}

