#pragma config(Hubs,  S1, HTServo,  HTServo,  HTServo,  HTMotor)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C4_1,     runBelt,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     goalLift,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_1,     tubeLift,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     centerLift,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     driveL,        tmotorTetrix, openLoop, reversed, driveLeft)
#pragma config(Motor,  mtr_S2_C2_2,     driveR,        tmotorTetrix, openLoop, reversed, driveRight)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    clampL,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    pushL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_5,    liftL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_6,    intake,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_1,    clampR,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    pushR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    liftR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo12,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_1,    headL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    headLid,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    headValve,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    headR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo17,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo18,              tServoNone)

//initialize array of boolean variables//
//have a scrolling function too//
void preAutoSet()
{
	int line = 1;
	bool toggleState = false;
	bool toggleLine = false;
	bool moveOutOfPartnersWay = false;
	while(true)
	{
		int btn = nNxtButtonPressed;
		if(btn == 3)
		{
			if(!toggleState)
			{
				//
			}
			toggleState = true;

		}
		else
		{
			toggleState = false;
		}

		//Toggle Through
		if(btn == 1 || btn == 2)
		{
			if(!toggleLine)
			{
				btn = (nNxtButtonPressed == 2)
				? -1
				:nNxtButtonPressed;
				line = abs(line + btn - 3.5) > 3.5
				? line
				: line+btn;
			}
			toggleLine = true;
		}
		else
		{
			toggleLine = false;
		}
		displayTextLine(1, "");
		displayTextLine(2, "");
		displayTextLine(3, "");
		displayTextLine(4, "");
		displayTextLine(5, "");
		displayTextLine(6, "");
		displayTextLine(7, "");
		sleep(50);
		eraseDisplay();
	}
}

void motorRun()
{
	bool centerNotMain = true;
	bool toggle = false;
	while(true)
	{
		int btn = nNxtButtonPressed;
		if(btn == 3)
		{
			if(!toggle)
			{
				centerNotMain = !centerNotMain;
			}
			toggle = true;
		}
		else
		{
			toggle = false;
		}
		nxtDisplayCenteredBigTextLine(1, "Orange");
		if(centerNotMain)
		{
			nxtDisplayCenteredTextLine(3, "Center Goal Lift");
			sleep(50);
			eraseDisplay();
		}
		else
		{
			nxtDisplayCenteredTextLine(3, "Normal Lift");
			sleep(50);
			eraseDisplay();
		}
		nxtDisplayCenteredTextLine(4,"[ up ]    [down]");
		switch(btn)
		{
			//Left Button
			case 2:
				nxtDisplayCenteredTextLine(5,"[!!!!]     ---- ");
				if(centerNotMain)
				{
					motor[centerLift] = 100;
				}
				else
				{
					motor[tubeLift] = 100;
				}
			break;

			//Right Button
			case 1:
				nxtDisplayCenteredTextLine(5," ----     [!!!!]");
				if(centerNotMain)
				{
					motor[centerLift] = -100;
				}
				else
				{
					motor[tubeLift] = -100;
				}
			break;

			default:
				nxtDisplayCenteredTextLine(5," ----      ---- ");
				motor[tubeLift] = 0;
				motor[centerLift] = 0;
		}
	}
}

task main()
{
	motorRun();
	while(true){}
}
