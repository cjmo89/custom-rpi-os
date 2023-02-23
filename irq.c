#include "irq.h"
#include "uart.h"

char entry_error_messages[16][32] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32"	
};

void show_invalid_entry_message(uint32_t type, uint64_t esr, uint64_t address) {
    uart_send_string("Invalid Exception ");
    uart_send_string(entry_error_messages[type]);
    uart_send_string("\nESR: ");
    uart_send_int(esr);
    uart_send_string("\nAt address: ");
    uart_send_int(address);
}

void enable_interrupt_controller() {
        *(uint32_t*) IRQ0_ENABLE_0 = AUX_IRQ;
}

void handle_irq() {
    uint32_t irq = *(uint32_t*) IRQ0_PENDING_0;
    while(irq) {
        if (irq & AUX_IRQ) {
            irq &= ~AUX_IRQ;
            while((*(uint32_t*) AUX_MU_IIR_REG) & 4) {
                uart_send_string("UART Interrupt: ");
                uart_send(uart_recv());
                uart_send_string("\n");
            }
        }
    }
}