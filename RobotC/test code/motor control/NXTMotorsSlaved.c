#pragma config(Motor,  motorA,          ONE,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          TWO,           tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true)
	{
		int btn = nNxtButtonPressed;
		switch(btn)
		{
			case 2:
				motor[ONE] = 100;
				motor[TWO] = 100;
			break;

			case 1:
				motor[ONE] = -100;
				motor[TWO] = -100;
			break;

			default:
				motor[ONE] = 0;
				motor[TWO] = 0;
		}
	}
}
