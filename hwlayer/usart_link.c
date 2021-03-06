#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "stm32f4xx_exti.h"
#include "usart_link.h"
#include "led_indicators.h"
#include "tm_stm32f4_delay.h"

extern volatile RcvBuff uart_buffer;

void usart_configure()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	// GPIO Pins configuration
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4); // Tx Line
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4); // Rx Line

	GPIO_InitTypeDef txrx_lines;
	txrx_lines.GPIO_OType = GPIO_OType_PP;
	txrx_lines.GPIO_PuPd = GPIO_PuPd_UP;
	txrx_lines.GPIO_Mode = GPIO_Mode_AF;
	txrx_lines.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	txrx_lines.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &txrx_lines);

	// UART parameters setup
	USART_InitTypeDef usart;
	usart.USART_BaudRate =9600;
	usart.USART_WordLength = USART_WordLength_8b;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(UART4, &usart);
	USART_Cmd(UART4, ENABLE);

	// Receiving interrupt configuration
	NVIC_InitTypeDef usart_nvic;
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	usart_nvic.NVIC_IRQChannel = UART4_IRQn;
	usart_nvic.NVIC_IRQChannelPreemptionPriority = 0;
	usart_nvic.NVIC_IRQChannelSubPriority = 0;
	usart_nvic.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&usart_nvic);
	NVIC_EnableIRQ(UART4_IRQn);

	RcvBuffReset(&uart_buffer);
}

void usart2_configure()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	// GPIO Pins configuration
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2); // Tx Line
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2); // Rx Line

	GPIO_InitTypeDef txrx_lines;
	txrx_lines.GPIO_OType = GPIO_OType_PP;
	txrx_lines.GPIO_PuPd = GPIO_PuPd_UP;
	txrx_lines.GPIO_Mode = GPIO_Mode_AF;
	txrx_lines.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	txrx_lines.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &txrx_lines);

	// UART parameters setup
	USART_InitTypeDef usart;
	usart.USART_BaudRate =9600;
	usart.USART_WordLength = USART_WordLength_8b;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &usart);
	USART_Cmd(USART2, ENABLE);
}

void send_char(char c)
{
	while (USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	USART_SendData(UART4, c);
}

void send_char_2(char c)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2, c);
}

void send_string(const char* s)
{
	while(*s) send_char(*s++);
	send_char('\r');
	send_char('\n');
}
void send_string_2(const char* s)
{
	while(*s) send_char_2(*s++);
	send_char_2('\r');
	send_char_2('\n');
}
void RcvBuffReset(volatile RcvBuff* buffer)
{

	buffer->current_pos = 0;
	for(int i=0; i<255; i++){
	buffer->buffer[i] = 0;
	}
	//set ready , new data can be write to it
	buffer->ready = 1;
	//false. after reset we have no new line
	buffer->newline = 1;
}

void UART4_IRQHandler(void)
{

	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		if(UART4->DR == '\n'){
			uart_buffer.newline = 1;
		}else
		{
			uart_buffer.newline = 0;
		}
		uart_buffer.buffer[uart_buffer.current_pos++] = UART4->DR;
	}
}


//uint8_t isComandEnd(){
//	//send_char_2(uart_buffer.buffer[uart_buffer.current_pos]);
//	//jesli czekamy 120ms od ostatniego znaku z esp
//	if(TM_DELAY_Time() > 1200){
//		set_red_led_off();
//		set_green_led_off();
//		if(uart_buffer.buffer[uart_buffer.current_pos] == '\n'){
//			uart_buffer.newline = 1;
//			set_green_led_on();
//			return 1;
//		}else {
//			uart_buffer.newline = 0;
//			set_red_led_on();
//			set_green_led_off();
//		}
//	}
//return 0;
//}

//		// receiving data, so we can't write to it
//		if(uart_buffer.ready == 1) {
//		send_char_2(UART4->DR);
////send_string_2("find <cr><nw>");
////send_string_2(uart_buffer.buffer);
//
//			//check if we get caret return & end line symbols
//			if( UART4->DR == '\n' && uart_buffer.buffer[uart_buffer.current_pos-1] == '\r') {
//			//	uart_buffer.buffer[uart_buffer.current_pos-1] = '\0';
//				//zero last char , also decrease current position counter
//			//	uart_buffer.buffer[uart_buffer.current_pos--] = '\0';
//				//set buffer ready to true,we received end line , so we can send data now
////send_string_2("found  <cr><nw>");
////send_string_2(uart_buffer.buffer);
//
//				//uart_buffer.ready = 0;
//				uart_buffer.newline = 1;
//			}else {
//				uart_buffer.buffer[uart_buffer.current_pos++] = UART4->DR;
//				//set ready to false, we still waiting for more data
//				//uart_buffer.ready = 1;
//				uart_buffer.newline =0;
//			}
//		}






