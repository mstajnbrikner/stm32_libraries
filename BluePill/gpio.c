#include "stm32f10x.h"                  // Device header
#include "gpio.h"

void GPIOB_initPin_8to15_OUT(int mode, int pinNumber)
{
	RCC->APB2ENR |= GPIOB_CLOCK;
	GPIOB->CRH &= ~(CLEAR << (4*(pinNumber-8)));
	GPIOB->CRH |= (mode << (4*(pinNumber-8)));
	
	if(mode == OUT_PWM_PP) 
	{
		if((pinNumber >= 8) && (pinNumber <= 9))
		{
			RCC->APB2ENR |= AFIO_CLOCK;
			RCC->APB1ENR |= TIM4_CLOCK;
			TIM4->EGR |= 1;
			TIM4->ARR = 47999;
			TIM4->PSC = 2;
			TIM4->CCMR2 |= (0x68 << (8*(pinNumber-8)));
			TIM4->CCER |= (1 << (4*(pinNumber-6)));
			TIM4->CR1 |= 0x81;
		}	
		else
		{
		}
	}
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

void GPIOB_initPin_0to7_OUT(int mode, int pinNumber)//************************OVDJE STAO
{
	RCC->APB2ENR |= GPIOB_CLOCK;
	GPIOB->CRL &= ~(CLEAR << (4*pinNumber));
	GPIOB->CRL |= (mode << (4*pinNumber));
	
	if(mode == OUT_PWM_PP) 
	{
		if((pinNumber >= 0) && (pinNumber <= 1))
		{
			RCC->APB2ENR |= AFIO_CLOCK;
			RCC->APB1ENR |= TIM3_CLOCK;
			TIM3->EGR |= 1;
			TIM3->ARR = 47999;
			TIM3->PSC = 2;
			TIM3->CCMR2 |= (0x68 << (8*pinNumber));
			TIM3->CCER |= (1 << (4*(pinNumber+2)));
			TIM3->CR1 |= 0x81;
		}
		else if(((pinNumber >= 6) && (pinNumber <= 7)))
		{
			RCC->APB2ENR |= AFIO_CLOCK;
			RCC->APB1ENR |= TIM4_CLOCK;
			TIM4->EGR |= 1;
			TIM4->ARR = 47999;
			TIM4->PSC = 2;
			TIM4->CCMR1 |= (0x68 << (8*(pinNumber-6)));
			TIM4->CCER |= (1 << (4*(pinNumber-6)));
			TIM4->CR1 |= 0x81;
		}
		else
		{
		}
	}
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
	
	if(mode == OUT_PWM_PP) 
	{
		if((pinNumber >= 8) && (pinNumber <= 9))
		{
			RCC->APB2ENR |= AFIO_CLOCK;
			RCC->APB2ENR |= TIM1_CLOCK;
			TIM1->EGR |= 1;
			TIM1->ARR = 47999;
			TIM1->PSC = 2;
			TIM1->CCMR1 |= (0x68 << (8*(pinNumber-8)));
			TIM1->CCER |= (1 << (4*(pinNumber-8)));
			TIM1->BDTR |= 0x8000;
			TIM1->CR1 |= 0x81;
		}
		else if(((pinNumber >= 10) && (pinNumber <= 11)))
		{
			RCC->APB2ENR |= AFIO_CLOCK;
			RCC->APB2ENR |= TIM1_CLOCK;
			TIM1->EGR |= 1;
			TIM1->ARR = 47999;
			TIM1->PSC = 2;
			TIM1->CCMR2 |= (0x68 << (8*(pinNumber-10)));
			TIM1->CCER |= (1 << (4*(pinNumber-8)));
			TIM1->BDTR |= 0x8000;
			TIM1->CR1 |= 0x81;
		}
		else
		{
		}
	}
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
	
	if(mode == OUT_PWM_PP) 
	{
		if((pinNumber >= 0) && (pinNumber <= 1))
		{
			RCC->APB2ENR |= AFIO_CLOCK;
			RCC->APB1ENR |= TIM2_CLOCK;
			TIM2->EGR |= 1;
			TIM2->ARR = 47999;
			TIM2->PSC = 2;
			TIM2->CCMR1 |= (0x68 << (8*pinNumber));
			TIM2->CCER |= (1 << (4*pinNumber));
			TIM2->CR1 |= 0x81;
		}
		else if(((pinNumber >= 2) && (pinNumber <= 3)))
		{
			RCC->APB2ENR |= AFIO_CLOCK;
			RCC->APB1ENR |= TIM2_CLOCK;
			TIM2->EGR |= 1;
			TIM2->ARR = 47999;
			TIM2->PSC = 2;
			TIM2->CCMR2 |= (0x68 << (8*(pinNumber-2)));
			TIM2->CCER |= (1 << (4*pinNumber));
			TIM2->CR1 |= 0x81;
		}
		else if(((pinNumber >= 6) && (pinNumber <= 7)))
		{
			RCC->APB2ENR |= AFIO_CLOCK;
			RCC->APB1ENR |= TIM3_CLOCK;
			TIM3->EGR |= 1;
			TIM3->ARR = 47999;
			TIM3->PSC = 2;
			TIM3->CCMR1 |= (0x68 << (8*(pinNumber-6)));
			TIM3->CCER |= (1 << (4*(pinNumber-6)));
			TIM3->CR1 |= 0x81;
		}
		else
		{
		}
	}
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

void GPIOA_analogWritePin(int pinNumber, int pwm)
{
	switch(pinNumber)
	{
		case 0:
			TIM2->CCR1 |= pwm;
			break;
		case 1:
			TIM2->CCR2 |= pwm;
			break;
		case 2:
			TIM2->CCR3 |= pwm;
			break;
		case 3:
			TIM2->CCR4 |= pwm;
			break;
		case 6:
			TIM3->CCR1 |= pwm;
			break;
		case 7:
			TIM3->CCR2 |= pwm;
			break;
		case 8:
			TIM1->CCR1 |= pwm;
			break;
		case 9:
			TIM1->CCR2 |= pwm;
			break;
		case 10:
			TIM1->CCR3 |= pwm;
			break;
		case 11:
			TIM1->CCR4 |= pwm;
			break;
		default:
			break;
	}
}

void GPIOB_analogWritePin(int pinNumber, int pwm)
{
	
}



















