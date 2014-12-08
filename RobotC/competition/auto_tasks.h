#ifndef AUTO_TASKS.H;
#define AUTO_TASKS.H;

#include "all_globVars.h"
#include "JoystickDriver.c"
#include "hitechnic-angle.h"

//odometry based control - position changes - velocity changes
//gyro based control - angular velocity
//encoder based control - position changes of each side - velocity of motors
//compass based control -

void initializeRobot()
{
	servo[liftR] = 255;
	servo[liftL] = 5;
	servo[clampL] = 0;
	servo[clampR] = 255;
	servo[pushR] = 130;
	servo[pushL] = 75;
	servo[beltGuard] = 255;
	servo[intake] = 0;
	servo[headL] = 150;
	servo[headR] = 90;
	return;
}

void stopDrive()
{
	motor[driveL] = 0;//driveL motor is at 0 power
	motor[driveR] = 0;//driveR motor is at 0 power
	wait10Msec(125);
}

void raiseTubes()
{
	motor[tubeLift] = 75;
	wait10Msec(700);
	motor[tubeLift] = 0;
}

void scoreBall()
{
	motor[runBelt] = 100;
	wait10Msec(250);
	motor[runBelt] = 0;
}

void moveStraight(float distCm, int speedL, int speedR)
{
	HTANGresetAccumulatedAngle(HTANG);
	while(true)
	{
		writeDebugStreamLine("dist: %f", HTANGreadAccumulatedAngle(HTANG) * ANG_CONV);
		if(distCm > abs((HTANGreadAccumulatedAngle(HTANG) * ANG_CONV)))
		{
			motor[driveR] = speedR;
			motor[driveL] = speedL;
		}
		else
		{
			stopDrive();
		}
	}
}

void moveSpin(float angRad, int speed)
{
	HTANGresetAccumulatedAngle(HTANG);
	while(true)
	{
		writeDebugStreamLine("ang: %f", HTANGreadAccumulatedAngle(HTANG) * ANG_CONV/ENC_RAD);
		if(abs(angRad) > abs((HTANGreadAccumulatedAngle(HTANG) * ANG_CONV/ENC_RAD)))
		{
			motor[driveR] = -speed * sgn(angRad);
			motor[driveL] = speed * sgn(angRad);
		}
		else
		{
			stopDrive();
		}
	}
}



#endif
