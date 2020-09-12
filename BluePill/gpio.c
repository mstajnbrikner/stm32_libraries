#include "stm32f10x.h"                  // Device header
#include "gpio.h"

void GPIOB_initPin_8to15_OUT(int mode, int pinNumber)
{
	RCC->APB2ENR |= GPIOB_CLOCK;
	GPIOB->CRH &= ~(CLEAR << (4*(pinNumber-8)));
	GPIOB->CRH |= (mode << (4*(pinNumber-8)));
}

void GPIOB_setPinHigh(int pinNumber)
{
	GPIOB->BSRR	= 1 << pinNumber;
}

void GPIOB_setPinLow(int pinNumber)
{
	GPIOB->BSRR	= 1 << (pinNumber + 16);
}

void GPIOB_initPin_8to15_IN(int mode, int pinNumber, int pupdResistor)
{
	RCC->APB2ENR |= GPIOB_CLOCK;
	GPIOB->CRH &= ~(CLEAR << (4*(pinNumber-8)));
	GPIOB->CRH |= (mode << (4*(pinNumber-8)));
	
	if(mode == IN_ANALOG)
	{
		RCC->APB2ENR |= ADC_CLOCK;
		RCC->APB2ENR |= AFIO_CLOCK;
		ADC1->CR2	|= 1;
	}
	else if(mode == IN_PUPDR)
	{		
		GPIOB->BSRR = pupdResistor << pinNumber;
	}
}

int GPIOB_digitalReadPin(int pinNumber)
{
	return ((1 << pinNumber) & GPIOB->IDR) >> pinNumber;
}

void GPIOB_initPin_0to7_OUT(int mode, int pinNumber)
{
	RCC->APB2ENR |= GPIOB_CLOCK;
	GPIOB->CRL &= ~(CLEAR << (4*pinNumber));
	GPIOB->CRL |= (mode << (4*pinNumber));
}

void GPIOB_initPin_0to7_IN(int mode, int pinNumber, int pupdResistor)
{
	RCC->APB2ENR |= GPIOB_CLOCK;
	GPIOB->CRL &= ~(CLEAR << (4*pinNumber));
	GPIOB->CRL |= (mode << (4*pinNumber));
	if(mode == IN_ANALOG)
	{
		RCC->APB2ENR |= ADC_CLOCK;
		RCC->APB2ENR |= AFIO_CLOCK;
		ADC1->CR2	|= 1;
	}
	else if(mode == IN_PUPDR)
	{		
		GPIOB->BSRR = pupdResistor << pinNumber;
	}
}

void GPIOA_initPin_8to15_OUT(int mode, int pinNumber)
{
	RCC->APB2ENR |= GPIOA_CLOCK;
	GPIOA->CRH &= ~(CLEAR << (4*(pinNumber-8)));
	GPIOA->CRH |= (mode << (4*(pinNumber-8)));
}

void GPIOA_initPin_8to15_IN(int mode, int pinNumber, int pupdResistor)
{
	RCC->APB2ENR |= GPIOA_CLOCK;
	GPIOA->CRH &= ~(CLEAR << (4*(pinNumber-8)));
	GPIOA->CRH |= (mode << (4*(pinNumber-8)));
	
	if(mode == IN_ANALOG)
	{
		RCC->APB2ENR |= ADC_CLOCK;
		RCC->APB2ENR |= AFIO_CLOCK;
		ADC1->CR2	|= 1;
	}
	else if(mode == IN_PUPDR)
	{		
		GPIOA->BSRR = pupdResistor << pinNumber;
	}
}

void GPIOA_initPin_0to7_OUT(int mode, int pinNumber)
{
	RCC->APB2ENR |= GPIOA_CLOCK;
	GPIOA->CRL &= ~(CLEAR << (4*pinNumber));
	GPIOA->CRL |= (mode << (4*pinNumber));
}

void GPIOA_initPin_0to7_IN(int mode, int pinNumber, int pupdResistor)
{
	RCC->APB2ENR |= GPIOA_CLOCK;
	GPIOA->CRL &= ~(CLEAR << (4*pinNumber));
	GPIOA->CRL |= (mode << (4*pinNumber));
	
	if(mode == IN_ANALOG)
	{
		RCC->APB2ENR |= ADC_CLOCK;
		RCC->APB2ENR |= AFIO_CLOCK;
		ADC1->CR2	|= 1;
	}
	else if(mode == IN_PUPDR)
	{		
		GPIOA->BSRR = pupdResistor << pinNumber;
	}
}

void GPIOA_setPinHigh(int pinNumber)
{
	GPIOA->BSRR	= 1 << pinNumber;
}

void GPIOA_setPinLow(int pinNumber)
{
	GPIOA->BSRR	= 1 << (pinNumber + 16);
}

int GPIOA_digitalReadPin(int pinNumber)
{
	return ((1 << pinNumber) & GPIOA->IDR) >> pinNumber;
}

int GPIOx_analogReadChannel(int channelNumber)
{
	ADC1->SR = 0;
	if((ADC1->SQR3 & 0x1f) != channelNumber)
	{
		ADC1->SQR3 = 0;
		ADC1->SQR3 |= channelNumber;
	}
	ADC1->CR2	|= 1;
	ADC1->CR2	|= 0x400000;
	
	while(!(ADC1->SR & 2)) {}
	
	return (ADC1->DR & 0xffff);
}


