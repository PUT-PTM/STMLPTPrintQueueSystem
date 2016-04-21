#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

int main(void)
{
	SystemInit();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef diode;
	diode.GPIO_Pin = GPIO_Pin_12;
	diode.GPIO_Mode = GPIO_Mode_OUT;
	diode.GPIO_OType = GPIO_OType_PP;
	diode.GPIO_Speed = GPIO_Speed_100MHz;
	diode.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &diode);

	unsigned int i;

    while(1)
    {
    	GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
    	for(i=0;i<10000000;i++);
    }
}
