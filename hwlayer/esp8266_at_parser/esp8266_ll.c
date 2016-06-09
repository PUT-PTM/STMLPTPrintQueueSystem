/**	
   ----------------------------------------------------------------------
    Copyright (c) 2016 Tilen Majerle

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge,
    publish, distribute, sublicense, and/or sell copies of the Software, 
    and to permit persons to whom the Software is furnished to do so, 
    subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
    AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
   ----------------------------------------------------------------------
 */
#include "esp8266_ll.h"

/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
/*                                                                        */
/*    Edit file name to esp8266_ll.c and edit values for your platform    */
/*                                                                        */
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

uint8_t ESP8266_LL_USARTInit(uint32_t baudrate) {
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
	usart.USART_BaudRate = baudrate;
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
    
	return 0;
}

uint8_t ESP8266_LL_USARTSend(uint8_t* data, uint16_t count) {
	int i;
    for (i = 0; i < count; i++) {
        while (USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
        USART_SendData(UART4, data[i]);
    }

	return 0;
}

/* USART receive interrupt handler */
void UART4_IRQHandler(void) {
	uint8_t ch;
    
    if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
        ch = UART4->DR;
        ESP8266_DataReceived(&ch, 1);
    }
}
