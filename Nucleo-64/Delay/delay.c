#include "delay.h"
#include "stm32f4xx.h"


/*
Accurate delay functions realized with 24-bit SysTick timer
*/

void delayMs(int millis)
{
	SysTick->LOAD = 16000-1; 	
	SysTick->VAL = 0;
	SysTick->CTRL = 0x5;
	
	for(int i = 0; i < millis; i++)
	{
		while((SysTick->CTRL & 0x10000) == 0) {}	
	}
	SysTick->CTRL = 0;
}
void delaySec(int seconds)
{
	SysTick->LOAD = 16000000-1; 	
	SysTick->VAL = 0;
	SysTick->CTRL = 0x5;
	
	for(int i = 0; i < seconds; i++)
	{
		while((SysTick->CTRL & 0x10000) == 0) {}	
	}
	SysTick->CTRL = 0;
}

void delayUs(int micros)
{
	SysTick->LOAD = 16-1; 	
	SysTick->VAL = 0;
	SysTick->CTRL = 0x5;
	
	for(int i = 0; i < micros; i++)
	{
		while((SysTick->CTRL & 0x10000) == 0) {}	
	}
	SysTick->CTRL = 0;
}

