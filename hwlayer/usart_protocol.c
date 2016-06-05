#include "usart_protocol.h"
#include "led_indicators.h"
#include "usart_link.h"
#include "tm_stm32f4_delay/tm_stm32f4_delay.h"
#include <string.h>

extern volatile RcvBuff uart_buffer;
char *error;
uint8_t establish_connection()
{

	for(int i=0; i<2;i++){
		send_string("AT");

		set_green_led_on();
			Delayms(50);

	while(!uart_buffer.ready) {}
	RcvBuffReset(&uart_buffer);
	set_green_led_off();
	if(!strstr(uart_buffer.buffer, "\r\nOK")) {
		set_blue_led_on(); //blue led will tell - wifi on and connected
		set_green_led_on();
		return 1;
	}
	else if(!strcmp(uart_buffer.buffer, "ERROR")){
		set_blue_led_on(); //blue led will tell - wifi on and connected
		set_red_led_on();

	}
	else {
		Delayms(5000);
		send_string("AT+RST");

		//connection_error("Can't check connection to ESP8266 WIFI with command \"AT\" ");
		set_blue_led_off();
		set_red_led_on();
		set_orange_led_on();

	}
	}
	//connection_error("Can't check connection to ESP8266 WIFI with command \"AT\" ");
	set_blue_led_off();
	set_red_led_on();
	return 0;
}
