#pragma once
#include "base.h"
#include <stdint.h>

void uart_init();
void uart_send(char c);
void uart_send_string(char *buffer);
void uart_send_int(int64_t n);
char uart_recv();

#define GPIO_BASE (PBASE + 0x200000)
#define AUX_BASE (PBASE + 0x215000)

enum {
    GPFSEL0         = GPIO_BASE + 0x0,
    GPFSEL1         = GPIO_BASE + 0x04,
    GPIO_PUP_PDN0   = GPIO_BASE + 0xE4,
};

enum {
    AUX_IRQ_STATUS  = AUX_BASE + 0x0,
    AUX_ENABLES     = AUX_BASE + 0x04,
    AUX_MU_IO_REG   = AUX_BASE + 0x40,
    AUX_MU_IER_REG  = AUX_BASE + 0x44,
    AUX_MU_IIR_REG  = AUX_BASE + 0x48,
    AUX_MU_LCR_REG  = AUX_BASE + 0x4c,
    AUX_MU_MCR_REG  = AUX_BASE + 0x50,
    AUX_MU_LSR_REG  = AUX_BASE + 0x54,
    AUX_MU_CNTL_REG = AUX_BASE + 0x60,
    AUX_MU_BAUD_REG = AUX_BASE + 0x68,
};