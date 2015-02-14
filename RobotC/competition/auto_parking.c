#pragma config(Hubs,  S1, HTServo,  HTServo,  HTServo,  HTMotor)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     HTANG,          sensorI2CCustom)
#pragma config(Sensor, S4,     HTGYRO,         sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C4_1,     runBelt,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     goalLift,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_1,     tubeLift,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     driveR,        tmotorTetrix, openLoop, reversed, driveRight)
#pragma config(Motor,  mtr_S2_C2_2,     driveL,        tmotorTetrix, openLoop, driveLeft, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    clampL,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    pushL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    liftL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    intake,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_1,    clampR,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    pushR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    liftR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo12,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_1,    beltGuard,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    headR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    headL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    headL,                tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo17,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo18,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "teleop_tasks.h"
#include "auto_tasks.h"

///////Moving from the parking zone///////

task main()
{
	initializeRobot();
	waitForStart();

	//StartTasks
	startTask(DCControl);
	startTask(servoControl);

	moveStraight(30, -100);

	//moveSpin(-50, 1.5);


	//moveStraight(-50, 220, 2.0);
	headUp = true;
	tubesUp = true;
	plateOpen = true;
	wait10Msec(400);
	StartTask(servoPush);
	while(true){};

	/*moveStraight(50, 30, 2.0);
	clampDown = true;
	moveSpin(-50, 1.0);
	clampDown = false;
	moveStraight(50, 20, 2.0);
	clampDown = true;
	moveStraight(-50, 10, 2.0);
	moveSpin(50, 1.9);
	moveStraight(-50, 120, 2.0);
	plateAngleState = 4;
	intakeIn = true;
	intakeIn = false;*/
}
