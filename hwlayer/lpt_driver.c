#include "lpt_driver.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"


#include <stdio.h>
#include "tm_stm32f4_delay/tm_stm32f4_delay.h"

//void Delay(int time){
//	for(int i=0; i<time*1000000;i++);
//}
//
//void Delayms(int time){
//	for(int i=0; i<time*100000;i++);
//}

byte startup_message[startup_num_lines][startup_charsPerLine] = {
  "start",
  "OK"
};


byte std_message[num_lines][charsPerLine] = {
 "oj ktos zapomnial co chce drukowac"
};

void stringToByte(byte *inbyte, char *msg ){
	int msg_len = strlen(msg);
	int pos=0;
	//iteruje po wierszach, ustawiona na sztywno maksymalna ilosc (10) wierszy
	for(int r=0; r< num_lines; r++){
		//iteruje przez kolumny, maks 80 znakow na wiersz
		for(int c=0;c<80,pos<msg_len;c++){
			//jesli obecna pozycja nie jest znakiem nowej lini
			if(msg[pos] != '\n'){
			(&inbyte)[r][c] = msg[pos++];
			}else{
				(&inbyte)[r][c] = '\0';
			}
		}


	}


	//byte inbyte[80][msg_len];
//	for(int r=0,cur_pos = 0;r<(msg_len/40),cur_pos<msg_len;r++){
//			for(int i=r*80; i< (r*80)+79, cur_pos<msg_len;i++,cur_pos++){//dlugosc wiadomosci / 80 )*2 bo po znaku na \n
//
//				(&inbyte)[r][i]=msg[i];
//				if(msg[i] == '\n'){
//					r++;
//				}
//			}
//
//	}

	//return inbyte;
}
void lpt_configure(){
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

		// GPIO Pins configuration


//data pins
		GPIO_InitTypeDef lpt_data_lines;
		lpt_data_lines.GPIO_OType = GPIO_OType_PP;
		lpt_data_lines.GPIO_PuPd = GPIO_PuPd_DOWN;
		lpt_data_lines.GPIO_Mode = GPIO_Mode_OUT;
		lpt_data_lines.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
		lpt_data_lines.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &lpt_data_lines);

//button 1 button 2, ack input,
		GPIO_InitTypeDef lpt_ack_pin;
				lpt_states_lines.GPIO_OType = GPIO_OType_PP;
				lpt_states_lines.GPIO_PuPd = GPIO_PuPd_UP;
				lpt_states_lines.GPIO_Mode = GPIO_Mode_IN;
				lpt_states_lines.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
				lpt_states_lines.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOB, &lpt_ack_pin);
//busy pin
				GPIO_InitTypeDef lpt_busy_pin;
						lpt_states_lines.GPIO_OType = GPIO_OType_PP;
						lpt_states_lines.GPIO_PuPd = GPIO_PuPd_UP;
						lpt_states_lines.GPIO_Mode = GPIO_Mode_IN;
						lpt_states_lines.GPIO_Pin = GPIO_Pin_9;
						lpt_states_lines.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOD, &lpt_busy_pin);



//strobe
		GPIO_InitTypeDef lpt_strobe_pin;
				lpt_strobe_pin.GPIO_OType = GPIO_OType_PP;
				lpt_strobe_pin.GPIO_PuPd = GPIO_PuPd_DOWN;
				lpt_strobe_pin.GPIO_Mode = GPIO_Mode_OUT;
				lpt_strobe_pin.GPIO_Pin = GPIO_Pin_10;
				lpt_strobe_pin.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOE, &lpt_strobe_pin);

}


void lpt_setup() {



  lpt_configure();
  Delayms(1000);

  resetPrinter();

  printStartupMessage();

  resetPrinter();

  Delayms(500);


}

//void lpt_loop() {
//
//
//  resetPrinter();
//
//  printMessage();
//
//  resetPrinter();
//}
int pin0;
int pin1;
int pin2;
int pin3;
int pin4;
int pin5;
int pin6;
int pin7;
int lpt_data;
byte InByteState;
int strobeState;
int ackState;
int busyState;
void print_states(byte InByte){
	 pin0 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
	 pin1 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1);
	 pin2 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2);
	 pin3 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3);
	 pin4 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4);
	 pin5 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5);
	 pin6 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_6);
	 pin7 = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_7);
	 lpt_data = GPIO_ReadOutputData(GPIOA);
	 InByteState = InByte;

	 busyState = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8);
	 ackState = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9);

}
uint8_t busy;
uint16_t check_state(uint16_t pin){
	 busy = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);
	if(busy == 0){
	return 1;
	}else return 0;
}

void printByte(byte inByte) {
	set_orange_led_on();
  while(check_state(GPIO_Pin_9)) {
    // wait for busy to go low
	  set_orange_led_off();
  }
  set_orange_led_on();

  //write character on data pins
  GPIO_Write(GPIOA, inByte);
  //print_states(inByte);
  GPIO_SetBits(GPIOE,GPIO_Pin_10);
  //digitalWrite(nStrobe, LOW);       // strobe nStrobe to input data bits

  Delay(strobeWait);
 // digitalWrite(nStrobe, HIGH);
  GPIO_ResetBits(GPIOE,GPIO_Pin_10);

  while(check_state(GPIO_Pin_9)) {
    // wait for busy line to go low
	  set_orange_led_off();
  }
  set_orange_led_on();
}

void resetPrinter() {
  //Serial.println("Reseting printer...");
  printByte(27); // reset printer
  printByte('E');
  //Serial.println("Printer Reset");
}

void printMessage(byte *message) {
  //digitalWrite(13, HIGH);
	if(!message){
		message = std_message;
	}
	sizeof(message);
  for(int line = 0; line < num_lines; line++) {
    for(int cursorPosition = 0; cursorPosition < charsPerLine; cursorPosition++) {
      byte character = (&message)[line][cursorPosition];
      printByte(character);
      Delay(10);
    }
    printByte(10); // new line
    Delay(10);
    printByte(13); // carriage return
    Delay(10);
  }
  //digitalWrite(13,LOW);
}

void printStartupMessage() {
  //Serial.println("Print start-up mssage");
 // digitalWrite(13, HIGH);

	//printByte(2);//start of text
	printByte(10);
	printByte(10);
	printByte(10);
	printByte(10);

  for(int line = 0; line < startup_num_lines; line++) {
    for(int cursorPosition = 0; cursorPosition < startup_charsPerLine; cursorPosition++) {
      byte character = startup_message[line][cursorPosition];
      printByte(character);
            Delay(4);
    }
    printByte(10); // new line
    printByte(13); // carriage return
    //Serial.print("Line ");
    //Serial.print(line);
    //Serial.println(" printed.");
  }
 //printByte(3);//end of text
  //Serial.println("Startup message printed");
 // digitalWrite(13,LOW);
}


