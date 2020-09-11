#ifndef SERVO_H
#define SERVO_H
#endif

//**** SERVO ****

//sets up pin for servo
//channelNumber = 1 => TIM3 CH1, PA6
//channelNumber = 2 => TIM3 CH2, PA7
void setUpServo(int channelNumber);

//sets up angle(0 - 180 degrees) for channelNumber
//channelNumber = 1 => TIM3 CH1, PA6
//channelNumber = 2 => TIM3 CH2, PA7
void setServoAngle(int channelNumber, int angle);

int map(int valueToMap, int in_min, int in_max, int out_min, int out_max);

