#ifndef USART6_H
#define USART6_H
#endif

//USART6 bus - APB2
//GPIOC bus - AHB1
//RX - PC7
//TX - PC6

void USART6_TX_init(int baudRate);
void USART6_writeString(char *text);
void USART6_write(char ch);

void USART6_RX_Init(int baudRate);
char USART6_read(void);
void USART6_readLine(char *receiveBuffer);