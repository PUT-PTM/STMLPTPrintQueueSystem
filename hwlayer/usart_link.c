#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_rcc.h"
#include "usart_link.h"

void usart_configure()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3); // Tx Line
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3); // Rx Line

	GPIO_InitTypeDef txrx_lines;
	txrx_lines.GPIO_OType = GPIO_OType_PP;
	txrx_lines.GPIO_PuPd = GPIO_PuPd_UP;
	txrx_lines.GPIO_Mode = GPIO_Mode_AF;
	txrx_lines.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	txrx_lines.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &txrx_lines);

	USART_InitTypeDef usart;
	usart.USART_BaudRate = 9600;
	usart.USART_WordLength = USART_WordLength_8b;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &usart);
	USART_Cmd(USART3, ENABLE);
}

void send_char(char c)
{
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	USART_SendData(USART3, c);
}

void send_string(const char* s)
{
	while(*s) send_char(*s++);
}
