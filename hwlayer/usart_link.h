#include <stdint.h>

typedef struct {
	uint8_t current_pos;
	char buffer[255];
	uint8_t ready;
} RcvBuff;

volatile RcvBuff uart_buffer;

void RcvBuffInit(volatile RcvBuff* buffer);
void RcvBuffReset(volatile RcvBuff* buffer);

// Configuration
void usart_configure();
void send_char(char c);
void send_string(const char* s);
