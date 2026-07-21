# Examples

The best way to understand mmio is to look at how it is used in practice. The integration tests in the repository provide a realistic example of register-oriented firmware code.

## Register access with `mmio::reg`

The integration tests define hardware registers directly using `mmio::reg` and then modify them through helper wrappers.

```cpp
using SYST_CSR = mmio::reg<0xE000E010U, 32U, mmio::rw>;
SYST_CSR::modify([](auto& reg) { reg |= 0x00000001U; });
```

This pattern is useful when you want to configure peripherals or system control blocks at a specific address.

## Bit-field access with `mmio::field`

Fields are expressed as typed bit ranges and can be read or written independently:

```cpp
using GPIOA_MODER = mmio::field<GPIOA::MODER, 0, 2>;
GPIOA_MODER::write(0b01U);
```

The integration tests use this style for configuring GPIO pin modes and peripheral enables.

## Combining registers and fields

A typical pattern looks like this:

```cpp
RCC::AHB1ENR::GPIOAEN::set();
GPIOA::MODER::PIN5::write(0b01U);
USART2::CR1::write_set<USART2::CR1::UE, USART2::CR1::TE, USART2::CR1::RE>();
```

This shows how mmio can be used to describe both low-level register writes and higher-level peripheral configuration in a concise way.

## Practical reference

The integration example in [test/integration/source/main.cpp](../../test/integration/source/main.cpp) is a good starting point for seeing the library in use with STM32-style peripheral headers.
