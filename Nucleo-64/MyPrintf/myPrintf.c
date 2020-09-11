#include "stm32f4xx.h"
#include "myPrintf.h"
#include <stdio.h>

void USART2_TX_init(void)
{
	RCC->APB1ENR |= 0x20000;					//enable clock for USART2				
	RCC->AHB1ENR |= 1;							//enable clock for GPIOA channel
	
	GPIOA->AFR[0] 		|= 0x700;				//set pin PA2 to alternative function USART
	GPIOA->MODER			|= 0x20;			//set PA2 to alternative mode
	
	USART2->BRR = 16000000/115200; 				//115200 @16MHz
	USART2->CR1 |= 0X0008; 						//enable tx
	USART2->CR1 |= 0x2000; 						//enable USART
}

void USART2_RX_Init(void)
{
	RCC->AHB1ENR |= 1; 							//ENABLE GPIOA channel clock
	RCC->APB1ENR |= 0x20000;					//enable USART2 clock
	
	GPIOA->AFR[0] |= 0x7000;					//alternate function 7 - USART
	GPIOA->MODER	|= 0x0080;					//enable alternate function 
	
	USART2->BRR = 16000000/115200;				//115200 @16MHz
	USART2->CR1 |= 0x0004;						//ENABLE rx
	USART2->CR1	|= 0x2000;						//ENABLE usart
}

void USART2_writeString(char *text)
{
	while(*text != 0)
	{
		while(!(USART2->SR & 0x0080)) {}		//wait till tx buffer is not empty
		
		USART2->DR = *text;
			
		text++;
	}
}

char USART2_read(void)
{
	while(!(USART2->SR & 0x0020)) {} 			//wait until character arrives
	return USART2->DR;		
}

void USART2_write(int ch)
{
	while(!(USART2->SR & 0x0080)) {}		//wait till tx buffer is not empty
		
	USART2->DR = (ch & 0xFF);		
}

void USART2_readLine(char *receiveBuffer)
{
	char receivedChar;

	USART2->SR &= ~(0x0020);

	while(1)
	{
		receivedChar = USART2_read();
		if(receivedChar == '\n')
		{
			*(receiveBuffer-1) = '\0';
			break;
		}
		else
		{
			*receiveBuffer = receivedChar;
			receiveBuffer++;
		}
	}
}

int fputc(int c, FILE *stream)
{
	USART2_write(c & 0xFF);
	return c;
}

int fgetc(FILE *stream)
{
	char c = USART2_read();
	//USART2_write(c);
	return c;
}
