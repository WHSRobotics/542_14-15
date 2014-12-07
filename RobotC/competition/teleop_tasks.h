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

int joyMapLin(int joyIn, int THRESH)
{
	return (abs(joyIn) > THRESH)
	? (int)(joyIn/1.28)
	: 0;
}

int joyMapCurve(int joyIn, int THRESH)
{
	return (abs(joyIn) > THRESH)
	? (int)(100.0/16384.0 * sgn(joyIn) * pow(joyIn,2))
	: 0;
}

//TASKS
task servoPlate()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy2Btn(03))
		{
			if(!togglePlate)
			{
				plateOpen = !plateOpen;
				headUp = true;
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

		if(joystick.joy2_TopHat == 0)
		{
			if(!toggleAngle)
			{
				plateAngleState = ((plateAngleState+1)%3);
			}
			toggleAngle = true;
		}
		else
		{
			toggleAngle = false;
		}

		if(abs(4-joystick.joy2_TopHat) == 2)
		{
			if(!toggleTilt)
			{
				tiltState = (sgn(tiltState) != sgn(4-joystick.joy2_TopHat))
				?tiltState + 4 - joystick.joy2_TopHat
				:tiltState;
				//tiltState -2, 0, 2
				//4-tophat -2, 2
			}
			toggleTilt = true;
		}
		else
		{
			toggleTilt = false;
		}

		switch(plateOpen)
		{
			case true:
				switch(plateAngleState)
				{
					case 1:
						servo[liftR] = 115 + 2*tiltState;
						servo[liftL] = 65 + 2*tiltState ;
						//tall
					break;

					case 0:
						servo[liftR] = 50 + 2*tiltState;
						servo[liftL] = 220 + 2*tiltState;
						//level
					break;

					case 2:
						servo[liftR] = 135 + 2*tiltState;
						servo[liftL] = 95 + 2*tiltState;
						//mid
					break;
				}
				servo[beltGuard] = 0;
				servo[intake] = 200;
			break;

			case false:
				servo[liftR] = 255;
				servo[liftL] = 5;
			break;
		}

		if(joy2Btn(01)&&plateOpen)
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
				servo[clampL] = 145;
				servo[clampR] = 105;
			break;

			case false:
				servo[clampL] = 0;
				servo[clampR] = 255;
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
			if (joy2Btn(04))
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
		motor[goalLift] = joy2Btn(05)
		? 100
		: joy2Btn(07)
		? -75
		: 0;
		motor[runBelt] = (joy1Btn(06))
		? 100
		: (joy1Btn(08))
		? -100
		: 0;
		if(headUp)
		{
			servo[headL] = 20;
			servo[headR] = 230;
		}
		if(joy1Btn(02)&&joy2Btn(02))
		{
			if(abs(nMotorEncoder[tubeLift]) < (5.0 * motorEncoderRot)) // Values need to be changed
			{
				motor[tubeLift] = 75;
			}
		}
		else
		{
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

void checkActive(int THRESH)
{
	if((abs(joystick.joy1_y1) > THRESH) || (abs(joystick.joy1_y2) > THRESH))
	{
		joy1Active = true;
	}
	else
	{
		joy1Active = false;
	}
	if((abs(joystick.joy2_y1) > THRESH) || (abs(joystick.joy2_y2) > THRESH))
	{
		joy2Active = true;
	}
	else
	{
		joy2Active = false;
	}
}

task drive()
{
	while(true)
	{
		getJoystickSettings(joystick);
		checkActive(JOY_THRESH);
		if(joy1Active)
		{
			motor[driveL] = joyMapLin(joystick.joy1_y1, JOY_THRESH);
			motor[driveR] = joyMapLin(joystick.joy1_y2, JOY_THRESH);
		}
		else if(joy2Active)
		{
			motor[driveL] = joyMapLin(-joystick.joy2_y2, JOY_THRESH);
			motor[driveR] = joyMapLin(-joystick.joy2_y1, JOY_THRESH);
		}
		else
		{
			motor[driveL] = 0;
			motor[driveR] = 0;
		}
	}
}

#endif
