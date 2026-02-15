#ifndef RCC_H
#define RCC_H

#include <cstdint>

#include "mmio/mmio.hpp"

template <std::uintptr_t Base>
struct rcc {

    using AHB1ENR_impl = mmio::reg<Base + 0x30U, 32U, mmio::rw>;
    struct AHB1ENR : AHB1ENR_impl {
        using GPIOAEN = mmio::bit<AHB1ENR_impl, 0>;
        using GPIOCEN = mmio::bit<AHB1ENR_impl, 2>;
    };

    using APB1ENR_impl = mmio::reg<Base + 0x40U, 32U, mmio::rw>;
    struct APB1ENR : APB1ENR_impl {
        using USART2EN = mmio::bit<APB1ENR_impl, 17>;
    };
};

using RCC = rcc<0x40023800U>;

#endif // RCC_H
