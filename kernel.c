#include "uart.h"

int get_el();

void print_el(int el) {
  char s[3];
    s[0] = el + 48;   // +48 to convert the digit to ASCII
    s[1] = '\n';
    s[2] = '\0';
    uart_send_string(s);
}
void main() {
    uart_init();
    uart_send_string("\n\nCurrent Execution Level: ");
    print_el(get_el());
    while (1) {
		  uart_send(uart_recv());
	}
}

