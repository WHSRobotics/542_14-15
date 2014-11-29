#include "JoystickDriver.c"
int sign(float input)
{
		if (input == 0)
		{
			return 0;
		}
		else
		{
			return input/abs(input);
		}
}

//functions with no inputs, no output > void (type)
//functions with no inputs, ouput > int, float (specific type)
//functions with inputs, outputs > ditto
//functions with inputs, no outputs > void

//if no output > type is void
//if not input > empty parentheses

//if output > specify type, and add in 'return placeholder', outputs placeholder.
//if input > specify type and parameters in parentheses

//int addOne(int x)
//{
//	return x+1;
//}

task main()
{
	while (true)
	{
		getJoystickSettings(joystick);
		if ((joystick.joy1_y1 > 5)||(joystick.joy1_y2 > 5))
		{
			int value = (pow(joystick.joy1_y1,2)/(16129))*80*(sign(joystick.joy1_y1));
			int valuetwo = (pow(joystick.joy1_y2,2)/(16129))*80*(sign(joystick.joy1_y2));
			if (value > 0)
			{
				motor[motorA] = value;
			}
			else
				motor[motorC] = value || valuetwo;
		}
		else
		{
			motor[motorA] = 0;
			motor[motorC] = 0;
		}
	}
}
