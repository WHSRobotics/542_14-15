#pragma config(Sensor, S1,     HTANG,               sensorI2CCustom)
#include "hitechnic-angle.h"
// #include "C:\Documents and Settings\Teemo Time\My Documents\Github\542_14-15\RobotC\drivers\include\hitechnic-angle.h"

//cm
float DIAMETER = 4.8;
float ROBOT_R = 10; //arbitrary robot radius
float TW_X = 3; //arb
float TW_Y = 3; //arb

//int RATIO = (5/3); //gear ratio 20/12

task main()
{
	clearTimer(T1);

	while(true) {
		/* int initRotation = (HTANGreadAccumulatedAngle(HTANG)/360);
		int rotation = \
		\
		(initRotation * RATIO);
		int dist = rotation * getArc(4.8); */

		float arcT = HTANGreadAccumulatedAngle(HTANG)/600.0 * DIAMETER * PI; //arc of tracking wheel (distance turned)
		float x = TW_X + ROBOT_R;a
		float dc = sqrt(pow(x,2) + pow(TW_Y,2)); //radius between center and tracking wheel
		float arcR = ((arcT*ROBOT_R)/dc);

		while(time1[T1] > 100) {
			writeDebugStreamLine("Ang: %7d deg", HTANGreadAngle(HTANG));
			writeDebugStreamLine("Tot: %7d deg", HTANGreadAccumulatedAngle(HTANG));
			writeDebugStreamLine("RPM: %7d", HTANGreadRPM(HTANG));
			writeDebugStreamLine("arc of tracking wheel: %7d, %7d", arcT, arcR);
			writeDebugStreamLine(" < Set angle");
			writeDebugStreamLine("   Reset total >");
			writeDebugStreamLine("");
			clearTimer(T1);
			// RESET CODE
			// If the left button is pressed, set the 0 point to the current angle
			if (nNxtButtonPressed == kLeftButton) {
				HTANGresetAngle(HTANG);
				while (nNxtButtonPressed != kNoButton) EndTimeSlice();

				// Reset the total accumulated angle to 0
				} else if (nNxtButtonPressed == kRightButton) {
				HTANGresetAccumulatedAngle(HTANG);
				while (nNxtButtonPressed != kNoButton) EndTimeSlice();
			} //else if
		} //while
	} //while
} //task
