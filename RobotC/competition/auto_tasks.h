#ifndef AUTO_TASKS.H;
#define AUTO_TASKS.H;

#include "all_globVars.h"
#include "JoystickDriver.c"

#include "hitechnic-irseeker-v2.h"
#include "hitechnic-angle.h"
#include "hitechnic-compass.h"
#include "hitechnic-gyro.h"
#include "hitechnic-accelerometer.h"

//Sensor Struct Definitions//
tHTGYRO gyroPitch;
tHTGYRO gyroYaw;
tHTGYRO compass;
tHTAC accel;
tHTIRS2 irSeeker;
tHTANG angEnc;

//Strictly Auto Related Variables//
int pos = 0;
bool rampStop = false;
bool rampBottomCheck = false;

void initializeRobot()
{
	servo[liftR] = 255;
	servo[liftL] = 5;
	servo[clampL] = 0;
	servo[clampR] = 255;
	servo[pushR] = 5;
	servo[pushL] = 235;
	servo[intake] = 59;
	servo[headL] = 0;
	servo[headR] = 255;
	servo[headValve] = 145;
	return;
}

//----[SENSOR TASKS AND FUNCTIONS]----//
void measureVelocity(int power)
{
	for(int i = 0; i < 5; i++)
	{
		motor[driveL] = -power;
		motor[driveR] = power;
		sleep(500);
		displayTextLine(i+1,"speed: %f", gyroYaw.rotation * DEG_TO_RAD * ROBOT_H_WID_IN);
	}
	motor[driveL] = 0;
	motor[driveR] = 0;
}

void resetBiasAccel()
{
	for(int i = 1; i<6; i++)
	{
		x_offset += accel.x;
		y_offset += accel.y;
		z_offset += accel.z;
	}
	x_offset /= 5;
	y_offset /= 5;
	z_offset /= 5;
	x_offset += 200;
}

void encoderReset()
{
	nMotorEncoder[driveL] = 0;
	nMotorEncoder[tubeLift] = 0;
}

void initializeSensors()
{
	initSensor(&gyroPitch, msensor_S3_2);
	initSensor(&accel, msensor_S3_1);
	initSensor(&irSeeker, S4);
	//initSensor(&gyroYaw, msensor_S3_3);
	//initSensor(&compass, msensor_S3_4);
	//initSensor(&angEnc, msensor_S3_4);
	irSeeker.mode = DSP_1200;
}

void calibrateSensors()
{
	resetBiasAccel();
	sensorCalibrate(&gyroPitch);
}

//Updates sensor values//
task sensorPoll()
{
	while(true)
	{
		while (time1[T1] < 32)
		{sleep(1);}
		time1[T1]=0;
		readSensor(&gyroPitch);
		pitch += gyroPitch.rotation * dT;
		pitch *= ALPHA_PITCH;
		readSensor(&accel);
		pitch += ALPHA_PITCH_COMP * atan2(accel.x - x_offset, accel.z - z_offset)/DEG_TO_RAD;
		displayTextLine(3, "%f", pitch);
		yaw = ENC_CONV*(nMotorEncoder[tubeLift]-nMotorEncoder[driveL])/ROBOT_WID_CM/DEG_TO_RAD;
	}
}

//Displays sensor values//
task display()
{
	disableDiagnosticsDisplay();
	while(true)
	{
		displayTextLine(2, "Pitch:%f", pitch);
		displayTextLine(3, "Yaw:%f", yaw);
		sleep(100);
		eraseDisplay();
	}
}

//Checks the ramp//
task rampCheck()
{
	while(true)
	{
		if(abs(pitch + 75.0) < 5.0)
		{
			rampBottomCheck = true;
		}
		if(rampBottomCheck)
		{
			if(abs(pitch + 90.0) < 3.0)
			{
				rampStop = true;
				break;
			}
		}
	}
}

//----[AUTO CONTROL FUNCTIONS]----//
void stopDrive()
{
	motor[driveL] = 0;//driveL motor is at 0 power
	motor[driveR] = 0;//driveR motor is at 0 power
	sleep(250);
}

void scoreBall()
{
	motor[runBelt] = 100;
	wait10Msec(250);
	motor[runBelt] = 0;
}

void moveStraight(float power, float distCm)
{
	encoderReset();
	power = abs(power) > 80
	? sgn(power) * 80
: power;
	float Kp = 1.2;
	float Kd = 0.0;
	float lastError = 0;
	float distTravCm = 0.0;

	while(true)
	{
		distTravCm = ENC_CONV*abs(nMotorEncoder[tubeLift] + nMotorEncoder[driveL])/2.0;
		float error = nMotorEncoder[tubeLift] - nMotorEncoder[driveL];
		float derivative = error - lastError;
		float turn = (Kp * error)+(Kd*derivative);
		motor[driveR] = power + turn;
		motor[driveL] = power - turn;
		lastError = error;
		if((abs(distCm - distTravCm) < 1) || rampStop)
		{
			stopDrive();
			break;
		}
	}
	rampStop = false;
	rampBottomCheck = false;
}

//Positive Degrees clockwise, Negative Degrees counter//
void spinDeg(float angDegrees)
{
	encoderReset();
	float Kp = 0.675;
	float Ki = 0.81;
	float Kid = 0.5;
	float errorAng = 0.0;
	float intAng = 0.0;
	float lastError = 0.0;
	float diff = 0.0;
	int loopCount = 0;
	float power = 0.0;

	while(true)
	{
		loopCount += 1;
		errorAng = angDegrees - yaw;
		intAng = intAng * Kid + errorAng;
		power = Kp * errorAng + Ki * intAng;
		diff = errorAng - lastError;

		motor[driveL] = power;
		motor[driveR] = -power;

		lastError = errorAng;
		if(loopCount > (abs(angDegrees)/90.0 * 2100) && abs(diff) < 5.0)
		{
			stopDrive();
			break;
		}
	}
}

#endif
