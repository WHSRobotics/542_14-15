#ifndef ALL_GLOBVARS.H;
#define ALL_GLOBVARS.H;

bool togglePlate = false;
bool toggleAngle = false;
bool toggleClamp = false;
bool toggleTilt = false;
bool toggleSlo = false;
bool toggleMouth = false;
bool toggleHead = false;

bool plateOpen = false;
bool clampDown = false;
bool sloMo = false;
bool headUp = false;

int plateAngleState = 0;
int angleGain = 5;
int tiltState = 0;
int tiltGain = 5;
int headState = 0;
int headGain = 10;

int mouthState = -1;

bool mouthRun = false;

bool goalUp = false;
bool goalDown = false;

bool intakeIn = false;
bool intakeOut = false;

bool pushOut = false;
bool tubesUp = false;

bool dowelUp = false;
bool dowelDown = false;

const int JOY_THRESH = 16;

//joystick activity vars
bool joy1Active = false;
bool joy2Active = false;

//auto program
const float CM_ENCODERVALUE = 35.089279; //The encoder value of the andymark motor[1120]/10.16cm * pi[3.14159...]
const float ENCODER_CONV = PI * 10.16/1120.0;
const float dT = 0.02;
const float ANG_CONV = 7.62 * PI/600.0;
const float ENC_RAD = 11.5;
const float TUBE_LIFT_ROT = 5400; //4.9 rots
float heading = 0.0;

#endif;
