#include "usart1.h"
#include "stm32f4xx.h"

void USART1_RX_Init(int baudRate)
{
	RCC->AHB1ENR 	|= 1;
	RCC->APB2ENR 	|= 0x10;
	
	GPIOA->AFR[1] 	|= 0x700;
	GPIOA->MODER	|= 0x200000;
	
	USART1->BRR		|= 16000000/baudRate;
	USART1->CR1		|= 0x0004;
	USART1->CR1		|= 0x2000;
}

char USART1_read(void)
{
	while(!(USART1->SR & 0x0020)) {} 			//wait until character arrives
	return USART1->DR;
}

void USART1_readLine(char *receiveBuffer)
{
	char receivedChar;
	
	USART1->SR &= ~(0x0020); 
	
	while(1)
	{
		receivedChar = USART1_read();
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