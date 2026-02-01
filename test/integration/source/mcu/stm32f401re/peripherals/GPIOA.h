#pragma once

// Auto-generated fmmio::rom SVD with Inja

#include <cstdint>

#include "mmio/mmio.h"

struct GPIOA
{
    static constexpr std::uint32_t BASE = 0x40020000;

    struct MODER : mmio::reg<32, mmio::rw>
    {
        using base = mmio::reg<32, mmio::rw>;

        constexpr MODER() : base(BASE + 0x0) { }

        [[nodiscard]] constexpr auto moder15() const { return mmio::make_field<30, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder14() const { return mmio::make_field<28, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder13() const { return mmio::make_field<26, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder12() const { return mmio::make_field<24, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder11() const { return mmio::make_field<22, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder10() const { return mmio::make_field<20, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder9() const { return mmio::make_field<18, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder8() const { return mmio::make_field<16, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder7() const { return mmio::make_field<14, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder6() const { return mmio::make_field<12, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder5() const { return mmio::make_field<10, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder4() const { return mmio::make_field<8, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder3() const { return mmio::make_field<6, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder2() const { return mmio::make_field<4, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder1() const { return mmio::make_field<2, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto moder0() const { return mmio::make_field<0, 2, mmio::rw>(*this); }

    } MODER;

    struct OTYPER : mmio::reg<32, mmio::rw>
    {
        using base = mmio::reg<32, mmio::rw>;

        constexpr OTYPER() : base(BASE + 0x4) { }

        [[nodiscard]] constexpr auto ot15() const { return mmio::make_field<15, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot14() const { return mmio::make_field<14, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot13() const { return mmio::make_field<13, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot12() const { return mmio::make_field<12, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot11() const { return mmio::make_field<11, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot10() const { return mmio::make_field<10, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot9() const { return mmio::make_field<9, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot8() const { return mmio::make_field<8, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot7() const { return mmio::make_field<7, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot6() const { return mmio::make_field<6, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot5() const { return mmio::make_field<5, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot4() const { return mmio::make_field<4, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot3() const { return mmio::make_field<3, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot2() const { return mmio::make_field<2, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot1() const { return mmio::make_field<1, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ot0() const { return mmio::make_field<0, 1, mmio::rw>(*this); }

    } OTYPER;

    struct OSPEEDR : mmio::reg<32, mmio::rw>
    {
        using base = mmio::reg<32, mmio::rw>;

        constexpr OSPEEDR() : base(BASE + 0x8) { }

        [[nodiscard]] constexpr auto ospeedr15() const { return mmio::make_field<30, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr14() const { return mmio::make_field<28, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr13() const { return mmio::make_field<26, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr12() const { return mmio::make_field<24, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr11() const { return mmio::make_field<22, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr10() const { return mmio::make_field<20, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr9() const { return mmio::make_field<18, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr8() const { return mmio::make_field<16, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr7() const { return mmio::make_field<14, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr6() const { return mmio::make_field<12, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr5() const { return mmio::make_field<10, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr4() const { return mmio::make_field<8, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr3() const { return mmio::make_field<6, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr2() const { return mmio::make_field<4, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr1() const { return mmio::make_field<2, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto ospeedr0() const { return mmio::make_field<0, 2, mmio::rw>(*this); }

    } OSPEEDR;

    struct PUPDR : mmio::reg<32, mmio::rw>
    {
        using base = mmio::reg<32, mmio::rw>;

        constexpr PUPDR() : base(BASE + 0xC) { }

        [[nodiscard]] constexpr auto pupdr15() const { return mmio::make_field<30, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr14() const { return mmio::make_field<28, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr13() const { return mmio::make_field<26, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr12() const { return mmio::make_field<24, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr11() const { return mmio::make_field<22, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr10() const { return mmio::make_field<20, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr9() const { return mmio::make_field<18, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr8() const { return mmio::make_field<16, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr7() const { return mmio::make_field<14, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr6() const { return mmio::make_field<12, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr5() const { return mmio::make_field<10, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr4() const { return mmio::make_field<8, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr3() const { return mmio::make_field<6, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr2() const { return mmio::make_field<4, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr1() const { return mmio::make_field<2, 2, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto pupdr0() const { return mmio::make_field<0, 2, mmio::rw>(*this); }

    } PUPDR;

    struct IDR : mmio::reg<32, mmio::ro>
    {
        using base = mmio::reg<32, mmio::ro>;

        constexpr IDR() : base(BASE + 0x10) { }

        [[nodiscard]] constexpr auto idr15() const { return mmio::make_field<15, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr14() const { return mmio::make_field<14, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr13() const { return mmio::make_field<13, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr12() const { return mmio::make_field<12, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr11() const { return mmio::make_field<11, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr10() const { return mmio::make_field<10, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr9() const { return mmio::make_field<9, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr8() const { return mmio::make_field<8, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr7() const { return mmio::make_field<7, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr6() const { return mmio::make_field<6, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr5() const { return mmio::make_field<5, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr4() const { return mmio::make_field<4, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr3() const { return mmio::make_field<3, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr2() const { return mmio::make_field<2, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr1() const { return mmio::make_field<1, 1, mmio::ro>(*this); }

        [[nodiscard]] constexpr auto idr0() const { return mmio::make_field<0, 1, mmio::ro>(*this); }

    } IDR;

    struct ODR : mmio::reg<32, mmio::rw>
    {
        using base = mmio::reg<32, mmio::rw>;

        constexpr ODR() : base(BASE + 0x14) { }

        [[nodiscard]] constexpr auto odr15() const { return mmio::make_field<15, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr14() const { return mmio::make_field<14, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr13() const { return mmio::make_field<13, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr12() const { return mmio::make_field<12, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr11() const { return mmio::make_field<11, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr10() const { return mmio::make_field<10, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr9() const { return mmio::make_field<9, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr8() const { return mmio::make_field<8, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr7() const { return mmio::make_field<7, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr6() const { return mmio::make_field<6, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr5() const { return mmio::make_field<5, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr4() const { return mmio::make_field<4, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr3() const { return mmio::make_field<3, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr2() const { return mmio::make_field<2, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr1() const { return mmio::make_field<1, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto odr0() const { return mmio::make_field<0, 1, mmio::rw>(*this); }

    } ODR;

    struct BSRR : mmio::reg<32, mmio::wo>
    {
        using base = mmio::reg<32, mmio::wo>;

        constexpr BSRR() : base(BASE + 0x18) { }

        [[nodiscard]] constexpr auto br15() const { return mmio::make_field<31, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br14() const { return mmio::make_field<30, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br13() const { return mmio::make_field<29, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br12() const { return mmio::make_field<28, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br11() const { return mmio::make_field<27, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br10() const { return mmio::make_field<26, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br9() const { return mmio::make_field<25, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br8() const { return mmio::make_field<24, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br7() const { return mmio::make_field<23, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br6() const { return mmio::make_field<22, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br5() const { return mmio::make_field<21, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br4() const { return mmio::make_field<20, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br3() const { return mmio::make_field<19, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br2() const { return mmio::make_field<18, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br1() const { return mmio::make_field<17, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto br0() const { return mmio::make_field<16, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs15() const { return mmio::make_field<15, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs14() const { return mmio::make_field<14, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs13() const { return mmio::make_field<13, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs12() const { return mmio::make_field<12, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs11() const { return mmio::make_field<11, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs10() const { return mmio::make_field<10, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs9() const { return mmio::make_field<9, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs8() const { return mmio::make_field<8, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs7() const { return mmio::make_field<7, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs6() const { return mmio::make_field<6, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs5() const { return mmio::make_field<5, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs4() const { return mmio::make_field<4, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs3() const { return mmio::make_field<3, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs2() const { return mmio::make_field<2, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs1() const { return mmio::make_field<1, 1, mmio::wo>(*this); }

        [[nodiscard]] constexpr auto bs0() const { return mmio::make_field<0, 1, mmio::wo>(*this); }

    } BSRR;

    struct LCKR : mmio::reg<32, mmio::rw>
    {
        using base = mmio::reg<32, mmio::rw>;

        constexpr LCKR() : base(BASE + 0x1C) { }

        [[nodiscard]] constexpr auto lckk() const { return mmio::make_field<16, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck15() const { return mmio::make_field<15, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck14() const { return mmio::make_field<14, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck13() const { return mmio::make_field<13, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck12() const { return mmio::make_field<12, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck11() const { return mmio::make_field<11, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck10() const { return mmio::make_field<10, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck9() const { return mmio::make_field<9, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck8() const { return mmio::make_field<8, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck7() const { return mmio::make_field<7, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck6() const { return mmio::make_field<6, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck5() const { return mmio::make_field<5, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck4() const { return mmio::make_field<4, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck3() const { return mmio::make_field<3, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck2() const { return mmio::make_field<2, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck1() const { return mmio::make_field<1, 1, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto lck0() const { return mmio::make_field<0, 1, mmio::rw>(*this); }

    } LCKR;

    struct AFRL : mmio::reg<32, mmio::rw>
    {
        using base = mmio::reg<32, mmio::rw>;

        constexpr AFRL() : base(BASE + 0x20) { }

        [[nodiscard]] constexpr auto afrl7() const { return mmio::make_field<28, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrl6() const { return mmio::make_field<24, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrl5() const { return mmio::make_field<20, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrl4() const { return mmio::make_field<16, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrl3() const { return mmio::make_field<12, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrl2() const { return mmio::make_field<8, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrl1() const { return mmio::make_field<4, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrl0() const { return mmio::make_field<0, 4, mmio::rw>(*this); }

    } AFRL;

    struct AFRH : mmio::reg<32, mmio::rw>
    {
        using base = mmio::reg<32, mmio::rw>;

        constexpr AFRH() : base(BASE + 0x24) { }

        [[nodiscard]] constexpr auto afrh15() const { return mmio::make_field<28, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrh14() const { return mmio::make_field<24, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrh13() const { return mmio::make_field<20, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrh12() const { return mmio::make_field<16, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrh11() const { return mmio::make_field<12, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrh10() const { return mmio::make_field<8, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrh9() const { return mmio::make_field<4, 4, mmio::rw>(*this); }

        [[nodiscard]] constexpr auto afrh8() const { return mmio::make_field<0, 4, mmio::rw>(*this); }

    } AFRH;
};
