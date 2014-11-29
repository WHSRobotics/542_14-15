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
	motor[LF] = 0;
	motor[LB] = 0;
	motor[RF] = 0;
	motor[RB] = 0;
}

void driveSetFor(int speedLeft, int speedRight, int timeSec)
{
	motor[LF] = speedLeft;
	motor[LB] = speedLeft;
	motor[RF] = speedRight;
	motor[RB] = speedRight;
}

void moveStraight(float distCm, int speed)
{ 
	if(abs(heading) != 0)
	{
	}
	else
	{
	}
}

void moveArc(float radians, float radiusCm, int speed)
{
}

void move(float radOrDistCm, float radiusCm, int speed)
{
	if(radiusCm == 0)
	{
	}
	else if(abs(radiusCm) == halfWidth)
	{
	}
	else
	{
	}
}

#endif