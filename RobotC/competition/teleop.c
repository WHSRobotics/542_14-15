#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     driveTrainBR,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     driveTrainBL,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     driveTrainTR,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     driveTrainTL,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorGoalLift, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorTubeLifts, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorIntake,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "teleop_tasks.h"

task main()
{
	startTask(runDriveTrain);
	startTask(runGoalLift);
	startTask(raiseTubeLifts);
	startTask(runIntakeBelt);
}
