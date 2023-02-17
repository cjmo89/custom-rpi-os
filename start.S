#include "sysregs.h"
.section ".text.boot" 
// Execution starts here
.global _start

_start:
    // proceed only with processor ID 0, park the others
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, 1f

hang:
    wfe
    b       hang

1:
    // set the system registers in EL3 and go to EL1
    ldr     x0, =SCTLR_VALUE_MMU_DISABLED
    msr     sctlr_el1, x0
    ldr     x0, =HCR_VALUE
    msr     hcr_el2, x0
    ldr     x0, =SCR_VALUE
    msr     scr_el3, x0
    ldr     x0, =SPSR_VALUE
    msr     spsr_el3, x0
    adr     x0, el1_entry
    msr     elr_el3, x0
    eret

el1_entry:
    // Set stack to start below our code
    ldr     x1, =_start
    mov     sp, x1

    // Clean the BSS section
    adr     x0, bss_begin
    adr     x1, bss_end
    sub     x1, x1, x0

memzero:
	str xzr, [x0], #8
	subs x1, x1, #8
	b.gt memzero

    // Jump to our main() routine in C
2:  bl      main
    // this should never run
    b       2b

