#include "stm32f10x.h"                  // Device header
#include "lcd_i2c.h"
#include "misc.h"

extern struct lcdMiscData lcdMiscelData;

void startI2C()
{
	I2C1->CR1 |= (1 << 8);			//start
	while(!(I2C1->SR1 & 1)) 
	{
	}
	lcdMiscelData.tempReceive = I2C1->SR1;
	
	I2C1->DR = (0x27 << 1);		//slave address 0x27
	while(!(I2C1->SR1 & 2))
	{
	}
	lcdMiscelData.tempReceive = I2C1->SR1;
	lcdMiscelData.tempReceive = I2C1->SR2;
}
void stopI2C()
{
	I2C1->CR1 |= (1 << 9); 		//stop
}
void backlightOn()
{
	startI2C();
	
	I2C1->DR = 0x08;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	
	stopI2C();
}
void writeChar(char ch)
{
	startI2C();
	
	char upperNibble = (ch & 0xf0) >> 4;
	char lowerNibble = (ch & 0x0f);
	
	I2C1->DR = 0x05;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = (upperNibble << 4) | 5;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = (upperNibble << 4) | 1;
	while(!(I2C1->SR1 & 4))						
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);									
	
	I2C1->DR = 0x05;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = (lowerNibble << 4) | 5;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = (lowerNibble << 4) | 1;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(50);									//wait at least 50 us
	
	stopI2C();
}

void writeString(char* text)
{
	while((*text) != '\0')
	{
		writeChar(*text);
		text++;
	}
}

void setCursor(int row, int column)
{
	int address = 0;
	
	
	if(row == 0)
	{
		address = column;
	}
	else if(row == 1)
	{
		address = column + (int)0x40;
	}		
	else {return;}
		
	int lowerNibble = (address & 0x0f);
	int upperNibble = (address & 0xf0) >> 4;
	upperNibble |= 0x8;
	
	startI2C();
	
	I2C1->DR = 0x05;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = (upperNibble << 4) | 4;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = (upperNibble << 4) | 0;
	while(!(I2C1->SR1 & 4))						
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);									
	
	I2C1->DR = 0x05;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = (lowerNibble << 4) | 4;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = (lowerNibble << 4) | 0;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(50);									//wait at least 50 us
	
	stopI2C();
}

void lcdInit()
{
	RCC->APB2ENR |= 8;					//gpio b clock for pb6 and pb7
	RCC->APB2ENR |= 1;					//afio clock
	RCC->APB1ENR |= (1 << 21);			//i2c1 clock enable	
	
	GPIOB->CRL &= ~(0xff000000); 		//clear pb6 and pb7
	GPIOB->CRL |= 0xdd000000;			//pb6 and pb7 - af open drain for i2c
	
	I2C1->CR2 |= 0x44;					//peripheral input clock from apb - 36 MHz
	I2C1->CCR |= 0xb4;					//clock control registers - 100 KHz
	I2C1->TRISE |= 0x25;				//rising time
	I2C1->CR1 |= 1;							//peripheral enable
	
	delayMs(50);
	
	startI2C();
	
	I2C1->DR = 0x00;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(10);
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x34;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x30;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayMs(10);									//wait at least 4.1 ms
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x34;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x30;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(200);									//wait at least 100 us
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x34;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x30;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayMs(10);									//wait at least 4.1 ms
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x24;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x20;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(60);									//wait at least 40 us
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x24;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x20;
	while(!(I2C1->SR1 & 4))					//FUNCTION SET 
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);

	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x84;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x80;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(50);									//wait at least 50 us
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x00;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);									
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x84;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x80;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(50);									//wait at least 50 us
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x00;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);									
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x14;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x10;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayMs(4);									//wait at least 1.64 ms
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x00;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);									
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x64;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x60;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(50);									//wait at least 50 us
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0x00;
	while(!(I2C1->SR1 & 4))						//DISPLAY ON
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);									
	
	I2C1->DR = 0x04;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0xE4;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(1);
	
	I2C1->DR = 0xE0;
	while(!(I2C1->SR1 & 4))
	lcdMiscelData.tempReceive = I2C1->SR1;
	delayUs(50);									//wait at least 50 us	
	
	stopI2C();
}

