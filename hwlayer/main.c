#include "stm32f4xx_rcc.h"
#include "usart_link.h"
#include "usart_protocol.h"
#include "led_indicators.h"
#include "lpt_driver.h"
#include "tm_stm32f4_delay/tm_stm32f4_delay.h"
extern volatile RcvBuff uart_buffer;

char *error;
int error_counter=0;
int unexpected_error_counter=0;
int main(void)
{
	SystemInit();
	TM_DELAY_Init();
	usart_configure();
	usart2_configure();
	discovery_led_configure();
	send_string_2("--start--");
//	lpt_setup();
	//lpt_loop();

	uint8_t ok = 0;
	while(!ok){
	for(int i=0;i<3;i++){
		if(establish_connection()) {
			ok = 1;
			set_green_led_on();


			//byte *msg = &uart_buffer.buffer;
//			resetPrinter();
//			printMessage(uart_buffer.buffer);
//			resetPrinter();
		} else {
			set_red_led_on();
			//set_green_led_on();
			//byte *msg = &uart_buffer.buffer;
	//		resetPrinter();
	//		printMessage(uart_buffer.buffer);
	//		resetPrinter();
		}//end if(establish_connection)

	}//end for( 3 times test connection)
	//Delayms(50000);

	}//end_while(!ok)

//	while(ok)
//	{
//		set_orange_led_off();
//		if(uart_buffer.ready == 1) {
//			RcvBuffReset(&uart_buffer);
//			send_string("AT+CIPSTART=?");
//			//Delay(500);
//			if(uart_buffer.ready == 1) {
//			if(strstr(uart_buffer.buffer, "OK")) {
//				RcvBuffReset(&uart_buffer);
//				if(uart_buffer.ready == 1) {
//		//					send_string("AT+CIPSTART?");
//							send_string("AT+CIPSTART=\"TCP\",\"192.168.0.105\",80");
//							RcvBuffReset(&uart_buffer);
//							Delay(5000);
//
//							if(uart_buffer.ready == 1) {
//								if(!strstr(uart_buffer.buffer, "LINKED")) {
//														send_string("AT+CIPSEND=0,69\n> GET \/ HTTP\/1.0 HOST: 192.168.0.105 Connection: keep-alive Accept: *\/*");
//
//														set_orange_led_on();
//														RcvBuffReset(&uart_buffer);
//														Delay(5000);
//											}
//							}
//
//
//				}
//			}
//			}
//		}
//
////		if(uart_buffer.ready == 1) {
////			Delay(5000);
////			send_string("AT+CIPCLOSE");
////			RcvBuffReset(&uart_buffer);
////
////		}
//
//		Delayms(5000);
//		//if(uart_buffer.ready == 1) {
//			//send_string(uart_buffer.buffer);
////			send_string("AT+CIPSTART=0,\"TCP\",\"192.168.0.108\",80");
////			send_string('AT+CIPSEND=0,69');
////			send_string('GET \/ HTTP\/1.0 HOST: 192.168.0.108 Connection: keep-alive Accept: *\/*');
////			RcvBuffReset(&uart_buffer);
//			//Delay(50);
////			set_orange_led_on();
//		//}
//	}//while
}
