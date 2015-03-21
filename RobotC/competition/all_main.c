#pragma config(Hubs,  S1, HTServo,  HTServo,  HTServo,  HTMotor)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C4_1,     runBelt,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     goalLift,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_1,     tubeLift,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     centerLift,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     driveL,        tmotorTetrix, openLoop, reversed, driveLeft)
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
#pragma config(Servo,  srvo_S1_C3_1,    servo13,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    headR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    headL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo16,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo17,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo18,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "teleop_tasks.h"

void initializeRobot()
{
	servo[intake] = 99;
	return;
}

task main()
{
	initializeRobot();
	waitForStart();

	startTask(DCControl);
	startTask(drive);
	startTask(servoControl);
	startTask(servoPush);

	while(true){}
}
