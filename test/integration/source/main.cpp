#include "GPIOA.h"
#include "GPIOC.h"
#include "RCC.h"
#include "USART2.h"
#include <cstddef> // for size_t
#include <cstdint> // for uint32_t


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
    USART2 usart2;

    if (usart2.SR.rxne().read()) {
        char c = static_cast<char>(usart2.DR.dr().read());
        if (uart_line_len < UART_LINE_BUF_SIZE - 1) {
            size_t idx                   = uart_line_len;
            uart_line_len                = idx + 1U;
            uart_line_buf[uart_line_len] = c;
        }

        if (c == '\r' || c == '\n') {
            uart_line_buf[uart_line_len] = '\0';

            for (size_t i = 0; i < uart_line_len; ++i) {
                while (!usart2.SR.txe().read()) {
                }
                usart2.DR.dr().write(static_cast<uint32_t>(uart_line_buf[i]));
                while (!usart2.SR.tc().read()) {
                }
            }
            uart_line_len = 0;
        }
    }
}

int main(void) {
    // Systick config: 1ms tick
    mmio::reg<32U, mmio::rw> SYST_CSR{0xE000E010U}; // CLKSOURCE = processor clock
    SYST_CSR.modify([](auto& reg) { reg |= 0x00000001U; }); // Enable the timer
    mmio::reg<32U, mmio::rw> SYST_RVR{0xE000E014U};
    SYST_RVR.write<16000U - 1U>();

    // Activate systick interrupt (Peripheral & NVIC)
    SYST_CSR.modify([](auto& reg) { reg |= 0x00000002U; });
    mmio::reg<32U, mmio::rw> NVIC_ISER0{0xE000E100U};
    NVIC_ISER0.write<1U << 15U>(); // SysTick interrupt

    // Clock
    RCC rcc;
    rcc.AHB1ENR.gpioaen().set_bit().gpiocen().set_bit();

    // GPIO A5: output
    GPIOA gpioa;
    gpioa.MODER.moder5().write<0b01U>(); // MODER5 = Output

    // GPIO C13: input
    GPIOC gpioc;
    gpioc.MODER.moder13().write<0b00U>(); // MODER13 = Input
    gpioc.PUPDR.pupdr13().write<0b10U>(); // Pull-down

    // USART2: TX on A2, RX on A3
    rcc.APB1ENR.usart2en().set_bit();
    gpioa.MODER.moder2()
        .write<0b10U>() // A2: AF
        .moder3()
        .write<0b10U>(); // A3: AF
    gpioa.AFRL.afrl2().write<0b0111U>(); // A2: AF7 (USART2_TX)
    gpioa.AFRL.afrl3().write<0b0111U>(); // A3: AF7 (USART2_RX)

    // USART2 configuration (baudrate 115200 @ 16MHz)
    USART2 usart2;
    // Baudrate = fclk / (16 * USARTDIV)
    // USARTDIV = 16MHz / (16 * 115200) = 8.6805
    // Mantissa = 8, Fraction = 11 (0.6805 * 16 = 10.89 ~ 11)
    usart2.BRR.div_mantissa()
        .write<8U>() // Mantissa
        .div_fraction()
        .write<11U>(); // Fraction

    usart2.CR1.ue()
        .set_bit() // USART enable
        .te()
        .set_bit() // Transmitter enable
        .re()
        .set_bit() // Receiver enable
        .rxneie()
        .set_bit() // RXNE interrupt enable
        .txeie()
        .clear_bit() // TXE interrupt disable
        .pce()
        .clear_bit(); // Parity control disable

    // NVIC USART2 interrupt enable
    mmio::reg<32U, mmio::rw> NVIC_ISER1{0xE000E104U};
    NVIC_ISER1.write<1U << 6U>(); // USART2 interrupt


    while (1) {
        if (gpioc.IDR.idr13().read()) {
            gpioa.ODR.odr5().set_bit();
        } else {
            gpioa.ODR.odr5().clear_bit();
        }
    }
}
