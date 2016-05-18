#include "stm32f4xx_gpio.h"

typedef uint8_t byte;

// this is the max # of chars per line
#define startup_charsPerLine 80
#define startup_num_lines  2
#define charsPerLine  80
#define num_lines 10
#define strobeWait 2

byte startup_message[startup_num_lines][startup_charsPerLine];
byte message[num_lines][charsPerLine];
byte inbyte = 0;
GPIO_InitTypeDef lpt_data_lines;
GPIO_InitTypeDef lpt_states_lines;//ack and busy
GPIO_InitTypeDef lpt_strobe_pin;

void Delay(int time);
void Delayms(int time);
void lpt_configure();
void lpt_setup();
uint16_t check_state(uint16_t pin);
void printByte(byte inByte);
void resetPrinter();
void printMessage();
void printStartupMessage();

