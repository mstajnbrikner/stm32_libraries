#ifndef USART2_H
#define USART2_H
#endif

void USART2_TX_init(int baudRate);
void USART2_writeString(char *text);
void USART2_write(char ch);

void USART2_RX_Init(int baudRate);
char USART2_read(void);
void USART2_readLine(char *receiveBuffer);
