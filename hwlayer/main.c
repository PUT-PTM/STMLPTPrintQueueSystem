#include "stm32f4xx_rcc.h"
#include "usart_link.h"

int main(void)
{
	SystemInit();

	usart_configure();

	unsigned int i;
    while(1)
    {
    	send_string("Test message");
    	for(i=0;i<10000000;i++);
    }
}
