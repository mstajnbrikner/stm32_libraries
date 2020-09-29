#include "stm32f10x.h"                  // Device header
#include "lcd_i2c.h"
#include "misc.h"

extern struct lcdMiscData lcdMiscelData;

void I2C_start()
{
	I2C1->CR1 |= (1 << 8);			//start
	while(!(I2C1->SR1 & 1)) 
	{
	}
	//lcdMiscelData.tempReceive = I2C1->SR1;
	
	I2C1->DR = (0x27 << 1);		//slave address 0x27
	while(!(I2C1->SR1 & 2))
	{
	}
	//lcdMiscelData.tempReceive = I2C1->SR1;
	lcdMiscelData.tempReceive = I2C1->SR2;
}
void I2C_stop()
{
	I2C1->CR1 |= (1 << 9); 		//stop
}

void I2C_sendByte(int data, int us)
{
	I2C1->DR = (data | lcdMiscelData.backlight);
	while(!(I2C1->SR1 & 4))
	delayUs(us);
}

void I2C_sendCommand(int mode, char lNibble, char uNibble)
{
	int temp1, temp2;
	if(mode == MODE_WRITECHAR)
	{
		temp1 = 5;
		temp2 = 1;
	}
	else if(mode == MODE_COMMAND)
	{
		temp1 = 4;
		temp2 = 0;
	}
	else
	{}
	
	I2C1->DR = 0x0d;
	while(!(I2C1->SR1 & 4))
	delayUs(1);
	
	I2C1->DR = (uNibble << 4) | temp1 | lcdMiscelData.backlight;
	while(!(I2C1->SR1 & 4))
	delayUs(1);
	
	I2C1->DR = (uNibble << 4) | temp2 | lcdMiscelData.backlight;
	while(!(I2C1->SR1 & 4))						
	delayUs(1);									
	
	I2C1->DR = 0x0d;
	while(!(I2C1->SR1 & 4))
	delayUs(1);
	
	I2C1->DR = (lNibble << 4) | temp1 | lcdMiscelData.backlight;
	while(!(I2C1->SR1 & 4))
	delayUs(1);
	
	I2C1->DR = (lNibble << 4) | temp2 | lcdMiscelData.backlight;
	while(!(I2C1->SR1 & 4))
	delayUs(50);									//wait at least 50 us
	
}

void backlightOn()
{
	I2C_start();
	
	I2C1->DR = BACKLIGHT_ON;
	while(!(I2C1->SR1 & 4))
	
	I2C_stop();
}

void backlightOff()
{
	I2C_start();
	
	I2C1->DR = BACKLIGHT_OFF;
	while(!(I2C1->SR1 & 4))
	
	I2C_stop();
}

void writeChar(char ch)
{
	char upperNibble = (ch & 0xf0) >> 4;
	char lowerNibble = (ch & 0x0f);
	
	I2C_start();
	
	I2C_sendCommand(MODE_WRITECHAR, lowerNibble, upperNibble);
	
	I2C_stop();
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
		
	char lowerNibble = (address & 0x0f);
	char upperNibble = (address & 0xf0) >> 4;
	upperNibble |= 0x8;
	
	I2C_start();
	
	I2C_sendCommand(MODE_COMMAND, lowerNibble, upperNibble);
	
	I2C_stop();
}

void lcdInit()
{
	//Basic GPIO and I2C setup
	RCC->APB2ENR |= 8;					
	RCC->APB2ENR |= 1;					
	RCC->APB1ENR |= (1 << 21);			
	
	GPIOB->CRL &= ~(0xff000000); 		
	GPIOB->CRL |= 0xdd000000;			
	
	I2C1->CR2 |= 0x44;					
	I2C1->CCR |= 0xb4;					
	I2C1->TRISE |= 0x25;				
	I2C1->CR1 |= 1;		
	//End GPIO and I2C setup
	
	delayMs(50);
	
	lcdMiscelData.backlight = BACKLIGHT_ON;
	
	I2C_start();
	
	I2C_sendByte(0x00, 1);
	I2C_sendByte(0x04, 1);
	
	I2C_sendByte(0x34, 1);
	I2C_sendByte(0x30, 10000);
	I2C_sendByte(0x04, 1);
	I2C_sendByte(0x34, 1);
	I2C_sendByte(0x30, 200);
	I2C_sendByte(0x04, 1);
	
	I2C_sendByte(0x34, 1);
	I2C_sendByte(0x30, 10000);
	I2C_sendByte(0x04, 1);
	I2C_sendByte(0x24, 1);
	I2C_sendByte(0x20, 60);
	I2C_sendByte(0x04, 1);
	
	I2C_sendByte(0x24, 1);
	I2C_sendByte(0x20, 1);
	I2C_sendByte(0x04, 1);
	I2C_sendByte(0x84, 1);
	I2C_sendByte(0x80, 50);
	I2C_sendByte(0x04, 1);
	
	I2C_sendByte(0x04, 1);
	I2C_sendByte(0x00, 1);
	I2C_sendByte(0x04, 1);
	I2C_sendByte(0x84, 1);
	I2C_sendByte(0x80, 50);
	I2C_sendByte(0x04, 1);
	
	I2C_sendByte(0x04, 1);
	I2C_sendByte(0x00, 1);
	I2C_sendByte(0x04, 1);
	I2C_sendByte(0x14, 1);
	I2C_sendByte(0x10, 4000);
	I2C_sendByte(0x04, 1);
	
	I2C_sendByte(0x04, 1);
	I2C_sendByte(0x00, 1);
	I2C_sendByte(0x04, 1);
	I2C_sendByte(0x64, 1);
	I2C_sendByte(0x60, 50);
	I2C_sendByte(0x04, 1);
	
	I2C_sendByte(0x04, 1);
	I2C_sendByte(0x00, 1);
	I2C_sendByte(0x04, 1);
	I2C_sendByte(0xe4, 1);
	I2C_sendByte(0xe0, 50);
	
	I2C_stop();
}

