#include "usart_link.h"
#include "led_indicators.h"

int main(void)
{
	SystemInit();

	usart_configure();
	discovery_led_configure();

	send_string("HELLO STM\n");

    while(1)
    {

    }
}

