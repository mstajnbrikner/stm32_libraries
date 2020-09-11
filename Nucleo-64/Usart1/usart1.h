#ifndef USART1_H
#define USART1_H
#endif

//RX pin - PA10

void USART1_RX_Init(int baudRate);

//reads and returns one byte 
char USART1_read(void);

//reads line which ends with CR LF and stores it in "receiveBuffer"
void USART1_readLine(char *receiveBuffer);