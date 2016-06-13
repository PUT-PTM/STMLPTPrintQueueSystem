#include <stdint.h>

typedef struct {
	uint8_t current_pos;
	char buffer[555];
	//is ready to receive data, 0 false, 1 true
	uint8_t ready;
	//is last received <CR><NW>, 0 false, 1 true
	uint8_t newline;

} RcvBuff;

//to copy from fast and proces data
volatile RcvBuff uart_buffer;



void RcvBuffReset(volatile RcvBuff* buffer);

// Configuration
void usart_configure();
void send_char(char c);
void send_char_2(char c);
void send_string(const char* s);
void send_string_2(const char* s);

