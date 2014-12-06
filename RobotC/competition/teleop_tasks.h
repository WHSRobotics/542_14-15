#ifndef TELEOP_TASKS.H;
#define TELEOP_TASKS.H;

//INCLUDES
#include "all_globVars.h"
#include "JoystickDriver.c"

//FUNCTIONS
float linMap(float rLower, float rUpper, float dLower, float dUpper, float dVal)
{
	return (dVal - dLower) * (rUpper - rLower) / (dUpper - dLower)+rLower;
}

float joyMap(int joyIn, int THRESH)
{
	return (abs(joyIn) > THRESH)
	? (100.0/16384.0 * sgn(joyIn) * pow(joyIn,2))
	: 0;
}

//TASKS
task servoPlate()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(03)&&headUp)
		{
			if(!togglePlate)
			{
				plateOpen = !plateOpen;
				clampDown = plateOpen
				?true
				:false;
			}
			togglePlate = true;
		}
		else
		{
			togglePlate = false;
		}
		switch(plateOpen)
		{
			case true:
				servo[liftR] = 50;
				servo[liftL] = 220;
				servo[beltGuard] = 0;
				servo[intake] = 200;
			break;

			case false:
				servo[liftR] = 255;
				servo[liftL] = 5;
			break;
		}
		//
		if(joy1Btn(01)&&plateOpen)
		{
			if(!toggleClamp)
			{
				clampDown = !clampDown;
			}
			toggleClamp = true;
		}
		else
		{
			toggleClamp = false;
		}
		switch(clampDown)
		{
			case true:
				servo[clampL] = 0;
				servo[clampR] = 255;
			break;

			case false:
				servo[clampL] = 255;
				servo[clampR] = 0;
			break;
		}
	}
}


task servoPush()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(plateOpen)
		{
			if (joy1Btn(04))
			{
				clampDown = !clampDown
				?true
				:clampDown;
				servo[pushL] = 75;
				wait10Msec(10);
				servo[pushR] = 175;
			}
			else
			{
				servo[pushR] = 5;
				wait10Msec(10);
				servo[pushL] = 235;
			}
		}
	}
}

//DC Stuff

task DCControl()
{
	while(true)
	{
		getJoystickSettings(joystick);
		motor[goalLift] = (joy1Btn(05))
		? 100
		: (joy1Btn(07))
		? -100
		: 0;
		motor[runBelt] = (joy1Btn(06))
		? 100
		: (joy1Btn(08))
		? -100
		: 0;
		if(joy1Btn(10))
		{
			headUp = true;
		}
		if(headUp)
		{
			servo[headL] = 20;
			servo[headR] = 230;
		}
		if(joy1Btn(02))
		{
			while(abs(nMotorEncoder[tubeLift]) < (5.0 * motorEncoderRot)) // Values need to be changed
			{
				motor[tubeLift] = 100;
			}
			motor[tubeLift] = 0;
		}
	}
}

//expand order
//head lift and tube lift simultaneously
//raise goal lift a bit
//open plate

//backward drive
//prioritization

task drive()
{
	while(true)
	{
		getJoystickSettings(joystick);
		motor[driveL] = joyMap(joystick.joy1_y1, JOY_THRESH);
		motor[driveR] = joyMap(joystick.joy1_y2, JOY_THRESH);
	}
}

#endif
