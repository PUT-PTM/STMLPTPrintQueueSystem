#include "stm32f4xx_rcc.h"
#include "usart_link.h"
#include "usart_protocol.h"
#include "led_indicators.h"
#include "lpt_driver.h"
#include "tm_stm32f4_delay/tm_stm32f4_delay.h"
#include "mytimer.h"
extern volatile RcvBuff uart_buffer;

volatile char *error;
volatile int error_counter=0;
volatile int unexpected_error_counter=0;
volatile uint8_t connected = 0;
void TIM3_IRQHandler(void);
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
for(int i=0;i<5;i++)
	if(!connected){
		send_string("AT+CWJAP?");
		set_orange_led_on();
		while(uart_buffer.newline == 0){set_blue_led_on();}
			if(strstr(uart_buffer.buffer, "OK")) {
						set_green_led_on();
						set_blue_led_off();
						set_orange_led_off();
						set_red_led_off();
						send_string_2("<log>OK:");
						send_string_2(uart_buffer.buffer);
						send_string_2("</log>");

						RcvBuffReset(&uart_buffer);
						connected = 1;
			}else{
				connected = 0;
			}


	}
}
void TIM3_IRQHandler(void)
{
             if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
             {
 // miejsce na kod wywo³ywany w momencie wyst¹pienia przerwania
            	 isComandEnd();
					 // wyzerowanie flagi wyzwolonego przerwania
			 TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			  }
}

	//while(!connected){
//
//		if(establish_connection() == 1 && connected == 0){
//			connected = 1;
//			set_green_led_on();
//		//	send_string_2("Connected");
//
//
//
//			//byte *msg = &uart_buffer.buffer;
////			resetPrinter();
////			printMessage(uart_buffer.buffer);
////			resetPrinter();
//		}else if(!connected) {
//			set_red_led_on();
//			set_green_led_on();
//		//	send_string_2("Can't establish connection");
//			//byte *msg = &uart_buffer.buffer;
//	//		resetPrinter();
//	//		printMessage(uart_buffer.buffer);
//	//		resetPrinter();
//		}//end if(establish_connection)
//		//Delayms(500);
//	//}//end for( 3 times test connection)
//
//	if(connected == 1){
//	RcvBuffReset(&uart_buffer);
//	//send_string_2("if connected , send new request");
//	send_string("AT+CIPSTART=\"TCP\",\"192.168.0.110\",8000");
//	//Delay(98);
//	//send_string_2(uart_buffer.buffer);
//	if(ReceivedNewLine()){
//		RcvBuffReset(&uart_buffer);
//
//			//char re_len[6] ;
//			//itoa(strlen(http_request), re_len, 10);
//			char  cipsend[400] = "AT+CIPSEND=69";
//			//strcat( cipsend, re_len);
//			//send_string_2("cisend");
//			send_string(cipsend);
//
//			//Delayms(120);
//	}
//	if(ReceivedNewLine()){
//		while(!strstr(uart_buffer.buffer,">")){}
//		RcvBuffReset(&uart_buffer);
//		//send_string_2("juz nie czekam na  >");
//	//	Delayms(120);
//			send_string_2("http request");
//			char * http_request = "GET http://192.168.0.110:8000/api/camount HTTP/1.0 HOST: 192.168.0.110 Accept: */*";
//		send_string(http_request);
//				//Delayms(120);
//
//				//send_string_2(uart_buffer.buffer);
//		}
//
//
//	Delayms(50000);
//				send_string("AT+CIPCLOSE");
//				//send_string_2(uart_buffer.buffer);
//				RcvBuffReset(&uart_buffer);
//
//	}

	//}//end_while(!ok)

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

