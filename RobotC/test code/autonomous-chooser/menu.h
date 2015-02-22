//menu
TButtons NEXT_BTN = kRightButton;
TButtons PREV_BTN = kLeftButton;
TButtons CAT_BTN = kEnterButton;

typedef enum color
{
	NONE = 0,
	RED = 1,
	BLUE = 2
};

color teamColor = NONE;

bool ramp = false;
bool getGoal = false;

char boolChar(bool val)
{
	return val ? 'T' : 'F';
}

void runMenu()
{
	while(true)
{
	wait10Msec(100);
	eraseDisplay();
	//nxt display
	displayTextLine(1, "%s", "%c", "Ramp:", boolChar(ramp));
	displayString(2, "%s", "%c", "getGoal?:", boolChar(getGoal));

	/*displayCenteredTextLine(0, "What color?");
	displayCenteredTextLine(5, "RED, BLUE");
	wait1Msec(300); //In order to prevent accidental selections
	while(nNxtButtonPressed != CAT_BTN)
		{
		if (nNxtButtonPressed == PREV_BTN) {
			teamColor = RED;
			} else if (nNxtButtonPressed == NEXT_BTN) {
			teamColor = BLUE;

		} // else if
		wait1Msec(300);
	} //while
	eraseDisplay();*/
}
}//void runMenu
