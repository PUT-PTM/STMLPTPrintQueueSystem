#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "usart_link.h"

int main(void)
{
	SystemInit();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef diodes;
	diodes.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	diodes.GPIO_Mode = GPIO_Mode_OUT;
	diodes.GPIO_OType = GPIO_OType_PP;
	diodes.GPIO_Speed = GPIO_Speed_100MHz;
	diodes.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &diodes);

	usart_configure();

	send_string("HELLO STM\n");

    while(1)
    {

    }
}

