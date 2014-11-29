#ifndef TELEOP_TASKS.H;
#define TELEOP_TASKS.H;
#include "JoystickDriver.c"

float MOTORRIGHTRUN = joystick.joy1_y2*0.78125;													//
float MOTORLEFTRUN = joystick.joy1_y1*0.78125;													//

task runIntakeBelt
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

task raiseTubeLifts
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

task runGoalLift
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

task runDriveTrain
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
