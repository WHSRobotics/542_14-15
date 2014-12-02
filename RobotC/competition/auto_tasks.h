#ifndef AUTO_TASKS.H;
#define AUTO_TASKS.H;

#include "all_globVars.h"

float heading = integratedGyroVal;
float distance = angleSensorval;

void robotExpand()
{
	
}

void stopDrive()
{
	motor[L] = 0;
	motor[R] = 0;
}

void driveSetFor(int speedLeft, int speedRight, int timeSec)
{
	motor[L] = speedLeft;
	motor[R] = speedRight;
}

void moveStraight(float distCm, int speed)
{ 
	if(abs(heading) != 0)
	{
	}
	else
	{
		motor[L] = speed;
		motor[R] = speed;
	}
}

void moveArc(float radians, float radiusCm, int speed)
{
}

void move(float radOrDistCm, float radiusCm, int speed)
{
	if(radiusCm == 0)
	{
		motor[L] = speed;
		motor[R] = -speed;
	}
	else if(abs(radiusCm) == halfWidth)
	{
		if(radiusCm <= 0 && radiusCm >= -halfWidth)
		{
			motor[L] = 0;
			motor[R] = speed;
		}
		else if(radiusCm >= 0 && radiusCm <= halfWidth)
		{
			motor[L] = speed;
			motor[R] = 0;
		}
	}
	else
	{
		motor[L] = speed;
		motor[R] = speed;
	}
}

#endif
