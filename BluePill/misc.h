#ifndef MISC_H
#define MISC_H
#endif

/******************************************************************
This function is valid (not perfectly accurate, ~95%) for system 
frequency 72 MHz and with no optimization when compiling.
******************************************************************/
void delayMs(int ms);



int map(int x, int in_min, int in_max, int out_min, int out_max);


