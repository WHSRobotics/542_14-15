#pragma config(Hubs,  S1, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Servo,  srvo_S1_C1_1,    pushR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    pushL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    clampR,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    clampL,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_5,    beltGuard,            tServoStandard)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_1,    liftR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    liftL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//tube lift defalt upward
//clamp defalt downward
//defalt when game starts
//only goes down when buttons are pressed
//clamps goes up when lift goes down
//clamps only functional when open
//look at toggle genral and fsm or fma
//toggle, push, delay

//Clamp, Push, Plate
//Clamp and Push only functional when Plate is down, otherwise, default positions
//Pause needed between clamp and push
//clear variables regarding state required (instead of a flipstate) - state variables make position?

//Amy! Look here! Look look look!
//program pushers to be open 
//program beltGuardLift done??? check for delay
//program intake set servo check; add teleop drop down

#include "JoystickDriver.c"

float map(float rLower, float rUpper, float dLower, float dUpper, float dVal)
{
	return (dVal - dLower) * (rUpper - rLower) / (dUpper - dLower)+rLower;
}

bool togglePlate = false;
bool toggleClamp = false;
bool plateOpen = false;
bool clampDown = false;

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

task main()
{
	servoInit();
	startTask(lift);
	startTask(push);
	startTask(clamp);
	while(true)
	{
		servo[beltGuard] = map(0, 255, 0, 128, joystick.joy1_y1);
	}
}

/*writeDebugStreamLine("%f, %f", map(0, 255, 0, 128, joystick.joy1_y1),map(0, 255, 128, 0, joystick.joy1_y1));
if(joy1Btn(4))
{
servo[pushR] = 175;
servo[pushL] = 75;
}
else
{
servo[pushR] = 5;
servo[pushL] = 235;
}
servo[liftR] = map(50, 255, 0, 128, joystick.joy1_y2);
servo[liftL] = map(5, 220, 128, 0, joystick.joy1_y2);
servo[clampR] = map(0, 255, 128, 0, joystick.joy1_y1);
servo[clampL] = map(0, 255, 0, 128, joystick.joy1_y1);*/