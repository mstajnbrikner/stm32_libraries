#include "hx711.h"
#include "stm32f4xx.h"
#include <math.h>

void HX711_init(int gain)
{
	RCC->AHB1ENR		|= 2;							//enable GPIOB clock
	GPIOB->MODER		|= 0x10000000;		//PB14 - output push-pull
	GPIOB->PUPDR		|= 0x4000000;			//PB13 - iput pull-up
	
	writeToSck(HIGH);
	HX711_delayUs(50000);
	writeToSck(LOW);
	
	HX711_getValue(gain);
}


int HX711_getValue(int gain)
{
	int buffer = 0;
	
	while(readFromDt() == 1) 
	{
	}
	
	for(int i = 0; i < 24; i++)
	{
		writeToSck(HIGH);
		buffer = buffer << 1;
		
		
		HX711_delayUs(1);
		writeToSck(LOW);
		if(readFromDt() == 1)
		{
			buffer++;
		}
		HX711_delayUs(1);
	}
	
	for(int i = 0; i < gain; i++)
	{
		writeToSck(HIGH);
		HX711_delayUs(1);
		writeToSck(LOW);
		HX711_delayUs(1);
	}
		
	buffer = buffer ^ 0x800000;
	
	return buffer;
}

int HX711_getAverageValue(int gain, int times)
{
	int sum = 0;
	
	for(int i = 0; i < times; i++)
	{
		sum += HX711_getValue(gain);
	}
	
	return sum / times;
}

int HX711_tare(int gain, int times)
{
	int tareValue = 0;
	
	tareValue = HX711_getAverageValue(gain, times);
	
	return tareValue;
}

int HX711_getGramsFromRawValue(int rawValue)
{
	return (int)round(((float)rawValue/196856.0f)*200.0f);
}

void writeToSck(int value)
{
	if(value == HIGH)
		GPIOB->ODR |= 1 << 14;
	else
		GPIOB->ODR	&= ~(1 << 14);
}

int readFromDt(void)
{
	return (GPIOB->IDR & 0x2000) >> 13;
}

void HX711_delayUs(int micros)
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



