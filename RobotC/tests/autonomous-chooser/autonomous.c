
//code for the menu
#include "menu.h"
#include "JoystickDriver.c"
void initializeRobot ()
{
	//put stuff here later
	return;
}


task main()
{
	//eraseDisplay(); //Clear the NXT screen
	//bDisplayDiagnostics = false; //Takes control away from FCS
	//bNxtLCDStatusDisplay = false; //Takes control away from NXT firmware
	wait1Msec(100);
	runMenu();
	//bDisplayDiagnostics = true; //Returns control back to FCS
  //bNxtLCDStatusDisplay = true; //Returns control back to NXT firmware
  wait1Msec(3000);

  initializeRobot();
  waitForStart();
	//do auto stuff here. sideColor is set in menu.h
	if (teamColor == RED) {
		//do this
		playTone(262, 1);

	}
	if (teamColor == BLUE) {
		//do this
		playTone(270, 1);

	}
} //task
