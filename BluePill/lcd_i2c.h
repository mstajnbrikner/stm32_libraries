#ifndef LCD_I2C_H
#define LCD_I2C_H
#endif

struct lcdMiscData
{
	int tempReceive;
};

void startI2C();
void stopI2C();
void backlightOn();
void writeChar(char ch);
void writeString(char* text);
void setCursor(int row, int column);
void lcdInit();
