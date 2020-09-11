#ifndef GPIO_H
#define GPIO_H
#endif

#define GPIOB_CLOCK			8
#define PBx_OUT_PP			0x00000001
#define PBx_OUT_OD			0x00000005
#define PBx_IN				0x00000004
#define PBx_IN_PUPDR		0x00000008
#define PBx_PULLUP			1
#define PBx_PULLDOWN		(1 << 16)
#define PBx_CLEAR			0x0000000f

void GPIOB_initPin_8to15_OUT(int pbx_mode, int pinNumber);
void GPIOB_initPin_8to15_IN(int pbx_mode, int pinNumber, int pupdResistor);

void GPIOB_setPinHigh(int pinNumber);
void GPIOB_setPinLow(int pinNumber);

int GPIOB_digitalReadPin(int pinNumber);