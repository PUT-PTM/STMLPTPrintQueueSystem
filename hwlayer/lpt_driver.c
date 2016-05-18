#include "lpt_driver.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"


#include <stdio.h>
#include "tm_stm32f4_delay.h"

//void Delay(int time){
//	for(int i=0; i<time*1000;i++);
//}
//
//void Delayms(int time){
//	for(int i=0; i<time*100;i++);
//}

byte startup_message[startup_num_lines][startup_charsPerLine] = {
  "This is the startup message. It prints whenever",
  "the Arduino is reset.",
};


byte message[num_lines][charsPerLine] = {
  "    ",   // blank line
  "This is the normal message. It prints whenever",
  "you connect pin 14 (analog 0) to GND.",
  "  ",  // blank line
  "------------------------------------------------------------------------------",   // a spiffy line
  "1) More message content",
  "  ",
  "II) you can have up to about 80 chars per line ",
  "  ",
  "------------------------------------------------------------------------------",
};

// parallel port pin# = arduino pin#
//const int nStrobe = 2;
//const int data_0 = 3;
//const int data_1 = 4;
//const int data_2 = 5;
//const int data_3 = 6;
//const int data_4 = 7;
//const int data_5 = 8;
//const int data_6 = 9;
//const int data_7 = 10;
//const int nAck = 11;
//const int busy = 12;


void lpt_configure(){
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);



		// GPIO Pins configuration


//data pins
		GPIO_InitTypeDef lpt_data_lines;
		lpt_data_lines.GPIO_OType = GPIO_OType_PP;
		lpt_data_lines.GPIO_PuPd = GPIO_PuPd_DOWN;
		lpt_data_lines.GPIO_Mode = GPIO_Mode_OUT;
		lpt_data_lines.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
		lpt_data_lines.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &lpt_data_lines);

//ack and busy input
		GPIO_InitTypeDef lpt_states_lines;
				lpt_states_lines.GPIO_OType = GPIO_OType_PP;
				lpt_states_lines.GPIO_PuPd = GPIO_PuPd_UP;
				lpt_states_lines.GPIO_Mode = GPIO_Mode_IN;
				lpt_states_lines.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
				lpt_states_lines.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOE, &lpt_states_lines);

//strobe pin
		GPIO_InitTypeDef lpt_strobe_pin;
				lpt_strobe_pin.GPIO_OType = GPIO_OType_PP;
				lpt_strobe_pin.GPIO_PuPd = GPIO_PuPd_UP;
				lpt_strobe_pin.GPIO_Mode = GPIO_Mode_OUT;
				lpt_strobe_pin.GPIO_Pin = GPIO_Pin_10;
				lpt_strobe_pin.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOD, &lpt_strobe_pin);

}


void lpt_setup() {



 // pinMode(nStrobe, OUTPUT);      // is active LOW
//  digitalWrite(nStrobe, HIGH);   // set HIGH
//  pinMode(data_0, OUTPUT);
//  pinMode(data_1, OUTPUT);
//  pinMode(data_2, OUTPUT);
//  pinMode(data_3, OUTPUT);
//  pinMode(data_4, OUTPUT);
//  pinMode(data_5, OUTPUT);
//  pinMode(data_6, OUTPUT);
//  pinMode(data_7, OUTPUT);

//  pinMode(nAck, INPUT);     // is active LOW
//  pinMode(busy, INPUT);

//  pinMode(13, OUTPUT);
//  pinMode(14, INPUT);   // analog pin 0 on duemilanove and uno
//  digitalWrite(14, HIGH); // enable pull-up


  lpt_configure();
  Delayms(1000);

  resetPrinter();

  printStartupMessage();

  resetPrinter();

  //Serial.println("Delayms for 5 sec");
  Delayms(5000);

  //Serial.println("Startup complete");
}

void lpt_loop() {


  resetPrinter();

  printMessage();

  resetPrinter();
}
int pin0 =0;
int pin1 =0;
int pin2 =0;
int pin3 =0;
int pin4 =0;
int pin5 =0;
int pin6 =0;
int pin7 =0;
int lpt_data =0;

void print_states(){
	 pin0 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
	 pin1 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
	 pin2 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
	 pin3 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
	 pin4 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
	 pin5 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
	 pin6 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
	 pin7 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
	 lpt_data = GPIO_ReadOutputData(GPIOA);

}
uint16_t check_state(uint16_t pin){
	uint8_t state = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9);
	if(state == 0){
	return 0;
	}else return 1;
}
void printByte(byte inByte) {
  while(check_state(GPIO_Pin_9) == 1) {
    // wait for busy to go low
  }



  GPIO_Write(GPIOE, inByte);

  GPIO_SetBits(GPIOE,GPIO_Pin_10);
  //digitalWrite(nStrobe, LOW);       // strobe nStrobe to input data bits

  Delay(strobeWait);
 // digitalWrite(nStrobe, HIGH);
  GPIO_ResetBits(GPIOE,GPIO_Pin_10);

  while(check_state(GPIO_Pin_9) == 1) {
    // wait for busy line to go low
  }
}

void resetPrinter() {
  //Serial.println("Reseting printer...");
  printByte(27); // reset printer
  printByte('E');
  //Serial.println("Printer Reset");
}

void printMessage() {
  //digitalWrite(13, HIGH);
  for(int line = 0; line < num_lines; line++) {
    for(int cursorPosition = 0; cursorPosition < charsPerLine; cursorPosition++) {
      byte character = message[line][cursorPosition];
      printByte(character);
      Delayms(1);
    }
    printByte(10); // new line
    printByte(13); // carriage return
  }
  //digitalWrite(13,LOW);
}

void printStartupMessage() {
  //Serial.println("Print start-up mssage");
 // digitalWrite(13, HIGH);
  for(int line = 0; line < startup_num_lines; line++) {
    for(int cursorPosition = 0; cursorPosition < startup_charsPerLine; cursorPosition++) {
      byte character = startup_message[line][cursorPosition];
      printByte(character);
            Delayms(1);
    }
    printByte(10); // new line
    printByte(13); // carriage return
    //Serial.print("Line ");
    //Serial.print(line);
    //Serial.println(" printed.");
  }
  //Serial.println("Startup message printed");
 // digitalWrite(13,LOW);
}


