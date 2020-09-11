#include "boxConfiguration.h"
#include <string.h>
#include <stdlib.h>

//    B1/Kocka/Crvena/10/100&B2/X/X/X/X&B3/Piramida/Zelena/15/90+

void SaveBoxesConfiguration(char* configString, struct boxConfiguration* boxConfig, int* numberOfBoxes)
{
	int state = 0;
	int boxIndex = 0;
	char segment[15];
	int segmentIndex = 0;
	*numberOfBoxes = 0;
	int notConfTempCount = 0;
	
	strcpy(segment, "");
	
	
	while(1)
	{
			if(*configString == '+')
			{
				if(notConfTempCount < 3)
					boxConfig[boxIndex].objectMaxMass = atoi(segment);
				else
					boxIndex--;
				break;
			}
			else if(*configString == '/')
			{
				if(state == 0)									
				{
					if(strcmp(segment, "B1") == 0)
					{
						boxConfig[boxIndex].boxServoAngle = 30;
					}
					else if(strcmp(segment, "B2") == 0)
					{
						boxConfig[boxIndex].boxServoAngle = 90;
					}
					else if(strcmp(segment, "B3") == 0)
					{
						boxConfig[boxIndex].boxServoAngle = 150;
					}
					segmentIndex = 0;
					state++;
					configString++;
				}
				else if(state == 1)
				{	
						if(strcmp(segment, "X") == 0)
						{
							notConfTempCount++;
						}
						
						strcpy(boxConfig[boxIndex].objectType, segment);								
						
						segmentIndex = 0;
						state++;
						configString++;		
				}
				else if(state == 2)
				{
					if(strcmp(segment, "X") == 0)
					{
						notConfTempCount++;
					}
					
					strcpy(boxConfig[boxIndex].objectColor, segment);
					
					segmentIndex = 0;
					state++;
					configString++;
				}
				else if(state == 3)
				{
					if(strcmp(segment, "X") == 0)
					{
						notConfTempCount++;
						boxConfig[boxIndex].objectMinMass = -1;
					}			
					else
					{
						boxConfig[boxIndex].objectMinMass = atoi(segment);
					}
					
					segmentIndex = 0;
					state = 0;
					configString++;
				}																															//ovdje stao				
			}
			else if(*configString == '&')
			{
				
				segmentIndex = 0;
				if(strcmp(segment, "X") == 0)
				{
					notConfTempCount++;
					boxConfig[boxIndex].objectMaxMass = -1;
				}
				else
				{
					boxConfig[boxIndex].objectMaxMass = atoi(segment);
				}
				
				if(notConfTempCount < 4)
				{					
					boxIndex++;
				}
				
				
				state = 0;
				configString++;
				notConfTempCount = 0;
			}
			else
			{				
			segment[segmentIndex] = *configString;
			segment[segmentIndex + 1] = '\0';
			
			configString++;
			segmentIndex++;
			}
	}
	*numberOfBoxes = boxIndex + 1;
}
