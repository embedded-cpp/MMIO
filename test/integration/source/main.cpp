#include "GPIOA.h"  // for GPIOA
#include "GPIOC.h"  // for GPIOC
#include "RCC.h"    // for RCC
#include "USART2.h" // for USART2
#include <cstddef>  // for size_t
#include <cstdint>  // for uint32_t

#include "mmio/mmio.hpp" // for reg, rw

using namespace mmio;

constexpr size_t UART_LINE_BUF_SIZE = 128;
static volatile char uart_line_buf[UART_LINE_BUF_SIZE];
static volatile size_t uart_line_len = 0;
static volatile uint32_t counter     = 0U;

extern "C" void SystemInit() {
    // Let the system clock run at 16MHz (HSI)
}

extern "C" void SysTick_Handler() {
    uint32_t tick_count = counter;
    counter             = tick_count + 1U;
}

extern "C" void USART2_IRQHandler() {
    // USART2 usart2;

    if (USART2::SR::RXNE::read()) {
        char c = static_cast<char>(USART2::DR::DATA::read());
        if (uart_line_len < UART_LINE_BUF_SIZE - 1) {
            size_t idx                   = uart_line_len;
            uart_line_buf[uart_line_len] = c;
            uart_line_len                = idx + 1U;
        }

        if (c == '\r' || c == '\n') {
            uart_line_buf[uart_line_len] = '\0';

            for (size_t i = 0; i < uart_line_len; ++i) {
                while (!USART2::SR::TXE::read()) {
                }
                USART2::DR::DATA::write(static_cast<uint32_t>(uart_line_buf[i]));
                while (!USART2::SR::TC::read()) {
                }
            }
            uart_line_len = 0;
        }
    }
}

int main() {
    // Systick config: 1ms tick
    using SYST_CSR = reg<0xE000E010U, 32U, rw>;
    SYST_CSR::modify([](auto& reg) { reg |= 0x00000001U; }); // Enable the timer
    using SYST_RVR = reg<0xE000E014U, 32U, rw>;
    SYST_RVR::write(16000U - 1U);

    // Activate systick interrupt (Peripheral & NVIC)
    SYST_CSR::modify([](auto& reg) { reg |= 0x00000002U; });

    // Clock
    RCC::AHB1ENR::GPIOAEN::set();
    RCC::AHB1ENR::GPIOCEN::set();

    // GPIO A5: output
    GPIOA::MODER::PIN5::write(0b01U); // MODER5 = Output

    // GPIO C13: input
    GPIOC::MODER::PIN13::write(0b00U); // MODER13 = Input
    GPIOC::PUPDR::PIN13::write(0b10U); // Pull-down

    // USART2: TX on A2, RX on A3
    RCC::APB1ENR::USART2EN::set();

    GPIOA::MODER::PIN2::write(0b10U);    // A2: AF
    GPIOA::MODER::PIN3::write(0b10U);    // A3: AF
    GPIOA::AFRL::AFRLL2::write(0b0111U); // A2: AF7 (USART2_TX)
    GPIOA::AFRL::AFRLL3::write(0b0111U); // A3: AF7 (USART2_RX)

    // USART2 configuration (baudrate 115200 @ 16MHz)
    // Baudrate = fclk / (16 * USARTDIV)
    // USARTDIV = 16MHz / (16 * 115200) = 8.6805
    // Mantissa = 8, Fraction = 11 (0.6805 * 16 = 10.89 ~ 11)
    USART2::BRR::DIV_MANTISSA::write(8U);  // Mantissa
    USART2::BRR::DIV_FRACTION::write(11U); // Fraction

    USART2::CR1::write_set<USART2::CR1::UE, // USART enable
        USART2::CR1::TE,                    // Transmitter enable
        USART2::CR1::RE,                    // Receiver enable
        USART2::CR1::RXNEIE                 // RXNE interrupt enable
        >();

    // NVIC USART2 interrupt enable
    using NVIC_ISER1 = reg<0xE000E104U, 32U, rw>;
    NVIC_ISER1::write(1U << 6U); // USART2 interrupt

    while (1) {
        if (GPIOC::IDR::PIN13::read()) {
            GPIOA::ODR::PIN5::set();
        } else {
            GPIOA::ODR::PIN5::clear();
        }
    }
}
