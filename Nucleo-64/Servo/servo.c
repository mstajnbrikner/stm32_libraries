#include "stm32f4xx.h"
#include "servo.h"

void setUpServo(int channelNumber)
{
	switch(channelNumber)
	{
		case 1:
			//TIM3 CH1, PA6
			RCC->AHB1ENR		|= 1;
			GPIOA->MODER		|= 0x2000;
			GPIOA->AFR[0]		|= 0x2000000;
			
			RCC->APB1ENR		|= 2;
			TIM3->PSC			= 5-1;
			TIM3->ARR			= 64000-1; 
			TIM3->CNT			= 0;
			TIM3->CCMR1			|= 0x60;
			TIM3->CCER			|= 1;
			TIM3->CCR1			= 4800-1;
			TIM3->CR1			|= 1;
			break;
		case 2:
			//TIM3 CH2, PA7
			RCC->AHB1ENR 		|= 1;
			GPIOA->MODER 		|= 0x8000;
			GPIOA->AFR[0]		|= 0x20000000;
						
			RCC->APB1ENR 		|= 2;
			TIM3->PSC			= 5-1;
			TIM3->ARR			= 64000-1; 
			TIM3->CNT			= 0;
			TIM3->CCMR1			|= 0x6000;
			TIM3->CCER			|= 0x10;
			TIM3->CCR2			= 4800-1;				
			TIM3->CR1			|= 1;
			break;
		default:
			break;
	}
}

void setServoAngle(int channelNumber, int angle)
{
	int angle_t = angle;
	
	if(angle_t > 180)
	{
		angle_t = 6400-1;
	}
	else if(angle_t < 0)
	{
		angle_t = 3200-1;
	}
	else
	{
		angle_t = map(angle_t, 0, 180, 3200, 6400) - 1;
	}
	
	switch(channelNumber)
	{
		case 1:
			TIM3->CCR1 = angle_t;
			break;
		case 2:
			TIM3->CCR2 = angle_t;
			break;
		default:
			break;
	}
}

int map(int valueToMap, int in_min, int in_max, int out_min, int out_max) {
  return (valueToMap - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}






