#include "mmio.h"

#include <cxxopts.hpp>

auto main(int argc, char** argv) -> int {
  cxxopts::Options options(*argv, "A program to welcome the world!");

  Register<32, rw> reg{0x40021000};
  reg.write(0x123456789); // Should trigger static assert

  return 0;
}
