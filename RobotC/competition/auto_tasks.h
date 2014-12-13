#ifndef AUTO_TASKS.H;
#define AUTO_TASKS.H;

#include "all_globVars.h"
#include "JoystickDriver.c"
#include "hitechnic-angle.h"
#include "hitechnic-gyro.h"

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
}

void raiseTubes()
{
	while(abs(nMotorEncoder[tubeLift]) < TUBE_LIFT_ROT * 1120)
	{
		motor[tubeLift] = 75;
	}
	motor[tubeLift] = 0;
}

void scoreBall()
{
	motor[runBelt] = 100;
	wait10Msec(250);
	motor[runBelt] = 0;
}

void setMotors(int left, int right)
{
	motor[driveL] = left;
	motor[driveR] = right;
}

void encoderReset()
{
	nMotorEncoder[driveL] = 0;
	nMotorEncoder[runBelt] = 0;
}

int encDist(int driveL, int driveR)
{
	return ENCODER_CONV * abs(driveR + driveL)/2.0;
}

float valInRange(float val, float threshold)
{
	return (abs(val) < threshold) ? 0.0 : val;
}

float valInRangeMirror(float val, float upLim, float downLim)
{
	return (abs(val) > downLim && abs(val) < upLim) ? val : 0.0;
}

bool isInRange(float heading, float targetHeading, float threshold = 1.0)
{
	return abs(heading - targetHeading) <= threshold;
}

/*void moveStraightDistance(float distCm, int speedL, int speedR)
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
}*/

//straight
void moveStraight(int power, int distCm, int turnParam)
{
	heading = 0.0;
	encoderReset();
	wait10Msec(25);
	while( (encDist(nMotorEncoder[driveL], nMotorEncoder[runBelt]) < distCm) )
	{
		heading += (valInRange(HTGYROreadRot(HTGYRO), 1.0) * dT); //edit for val in range?
		if(isInRange(heading, 0, 1.0))
		{
			setMotors(power, power);
		}
		else
		{//if going backwards - if heading is left of center (-) reduce right
		//if going back - if heading is right of center (+) reduce left
		//if going forwards - if heading is left of center (-) reduce right
		//if going forwards - if heading is right of center (+) reduce left
			int left = (power > 0)
			? (heading > 0) ? power : power/turnParam
			: (heading > 0) ? power/turnParam : power;
			int right = (power > 0)
			? (heading > 0) ? power/turnParam : power
			: (heading > 0) ? power : power/turnParam;
			setMotors(left, right);
			wait10Msec(2);
		}
	}
	stopDrive();
}

void moveStraightP(int power, int distCm, int turnParam)
{
	heading = 0.0;
	encoderReset();
	wait10Msec(25);
	while( (encDist(nMotorEncoder[driveL], nMotorEncoder[runBelt]) < distCm) )
	{
		writeDebugStreamLine("%f", encDist(nMotorEncoder[driveL], nMotorEncoder[runBelt]));
		heading += valInRange(HTGYROreadRot(HTGYRO), 1.0) * dT; //edit for val in range?
		setMotors(power - (heading * turnParam), power + (heading * turnParam));
		wait10Msec(2);
	}
	stopDrive();
}

//spin
void moveSpin(int power, float angRad)
{
	HTANGresetAccumulatedAngle(HTANG);
	while( abs(HTANGreadAccumulatedAngle(HTANG) * ANG_CONV/ENC_RAD) < angRad )
	{
		setMotors(-power, power);
		writeDebugStreamLine("%f", HTANGreadAccumulatedAngle(HTANG) * ANG_CONV/ENC_RAD);
	}
	stopDrive();
}

//turn
//pivot

/*void moveSpinDistance(float angRad, int speed)
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
}*/



#endif
