#include <doctest/doctest.h>
#include "mmio.h"

#include <string>

TEST_CASE("Dummy") {
  std::uint32_t dummy_reg = 0;
  std::uint32_t* reg_ptr = &dummy_reg;
  std::uint32_t reg_addr = reinterpret_cast<std::uint32_t>(reg_ptr);

  Register<32, rw> reg{reg_addr};
  // reg.write(0x12345678);
  // CHECK(reg.read() == 0x12345678);
}
