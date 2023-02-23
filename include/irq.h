#pragma once
#include "base.h"

void irq_vector_init();
void enable_irq();
void disable_irq();
void enable_interrupt_controller();

#define IRQ_BASE (PBASE + 0xB000)

#define IRQ0_PENDING_0      (IRQ_BASE + 0x200)
#define IRQ0_PENDING_1      (IRQ_BASE + 0x204)
#define IRQ0_PENDING_2      (IRQ_BASE + 0x208)
#define IRQ0_ENABLE_0       (IRQ_BASE + 0x210)
#define IRQ0_ENABLE_1       (IRQ_BASE + 0x214)
#define IRQ0_ENABLE_2       (IRQ_BASE + 0x218)
#define IRQ0_DISABLE_0      (IRQ_BASE + 0x220)
#define IRQ0_DISABLE_1      (IRQ_BASE + 0x224)
#define IRQ0_DISABLE_2      (IRQ_BASE + 0x228)

#define AUX_IRQ             (1 << 29)   // 29th bit is the aux irq
