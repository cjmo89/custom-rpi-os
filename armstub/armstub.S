// Replacement for the original armstub to avoid going into execution level 2
// This barebone atmstub doesn't spin the cpus and stays in EL 3

.globl _start
_start:
    ldr w0, kernel_entry32
    br x0           // branch to the kernel entry

// values that the firmware needs to find 
.ltorg
.org 0xf0
.globl stub_magic
stub_magic:
    .word 0x5afe570b
.org 0xf4
.globl stub_version
stub_version:
    .word 0

.org 0xfc
.globl kernel_entry32
kernel_entry32:
    .word 0x0       // start at the very beginning of the binary file