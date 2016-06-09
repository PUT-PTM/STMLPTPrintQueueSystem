#include "stm32f4xx_rcc.h"
#include "led_indicators.h"
#include "lpt_driver.h"
#include "tm_stm32f4_delay/tm_stm32f4_delay.h"
#include "esp8266_at_parser/esp8266.h"



int main(void)
{
	SystemInit();
	TM_DELAY_Init();
	discovery_led_configure();

	ESP8266_t esp;
	ESP8266_Result_t result;
	result = ESP8266_Init(&esp, 9600);
	if (result == ESP_OK) {
		set_green_led_on();
	} else {
		set_red_led_on();
	}
}
