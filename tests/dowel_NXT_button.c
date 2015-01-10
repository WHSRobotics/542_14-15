#pragma config(Hubs,  S1, HTServo,  HTServo,  HTServo,  HTMotor)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     HTANG,          sensorI2CCustom)
#pragma config(Sensor, S4,     HTGYRO,         sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C4_1,     runBelt,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     goalLift,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     tubeLift,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     dowelLift,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     driveR,        tmotorTetrix, openLoop, reversed, driveRight)
#pragma config(Motor,  mtr_S2_C2_2,     driveL,        tmotorTetrix, openLoop, driveLeft, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    clampL,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    pushL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    liftL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    intake,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_1,    clampR,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    pushR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    liftR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo12,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_1,    beltGuard,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    headR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    headL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    headL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo17,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo18,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//goal lift encoder - tube lift//
//run belt encoder - right drive train//
//drive L encoder - left drive train//

task main()
{
	while(true)
	{
		int btn = nNxtButtonPressed;
		switch(btn)
		{
			case 2:
				motor[dowelLift] = 100;
			break;

			case 1:
				motor[dowelLift] = -100;
			break;

			default:
				motor[dowelLift] = 0;
		}
	}
}