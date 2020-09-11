#include "stepper.h"
#include "stm32f4xx.h"

extern struct stepperMisc stepperMiscVars;

void setupTim4(void)	//generates interrupt every 100 us
{
	RCC->APB1ENR 		|= 4;
	TIM4->PSC			= 0;
	TIM4->ARR			= 1600-1;		
	TIM4->CNT			= 0;
	TIM4->CR1			|= 1; 
	TIM4->DIER			|= 1;
}

void setupStepper(void)
{
	//setting STEP pin PB8
	RCC->AHB1ENR 		|= 2;
	GPIOB->MODER		|= 0x10000;
	GPIOB->BSRR			= 0x1000000;
	//************************
	
	//setting DIR pin PB9
	GPIOB->MODER 		|= 0x40000;
	GPIOB->ODR 			&= ~(0x200);
}


int stepperStartAltMode(int direction, int fwdSteps, int bcdSteps, int fwdSpeed, int bcdSpeed)
{
	if((stepperMiscVars.stepperOnFlag == 1) || (stepperMiscVars.stepperAltModeOnFlag == 1))
	{
		return 1;
	}
	
	stepperMiscVars.stepperSpeedCount = 0;
	stepperMiscVars.forwardSteps = fwdSteps;
	stepperMiscVars.backwardSteps = bcdSteps;
	stepperMiscVars.stepperSpeedForward = (3000/fwdSpeed);
	stepperMiscVars.stepperSpeedBackward = (3000/bcdSpeed);
	stepperMiscVars.stepsCount = fwdSteps;	
	stepperMiscVars.stepperDirection = FORWARD;
	
	if(direction == FORWARD)
	{
		GPIOB->ODR &= ~(0x200);
	}
	else
	{
		GPIOB->ODR 	|= 0x200;
	}
	stepperMiscVars.stepperAltModeOnFlag = 1;
	
	return 0;
}

