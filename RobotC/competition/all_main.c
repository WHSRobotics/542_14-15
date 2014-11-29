#include "teleop_tasks.h"

intializeRobot()
{
	/*servo[liftR] = 255;
	servo[liftL] = 5;
	servo[clampL] = 255;
	servo[clampR] = 0;
	servo[pushR] = initpos;//findoutdefault
	servo[pushL] = initpos;//findoutdefault
	servo[beltGuard] = initpos;//should be down
	servo[intake] = initpos;//should be up
	*/

	/*muxUpdateInterval = 1;
	servoChangeRate[] = 0;
	servoChangeRate[] = 0;
	servoChangeRate[] = 0;
	servoChangeRate[] = 0;
	servoChangeRate[] = 0;
	servoChangeRate[] = 0;
	servoChangeRate[] = 0;
	servoChangeRate[] = 0;
	servoChangeRate[] = 0;
	servoChangeRate[] = 0;*/

	return;
}

task main()
{
	initializeRobot();
	waitForStart();

	//startTark(servoLift);
	//startTark(servoClamp);
	//startTark(servoPush);

	startTask(drive);
	//startTask(runGoalLift);
	//startTask(raiseTubeLifts);
	//startTask(runIntakeBelt);
	while(true)
	{}
}
