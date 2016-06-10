#include <stdint.h>

typedef struct {
	uint8_t current_pos;
	char buffer[255];
	//0 - false, 1 true - is ready
	uint8_t ready;

} RcvBuff;

volatile RcvBuff uart_buffer;

void RcvBuffReset(volatile RcvBuff* buffer);

// Configuration
void usart_configure();
void send_char(char c);
void send_char_2(char c);
void send_string(const char* s);
void send_string_2(const char* s);
uint8_t isReady(volatile RcvBuff* buffer);
