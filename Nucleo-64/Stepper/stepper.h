#ifndef STEPPER_H
#define STEPPER_H
#endif

#define FORWARD 0
#define BACKWARD 1

//Interrupt service routine TIM4_IRQHandler must be copied in main *.c file

struct stepperMisc //after reset, all variables are 0 except "stepperDirection" that is FORWARD
{
	volatile int stepperOnFlag;
	volatile int stepperAltModeOnFlag;
	volatile int stepsCount;
	volatile int stepperSpeedCount;
	volatile int backwardSteps;
	volatile int forwardSteps;
	volatile int stepperDirection;
	volatile int stepperSpeedForward;
	volatile int stepperSpeedBackward;
};

void setupTim4(void);
void setupStepper(void);
int stepperStartAltMode(int direction, int fwdSteps, int bcdSteps, int fwdSpeed, int bcdSpeed);

/*
void TIM4_IRQHandler(void)
{
	TIM4->SR 		= 0;
	GPIOB->BSRR	= 0x1000000;
	
	if(stepperMiscVars.stepperOnFlag == 1)
	{
			stepperMiscVars.stepperSpeedCount++;
			if(stepperMiscVars.stepperSpeedCount == 120)
			{
				stepperMiscVars.stepsCount--;
				stepperMiscVars.stepperSpeedCount = 0;				
				if(stepperMiscVars.stepsCount == -1)
				{					
					stepperMiscVars.stepperOnFlag = 0;					
				}
				else
				{				
				GPIOB->BSRR	= 0x100;
				}
			}
	}
	else if(stepperMiscVars.stepperAltModeOnFlag == 1)
	{
		stepperMiscVars.stepperSpeedCount++;
		if(stepperMiscVars.stepperDirection == FORWARD)
		{
			if(stepperMiscVars.stepperSpeedCount == stepperMiscVars.stepperSpeedForward)
			{			
				stepperMiscVars.stepsCount--;
				stepperMiscVars.stepperSpeedCount = 0;
				if(stepperMiscVars.stepsCount == -1)
				{
					stepperMiscVars.stepsCount = stepperMiscVars.backwardSteps;
					stepperMiscVars.stepperDirection = BACKWARD;
					GPIOB->ODR ^= 0x200;
				}
				else
				{
					GPIOB->BSRR	= 0x100;
				}
			}
		}
		else if(stepperMiscVars.stepperDirection == BACKWARD)
		{
			if(stepperMiscVars.stepperSpeedCount == stepperMiscVars.stepperSpeedBackward)
			{			
				stepperMiscVars.stepsCount--;
				stepperMiscVars.stepperSpeedCount = 0;
				if(stepperMiscVars.stepsCount == -1)
				{
					stepperMiscVars.stepsCount = stepperMiscVars.forwardSteps;
					stepperMiscVars.stepperDirection = FORWARD;
					GPIOB->ODR ^= 0x200;
				}
				else
				{
					GPIOB->BSRR	= 0x100;
				}
			}
		}
		else{}
		
	}
}
*/
