[![Develop](https://github.com/embedded-cpp/mmio/actions/workflows/develop.yml/badge.svg)](https://github.com/embedded-cpp/mmio/actions/workflows/develop.yml)
[![Release](https://github.com/embedded-cpp/mmio/actions/workflows/release.yml/badge.svg)](https://github.com/embedded-cpp/mmio/actions/workflows/release.yml)
[![Documentation](https://img.shields.io/badge/docs-online-brightgreen)](https://embedded-cpp.github.io/mmio/)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=embedded-cpp_mmio&metric=alert_status&token=0414d3703cd49f8a7de6c25ba8d49b4826a9bcb9)](https://sonarcloud.io/summary/new_code?id=embedded-cpp_mmio)
[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

<p align="center">
  <img src="https://repository-images.githubusercontent.com/254842585/4dfa7580-7ffb-11ea-99d0-46b8fe2f4170" height="175" width="auto" />
</p>


# mmio

mmio is a lightweight C++20 library for expressing memory-mapped I/O access in a clear, type-safe way. It is designed for embedded and low-level software where register-level code must stay readable, maintainable, and close to the hardware.

## Why use mmio?

- Write register access with expressive types instead of scattered bit masks.
- Keep driver code readable while preserving low-level control.
- Use strongly-typed register and field abstractions for safer embedded development.
- Build against a header-only API that fits naturally into existing firmware projects.

## What you get

- `mmio::reg` for typed access to a hardware register address
- `mmio::field` for bit-field access with masking and shifting
- access policies such as `ro`, `wo`, `rw`, and `w1c`
- compile-time support for common register sizes and alignment checks

## A simple example

```cpp
#include "mmio/mmio.hpp"

using CTRL = mmio::reg<0x40000000, 32, mmio::rw>;
using ENABLE = mmio::field<CTRL, 0, 1>;

ENABLE::write(1);
auto value = ENABLE::read();
```

## Getting started

The documentation includes a dedicated guide for integration and usage:

- [Getting started](doc/tabs/getting_started.md)
- [Examples](doc/tabs/examples.md)
- [Contributing](doc/tabs/contributing.md)

## Build locally

If you want to build the project, run the tests, or generate the documentation:

```bash
cmake -S all -B build
cmake --build build
ctest --test-dir build --output-on-failure
cmake -S doc -B build/doc
cmake --build build/doc --target generate_docs
```

## License

This project is licensed under the [LICENSE](LICENSE).
