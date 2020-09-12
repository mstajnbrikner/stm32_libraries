#include "misc.h"

void delayMs(int ms)
{
	for(int i = 0; i < (9600*ms); i++) {}
}


int map(int x, int in_min, int in_max, int out_min, int out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

