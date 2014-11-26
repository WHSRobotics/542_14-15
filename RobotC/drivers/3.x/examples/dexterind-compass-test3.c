#pragma config(Sensor, S1,     DIMC,           sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: dexterind-compass-test3.c 133 2013-03-10 15:15:38Z xander $
 */

/**
 * dexterind-compass.h provides an API for the Dexter Industries dCompass Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Dexter Industries for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER. 

 * Xander Soldaat (xander_at_botbench.com)
 * 05 April 2012
 * version 0.1
 */

#include "drivers/dexterind-compass.h"

task main ()
{
  // Our local variables
	int fieldX = 0;
	int fieldY = 0;
	int fieldZ = 0;
	int strength = 0;

	// Initialise the sensor
	DIMCinit(DIMC);

	// Loop forever, reading the sensor and calulating total
	// field strength
	while (true)
	{
	  // read the individual axes
		DIMCreadAxes(DIMC, fieldX, fieldY, fieldZ);

		// calculate the field strength
		strength = sqrt(pow(fieldX, 2) + pow(fieldY, 2) + pow(fieldZ, 2));

		// Play a tone of the frequency of the field strength
		// Great for annoying the cat/dog/wife/parent
		PlayImmediateTone(strength, 8);

		// display on the screen
		nxtDisplayCenteredBigTextLine(3, "%d", strength);
		wait1Msec(50);
  }
}

/*
 * $Id: dexterind-compass-test3.c 133 2013-03-10 15:15:38Z xander $
 */
