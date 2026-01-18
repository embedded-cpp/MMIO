[![MacOS](https://github.com/embedded-cpp/MMIO/actions/workflows/macos.yml/badge.svg)](https://github.com/embedded-cpp/MMIO/actions/workflows/macos.yml)
[![Ubuntu](https://github.com/embedded-cpp/MMIO/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/embedded-cpp/MMIO/actions/workflows/ubuntu.yml)
[![Windows](https://github.com/embedded-cpp/MMIO/actions/workflows/windows.yml/badge.svg)](https://github.com/embedded-cpp/MMIO/actions/workflows/windows.yml)
[![Style](https://github.com/embedded-cpp/MMIO/actions/workflows/style.yml/badge.svg)](https://github.com/embedded-cpp/MMIO/actions/workflows/style.yml)
[![Documentation](https://github.com/embedded-cpp/MMIO/actions/workflows/documentation.yaml/badge.svg)](https://github.com/embedded-cpp/MMIO/actions/workflows/documentation.yaml)
[![Install](https://github.com/embedded-cpp/MMIO/actions/workflows/install.yml/badge.svg)](https://github.com/embedded-cpp/MMIO/actions/workflows/install.yml)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=embedded-cpp_MMIO&metric=alert_status&token=0414d3703cd49f8a7de6c25ba8d49b4826a9bcb9)](https://sonarcloud.io/summary/new_code?id=embedded-cpp_MMIO)

<p align="center">
  <img src="https://repository-images.githubusercontent.com/254842585/4dfa7580-7ffb-11ea-99d0-46b8fe2f4170" height="175" width="auto" />
</p>


# MMIO

**MMIO** is a modern C++ library for safe, type-driven access to memory‑mapped I/O registers.  
It provides clean abstractions for fields, access policies, and size traits while preserving the performance of low‑level register operations.

## Features

- **Type‑safe register access** via policies and field proxies
- **Header‑only design** for easy integration
- **Zero‑cost abstractions** using templates and traits
- **Built‑in tests** for core behavior
- **Doxygen-ready documentation** pipeline

## Project Layout

- `include/`
  - `policy/` – access policy definitions
  - `proxy/` – field / register access wrappers
  - `traits/` – utilities like size traits
  - `mmio.h` – main public header
- `test/` – tests
- `documentation/` – Doxygen configuration and pages
- `all/` – meta build for library + tests + docs

## Requirements

- A C++ compiler with modern C++ support (C++17 or newer recommended)
- CMake (for building tests, docs, and integration)
- Doxygen (optional, for docs generation)

## Integration

### Use as a subproject (recommended)

Add the repository as a submodule or fetch it in your build, then:
```cmake 
add_subdirectory(path/to/MMIO)
target_link_libraries(your_target PRIVATE MMIO)
```

### Header-only usage

You can also include the main header directly:
```cpp 
#include "mmio/mmio.h"
```

## Quick Start
Include the library and start defining registers and fields in a header shared by your drivers or HAL code.

## Register / Field Example
Below is a generic example illustrating the common structure used with MMIO-style libraries.
Adapt the names and parameters to your own register layout and policies.

```cpp
#include "mmio/mmio.h"

Example structure (pseudocode-style):
using CTRL = mmio::reg<0x40000000, mmio::rw, std::uint32_t>;
using ENABLE = mmio::field<CTRL, 0, 1>;
using MODE = mmio::field<CTRL, 1, 2>;
ENABLE::mmio::set_bit();
MODE::mmio::write(0b10);
auto current = mmio::MODE::read();
```

## Design Goals
- **Safety first**: prevent invalid accesses at compile time whenever possible.
- **Zero overhead**: abstractions compile down to the same instructions as raw register access.
- **Clarity**: expressive field definitions that are easy to read and audit.
- **Portability**: usable across embedded toolchains with minimal dependencies.
- **Scalability**: reusable building blocks for large register maps.


## Build Everything (recommended)
```bash
cmake -S all -B build
cmake --build build
```

## Run Tests
```bash
 cmake -S all -B build/test
 cmake --build build/test
 ctest --test-dir build/test --output-on-failure
```

## Build Documentation
```bash
cmake -S documentation -B build/doc
cmake --build build/doc --target GenerateDocs
```

## Code Formatting
```bash
cmake --build build --target fix-format
```

## Continuous Integration
The project includes CI workflows for:

- **Linux / Windows / macOS** builds
- **Formatting checks**
- **Documentation generation**
- **Installation verification**

## FAQ
**Q: Is MMIO header-only?**  
A: Yes. The core library is intended to be used as headers only.

**Q: Does this add runtime overhead?**  
A: No. The abstractions are designed to optimize away to direct register access.

**Q: Can I use this without CMake?**  
A: Yes. Since it’s header-only, you can just include the headers directly.

**Q: Is this suitable for bare-metal targets?**  
A: Yes. The library is designed with embedded systems and low-level targets in mind.

## Contributing
Contributions are welcome!  
Please open an issue first for major changes and keep the code style consistent by running the formatter.

## License
This project is licensed under the [LICENSE](LICENSE).
