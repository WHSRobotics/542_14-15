#pragma config(Sensor, S1,     HTANG,               sensorI2CCustom)
#include "C:\Program Files\Robomatter Inc\ROBOTC Development Environment\Includes\hitechnic-angle.h"

long getCirc(int DIAMETER)
{
	return(2*PI*DIAMETER);
}

int CONVERSION = (5/3);
task main()
{
	while(true) {
	int initRotation = (HTANGreadAccumulatedAngle(HTANG)/360);
	int rotation = (initRotation * CONVERSION);
	rotation * getCirc(48);
	}
}
