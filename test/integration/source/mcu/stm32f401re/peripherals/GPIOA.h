#ifndef GPIOA_H
#define GPIOA_H

#include "mmio/mmio.hpp"

template <std::uintptr_t Base>
struct gpio {
    using MODER_impl = mmio::reg<Base + 0x00U, 32U, mmio::rw>;
    struct MODER : MODER_impl {
        using PIN2 = mmio::field<MODER_impl, 4, 2>;
        using PIN3 = mmio::field<MODER_impl, 6, 2>;
        using PIN5 = mmio::field<MODER_impl, 10, 2>;
    };

    using ODR_impl = mmio::reg<Base + 0x14U, 32U, mmio::rw>;
    struct ODR : ODR_impl {
        using PIN5 = mmio::bit<ODR_impl, 5>;
    };

    using BSRR_impl = mmio::reg<Base + 0x18U, 32U, mmio::wo>;
    struct BSRR : BSRR_impl {
        using SET0   = mmio::bit<BSRR_impl, 0>;
        using CLEAR0 = mmio::bit<BSRR_impl, 16>;
        using SET5   = mmio::bit<BSRR_impl, 5>;
        using CLEAR5 = mmio::bit<BSRR_impl, 21>;
    };

    using AFRL_impl = mmio::reg<Base + 0x20U, 32U, mmio::rw>;
    struct AFRL : AFRL_impl {
        using AFRLL2 = mmio::field<AFRL_impl, 8, 4>;
        using AFRLL3 = mmio::field<AFRL_impl, 12, 4>;
    };
};

using GPIOA = gpio<0x40020000U>;

#endif
