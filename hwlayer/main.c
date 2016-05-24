#include "stm32f4xx_rcc.h"
#include "usart_link.h"
#include "usart_protocol.h"
#include "led_indicators.h"
#include "lpt_driver.h"
//#include "tm_stm32f4_delay/tm_stm32f4_delay.h"
extern volatile RcvBuff uart_buffer;

int main(void)
{
	SystemInit();
	TM_DELAY_Init();
	usart_configure();
	discovery_led_configure();

	lpt_setup();
	//lpt_loop();

	uint8_t ok = 0;
	while(ok==0){
	if(establish_connection()) {
		ok = 1;
		set_green_led_on();
		//byte *msg = &uart_buffer.buffer;
			resetPrinter();
			printMessage(uart_buffer.buffer);
			resetPrinter();
	} else {
		set_red_led_on();
		//byte *msg = &uart_buffer.buffer;
		resetPrinter();
		printMessage(uart_buffer.buffer);
		resetPrinter();
	}

	}

	while(ok)
	{
		if(uart_buffer.ready == 1) {
			send_string(uart_buffer.buffer);
			RcvBuffReset(&uart_buffer);
		}
	}
}
