#include "usart_link.h"
#include "led_indicators.h"

extern volatile RcvBuff uart_buffer;

int main(void)
{
	SystemInit();

	usart_configure();
	discovery_led_configure();

	send_string("HELLO STM");

    while(1)
    {
    	if(uart_buffer.ready == 1) {
    		RcvBuffReset(&uart_buffer);
    		send_string(uart_buffer.buffer);
    	}
    }
}

