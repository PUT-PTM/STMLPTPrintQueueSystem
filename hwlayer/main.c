#include "stm32f4xx_rcc.h"
#include "led_indicators.h"
#include "lpt_driver.h"
#include "tm_stm32f4_delay/tm_stm32f4_delay.h"
#include "esp8266_at_parser/esp8266.h"


ESP8266_Result_t result;
int main(void)
{
	SystemInit();
	TM_DELAY_Init();
	discovery_led_configure();
	set_orange_led_on();
	ESP8266_t esp;

	result = ESP8266_Init(&esp, 9600);
	result = ESP8266_StartClientConnectionTCP(&esp,	"ubuntu.local",	"192.168.0.105",80,"");
	ESP8266_Connection_t con = esp.Connection[0];
	con.Data="GET \/ HTTP\/1.0 HOST: 192.168.0.108 Connection: keep-alive Accept: *\/*";
	result = ESP8266_RequestSendData(&esp, &con);

	if (result == ESP_OK) {
		set_green_led_on();
	} else {
		set_red_led_on();
	}

}
