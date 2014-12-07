#ifndef ALL_GLOBVARS.H;
#define ALL_GLOBVARS.H;

bool togglePlate = false;
bool toggleAngle = false;
bool toggleClamp = false;
bool toggleTilt = false;

bool plateOpen = false;
bool clampDown = false;
bool headUp = false;

int plateAngleState = 0;
int tiltState = 0;
int tiltGain = 5;

const int JOY_THRESH = 16;

//joystick activity vars
bool joy1Active = false;
bool joy2Active = false;

//auto program
const float CM_ENCODERVALUE = 35.089279; //The encoder value of the andymark motor[1120]/10.16cm * pi[3.14159...]
const float motorEncoderRot = 1120.0;
const float deltaT = 0.02;

#endif;
