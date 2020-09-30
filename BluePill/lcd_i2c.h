#ifndef LCD_I2C_H
#define LCD_I2C_H
#endif

#define BACKLIGHT_ON				0x08
#define BACKLIGHT_OFF				0x00

#define MODE_writeChar  		0x454545
#define MODE_COMMAND				0x545454
#define DISPLAY_ON					0x04
#define DISPLAY_OFF					0x00
#define CURSOR_ON						0x02
#define CURSOR_OFF					0x00
#define CURSOR_BLINKING			0x01
#define CURSOR_NOBLINKING		0x00

struct lcdMiscData
{
	int tempReceive;
	int backlight;
};

void I2C_start(void);
void I2C_stop(void);
void I2C_sendByte(int data, int us);
void I2C_sendCommand(int mode, char lNibble, char uNibble);

void LCD_backlightOn(void);
void LCD_backlightOff(void);
void LCD_writeChar(char ch);
void LCD_writeString(char* text);
void LCD_setCursor(int row, int column);
void LCD_init(void);
void LCD_clearDisplay(void);
void LCD_setDisplayProperties(char displayState, char cursorState, char blinkingCursorState);
