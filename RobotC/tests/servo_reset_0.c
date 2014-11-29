#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_1,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo5,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo6,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task main()
{
	while(true)
	{
		getJoystickSettings(joystick);
		while(joy1Btn(1) == 1)
		{
			servo[servo1] = 25;
			servo[servo4] = 25;
		}
		/*else if(joy1Btn(2) == 1)
		{
			servo[servo2] = 0;
		}
		else if(joy1Btn(3) == 1)
		{
			servo[servo3] = 0;
		}*/
		//else if(joy1Btn(4) == 1)
		//{
		//	servo[servo4] = 0;
		//}
		//else if(joy1Btn(5) == 1)
		//{
		//	servo[servo5] = 0;
		//}
		//else if(joy1Btn(6) == 1)
		//{
		//	servo[servo6] = 0;
		//}
		//else
		//{
		//	wait10Msec(100);
		//}
	}



}