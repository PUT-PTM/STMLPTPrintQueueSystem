#include "stm32f4xx_rcc.h"
#include "usart_link.h"
#include "usart_protocol.h"
#include "led_indicators.h"

extern volatile RcvBuff uart_buffer;

int main(void)
{
	SystemInit();

	usart_configure();
	discovery_led_configure();

	uint8_t ok = 0;
	if(establish_connection()) {
		ok = 1;
		set_green_led_on();
	} else {
		set_red_led_on();
	}

	while(ok)
	{
		if(uart_buffer.ready == 1) {
			send_string(uart_buffer.buffer);
			RcvBuffReset(&uart_buffer);
		}
	}
}
