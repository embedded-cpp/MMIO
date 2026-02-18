#ifndef GPIOC_H
#define GPIOC_H

#include "mmio/mmio.hpp"

template <std::uintptr_t Base>
struct gpioc {
    using MODER_impl = mmio::reg<Base + 0x00U, 32U, mmio::rw>;
    struct MODER : MODER_impl {
        using PIN13 = mmio::field<MODER_impl, 26, 2>;
    };


    using IDR_impl = mmio::reg<Base + 0x10U, 32U, mmio::rw>;
    struct IDR : IDR_impl {
        using PIN13 = mmio::bit<IDR_impl, 13>;
    };

    using PUPDR_impl = mmio::reg<Base + 0x0CU, 32U, mmio::rw>;
    struct PUPDR : PUPDR_impl {
        using PIN13 = mmio::field<PUPDR_impl, 26, 2>;
    };
    using BSRR_impl = mmio::reg<Base + 0x18U, 32U, mmio::wo>;
    struct BSRR : BSRR_impl {
        using SET13   = mmio::bit<BSRR_impl, 13>;
        using CLEAR13 = mmio::bit<BSRR_impl, 29>;
    };
};

using GPIOC = gpioc<0x40020800U>;

#endif
