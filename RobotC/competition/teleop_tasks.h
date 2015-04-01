#ifndef TELEOP_TASKS.H;
#define TELEOP_TASKS.H;

//INCLUDES
#include "all_globVars.h"
#include "JoystickDriver.c"

//TOGGLE BOOLS
bool togglePlate = false;
bool toggleIntake = false;
bool toggleAngle = false;
bool toggleTilt = false;
bool toggleClamp = false;
bool toggleSlo = false;
bool toggleValve = false;
bool toggleLid = false;

//JOYSTICK ACTIVITY BOOLS
bool joy1Active = false;
bool joy2Active = false;

//FUNCTIONS
//A Value on a defined domain is mapped to a defined range//
//Example usage: Joystick Value to Servo Position//
float linMap(float rLower, float rUpper, float dLower, float dUpper, float dVal)
{
	return (dVal - dLower) * (rUpper - rLower) / (dUpper - dLower)+rLower;
}

//Special Linear Map for Joysticks to drive motors//
int joyMapLin(int joyIn, int THRESH)
{
	return (abs(joyIn) > THRESH)
	? (int)(joyIn/1.28)
	: 0;
}

//TASKS
task servoControl()
{
	while(true)
	{
		getJoystickSettings(joystick);
		//Commands are executed when Button 3 is pressed//
		if(joy2Btn(03))
		{
			//Boolean Conditional here with value setting insures flipflop behavior of plate opening and closing//
			if(!togglePlate)
			{
				if(plateAngleState != 0)
				{
					plateAngleState = 0;
					togglePlate = true;
				}
				else
				{
					plateOpen = !plateOpen;
					headUp = true;
					clampDown = plateOpen;
					togglePlate = true;
					intakeDown = true;
				}
			}
		}
		else
		{
			togglePlate = false;
		}

		//HeadLid State toggle triggered by Joy1Btn4//
		if(joy1Btn(04))
		{
			if(!toggleLid)
			{
				lidClosed = !lidClosed;
			}
			toggleLid = true;
		}
		else
		{
			toggleLid = false;
		}

		//State switch//
		switch(lidClosed)
		{
			case true:
				servo[headLid] = 55;
			break;

			case false:
				servo[headLid] = 0;
			break;
		}

		//headValve State toggle triggered by joy1Btn3//
		if(joy1Btn(03))
		{
			if(!toggleValve)
			{
				valveOpen = !valveOpen;
			}
			toggleValve = true;
		}
		else
		{
			toggleValve = false;
		}

		//state switch//
		switch(valveOpen)
		{
			case true:
				servo[headValve] = 45;
			break;

			case false:
				servo[headValve] = 145;
			break;
		}

		//Intake State toggle triggered by joy2Btn7//
		if(joy2Btn(07))
		{
			if(!toggleIntake)
			{
				intakeDown = !intakeDown;
			}
			toggleIntake = true;
		}
		else
		{
			toggleIntake = false;
		}

		//Commands are executed when the joystick 2 d-pad is at values of 0 or 4 (up and down)//
		if(abs(2-joystick.joy2_TopHat) == 2)
		{
			//Angle of Plate can be changed incrementally by pressing up or down//
			//A specific limit is set so that the angle of the plate cannot decrease past 0//
			if(!toggleAngle)
			{
				plateAngleState = ((float)(abs(plateAngleState + sgn(2-joystick.joy2_TopHat)- ANGLE_MAX/2.0)) > ANGLE_MAX/2.0)
				?plateAngleState
				:plateAngleState + sgn(2-joystick.joy2_TopHat);
			}
			toggleAngle = true;
		}
		else
		{
			toggleAngle = false;
		}

		//Commands are executed when the joystick 2 d-pad is at values of 2 or 6 (left and right)//
		if(abs(4-joystick.joy2_TopHat) == 2)
		{
			//Tilt of Plate can be adjusted incrementally by pressing left or right//
			//No limit set here, drivers moderate visually//
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

		//Commands are executed when the joystick 1 d-pad is at values of 0 or 4 (up and down)//

		//A switch was used as a simple 2 state automata controlling the plate//
		//A switch was also used to keep states mutually exclusive in the while loop//
		//Conditionals instead of switches would have had subsequent execution as soon as the condition was violated//
		switch(plateOpen)
		{
			case true:
				servo[liftR] = 50 + (plateAngleState * ANGLE_GAIN) + (tiltState * TILT_GAIN);
				servo[liftL] = 220 - (plateAngleState * ANGLE_GAIN) + (tiltState * TILT_GAIN);
			break;

			case false:
				servo[liftR] = 255;
				servo[liftL] = 5;
				plateAngleState = 0;
				tiltState = 0;
			break;
		}

		//Command is executed when both the plate is open and Button 1 is pressed//
		if(joy2Btn(01)&&plateOpen)
		{
			if(!toggleClamp)
			{
				//Clamp Down or Clamp off: a boolean acts as a flipflop switch with clear state change//
				clampDown = !clampDown;
			}
			toggleClamp = true;
		}
		else
		{
			toggleClamp = false;
		}

		//State switch//
		switch(headUp)
		{
			case false:
				servo[headL] = 0;
				servo[headR] = 255;
			break;

			case true:
				servo[headL] = 120;
				servo[headR] = 95;
			break;
		}

		//A switch was used as a simple 2 state automata controlling the clamp//
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

		//A switch was used as a simple 2 state automata controlling the intake//
		switch(intakeDown)
		{
			case true:
				servo[intake] = 221;
			break;

			case false:
				servo[intake] = 99;
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
			//A switch was used as a simple 2 state automata controlling the push servos//
			switch(pushOut)
			{
				case false:
					servo[pushR] = 5;
					wait10Msec(10);
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
		//These ternary operators set motor power based on button presses or boolean values//
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

		if(joy1Btn(05)||centerUp)
		{
			motor[centerLift] = 100;
		}
		else if(joy1Btn(07) || centerDown)
		{
			motor[centerLift] = -100;
		}
		//This conditional is to make sure only one set of commands are being run at a time//
		else if(!((joy1Btn(02)&&joy2Btn(02))||tubesUp))
		{
			motor[centerLift] = 0;
		}

		//Automatic Tube lifting (only used in autonomous)//
		if((joy1Btn(02)&&joy2Btn(02))||tubesUp)	//If both joysticks press their button 2 then commit the following command
		{
			motor[tubeLift] = 100;
			motor[centerLift] = -75;
			if(tubesUp)
			{
				//AMY DANIEL ADJUST THIS TIMING AS NECESSARY//
				sleep(4750);
				tubesUp = false;
			}
		}
		//This conditional is to make sure only one set of commands are being run at a time//
		else if(!((joy1Btn(05)||centerUp) || (joy1Btn(07) || centerDown)))
		{
			motor[tubeLift] = 0;
			motor[centerLift] = 0;
		}
	}
}

////////checkActive///////////
//It's purpose is to//////////
//determine which joystick////
//to be given priority to/////

void checkActive(int THRESH)
{
	//If the absolute value of the 1st joystick sticks go past a threshold, show with a boolean that joystick 1 is active
	if((abs(joystick.joy1_y1) > THRESH) || (abs(joystick.joy1_y2) > THRESH))
	{
		joy1Active = true;
	}
	else
	{
		joy1Active = false;
	}
	//If the absolute value of the 2nd joystick sticks go past a threshold, show with a boolean that joystick 2 is active
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
		//If the 1st joystick button 5 is pressed, change which drive mode it is//
		if(joy1Btn(01))
		{
			if(!toggleSlo)
			{
				sloMo = !sloMo;
			}
			toggleSlo = true;
		}
		else
		{
			toggleSlo = false;
		}
		checkActive(JOY_THRESH);
		//The conditionals here allow each drive to move the robot
		//The If - Else-If make sure that their commands are exclusive and that the 1st joystick is prioritized
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
