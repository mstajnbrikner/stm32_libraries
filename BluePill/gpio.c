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
	if(mode == IN)
	{
		RCC->APB2ENR |= GPIOB_CLOCK;
		GPIOB->CRH &= ~(CLEAR << (4*(pinNumber-8)));
		GPIOB->CRH |= (mode << (4*(pinNumber-8)));
	}
	else
	{
		RCC->APB2ENR |= GPIOB_CLOCK;
		GPIOB->CRH &= ~(CLEAR << (4*(pinNumber-8)));
		GPIOB->CRH |= (mode << (4*(pinNumber-8)));
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
	if(mode == IN)
	{
		RCC->APB2ENR |= GPIOB_CLOCK;
		GPIOB->CRL &= ~(CLEAR << (4*pinNumber));
		GPIOB->CRL |= (mode << (4*pinNumber));
	}
	else
	{
		RCC->APB2ENR |= GPIOB_CLOCK;
		GPIOB->CRL &= ~(CLEAR << (4*pinNumber));
		GPIOB->CRL |= (mode << (4*pinNumber));
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
	if(mode == IN)
	{
		RCC->APB2ENR |= GPIOA_CLOCK;
		GPIOA->CRH &= ~(CLEAR << (4*(pinNumber-8)));
		GPIOA->CRH |= (mode << (4*(pinNumber-8)));
	}
	else
	{
		RCC->APB2ENR |= GPIOA_CLOCK;
		GPIOA->CRH &= ~(CLEAR << (4*(pinNumber-8)));
		GPIOA->CRH |= (mode << (4*(pinNumber-8)));
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
	if(mode == IN)
	{
		RCC->APB2ENR |= GPIOA_CLOCK;
		GPIOA->CRL &= ~(CLEAR << (4*pinNumber));
		GPIOA->CRL |= (mode << (4*pinNumber));
	}
	else
	{
		RCC->APB2ENR |= GPIOA_CLOCK;
		GPIOA->CRL &= ~(CLEAR << (4*pinNumber));
		GPIOA->CRL |= (mode << (4*pinNumber));
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



