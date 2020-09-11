#ifndef GPIO_H
#define GPIO_H
#endif

#define GPIOA_CLOCK 		4
#define GPIOB_CLOCK			8
#define OUT_PP					0x00000001
#define OUT_OD					0x00000005
#define IN							0x00000004
#define IN_PUPDR				0x00000008
#define PULLUP					1
#define PULLDOWN				(1 << 16)
#define CLEAR						0x0000000f

//Don't use pins PA15, PB3, PB4 - control pins

void GPIOB_initPin_8to15_OUT(int mode, int pinNumber);
void GPIOB_initPin_8to15_IN(int mode, int pinNumber, int pupdResistor);
void GPIOB_initPin_0to7_OUT(int mode, int pinNumber);
void GPIOB_initPin_0to7_IN(int mode, int pinNumber, int pupdResistor);

void GPIOA_initPin_8to15_OUT(int mode, int pinNumber);
void GPIOA_initPin_8to15_IN(int mode, int pinNumber, int pupdResistor);
void GPIOA_initPin_0to7_OUT(int mode, int pinNumber);
void GPIOA_initPin_0to7_IN(int mode, int pinNumber, int pupdResistor);

void GPIOB_setPinHigh(int pinNumber);
void GPIOB_setPinLow(int pinNumber);

void GPIOA_setPinHigh(int pinNumber);
void GPIOA_setPinLow(int pinNumber);

int GPIOB_digitalReadPin(int pinNumber);

int GPIOA_digitalReadPin(int pinNumber);
