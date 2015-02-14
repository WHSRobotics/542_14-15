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
task servoControl()
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
		if(abs(2-joystick.joy2_TopHat) == 2)
		{
			if(!toggleAngle)
			{
				plateAngleState = ((plateAngleState + sgn(2-joystick.joy2_TopHat)) < 0)
				?plateAngleState
				:plateAngleState + sgn(2-joystick.joy2_TopHat);
			}
			toggleAngle = true;
		}
		else
		{
			toggleAngle = false;
		}

		if(abs(4-joystick.joy2_TopHat) == 2)	//If the joystick d-pad is at the 2 or 6 value then commit the following command
		{
			if(!toggleTilt)
			{
				tiltState += sgn(4 - joystick.joy2_TopHat);
			}
			toggleTilt = true;
		}
		else
		{
			toggleTilt = false;
		}
		if(abs(2-joystick.joy1_TopHat) == 2)
		{
			if(!toggleHead)
			{
				headState = ((headState - sgn(2-joystick.joy1_TopHat)) < 0)
				?headState
				:headState - sgn(2-joystick.joy1_TopHat);
			}
			toggleHead = true;
		}
		else
		{
			toggleHead = false;
		}
		switch(plateOpen)
		{
			case true:
				servo[liftR] = 50 + (plateAngleState * angleGain) + (tiltState * tiltGain);
				servo[liftL] = 220 - (plateAngleState * angleGain) + (tiltState * tiltGain);
				servo[beltGuard] = 0;
				servo[intake] = 200;
			break;

			case false:
				servo[liftR] = 255;
				servo[liftL] = 5;
				plateAngleState = 0;
				tiltState = 0;
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
			switch(pushOut)
			{
				case false:
					servo[pushR] = 5;
					wait10msec(10);
					servo[pushL] = 235;
					if(joy2Btn(05))
					{
						pushOut = true;
					}
				break;

				case true:
					clampDown = (!clampDown)
					? true
					: clampDown;
					servo[pushL] = 75;
					wait10Msec(10);
					servo[pushR] = 175;
					if(ServoValue[pushR] == 175)
					{
						pushOut=false;
					}
				break;
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
		motor[goalLift] = (joy2Btn(06) || goalUp)
		? 100
		: (joy2Btn(08) || goalDown)
		? -75
		: 0;
		motor[runBelt] = (joy1Btn(06) || intakeIn)
		? 100
		: (joy1Btn(08) || intakeOut)
		? -100
		: 0;
		if(headUp)
		{
			servo[headL] = 20 + headState * headGain;
			servo[headR] = 230 - headState * headGain;
		}
		if(tubesUp)
		{
			/*
			nMotorEncoder[tubeLift] = 0;
			while(nMotorEncoder[tubeLift] < TUBE_LIFT_ROT)
			{*/
				motor[tubeLift] = 100;
				wait10Msec(490);
				motor[tubeLift] = 0;
				writeDebugStreamLine("encoder %d", nMotorEncoder[tubeLift]);
				tubesUp = false;
			/*}
			motor[tubeLift] = 0;
			tubesUp = false;*/
		}
		if(joy1Btn(02)&&joy2Btn(02))	//If both joysticks press their button 2 then commit the following command
		{
			motor[tubeLift] = 100;
		}
		else
		{
			motor[tubeLift] = 0;
		}
	}
}

////////checkActive///////////
//It's purpose is to//////////
//determine which joystick////
//to be given priority to/////

void checkActive(int THRESH)
{
	if((abs(joystick.joy1_y1) > THRESH) || (abs(joystick.joy1_y2) > THRESH))	//If the absolute value of the 1st joystick sticks go past a threshold, commit the following command
	{
		joy1Active = true;
	}
	else
	{
		joy1Active = false;
	}
	if((abs(joystick.joy2_y1) > THRESH) || (abs(joystick.joy2_y2) > THRESH))	//If the absolute value of the 2nd joystick sticks go past a threshold, commit the following command
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
		if(joy1Btn(05))	//If the 1st joystick button 5 is pressed, commit the following command
		{
			if(!toggleSlo)	//If the toggleSlo is false, then commit the following command
			{
				sloMo = !sloMo;
			}
			toggleSlo = true;
		}
		else
		{
			toggleSlo = false;
		}
		getJoystickSettings(joystick);
		checkActive(JOY_THRESH);
		if(joy1Active)
		{
			if(sloMo)
			{
				motor[driveL] = joyMapLin(0.35*joystick.joy1_y1, 5);
				motor[driveR] = joyMapLin(0.35*joystick.joy1_y2, 5);
			}
			else
			{
				motor[driveL] = joyMapLin(joystick.joy1_y1, JOY_THRESH);
				motor[driveR] = joyMapLin(joystick.joy1_y2, JOY_THRESH);
			}
		}
		else if(joy2Active)
		{
			motor[driveL] = joyMapLin(-joystick.joy2_y2 * 0.35, 5);
			motor[driveR] = joyMapLin(-joystick.joy2_y1 * 0.35, 5);
		}
		else
		{
			motor[driveL] = 0;
			motor[driveR] = 0;
		}
	}
}

#endif
