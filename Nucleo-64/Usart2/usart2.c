#include "usart2.h"
#include "stm32f4xx.h"

void USART2_TX_init(int baudRate)
{
	RCC->APB1ENR |= 0x20000;					//enable clock for USART2				
	RCC->AHB1ENR |= 1;							//enable clock for GPIOA channel
	
	GPIOA->AFR[0] 		|= 0x700;				//set pin PA2 to alternative function USART
	GPIOA->MODER			|= 0x20;			//set PA2 to alternative mode
	
	USART2->BRR = 16000000/baudRate; 				//115200 @16MHz
	USART2->CR1 |= 0X0008; 						//enable tx
	USART2->CR1 |= 0x2000; 						//enable USART
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

void USART2_write(char ch)
{
	while(!(USART2->SR & 0x0080)) {}		//wait till tx buffer is not empty
		
	USART2->DR = ch;		
}

void USART2_RX_Init(int baudRate)
{
	RCC->AHB1ENR |= 1; 							//ENABLE GPIOA channel clock
	RCC->APB1ENR |= 0x20000;					//enable USART2 clock
	
	GPIOA->AFR[0] |= 0x7000;					//alternate function 7 - USART
	GPIOA->MODER	|= 0x0080;					//enable alternate function 
	
	USART2->BRR = 16000000/baudRate;				//115200 @16MHz
	USART2->CR1 |= 0x0004;						//ENABLE rx
	USART2->CR1	|= 0x2000;						//ENABLE usart
}

char USART2_read(void)
{
	while(!(USART2->SR & 0x0020)) {} 			//wait until character arrives
	return USART2->DR;	
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

