#include "usart_protocol.h"
#include "led_indicators.h"
#include "usart_link.h"
#include <string.h>

extern volatile RcvBuff uart_buffer;

uint8_t establish_connection()
{
	send_string("HELLO STM");
	while(!uart_buffer.ready) {}
	RcvBuffReset(&uart_buffer);
	if(!strcmp(uart_buffer.buffer, "HELLO PI")) {
		return 1;
	} else {
		return 0;
	}
}
