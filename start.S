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
    // We're on the main core
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

