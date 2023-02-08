#include "uart.h"

void main() {
    uart_init();
    uart_send_string("Hello new world!\n");
    while (1) {
		uart_send(uart_recv());
	}
}

