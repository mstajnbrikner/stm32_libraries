#ifndef BOXCONFIGURATION_H
#define BOXCONFIGURATION_H
#endif


//configuration parameters for one box
struct boxConfiguration
{
	int boxServoAngle;
	char objectType[10];
	char objectColor[15];
	int objectMinMass;
	int objectMaxMass;
};

//Method to save configuration received from Bluetooth module to boxConfiguration struct array
//Saves number of configured boxes to address from parameter "numberOfBoxes"
void SaveBoxesConfiguration(char* configString, struct boxConfiguration* boxConfig, int* numberOfBoxes);
