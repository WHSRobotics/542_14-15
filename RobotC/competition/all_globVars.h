#ifndef ALL_GLOBVARS.H;
#define ALL_GLOBVARS.H;

bool togglePlate = false;
bool toggleClamp = false;
bool plateOpen = false;
bool clampDown = false;
bool headUp = false;

int tiltState = 1;

const int JOY_THRESH = 16;

//auto program
const float CM_ENCODERVALUE = 35.089279; //The encoder value of the andymark motor[1120]/10.16cm * pi[3.14159...]
const float motorEncoderRot = 1120.0;
const float deltaT = 0.02;

#endif;
