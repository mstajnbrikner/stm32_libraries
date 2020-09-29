#ifndef LCD_I2C_H
#define LCD_I2C_H
#endif

#define BACKLIGHT_ON		0x08
#define BACKLIGHT_OFF		0x00

#define MODE_WRITECHAR  0x454545
#define MODE_COMMAND		0x545454

struct lcdMiscData
{
	int tempReceive;
	int backlight;
};

void I2C_start();
void I2C_stop();
void I2C_sendByte(int data, int us);
void I2C_sendCommand(int mode, char lNibble, char uNibble);

void backlightOn();
void backlightOff();
void writeChar(char ch);
void writeString(char* text);
void setCursor(int row, int column);
void lcdInit();
