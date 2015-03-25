#ifndef AUTO_TASKS.H;
#define AUTO_TASKS.H;

#include "all_globVars.h"
#include "JoystickDriver.c"
#include "hitechnic-angle.h"
#include "hitechnic-irseeker-v2.h"
#include "hitechnic-eopd.h"

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
	servo[intake] = 99;
	servo[headL] = 150;
	servo[headR] = 90;
	return;
}

void stopDrive()
{
	motor[driveL] = 0;//driveL motor is at 0 power
	motor[driveR] = 0;//driveR motor is at 0 power
	wait10Msec(75);
}

void scoreBall()
{
	motor[runBelt] = 100;
	wait10Msec(250);
	motor[runBelt] = 0;
}

void setMotors(int left, int right = left)
{
	motor[driveL] = left;
	motor[driveR] = right;
}

void encoderReset()
{
	nMotorEncoder[driveL] = 0;
	nMotorEncoder[runBelt] = 0;
}

bool isInRange(float reference, float compared , float threshold)
{
	return abs(reference - compared) < threshold;
}

void moveStraight(int power, float distCm)
{
	encoderReset();
	power = abs(power) > 70
	? 70
	: power;
	float lastError = 0;
	//distance
	while (nMotorEncoder[driveL]<3000)
	{
		sleep(31);
		float error = nMotorEncoder[tubeLift] + nMotorEncoder[driveL];
		float derivative = error - lastError;
		float turn = (Kp * error)+(Kd*derivative);
		motor[driveR] = power + turn;
		motor[driveL] = power - turn;
		float lastError = error;
	}
}


task sensorWallGuide()
{
	eraseDisplay();
	tHTEOPD eopdSensor;

	initSensor(&eopdSensor, S1);
	//HTEOPDsetShortRange(S1);
	//const int EOPD_MIN_VALUE = 100;
	//const int EOPD_MAX_VALUE = 300;
	while(true)
	{
		eopdSensor.shortRange = true;
		configSensor(&eopdSensor);
		setMotors(70,70);
		wait1Msec(500);
		stopDrive();
	}
}

#endif
