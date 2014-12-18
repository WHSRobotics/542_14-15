#ifndef AUTO_TASKS.H;
#define AUTO_TASKS.H;

#include "all_globVars.h"
#include "hitechnic-angle.h"

//odometry based control - position changes - velocity changes
//gyro based control - angular velocity
//encoder based control - position changes of each side - velocity of motors
//compass based control -

void stopDrive()
{
	motor[driveL] = 0;//driveL motor is at 0 power
	motor[driveR] = 0;//driveR motor is at 0 power
}

void resetEncoder()//reseting encoders
{
	HTANGresetAccumulatedAngle(HTANG);
}

void moveStraight(float distCm, int speed)
{
	float distCmActual = HTANGreadAccumulatedAngle(HTANG)/600.0 * DIAMETER * PI;
	while(true)
	{
		if(distCm >= distCmActual)
		{
			motor[driveR] = speed;
			motor[driveL] = speed;
		}
		else
		{
			motor[driveR] = 0;
			motor[driveL] = 0;
		}
	}
	/*
	while(true)
	{
		if(abs(nMotorEncoder[driveL]) <= distCm * CM_ENCODERVALUE || abs(nMotorEncoder[driveR]) <= distCm * CM_ENCODERVALUE)
		{
			motor[driveR] = speed; //spins left if speed input is positive
			motor[driveL] = speed;//spins right if speed input is positive
		}
		else
		{
			motor[driveR] = 0; // doesn't do anything if the speed input is negative or 0
			motor[driveL] = 0; // doesn't do anything if the speed input is negative or 0
		}
	}
	*/
}

void moveArc(float radians, float radiusCm)
{
	resetEncoders();
}

void moveSpin(float distCm, int speed)
{
	float distActual = HTANGreadAccumulatedAngle(HTANG)/600.0 * DIAMETER * PI;
	while(true)
	{
		if(distCm >= arcT)
		{
			motor[driveR] = speed;
			motor[driveL] = -speed;
		}
		else
		{
			motor[driveR] = 0;
			motor[driveL] = 0;
		}
	}
	/*
	while(true)
	{
		if(abs(nMotorEncoder[driveL]) <= distCm *CM_ENCODERVALUE || abs(nMotorEncoder[driveR]) <= distCm * CM_ENCODERVALUE)
		{
			motor[driveR] = speed;		//Spins left if speed input is positive
			motor[driveL] = -speed;		//Spins right if speed input is negative
		}
		else
		{
			motor[driveR] = 0;		//spins nowhere if speed input is negative or 0
			motor[driveL] = 0;		//spins nowhere if speed input is negative or 0
		}
	}
	*/


}



#endif
