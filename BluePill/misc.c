#include "misc.h"

void delayMs(int ms)
{
	for(int i = 0; i < (9600*ms); i++) {}
}
