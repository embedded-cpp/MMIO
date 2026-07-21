# mmio documentation

Welcome to the documentation for mmio, a lightweight C++20 library for expressing memory-mapped I/O access in a clear and type-safe way.

## Why mmio?

mmio helps you write register-level code that is easier to read, safer to maintain, and closer to the hardware than raw pointer-based patterns.

It is especially useful for:

- embedded firmware and board support code
- low-level drivers for peripherals and system registers
- projects that need expressive register and bit-field abstractions

## Start here

- [Getting started](getting_started.md) for integration guidance
- [Examples](examples.md) for practical usage patterns
- [Contributing](contributing.md) for project contribution rules
- [API reference](mmio/pages.md) for the generated Doxygen documentation

## What the library offers

- `mmio::reg` for typed register access
- `mmio::field` for bit-field access with masking and shifting
- access policies such as `ro`, `wo`, `rw`, and `w1c`
- a header-only API that fits naturally into embedded C++ projects
