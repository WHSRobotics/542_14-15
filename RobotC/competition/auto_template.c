#pragma config(Hubs,  S1, HTServo,  HTServo,  HTServo,  HTMotor)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S3,     HTANG,          sensorI2CCustom)
#pragma config(Sensor, S4,     HTCOMP,         sensorI2CHiTechnicCompass)
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
#pragma config(Servo,  srvo_S1_C3_4,    servo16,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo17,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo18,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "teleop_tasks.h"
#include "auto_tasks.h"

task main()
{
	initializeRobot();
	waitForStart();

	//AUTO CODE START//
	//ramp length 58 in. - 147.32//
	//ramp space taken up 56.77 in. - 144.20//
	//extra 15.22 in. - 38.68//

	//To goal intermediate from ramp//
#ifdef
	moveStraight(163.78, -50);
	moveSpin(-PI/2.0, 100);
	moveStraight(76.2, -100);
	moveSpin(PI/2.0, 100);
	moveSpin(0.4636, 100);
#endif
	//

//#ifdef
	startTask(DCControl);
	//to goal intermediate from parking//
	//moveStraight(65.22, -100);
	moveSpin(PI/2, 100);
	moveSpin(-PI/2, 100);
	//moveSpin(-PI/2, 100);
	//moveSpin(-PI/2, 100);
	//moveStraight(102.23, -100);
//#endif

	//to goal + expansion//
#ifdef
	startTask(DCControl);
	startTask(servoControl);
	//plateOpen = true;
	//headUp = true;
	//tubesUp = true;
	//wait10Msec(200);
	//startTask(servoPush);
	moveStraight(140.55, 100);
	//clampDown = true;
#endif

	//goal alignment//




	while(true)
	{
	}
}
