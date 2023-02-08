#define GPIO_BASE 0xFE200000
#define AUX_BASE 0xFE215000
#define ALT_5 2
#include <stdint.h>

enum {
    GPFSEL0         = GPIO_BASE + 0x0,
    GPFSEL1         = GPIO_BASE + 0x04,
    GPIO_PUP_PDN0   = GPIO_BASE + 0xE4,
};

enum {
    AUX_IRQ         = AUX_BASE + 0x0,
    AUX_ENABLES     = AUX_BASE + 0x04,
    AUX_MU_IO_REG   = AUX_BASE + 0x40,
    AUX_MU_IER_REG  = AUX_BASE + 0x44,
    AUX_MU_LCR_REG  = AUX_BASE + 0x4c,
    AUX_MU_MCR_REG  = AUX_BASE + 0x50,
    AUX_MU_LSR_REG  = AUX_BASE + 0x54,
    AUX_MU_CNTL_REG = AUX_BASE + 0x60,
    AUX_MU_BAUD_REG = AUX_BASE + 0x68,
};

void mmio_write(long reg, unsigned int val) {
    *(volatile unsigned int*) reg = val;
}

unsigned int mmio_read(long reg) {
    return *(volatile unsigned int*) reg;
}

void gpio_set_function(uint8_t pin, uint8_t function) {
    if (function > 7 || pin > 57)
        return;
    uint8_t bit_start = (pin * 3) % 30;
    uint8_t reg = pin / 10;
    uint64_t reg_address = GPIO_BASE + reg * 4;    // all registers are stacked starting at the offset and is 32 bits wide
    uint32_t selector = mmio_read(reg_address);
    selector &= ~(7<<bit_start);                    // AND bits (bit_start+2:bit_start) with 000 to clear GPIO pin
    selector |= function<<bit_start;                // OR bits (bit_start+2:bit_start) with function to set GPIO pin to desired function
    mmio_write(reg_address, selector);
}

void uart_init() {
    gpio_set_function(14, ALT_5);       // set pin 14 as TXD1
    gpio_set_function(15, ALT_5);       // set pin 15 as RXD1
    mmio_write(GPIO_PUP_PDN0, 0);       // set pins as pull none
    mmio_write(AUX_ENABLES, 1);         // Enable mini UART
    mmio_write(AUX_MU_CNTL_REG, 0);     // Disable auto flow control and disable receiver and transmitter
    mmio_write(AUX_MU_IER_REG, 0);      // Disable receive and transmit interrupts
    mmio_write(AUX_MU_LCR_REG, 3);      // Set the UART in 8-bit mode
    mmio_write(AUX_MU_MCR_REG, 0);      // Set the UART1_RTS line to be always high
    mmio_write(AUX_MU_BAUD_REG, 541);   // Set the baud rate to 115200 @ 500MHz
    mmio_write(AUX_MU_CNTL_REG, 3);     // Enable receiver and transmitter
}

void uart_send(char c) {
    while(1) {
        if (mmio_read(AUX_MU_LSR_REG) & 0x20)
            break;
    }
    mmio_write(AUX_MU_IO_REG, c);
}

char uart_recv() {
    while(1) {
        if (mmio_read(AUX_MU_LSR_REG) & 0x1)
            break;
    }
    return mmio_read(AUX_MU_IO_REG) & 0xFF;
}

void uart_send_string(char* buffer) {
    while (*buffer != '\0') {
        if (*buffer == '\n') {
            uart_send('\r');
        }
        uart_send(*buffer);
        buffer++;
    }
}