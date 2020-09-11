#include "stm32f4xx.h"
#include "nucleoLed.h"

void setupNucleoLed(void)
{
	RCC->AHB1ENR |= 1;	
	GPIOA->MODER |= 0x400;
}

void turnNucleoLedOn(void)
{	
	GPIOA->BSRR = 0x20;
}
void turnNucleoLedOff(void)
{	
	GPIOA->BSRR = 0x200000;
}
void toggleNucleoLed(void)
{
	GPIOA->ODR ^= 0x20;
}
