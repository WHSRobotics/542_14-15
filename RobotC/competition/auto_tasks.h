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

//float heading = integratedGyroVal;
//float distance = angleSensorval;

float DIAMETER = 4.8

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

void moveStraight(int speed)
{
	while(true)
	{
		float arcT = HTANGreadAccumulatedAngle(HTANG)/600.0 * DIAMETER * PI;
	/*
	resetEncoders();
	while(true)
	{
		if(abs(nMotorEncoder[driveL]) <= distCm * CM_ENCODERVALUE || abs(nMotorEncoder[driveR]) <= distCm * CM_ENCODERVALUE)
		{
			motor[driveR] = speed;
			motor[driveL] = speed;
		}
		else
		{
			motor[driveR] = 0;
			motor[driveL] = 0;
		}
	*/
}
}

void moveArc(float radians, float radiusCm)
{
	resetEncoders();
	while(true)
	{
	}
}

void moveSpin(float distCm, int speed)
{

	/*resetEncoders();
	while(true)
	{
		if(abs(nMotorEncoder[driveL]) <= distCm *CM_ENCODERVALUE || abs(nMotorEncoder[driveR]) <= distCm * CM_ENCODERVALUE)
		{
			motor[driveR] = speed;		//Spins left if speed input is positive
			motor[driveL] = -speed;		//Spins right if speed input is negative
		}
		else
		{
			motor[driveR] = 0;
			motor[driveL] = 0;
		}
	}
	*/

}



#endif
