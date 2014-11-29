#ifndef TELEOP_TASKS.H;
#define TELEOP_TASKS.H;
#include "JoystickDriver.c"

float heading = integratedGyroVal;
float distance = angleSensorval;

void stopDrive()
{
	motor[LF] = 0;
	motor[LB] = 0;
	motor[RF] = 0;
	motor[RB] = 0;
}

void driveSetFor(int speedLeft, int speedRight, int timeSec)
{
	motor[LF] = speedLeft;
	motor[LB] = speedLeft;
	motor[RF] = speedRight;
	motor[RB] = speedRight;
}

void moveStraight(float distCm, int speed)
{ 
	if(abs(heading) != 0)
	{
	}
	else
	{
	}
}

void moveArc(float radians, float radiusCm, int speed)
{
}

void move(float radOrDistCm, float radiusCm, int speed)
{
	if(radiusCm == 0)
	{
	}
	else if(abs(radiusCm) == halfWidth)
	{
	}
	else
	{
	}
}

void robotExpand()
{
}

float map(float rLower, float rUpper, float dLower, float dUpper, float dVal)
{
	return (dVal - dLower) * (rUpper - rLower) / (dUpper - dLower)+rLower;
}

void servoInit()
{
	servo[liftR] = 255;
	servo[liftL] = 5;
	servo[clampL] = 255;
	servo[clampR] = 0;
	servo[pushR] = initpos;//findoutdefault
	servo[pushL] = initpos;//findoutdefault
	servo[beltGuard] = initpos;//should be down
	servo[intake] = initpos;//should be up
}

task lift()
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


task clamp()
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

task push()
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

float MOTORRIGHTRUN = joystick.joy1_y2*0.78125;													//
float MOTORLEFTRUN = joystick.joy1_y1*0.78125;													//

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

task runDriveTrain()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(abs(joystick.joy1_y1) > 25 || abs(joystick.joy1_y2) > 25)
		{
			motor[driveTrainBR] = MOTORRIGHTRUN;
			motor[driveTrainBL] = MOTORLEFTRUN;
			motor[driveTrainTR] = MOTORRIGHTRUN;
			motor[driveTrainTL] = MOTORLEFTRUN;
		}
		else
		{
			motor[driveTrainBR] = 0;
			motor[driveTrainBL] = 0;
			motor[driveTrainTR] = 0;
			motor[driveTrainTL] = 0;
		}
	}
}

#endif