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

float joyMap(int joyIn, int THRESH, float START_POW)
{
	return (abs(joyIn) > THRESH)
	? ((100.0-START_POW)/16384.0 * sgn(joyIn) * joyIn) + (START_POW * sgn(joyIn))
	: 0;
}

//TASKS
task servoLift()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(01))
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
				servo[beltGuard] = endpos;//arm up
			break;

			case false:
				servo[liftR] = 255;
				servo[liftL] = 5;
			break;
		}
	}
}

task servoClamp()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(03)&&plateOpen)
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
			if (joy1Btn(02))
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
/*
task runIntakeBelt()
{
	if(joy1Btn(0))
	{
		motor[motorIntake] = 100;
	}
	else if(joy1Btn(1))
	{
		motor[motorIntake] = -100;
	}
	else
	{
		motor[motorIntake] = 0;
	}
}

task raiseTubeLifts()
{
	if(joy1Btn(6))
	{
		motor[motorTubeLifts] = 100;
	}
	else if(joy1Btn(8))
	{
		motor[motorTubeLifts] = -100;
	}
	else
	{
		motor[motorTubeLifts] = 0;
	}
}

task runGoalLift()
{
	if(joy1Btn(7))
	{
		motor[motorGoalLift] = 100;
	}
	else if(joy1Btn(9))
	{
		motor[motorGoalLift] = -100;
	}
	else
	{
		motor[motorGoalLift] = 0;
	}
}
*/

task drive()
{
	while(true)
	{
		getJoystickSettings(joystick);
		motor[driveLF] = joyMap(joystick.joy1_y1, 5, 20.0);
		motor[driveLB] = joyMap(joystick.joy1_y1, 5, 20.0);
		motor[driveRF] = joyMap(joystick.joy1_y2, 5, 20.0);
		motor[driveRB] = joyMap(joystick.joy1_y2, 5, 20.0);
	}
}

#endif