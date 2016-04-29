#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "led_indicators.h"

void discovery_led_configure()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef diodes;
	diodes.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	diodes.GPIO_Mode = GPIO_Mode_OUT;
	diodes.GPIO_OType = GPIO_OType_PP;
	diodes.GPIO_Speed = GPIO_Speed_100MHz;
	diodes.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &diodes);
}

void set_red_led_on()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_14);
}

void set_red_led_off()
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_14);
}

void set_green_led_on()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
}

void set_green_led_off()
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
}

void set_orange_led_on()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_13);
}

void set_orange_led_off()
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_13);
}

void set_blue_led_on()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_15);
}

void set_blue_led_off()
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_15);
}
