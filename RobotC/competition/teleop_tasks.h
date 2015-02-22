#ifndef TELEOP_TASKS.H;
#define TELEOP_TASKS.H;

//INCLUDES
#include "all_globVars.h"
#include "JoystickDriver.c"

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
				plateOpen = !plateOpen;
				headUp = true;
				clampDown = plateOpen;
			}
			togglePlate = true;
		}
		else
		{
			togglePlate = false;
		}

		//Commands are executed when the joystick 2 d-pad is at values of 0 or 4 (up and down)//
		if(abs(2-joystick.joy2_TopHat) == 2)
		{
			//Angle of Plate can be changed incrementally by pressing up or down//
			//A specific limit is set so that the angle of the plate cannot decrease past 0//
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
		if(abs(2-joystick.joy1_TopHat) == 2)
		{
			//Tilt of Redirector (head) can be adjusted incrementally by pressing up and down//
			//A specific limit is set so that it does not go past the full up position// 
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

		//A switch was used as a simple 2 state automata controlling the plate//
		//A switch was also used to keep states mutually exclusive in the while loop//
		//Conditionals instead of switches would have had subsequent execution as soon as the condition was violated//
		switch(plateOpen)
		{
			case true:
				servo[liftR] = 50 + (plateAngleState * ANGLE_GAIN) + (tiltState * TILT_GAIN);
				servo[liftL] = 220 - (plateAngleState * ANGLE_GAIN) + (tiltState * TILT_GAIN);
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
		//Why is this here and not in servo control?//
		if(headUp)
		{
			servo[headL] = 20 + headState * HEAD_GAIN;
			servo[headR] = 230 - headState * HEAD_GAIN;
		}
		//Automatic Tube lifting (only used in autonomous)//
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
		if(joy1Btn(05))
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
