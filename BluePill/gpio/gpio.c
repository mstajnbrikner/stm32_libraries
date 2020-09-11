#include "stm32f10x.h"                  // Device header
#include "gpio.h"

void GPIOB_initPin_8to15_OUT(int pbx_mode, int pinNumber)
{
	RCC->APB2ENR |= GPIOB_CLOCK;
	GPIOB->CRH &= ~(PBx_CLEAR << (4*(pinNumber-8)));
	GPIOB->CRH |= (pbx_mode << (4*(pinNumber-8)));
}

void GPIOB_setPinHigh(int pinNumber)
{
	GPIOB->BSRR	= 1 << pinNumber;
}

void GPIOB_setPinLow(int pinNumber)
{
	GPIOB->BSRR	= 1 << (pinNumber + 16);
}

void GPIOB_initPin_8to15_IN(int pbx_mode, int pinNumber, int pupdResistor)
{
	if(pbx_mode == PBx_IN)
	{
		RCC->APB2ENR |= GPIOB_CLOCK;
		GPIOB->CRH &= ~(PBx_CLEAR << (4*(pinNumber-8)));
		GPIOB->CRH |= (pbx_mode << (4*(pinNumber-8)));
	}
	else
	{
		RCC->APB2ENR |= GPIOB_CLOCK;
		GPIOB->CRH &= ~(PBx_CLEAR << (4*(pinNumber-8)));
		GPIOB->CRH |= (pbx_mode << (4*(pinNumber-8)));
		GPIOB->BSRR = pupdResistor << pinNumber;
	}
}

int GPIOB_digitalReadPin(int pinNumber)
{
	return ((1 << pinNumber) & GPIOB->IDR) >> pinNumber;
}