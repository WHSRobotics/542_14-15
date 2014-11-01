#pragma config(Sensor, S1,     HTANG,               sensorI2CCustom)
#include "C:\Documents and Settings\Teemo Time\My Documents\Github\542_14-15\RobotC\drivers\hitechnic-angle.h"

//cm
float DIAMETER = 4.8;
float ROBOT_RADIUS = 10; //arbitrary
float TW_X = 3; //arb
float TW_Y = 3; //arb

long getCirc(int DIAMETER)
{
	return(PI*DIAMETER);
}

//int CONVERSION = (5/3);
task main()
{
	while(true) {
		/* int initRotation = (HTANGreadAccumulatedAngle(HTANG)/360);
		int rotation = (initRotation * CONVERSION);
		int dist = rotation * getCirc(4.8); */
		float arcT = HTANGreadAccumulatedAngle(HTANG)/600.0 * DIAMETER * PI; //arc of tracking wheel (distance turned)
		float x = TW_X + ROBOT_RADIUS;
		float dc = sqrt(pow(x,2) + pow(TW_Y,2)); //radius between center and tracking wheel
		float arcR = ((arcT*ROBOT_RADIUS)/dc);
	}
}
