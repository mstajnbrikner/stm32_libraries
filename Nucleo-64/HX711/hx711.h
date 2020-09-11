#ifndef HX711_H
#define HX711_H
#endif

#define HIGH 		1
#define LOW 		0
#define GAIN_64		3
#define GAIN_128 	1

/*
User can call this functions in user code.
Parameter "gain" can be: GAIN_64 or GAIN_128 
	- greater the gain, greater the input sensitivity of HX711 ADC
Parameter "times" can be any positive number (advice: don't make it bigger than 30)
*/
void HX711_init(int gain);
int HX711_getValue(int gain);	// GAIN_64 or GAIN_128
int HX711_getAverageValue(int gain, int times);
int HX711_tare(int gain, int times);
int HX711_getGramsFromRawValue(int rawValue);


//This functions should not be called in user code!!
void writeToSck(int value);
int readFromDt(void);
void HX711_delayUs(int micros);


