#pragma once

#include <cstdint>

#include "mmio/mmio.hpp" // IWYU pragma: export

struct USART2 {
    static constexpr std::uint32_t BASE = 0x40004400;

    struct SR : mmio::reg<32, mmio::na> {
        using base = mmio::reg<32, mmio::na>;

        constexpr SR() : base(BASE + 0x0) {}

        [[nodiscard]] constexpr auto cts() const {
            return mmio::make_field<9, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto lbd() const {
            return mmio::make_field<8, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto txe() const {
            return mmio::make_field<7, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto tc() const {
            return mmio::make_field<6, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto rxne() const {
            return mmio::make_field<5, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto idle() const {
            return mmio::make_field<4, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto ore() const {
            return mmio::make_field<3, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto nf() const {
            return mmio::make_field<2, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto fe() const {
            return mmio::make_field<1, 1, mmio::ro>(*this);
        }

        [[nodiscard]] constexpr auto pe() const {
            return mmio::make_field<0, 1, mmio::ro>(*this);
        }

    } SR;

    struct DR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr DR() : base(BASE + 0x4) {}

        [[nodiscard]] constexpr auto dr() const {
            return mmio::make_field<0, 9, mmio::rw>(*this);
        }

    } DR;

    struct BRR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr BRR() : base(BASE + 0x8) {}

        [[nodiscard]] constexpr auto div_mantissa() const {
            return mmio::make_field<4, 12, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto div_fraction() const {
            return mmio::make_field<0, 4, mmio::rw>(*this);
        }

    } BRR;

    struct CR1 : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr CR1() : base(BASE + 0xC) {}

        [[nodiscard]] constexpr auto over8() const {
            return mmio::make_field<15, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto ue() const {
            return mmio::make_field<13, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto m() const {
            return mmio::make_field<12, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto wake() const {
            return mmio::make_field<11, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto pce() const {
            return mmio::make_field<10, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto ps() const {
            return mmio::make_field<9, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto peie() const {
            return mmio::make_field<8, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto txeie() const {
            return mmio::make_field<7, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto tcie() const {
            return mmio::make_field<6, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto rxneie() const {
            return mmio::make_field<5, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto idleie() const {
            return mmio::make_field<4, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto te() const {
            return mmio::make_field<3, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto re() const {
            return mmio::make_field<2, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto rwu() const {
            return mmio::make_field<1, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto sbk() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } CR1;

    struct CR2 : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr CR2() : base(BASE + 0x10) {}

        [[nodiscard]] constexpr auto linen() const {
            return mmio::make_field<14, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto stop() const {
            return mmio::make_field<12, 2, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto clken() const {
            return mmio::make_field<11, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto cpol() const {
            return mmio::make_field<10, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto cpha() const {
            return mmio::make_field<9, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto lbcl() const {
            return mmio::make_field<8, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto lbdie() const {
            return mmio::make_field<6, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto lbdl() const {
            return mmio::make_field<5, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto add() const {
            return mmio::make_field<0, 4, mmio::rw>(*this);
        }

    } CR2;

    struct CR3 : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr CR3() : base(BASE + 0x14) {}

        [[nodiscard]] constexpr auto onebit() const {
            return mmio::make_field<11, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto ctsie() const {
            return mmio::make_field<10, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto ctse() const {
            return mmio::make_field<9, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto rtse() const {
            return mmio::make_field<8, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto dmat() const {
            return mmio::make_field<7, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto dmar() const {
            return mmio::make_field<6, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto scen() const {
            return mmio::make_field<5, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto nack() const {
            return mmio::make_field<4, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto hdsel() const {
            return mmio::make_field<3, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto irlp() const {
            return mmio::make_field<2, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto iren() const {
            return mmio::make_field<1, 1, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto eie() const {
            return mmio::make_field<0, 1, mmio::rw>(*this);
        }

    } CR3;

    struct GTPR : mmio::reg<32, mmio::rw> {
        using base = mmio::reg<32, mmio::rw>;

        constexpr GTPR() : base(BASE + 0x18) {}

        [[nodiscard]] constexpr auto gt() const {
            return mmio::make_field<8, 8, mmio::rw>(*this);
        }

        [[nodiscard]] constexpr auto psc() const {
            return mmio::make_field<0, 8, mmio::rw>(*this);
        }

    } GTPR;
};
