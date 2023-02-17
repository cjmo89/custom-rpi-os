#pragma once

// System control register (EL1) SCTLR_EL1

#define SCTLR_EE_LITTLE_ENDIAN          (0 << 25)   // use little endian at EL1
#define SCTLR_EOE_LITTLE_ENDIAN         (0 << 24)   // use little endian at EL0
#define SCTLR_I_CACHE_DISABLED          (0 << 12)   // disable instruction cache
#define SCTLR_D_CACHE_DISABLED          (0 << 2)    // disable data cache
#define SCTLR_MMU_DISABLED              (0 << 0)    // disable the MMU
#define SCTLR_MMU_ENABLED               (1 << 0)    // enable the MMU
#define SCTLR_VALUE_MMU_DISABLED        (SCTLR_EE_LITTLE_ENDIAN | SCTLR_EOE_LITTLE_ENDIAN | SCTLR_I_CACHE_DISABLED | SCTLR_D_CACHE_DISABLED | SCTLR_MMU_DISABLED)

// Hypervisor Configuration Register HCR_EL2

#define HCR_RW	    		        	(1 << 31)   // Execution state control for EL1 is AArch64
#define HCR_VALUE           			HCR_RW

//Secure Configuration Register (EL3) SCR_EL3

#define SCR_RESERVED	    		    (3 << 4)    // reserved 1
#define SCR_RW			                (1 << 10)   // the next lower level is AArch64
#define SCR_NS				            (1 << 0)    // indicates that Exception levels lower than EL3 are in Non-secure state
#define SCR_VALUE	    	    	    (SCR_RESERVED | SCR_RW | SCR_NS)

 // Saved Program Status Register (EL3) SPSR_EL3

#define SPSR_MASK_ALL 		        	(7 << 6)    // mask SError interrupt, IRQ Interrupt and FIQ interrupt
#define SPSR_EL1h           			(5 << 0)    // use the dedicated EL1 stack pointer
#define SPSR_VALUE			            (SPSR_MASK_ALL | SPSR_EL1h)