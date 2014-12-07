#include "hitechnic-angle.h"

task main()
{
	float convert = 4.8 * PI/600.0;
	while(true)
	{
		int dist = HTANGreadAccumulatedAngle(S4) * convert;
	}
}
