#include "hitechnic-compass.h"
#include "hitechnic-gyro.h"
#include "hitechnic-accelerometer.h"

tHTMC compass;
tHTGYRO gyroYaw;
tHTGYRO gyroPitch;
tHTAC accel;

float pitch = 0.0;
float yaw = 0.0;
int time = 0;

int x_offset = -20;
int y_offset = -5;
int z_offset = 5;

const float accelConvert = 0.049;
const float gyroConvert = PI/180.0;

const float dT = 0.031;
const float TAU_PITCH = 0.9;
const float TAU_YAW = 0.9;
const float ALPHA_PITCH = TAU_PITCH/(TAU_PITCH + dT);
const float ALPHA_PITCH_COMP = 1.0 - ALPHA_PITCH;

const float ALPHA_YAW = TAU_YAW/(TAU_YAW + dT);
const float ALPHA_YAW_COMP = 1.0 - ALPHA_YAW;

task display()
{
	while(true)
	{
	displayTextLine(1, "dT:%f", time);
	displayTextLine(2, "Pitch:%f", pitch);
	displayTextLine(3, "Yaw:%f", yaw);
	displayTextLine(4, "Tgt: %4d", compass.offset);
  displayTextLine(5, "Abs:   %4d", compass.heading);
  displayTextLine(6, "Rel:   %4d", compass.relativeHeading);
  sleep(100);
  eraseDisplay();
	}
}

task fusion()
{
	while(true)
	{
		while (time1[T1] < 31)
  	{sleep(1);}
    time1[T1]=0;

		readSensor(&gyroPitch);
		pitch += gyroPitch.rotation * dT;
		pitch *= ALPHA_PITCH;
		readSensor(&accel);
		pitch += ALPHA_PITCH_COMP * atan2(accel.y - y_offset, accel.x - x_offset)/gyroConvert;

		readSensor(&gyroYaw);
		yaw += gyroYaw.rotation * dT;
		yaw *= ALPHA_YAW;
		readSensor(&compass);
		yaw += ALPHA_YAW_COMP * compass.relativeHeading;

	}
}

void turn(int setPoint, float Ka,float Kw)
{
	while(true)
	{
		sleep(31);
		int errorAng = setPoint - yaw;
		int wSet = Ka*errorAng;
		int errorW = wSet - gyroYaw.rotation;
		int power = Kw * errorW;
		int power = Kw * Ka * setPoint - Kw * Ka * yaw - Kw * gyroYaw.rotation;
		if(heading == 0)
		{
			//break;
		}
	}
}

task main()
{
	initSensor(&gyroYaw, msensor_S4_1);
	initSensor(&gyroPitch, msensor_S4_2);
	initSensor(&accel, msensor_S4_3);
	initSensor(&compass, msensor_S4_4);
	sensorCalibrate(&gyroYaw);
	sensorCalibrate(&gyroPitch);

	sensorCalibrate(&compass);
	sleep(1000);
	sensorStopCalibrate(&compass);

	readSensor(&compass);
	compass.offset = compass.heading;
	StartTask(display);
	StartTask(fusion);

	//ramp sequence
	moveForward(10, 100);
	while(abs(pitch) > 2)
	{
		moveForward(10, 100);
	}
	//stop robot

	while(true)
	{}
}
