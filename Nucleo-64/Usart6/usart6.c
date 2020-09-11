#include "usart6.h"
#include "stm32f4xx.h"

//USART6 bus - APB2
//GPIOC bus - AHB1
//RX - PC7
//TX - PC6

void USART6_TX_init(int baudRate)
{
	RCC->APB2ENR |= 0x20;					//enable clock for USART6				
	RCC->AHB1ENR |= 4;							//enable clock for GPIOC channel
	
	GPIOC->AFR[0] 	|= 0x8000000;				//set pin PC6 to alternative function USART
	GPIOC->MODER	|= 0x2000;					//set PC6 to alternative mode
	
	USART6->BRR = 16000000/baudRate; 				
	USART6->CR1 |= 0X0008; 						//enable tx
	USART6->CR1 |= 0x2000; 						//enable USART
}

void USART6_writeString(char *text)
{
	while(*text != 0)
	{
		while(!(USART6->SR & 0x0080)) {}		//wait till tx buffer is not empty
		
		USART6->DR = *text;
			
		text++;
	}
}

void USART6_write(char ch)
{
	while(!(USART6->SR & 0x0080)) {}		//wait till tx buffer is not empty
		
	USART6->DR = ch;		
}

void USART6_RX_Init(int baudRate)
{
	RCC->APB2ENR |= 0x20;					//enable clock for USART6				
	RCC->AHB1ENR |= 4;							//enable clock for GPIOC channel
	
	GPIOC->AFR[0] 	|= 0x80000000;				//set pin PC7 to alternative function USART
	GPIOC->MODER	|= 0x8000;					//set PC7 to alternative mode
	
	USART6->BRR = 16000000/baudRate;				
	USART6->CR1 |= 0x0004;						//ENABLE rx
	USART6->CR1	|= 0x2000;						//ENABLE usart
}

char USART6_read(void)
{
	while(!(USART6->SR & 0x0020)) {} 			//wait until character arrives
	return USART6->DR;	
}

void USART6_readLine(char *receiveBuffer)
{
	char receivedChar;

	USART6->SR &= ~(0x0020);

	while(1)
	{
		receivedChar = USART6_read();
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