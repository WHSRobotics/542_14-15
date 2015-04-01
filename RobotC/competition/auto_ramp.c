#pragma config(Hubs,  S1, HTServo,  HTServo,  HTServo,  HTMotor)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C4_1,     runBelt,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     goalLift,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_1,     tubeLift,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     centerLift,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     driveL,        tmotorTetrix, openLoop, reversed, driveLeft, encoder)
#pragma config(Motor,  mtr_S2_C2_2,     driveR,        tmotorTetrix, openLoop, reversed, driveRight)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    clampL,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    pushL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_5,    liftL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_6,    intake,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_1,    clampR,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    pushR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    liftR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo12,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_1,    headL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    headLid,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    headValve,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    headR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo17,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo18,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "auto_tasks.h"
#include "teleop_tasks.h"

//------------[AUTO:RAMP START]------------//
//Position: Centered on the ramp           //
//Orientation: Intake forward, sensor forward//
task main()
{
	initializeRobot();
	waitForStart();

	initializeSensors();
	calibrateSensors();
	startTask(sensorPoll);
	startTask(DCControl);
	startTask(servoControl);
	startTask(rampCheck);

	//1. Go down Ramp//
	//!WARNING! THIS MOVE STRAIGHT SHOULD STOP WHEN IT DETECTS THE RAMP HAS ENDED//
	moveStraight(70.0, 180.0);
	//2. Move to IR checking Position//
	moveStraight(70.0, 45.72)
	spinDeg(-90.0);

	//3. IR Beacon Position Search//
	for(int i = 0; i < 20; i++)
	{
		readSensor(&irSeeker);
		if (irSeeker.acValues[2] > 45)
		{
			pos = 1;
		}
		else if(irSeeker.acValues[2] > 25)
		{
			pos = 2;
		}
		else if(irSeeker.acValues[2] != 0)
		{
			pos = 3;
		}
	}

	switch(pos)
	{
		//4a. Knock kickstand Down//
		case 1:
		spinDeg(-45.0);
		moveStraight(70, 122.0);
		spinDeg(45.0);
		moveStraight(70, 100.0);
		break;

		//4b. Knock kickstand Down//
		case 2:
		moveStraight(70.0, 71.0);
		spinDeg(-45.0);
		moveStraight(70.0, 122.0)
		break;

		//4c. Knock kickstand Down//
		case 3:
		moveStraight(70.0, 109.0);
		spinDeg(-90.0);
		moveStraight(70.0, 20.0);
		break;

		//4d. Go to goal//
		default:
		moveStraight(70.0, 61.0);
		spinDeg(90.0);
		moveStraight(70.0, 61.0);
		spinDeg(45.0);
		break;
	}

	//5. Tubes Go Up//
	tubesUp = true;
	//Edit this sleep variable with the tubesUp timing//
	sleep(5000);
	//6. Head Goes Up//
	headUp = true;

	while(true){}
}
