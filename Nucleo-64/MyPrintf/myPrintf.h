#ifndef MYPRINTF_H
#define MYPRINTF_H
#endif

/*
Functions to use printf() and scanf() in serial communication with PC.
You may also use other functions from this header file to establish
communication via USART2 (pins PA2 and PA3) which is connected to USB cable which connects 
you with PC.

IMPORTANT:
To use all other functions you must first call "USART2_RX_Init()"
and "USART2_TX_init()"!
*/

void USART2_TX_init(void);
void USART2_RX_Init(void);
char USART2_read(void);
void USART2_write(int);
void USART2_readLine(char *receiveBuffer);
void USART2_writeString(char *text);

struct __FILE
{
	int dummyVar;
};
