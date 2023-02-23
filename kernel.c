#include "uart.h"
#include "irq.h"

int get_el();

void main() {
    uart_init();
    uart_send_string("\n Booting...\n");
    irq_vector_init();
    enable_interrupt_controller();
    enable_irq();
    uart_send_string("\n\nCurrent Execution Level: ");
    uart_send_int(get_el());
    uart_send_string("\n");
    while (1) {
		  //uart_send(uart_recv());
	}
}


