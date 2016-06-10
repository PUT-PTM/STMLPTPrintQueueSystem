#include "usart_protocol.h"
#include "led_indicators.h"
#include "usart_link.h"
#include "tm_stm32f4_delay/tm_stm32f4_delay.h"
#include <string.h>

extern volatile RcvBuff uart_buffer;
extern volatile error_counter;
extern volatile unexpected_error_counter;
char *error;
uint8_t establish_connection()
{
	for(int i=0;i<3;i++){

//	send_string_2("establish_connection");
	send_string("AT+CWJAP?");
	set_blue_led_on();
	Delay(5000);
	if(ReceivedNewLine()){

//		send_string_2("<log>:");
//		send_string_2(uart_buffer.buffer);
//		send_string_2("</log>");

		if(ReceivedNewLine()){
			if(strstr(uart_buffer.buffer, "OK")) {
				set_green_led_on();
				set_blue_led_on();
				set_orange_led_off();
				set_red_led_off();
//				send_string_2("<log>OK:");
//				send_string_2(uart_buffer.buffer);
//				send_string_2("</log>");
				RcvBuffReset(&uart_buffer);
				return 1;
			}
			else if(strstr(uart_buffer.buffer, "ERROR")){
				set_green_led_off();
				set_blue_led_off();
				set_orange_led_off();
				set_red_led_on();
//				send_string_2( strcat("<log>Error:",error_counter++) );
//				send_string_2(uart_buffer.buffer);
//				send_string_2("</log>");
				Delay(500);
				return 0;
			}
			else{
				set_green_led_off();
				set_blue_led_off();
				set_orange_led_on();
				set_red_led_on();
//				send_string_2(strcat( "<log>Unexpected Error:", unexpected_error_counter++));
//				send_string_2(uart_buffer.buffer);
//				send_string_2("</log>");
				Delay(5000);
				return 0;

			}

		}//isready , receive message


	}//isready , send message
}
}//for 3 times




//	for(int i=0; i<2;i++){
//		send_string("AT+CWJAP?");
//
//	//set_green_led_on();
//	while(!uart_buffer.ready) {}
//	RcvBuffReset(&uart_buffer);
//
//	if(!strstr(uart_buffer.buffer, "OK")) {
//		set_green_led_off();
//		set_blue_led_on();
//
//		return 1;
//	}
//	else if(!strcmp(uart_buffer.buffer, "ERROR")){
//
//		set_red_led_on();
//
//	}
//	else {
//		Delayms(500);
//		send_string("AT+RST");
//
//		//connection_error("Can't check connection to ESP8266 WIFI with command \"AT\" ");
//		//set_blue_led_off();
//		set_red_led_on();
//		set_orange_led_on();
//
//	}
//	}
//	//connection_error("Can't check connection to ESP8266 WIFI with command \"AT\" ");
//	set_blue_led_off();
//	set_red_led_on();
//	return 0;

