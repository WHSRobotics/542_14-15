#ifndef AUTO_TASKS.H;
#define AUTO_TASKS.H;

#include "all_globVars.h"
#include "hitechnic-gyro.h"
#include "hitechnic-sensormux.h"
#include "hitechnic-angle.h"
#include "hitechnic-compass.h"

//odometry based control - position changes - velocity changes
//gyro based control - angular velocity
//encoder based control - position changes of each side - velocity of motors
//compass based control -

float heading = integratedGyroVal;
float distance = angleSensorval;

void stopDrive()
{
	motor[driveL] = 0;
	motor[driveR] = 0;
}

void resetEncoders()
{
	nMotorEncoder[driveL] = 0;
	nMotorEncoder[driveR] = 0;
}

void moveStraight(float distCm, int speed)
{
	resetEncoders();
	while(true)
	{

	}
}

void moveArc(float radians, float radiusCm)
{
	resetEncoders();
	while(true)
	{
	}
}

#endif
