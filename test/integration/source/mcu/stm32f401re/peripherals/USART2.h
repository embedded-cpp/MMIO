#ifndef USART2_H
#define USART2_H

#include "mmio/mmio.hpp"

template <std::uintptr_t Base>
struct usart2 {
    // Status Register (Read-Only pour certains bits)
    using SR_impl = mmio::reg<Base + 0x00U, 32U, mmio::rw>;
    struct SR : SR_impl {
        using TXE  = mmio::bit<SR_impl, 7>; // Transmit data register empty
        using TC   = mmio::bit<SR_impl, 6>; // Transmission complete
        using RXNE = mmio::bit<SR_impl, 5>; // Read data register not empty
    };

    // Data Register
    using DR_impl = mmio::reg<Base + 0x04U, 32U, mmio::rw>;
    struct DR : DR_impl {
        using DATA = mmio::field<DR_impl, 0, 9>;
    };

    // Control Register 1
    using CR1_impl = mmio::reg<Base + 0x0CU, 32U, mmio::rw>;
    struct CR1 : CR1_impl {
        using RE     = mmio::bit<CR1_impl, 2>;  // Receiver enable
        using TE     = mmio::bit<CR1_impl, 3>;  // Transmitter enable
        using RXNEIE = mmio::bit<CR1_impl, 5>;  // RXNE interrupt enable
        using TXEIE  = mmio::bit<CR1_impl, 7>;  // TXE interrupt enable
        using PCE    = mmio::bit<CR1_impl, 10>; // Parity control enable
        using M      = mmio::bit<CR1_impl, 12>; // Word length
        using UE     = mmio::bit<CR1_impl, 13>; // USART enable
    };

    using BRR_impl = mmio::reg<Base + 0x08U, 32U, mmio::rw>;
    struct BRR : BRR_impl {
        using DIV_MANTISSA = mmio::field<BRR_impl, 4, 12>;
        using DIV_FRACTION = mmio::field<BRR_impl, 0, 4>;
    };
};

using USART2 = usart2<0x40004400U>;

#endif
