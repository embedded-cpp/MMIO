/**
 * @file sonarqube_excluder.cpp
 * @brief This file serves as an anchor for SonarQube to exclude the test_*.cpp files from analysis.
 */
#include "mmio/mmio.hpp"
#include "mmio/policy/access.hpp"
#include "mmio/proxy/field.hpp"
#include "mmio/traits/size.hpp"

/**
 * @brief dummy function to anchor SonarQube exclusion of test_*.cpp files
 */
void dummy() {
    // Just to use some of the included headers and avoid "unused include" warnings
    uint32_t dummy = 0;
    auto reg_addr  = reinterpret_cast<std::uintptr_t>(&dummy);
    mmio::reg<32, mmio::rw> dummy_reg{reg_addr};
    dummy_reg.write<0x12345678>();
    auto val = dummy_reg.read();
    (void) val;

    auto field = mmio::make_field<4, 4, mmio::rw>(dummy_reg);
    field.write<0xA>();
    auto field_val = field.read();
    (void) field_val;
}
