#ifndef RCC_H
#define RCC_H


#include <cstdint>

#include "mmio/mmio.hpp" // IWYU pragma: export

struct RCC {
    static constexpr std::uint32_t BASE = 0x40023800;

    struct CR : mmio::reg<32, mmio::na> {
        using base = mmio::reg<32, mmio::na>;

        constexpr CR() : base(BASE + 0x0) {}

        [[nodiscard]] constexpr auto plli2srdy() const {
            return mmio::make_field<27, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto plli2son() const {
            return mmio::make_field<26, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllrdy() const {
            return mmio::make_field<25, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto pllon() const {
            return mmio::make_field<24, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto csson() const {
            return mmio::make_field<19, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto hsebyp() const {
            return mmio::make_field<18, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto hserdy() const {
            return mmio::make_field<17, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto hseon() const {
            return mmio::make_field<16, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto hsical() const {
            return mmio::make_field<8, 8, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto hsitrim() const {
            return mmio::make_field<3, 5, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto hsirdy() const {
            return mmio::make_field<1, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto hsion() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } CR;

    struct PLLCFGR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr PLLCFGR() : base(BASE + 0x4) {}

        [[nodiscard]] constexpr auto pllq3() const {
            return mmio::make_field<27, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllq2() const {
            return mmio::make_field<26, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllq1() const {
            return mmio::make_field<25, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllq0() const {
            return mmio::make_field<24, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllsrc() const {
            return mmio::make_field<22, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllp1() const {
            return mmio::make_field<17, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllp0() const {
            return mmio::make_field<16, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto plln8() const {
            return mmio::make_field<14, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto plln7() const {
            return mmio::make_field<13, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto plln6() const {
            return mmio::make_field<12, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto plln5() const {
            return mmio::make_field<11, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto plln4() const {
            return mmio::make_field<10, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto plln3() const {
            return mmio::make_field<9, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto plln2() const {
            return mmio::make_field<8, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto plln1() const {
            return mmio::make_field<7, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto plln0() const {
            return mmio::make_field<6, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllm5() const {
            return mmio::make_field<5, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllm4() const {
            return mmio::make_field<4, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllm3() const {
            return mmio::make_field<3, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllm2() const {
            return mmio::make_field<2, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllm1() const {
            return mmio::make_field<1, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllm0() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } PLLCFGR;

    struct CFGR : mmio::reg<32, mmio::na> {
        using base = mmio::reg<32, mmio::na>;

        constexpr CFGR() : base(BASE + 0x8) {}

        [[nodiscard]] constexpr auto mco2() const {
            return mmio::make_field<30, 2, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto mco2pre() const {
            return mmio::make_field<27, 3, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto mco1pre() const {
            return mmio::make_field<24, 3, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto i2ssrc() const {
            return mmio::make_field<23, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto mco1() const {
            return mmio::make_field<21, 2, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto rtcpre() const {
            return mmio::make_field<16, 5, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto ppre2() const {
            return mmio::make_field<13, 3, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto ppre1() const {
            return mmio::make_field<10, 3, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto hpre() const {
            return mmio::make_field<4, 4, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto sws1() const {
            return mmio::make_field<3, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto sws0() const {
            return mmio::make_field<2, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto sw1() const {
            return mmio::make_field<1, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto sw0() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } CFGR;

    struct CIR : mmio::reg<32, mmio::na> {
        using base = mmio::reg<32, mmio::na>;

        constexpr CIR() : base(BASE + 0xC) {}

        [[nodiscard]] constexpr auto cssc() const {
            return mmio::make_field<23, 1, mmio::wo>(*this);
        }

        [[nodiscard]] constexpr auto plli2srdyc() const {
            return mmio::make_field<21, 1, mmio::wo>(*this);
        }

        [[nodiscard]] constexpr auto pllrdyc() const {
            return mmio::make_field<20, 1, mmio::wo>(*this);
        }

        [[nodiscard]] constexpr auto hserdyc() const {
            return mmio::make_field<19, 1, mmio::wo>(*this);
        }

        [[nodiscard]] constexpr auto hsirdyc() const {
            return mmio::make_field<18, 1, mmio::wo>(*this);
        }

        [[nodiscard]] constexpr auto lserdyc() const {
            return mmio::make_field<17, 1, mmio::wo>(*this);
        }

        [[nodiscard]] constexpr auto lsirdyc() const {
            return mmio::make_field<16, 1, mmio::wo>(*this);
        }

        [[nodiscard]] constexpr auto plli2srdyie() const {
            return mmio::make_field<13, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pllrdyie() const {
            return mmio::make_field<12, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto hserdyie() const {
            return mmio::make_field<11, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto hsirdyie() const {
            return mmio::make_field<10, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto lserdyie() const {
            return mmio::make_field<9, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto lsirdyie() const {
            return mmio::make_field<8, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto cssf() const {
            return mmio::make_field<7, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto plli2srdyf() const {
            return mmio::make_field<5, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto pllrdyf() const {
            return mmio::make_field<4, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto hserdyf() const {
            return mmio::make_field<3, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto hsirdyf() const {
            return mmio::make_field<2, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto lserdyf() const {
            return mmio::make_field<1, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto lsirdyf() const {
            return mmio::make_field<0, 1, mmio::ro>(*this);
        }

    } CIR;

    struct AHB1RSTR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr AHB1RSTR() : base(BASE + 0x10) {}

        [[nodiscard]] constexpr auto dma2rst() const {
            return mmio::make_field<22, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto dma1rst() const {
            return mmio::make_field<21, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto crcrst() const {
            return mmio::make_field<12, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpiohrst() const {
            return mmio::make_field<7, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpioerst() const {
            return mmio::make_field<4, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpiodrst() const {
            return mmio::make_field<3, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpiocrst() const {
            return mmio::make_field<2, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpiobrst() const {
            return mmio::make_field<1, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpioarst() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } AHB1RSTR;

    struct AHB2RSTR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr AHB2RSTR() : base(BASE + 0x14) {}

        [[nodiscard]] constexpr auto otgfsrst() const {
            return mmio::make_field<7, 1, mmio::rw>(*this);
        }

    } AHB2RSTR;

    struct APB1RSTR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr APB1RSTR() : base(BASE + 0x20) {}

        [[nodiscard]] constexpr auto pwrrst() const {
            return mmio::make_field<28, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto i2c3rst() const {
            return mmio::make_field<23, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto i2c2rst() const {
            return mmio::make_field<22, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto i2c1rst() const {
            return mmio::make_field<21, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto uart2rst() const {
            return mmio::make_field<17, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto spi3rst() const {
            return mmio::make_field<15, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto spi2rst() const {
            return mmio::make_field<14, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto wwdgrst() const {
            return mmio::make_field<11, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim5rst() const {
            return mmio::make_field<3, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim4rst() const {
            return mmio::make_field<2, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim3rst() const {
            return mmio::make_field<1, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim2rst() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } APB1RSTR;

    struct APB2RSTR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr APB2RSTR() : base(BASE + 0x24) {}

        [[nodiscard]] constexpr auto tim11rst() const {
            return mmio::make_field<18, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim10rst() const {
            return mmio::make_field<17, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim9rst() const {
            return mmio::make_field<16, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto syscfgrst() const {
            return mmio::make_field<14, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto spi1rst() const {
            return mmio::make_field<12, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto sdiorst() const {
            return mmio::make_field<11, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto adcrst() const {
            return mmio::make_field<8, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto usart6rst() const {
            return mmio::make_field<5, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto usart1rst() const {
            return mmio::make_field<4, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim1rst() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } APB2RSTR;

    struct AHB1ENR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr AHB1ENR() : base(BASE + 0x30) {}

        [[nodiscard]] constexpr auto dma2en() const {
            return mmio::make_field<22, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto dma1en() const {
            return mmio::make_field<21, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto crcen() const {
            return mmio::make_field<12, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpiohen() const {
            return mmio::make_field<7, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpioeen() const {
            return mmio::make_field<4, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpioden() const {
            return mmio::make_field<3, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpiocen() const {
            return mmio::make_field<2, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpioben() const {
            return mmio::make_field<1, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpioaen() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } AHB1ENR;

    struct AHB2ENR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr AHB2ENR() : base(BASE + 0x34) {}

        [[nodiscard]] constexpr auto otgfsen() const {
            return mmio::make_field<7, 1, mmio::rw>(*this);
        }

    } AHB2ENR;

    struct APB1ENR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr APB1ENR() : base(BASE + 0x40) {}

        [[nodiscard]] constexpr auto pwren() const {
            return mmio::make_field<28, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto i2c3en() const {
            return mmio::make_field<23, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto i2c2en() const {
            return mmio::make_field<22, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto i2c1en() const {
            return mmio::make_field<21, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto usart2en() const {
            return mmio::make_field<17, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto spi3en() const {
            return mmio::make_field<15, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto spi2en() const {
            return mmio::make_field<14, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto wwdgen() const {
            return mmio::make_field<11, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim5en() const {
            return mmio::make_field<3, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim4en() const {
            return mmio::make_field<2, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim3en() const {
            return mmio::make_field<1, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim2en() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } APB1ENR;

    struct APB2ENR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr APB2ENR() : base(BASE + 0x44) {}

        [[nodiscard]] constexpr auto tim11en() const {
            return mmio::make_field<18, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim10en() const {
            return mmio::make_field<17, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim9en() const {
            return mmio::make_field<16, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto syscfgen() const {
            return mmio::make_field<14, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto spi1en() const {
            return mmio::make_field<12, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto sdioen() const {
            return mmio::make_field<11, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto adc1en() const {
            return mmio::make_field<8, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto usart6en() const {
            return mmio::make_field<5, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto usart1en() const {
            return mmio::make_field<4, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim1en() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } APB2ENR;

    struct AHB1LPENR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr AHB1LPENR() : base(BASE + 0x50) {}

        [[nodiscard]] constexpr auto dma2lpen() const {
            return mmio::make_field<22, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto dma1lpen() const {
            return mmio::make_field<21, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto sram1lpen() const {
            return mmio::make_field<16, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto flitflpen() const {
            return mmio::make_field<15, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto crclpen() const {
            return mmio::make_field<12, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpiohlpen() const {
            return mmio::make_field<7, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpioelpen() const {
            return mmio::make_field<4, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpiodlpen() const {
            return mmio::make_field<3, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpioclpen() const {
            return mmio::make_field<2, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpioblpen() const {
            return mmio::make_field<1, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto gpioalpen() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } AHB1LPENR;

    struct AHB2LPENR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr AHB2LPENR() : base(BASE + 0x54) {}

        [[nodiscard]] constexpr auto otgfslpen() const {
            return mmio::make_field<7, 1, mmio::rw>(*this);
        }

    } AHB2LPENR;

    struct APB1LPENR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr APB1LPENR() : base(BASE + 0x60) {}

        [[nodiscard]] constexpr auto pwrlpen() const {
            return mmio::make_field<28, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto i2c3lpen() const {
            return mmio::make_field<23, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto i2c2lpen() const {
            return mmio::make_field<22, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto i2c1lpen() const {
            return mmio::make_field<21, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto usart2lpen() const {
            return mmio::make_field<17, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto spi3lpen() const {
            return mmio::make_field<15, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto spi2lpen() const {
            return mmio::make_field<14, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto wwdglpen() const {
            return mmio::make_field<11, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim5lpen() const {
            return mmio::make_field<3, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim4lpen() const {
            return mmio::make_field<2, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim3lpen() const {
            return mmio::make_field<1, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim2lpen() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } APB1LPENR;

    struct APB2LPENR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr APB2LPENR() : base(BASE + 0x64) {}

        [[nodiscard]] constexpr auto tim11lpen() const {
            return mmio::make_field<18, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim10lpen() const {
            return mmio::make_field<17, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim9lpen() const {
            return mmio::make_field<16, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto syscfglpen() const {
            return mmio::make_field<14, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto spi1lpen() const {
            return mmio::make_field<12, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto sdiolpen() const {
            return mmio::make_field<11, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto adc1lpen() const {
            return mmio::make_field<8, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto usart6lpen() const {
            return mmio::make_field<5, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto usart1lpen() const {
            return mmio::make_field<4, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tim1lpen() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } APB2LPENR;

    struct BDCR : mmio::reg<32, mmio::na> {
        using base = mmio::reg<32, mmio::na>;

        constexpr BDCR() : base(BASE + 0x70) {}

        [[nodiscard]] constexpr auto bdrst() const {
            return mmio::make_field<16, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto rtcen() const {
            return mmio::make_field<15, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto rtcsel1() const {
            return mmio::make_field<9, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto rtcsel0() const {
            return mmio::make_field<8, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto lsebyp() const {
            return mmio::make_field<2, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto lserdy() const {
            return mmio::make_field<1, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto lseon() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } BDCR;

    struct CSR : mmio::reg<32, mmio::na> {
        using base = mmio::reg<32, mmio::na>;

        constexpr CSR() : base(BASE + 0x74) {}

        [[nodiscard]] constexpr auto lpwrrstf() const {
            return mmio::make_field<31, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto wwdgrstf() const {
            return mmio::make_field<30, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto wdgrstf() const {
            return mmio::make_field<29, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto sftrstf() const {
            return mmio::make_field<28, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto porrstf() const {
            return mmio::make_field<27, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto padrstf() const {
            return mmio::make_field<26, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto borrstf() const {
            return mmio::make_field<25, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto rmvf() const {
            return mmio::make_field<24, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto lsirdy() const {
            return mmio::make_field<1, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto lsion() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } CSR;

    struct SSCGR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr SSCGR() : base(BASE + 0x80) {}

        [[nodiscard]] constexpr auto sscgen() const {
            return mmio::make_field<31, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto spreadsel() const {
            return mmio::make_field<30, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto incstep() const {
            return mmio::make_field<13, 15, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto modper() const {
            return mmio::make_field<0, 13, mmio::rw>(*this);
        }

    } SSCGR;

    struct PLLI2SCFGR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr PLLI2SCFGR() : base(BASE + 0x84) {}

        [[nodiscard]] constexpr auto plli2srx() const {
            return mmio::make_field<28, 3, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto plli2snx() const {
            return mmio::make_field<6, 9, mmio::rw>(*this);
        }

    } PLLI2SCFGR;
};

#endif // RCC_H
