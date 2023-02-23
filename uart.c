#include "base.h"
#include "uart.h"


#define ALT_5 2
#include <stdint.h>

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
    mmio_write(AUX_MU_IER_REG, 2);      // Enable receive interrupts
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

void uart_send_int(int64_t n) {
    if (n < 0) {
        uart_send(45);  // - in ASCII
        n *= -1;
    }
    char digits[19];    // max signed int64 value is 19 digits long
    int count = 0;
    do {
        digits[count] = n % 10;
        count++;
        n /= 10;
    } while (n > 0);
    while (count > 0) {
        uart_send(digits[count - 1] + 48);  // +48 converts digit to ASCII
        count--;
    }
}