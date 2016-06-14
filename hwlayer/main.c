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
int sizeof_http_request(char *buffer);
int sizeof_http_content(char *buffer);
char* get_http_content(char *buffer);
char* get_queue_number(char *content);
char *prepare_ticket(char *queue_number);
volatile uint8_t link_error = 0;
//TM_DELAY_Timer_t* timer = TM_DELAY_TimerCreate(20,1,1);
//TM_Delay_Timer_Start(timer);
volatile char category[2];
int main(void)
{
	SystemInit();
	TM_DELAY_Init();
	usart_configure();
	usart2_configure();
	discovery_led_configure();
	send_string_2("--start--");
	lpt_setup();
//	lpt_loop();

enum Flag uart_flag = start;
strcpy(category , "01");
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
				//rest
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
				send_string("AT+CIPSEND=106");
				uart_flag = declare_http_request;
				set_blue_led_on();
			}
		}
		break;
		case declare_http_request:
			if(strstr(uart_buffer.buffer, ">")){
				set_blue_led_off();
				send_string_2(uart_buffer.buffer);
				char request[108] = "GET http://192.168.0.105/api/number/";
				strcat(request, category);//depend on wich button wos pressed last
				strcat(request, "/ HTTP/1.0 Host: 192.168.0.105 Connection: keep-alive Accept: */*\n\n");
				//send_string("GET http://192.168.0.105/api/number/01 HTTP/1.0 Host: 192.168.0.105 Connection: keep-alive Accept: */*\n\n");
				send_string(request);
				//send_string_2(request);
				uart_flag = send_http_request;
				RcvBuffReset(&uart_buffer);
			}
		break;
		case send_http_request:{
			if(strstr(uart_buffer.buffer, "SEND OK")){
				set_blue_led_on();
				uart_flag = receive_http_data;
			}
		}
		break;
		case receive_http_data:{
			//here we receive data from server
			if( (sizeof_http_request(uart_buffer.buffer)+16) <= uart_buffer.current_pos ){

				char temp[555];
				strcpy(temp, uart_buffer.buffer);
				char *content = get_http_content(temp);
				send_string_2(content);
				char *ticket = prepare_ticket( get_queue_number(content));
				send_string_2("print ticket\n");
				send_string_2(ticket);
				printMessage(stringToByte(ticket));
				uart_flag = disconnecting;
				set_orange_led_on();
			}

		}
		break;
		case disconnecting:{
			set_blue_led_off();
		}

		break;
		case disconected:

		break;
		default:{
			char temp[255];
			strcpy(temp,"<log>default switch");
			strcat(temp, uart_buffer.buffer);
			strcat(temp,"</log>");
			send_string_2(temp);
			Delayms(500);
		}
		break;
		}
	//if last char is not a \n
	}else if(strstr(uart_buffer.buffer, "> ") && uart_flag == declare_http_request){
		uart_buffer.newline = 1;
	}
	else{
		//wait 200ms
		Delayms(20);

	}
}

}

int sizeof_http_request(char *buffer) {
	char * content_lenght = strstr(buffer, "+IPD,") + strlen("+IPD,")-1;
	char lenght[3] = ""; strncpy(lenght, content_lenght, 3);
	return atoi(lenght);
}

int sizeof_http_content(char *buffer) {
	char * content_lenght = strstr(buffer, "Content-Length: ") + strlen("Content-Length: ")-1;
	char lenght[3] = ""; strncpy(lenght, content_lenght, 3);
	return atoi(lenght);
}
char* get_http_content(char *buffer){
	char * content_ptr = strstr(buffer, "Content-Type: text/html") + strlen("Content-Type: text/html")+3;
 //	size_t content_size = sizeof_http_content(buffer);
// 	char * content;// content = (char*)malloc( content_size );
// 	strncpy(content, content_ptr, content_size+3);
// 	content[content_size] = '\n';

 	return content_ptr;
}
char* get_queue_number(char *content){
	char * content_ptr = strstr(content, "number:\"")+8;
	char queue_number[8]=""; strncpy(queue_number,content_ptr,8);
	queue_number[7]='\0';
	return (&queue_number);
}
char *prepare_ticket(char * queue_number){
	char *ticket_message;
	strcpy(ticket_message,"\r\n Bilet STMLPTPQS\r\n Twoj\tNumer\r\n\r\n\t");
	strcat(ticket_message,queue_number);
	strcat(ticket_message,"\r\nTu powinna byc godzina\r\n");
	return ticket_message;
}

