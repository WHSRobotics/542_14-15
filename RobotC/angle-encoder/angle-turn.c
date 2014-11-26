#pragma config(Sensor, S1,     HTANG,               sensorI2CCustom)
#include "C:\Documents and Settings\Teemo Time\My Documents\Github\542_14-15\RobotC\drivers\3.x\drivers\hitechnic-angle.h"
// #include "C:\Documents and Settings\Teemo Time\My Documents\Github\542_14-15\RobotC\drivers\include\hitechnic-angle.h"

//cm
float DIAMETER = 4.8; //diameter of tracking wheel
float ROBOT_R = 10; //arbitrary robot radius
float TW_X = 3; //arb
float TW_Y = 3; //arb

//float RATIO = (5/3); //gear ratio 20/12

task main()
{
	clearTimer(T1);

	while(true) {
		/*
		int initRotation = (HTANGreadAccumulatedAngle(HTANG)/360); //amount of rotations
		int rotation = (initRotation * RATIO);
		int dist = rotation * getCirc(4.8); //amount of rotation times circumference of circle of radius 4.8
		*/

		//simplified to ->

		float arcT = HTANGreadAccumulatedAngle(HTANG)/600.0 * DIAMETER * PI; //arc of tracking wheel (distance turned)
		float x = TW_X + ROBOT_R;
		float dc = sqrt(pow(x,2) + pow(TW_Y,2)); //radius between center and tracking wheel
		float arcR = ((arcT*ROBOT_R)/dc);
	}
} //task
