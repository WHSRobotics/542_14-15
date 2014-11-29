#pragma config(Sensor, S1,     sensorEOPD,     sensorAnalogActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-eopd.h"

task main()
{
	while(true)
	{
		HTEOPDsetShortRange(S1);
		writeDebugStreamLine("The EOPD value is: %d", HTEOPDreadRaw(sensorEOPD));
		wait10Msec(100);
	}
}