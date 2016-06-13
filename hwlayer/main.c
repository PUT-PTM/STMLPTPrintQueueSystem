#include "stm32f4xx_rcc.h"
#include "usart_link.h"
#include "usart_protocol.h"
#include "led_indicators.h"
#include "lpt_driver.h"
#include "tm_stm32f4_delay/tm_stm32f4_delay.h"

extern volatile RcvBuff uart_buffer;
volatile enum Flag{
	start,//just started
	connecting,//waiting for answer is esp connected to wifi network
	connected,//esp is connected to wifi network
	linking,//waiting for answer is esp connected to server
	linked,//esp is linked to http server
	declare_http_request,//declaration of new reqest was send, waitng for ">" char
	send_http_request,//
	receive_http_data,//
	disconnecting,//
	disconected//
};
volatile uint8_t link_error = 0;
//TM_DELAY_Timer_t* timer = TM_DELAY_TimerCreate(20,1,1);
//TM_Delay_Timer_Start(timer);

int main(void)
{
	SystemInit();
	TM_DELAY_Init();
	usart_configure();
	usart2_configure();
	discovery_led_configure();
	send_string_2("--start--");
//	lpt_setup();
//	lpt_loop();

enum Flag uart_flag = start;
for(;;){


	//check if new line is on end
	if(uart_buffer.newline == 1){
		switch(uart_flag){
		case start:{
			RcvBuffReset(&uart_buffer);
			if(uart_buffer.ready == 1){
			send_string("AT+CWJAP?");
			uart_flag = connecting;
			}
		}
		break;
		case connecting:{
			if(strstr(uart_buffer.buffer, "OK")){
				uart_flag = connected;
				char temp[255];
				strcpy(temp,"<log>OK: ");
				strcat(temp, uart_buffer.buffer);
				strcat(temp,"</log>");
				send_string_2(temp);
				RcvBuffReset(&uart_buffer);
			}
		}
		break;
		case connected:{
			if(uart_buffer.ready == 1){
				send_string("AT+CIPSTART=\"TCP\",\"192.168.0.105\",80");
				uart_flag = linking;
				char temp[255];
				strcpy(temp,"...Linking");
				send_string_2(temp);
			}
		}
		break;
		case linking:{
			if(strstr(uart_buffer.buffer, "ALREAY CONNECT") || strstr(uart_buffer.buffer, "OK\r\nLinked") ){
			uart_flag = linked;
			set_green_led_on();
			char temp[255];
			strcpy(temp,"<log>Linked: ");
			strcat(temp, uart_buffer.buffer);
			strcat(temp,"</log>");
			send_string_2(temp);
			RcvBuffReset(&uart_buffer);
			}else if(link_error > 3){
				char temp[255];
				strcpy(temp,"<log>Not Linked, restart: ");
				strcat(temp, uart_buffer.buffer);
				strcat(temp,"</log>");
				send_string_2(temp);
				RcvBuffReset(&uart_buffer);
				uart_flag = start;
			}
			else{
				link_error++;
				set_green_led_off();
				set_red_led_on();
			}
		}
		break;
		case linked:{
			char temp[255];
			strcpy(temp,"<log>Declare http request: ");
			strcat(temp, uart_buffer.buffer);
			strcat(temp,"</log>");
			send_string_2(temp);
			RcvBuffReset(&uart_buffer);
			if(uart_buffer.ready == 1){
				send_string("AT+CIPSEND=71");
				uart_flag = declare_http_request;
				set_blue_led_on();
			}
		}
		break;
		case declare_http_request:
			if(strstr(uart_buffer.buffer, ">")){
				set_blue_led_off();
				//send_string_2(uart_buffer.buffer);
				send_string("GET / HTTP/1.0 Host: 192.168.0.105 Connection: keep-alive Accept: */*\n\n");
				uart_flag = send_http_request;
				RcvBuffReset(&uart_buffer);
			}
		break;
		case send_http_request:{
				//	send_string_2(uart_buffer.buffer);
					if(strstr(uart_buffer.buffer, "SEND OK")){
						RcvBuffReset(&uart_buffer);
								set_blue_led_on();
		//						char temp[255];
		//									//strcpy(temp,"<http>\n");
		//									strcat(temp, uart_buffer.buffer);
		//									//strcat(temp,"</http>");
		//									send_string_2(uart_buffer.buffer);
											uart_flag = receive_http_data;

							}

						}
		break;
		case receive_http_data:{
			if(strstr(uart_buffer.buffer, "Content-Type: text/html")){
				send_string_2("<http>\n");
			}

		}
		break;
		case disconnecting:

		break;
		case disconected:

		break;
		default:
			send_string_2("<log>default switch</log>");
			char temp[255];
										//strcpy(temp,"<http>\n");
										strcat(temp, uart_buffer.buffer);
										//strcat(temp,"</http>");
										send_string_2(temp);
			Delayms(500);
		break;
		}

	}else if(strstr(uart_buffer.buffer, "> ") && uart_flag == declare_http_request){
		uart_buffer.newline = 1;
	}
	else if(strstr(uart_buffer.buffer, "+IPD")  && uart_flag == receive_http_data){
		uart_buffer.newline = 1;
	}
	else{

		//wait 200ms
		Delayms(20);
		//send_string_2("--delay--");
	}
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

