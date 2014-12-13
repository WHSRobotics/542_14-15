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
//////Servo Plate Task///////
task servoPlate()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy2Btn(03))																															//If button 3 is pressed follow through with the following command
		{
			if(!togglePlate)																													//If the boolean togglePlate is false then commit the following command
			{
				plateOpen = !plateOpen;																									//plateOpen boolean is set to true
				headUp = true;																													//headUp boolean is set to true
				clampDown = plateOpen																										//clampDown boolean value is determined by plateOpen boolean value
				?true																																		//If plateOpen is true, then clampDown is set to true
				:false;																																	//Else, clampDown is set to false
			}
			togglePlate = true;																												//togglePlate is set to true
		}
		else
		{
			togglePlate = false;																											//togglePlate is set to false if the 2nd joystick button 3 is not pressed
		}

		//Edit
		if(abs(2-joystick.joy2_TopHat) == 2)																				//If the joystick d-pad is at the 2 value then commit the following command
		{
			if(!toggleAngle)																													//If the toggleAngle value is false, then commit the following command
			{
				plateAngleState = ((plateAngleState + sgn(2-joystick.joy2_TopHat)) < 0)	//
				?plateAngleState
				:plateAngleState + sgn(2-joystick.joy2_TopHat);
			}
			toggleAngle = true;
		}
		else
		{
			toggleAngle = false;
		}
		//End edit

		if(abs(4-joystick.joy2_TopHat) == 2)
		{
			if(!toggleTilt)
			{
				tiltState = (sgn(tiltState) != sgn(4-joystick.joy2_TopHat))
				?tiltState + sgn(4 - joystick.joy2_TopHat)
				:tiltState;
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
			if (joy2Btn(05))
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
		getJoystickSettings(joystick);																							//Get the joystick settings from include file JoystickDriver
		motor[goalLift] = joy2Btn(06)																								//If the 2nd joystick button 6 is pressed commit following command
		? 100																																				//Motor[goalLift] power will be set to 100
		: joy2Btn(08)																																//Else if the 2nd joystick button 8 is pressed commit following command
		? -75																																				//motor[goalLift] power will be set to -75
		: 0;																																				//Else the motor[goalLift] power will be set to 0
		motor[runBelt] = (joy1Btn(06))																							//If the 1st joystick button 6 is pressed commit following command
		? 100																																				//Motor[runBelt] power will be set to 100
		: (joy1Btn(08))																															//Else if the 1st joystick button 8 is pressed commit following command
		? -100																																			//motor[goalLift] power will be set to -100
		: 0;																																				//Else the motor[goalLift] power will be set to 0
		if(headUp)																																	//If headUp is true then commit following command
		{
			servo[headL] = 20;																												//servo[headL] is set to 20
			servo[headR] = 230;																												//servo[headR] is set to 230
		}
		if(joy1Btn(02)&&joy2Btn(02))																								//If both joysticks press their button 2 then commit the following command
		{
			if(abs(nMotorEncoder[tubeLift]) < (5.0 * motorEncoderRot))								//If the absolute value of the motorEncoder[tubeLift] is less than 5600 commit following command
			{
				motor[tubeLift] = 75;																										//Have motor[tubeLift] set to power 75
			}
		}
		else
		{
			motor[tubeLift] = 0;																											//Else motor[tubeLift] is set to power 0
		}
	}
}
////////checkActive///////////
//It's purpoes is to//////////
//determine which joystick////
//to be given priority to/////
void checkActive(int THRESH)
{
	if((abs(joystick.joy1_y1) > THRESH) || (abs(joystick.joy1_y2) > THRESH))			//If the absolute value of the 1st joystick sticks go past a threshold, commit the following command
	{
		joy1Active = true;																													//1st joystick is active
	}
	else
	{
		joy1Active = false;																													//Else the 1st joystick is not active
	}
	if((abs(joystick.joy2_y1) > THRESH) || (abs(joystick.joy2_y2) > THRESH))			//If the absolute value of the 2nd joystick sticks go past a threshold, commit the following command
	{
		joy2Active = true;																													//2nd joystick is active
	}
	else
	{
		joy2Active = false;																													//Else the 2nd joystick is not active
	}
}

task drive()
{
	while(true)
	{
		if(joy1Btn(05))																															//If the 1st joystick button 5 is pressed, commit the following command
		{
			if(!toggleSlo)																														//If the toggleSlo is false, then commit the following command
			{
				sloMo = !sloMo;																													//sloMo is set to true
			}
			toggleSlo = true;																													//toggleSlo is set to true
		}
		else
		{
			toggleSlo = false;																												//toggleSlo is set to false
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
