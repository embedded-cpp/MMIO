/**
 * @file sonarqube_excluder.cpp
 * @brief This file serves as an anchor for SonarQube to exclude the test_*.cpp files from analysis.
 */
#include <sys/mman.h>

#include "mmio/mmio.hpp"
#include "mmio/policy/access.hpp"
#include "mmio/traits/size.hpp"

static constexpr std::uintptr_t MOCK_ADDR = 0x10000U;

/**
 * @brief dummy function to anchor SonarQube exclusion of test_*.cpp files
 */
void dummy() {
    void* mem;
    mem = mmap(reinterpret_cast<void*>(MOCK_ADDR), 4096, PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);

    using TEST_REG   = mmio::reg<MOCK_ADDR, 32, mmio::rw>;
    using TEST_FIELD = mmio::field<TEST_REG, 8, 8>;

    TEST_REG::write(0xDEADBEEF);
    uint32_t val = TEST_REG::read();
    (void) val; // Suppress unused variable warning
    TEST_REG::modify([](auto& v) { v ^= 0xFFFFFFFF; });

    TEST_FIELD::write(0xAB);
    uint32_t field_val = TEST_FIELD::read();
    (void) field_val; // Suppress unused variable warning
    TEST_FIELD::modify([](auto& v) { v ^= 0xFF; });

    if (mem != MAP_FAILED) {
        munmap(mem, 4096);
    }
}
