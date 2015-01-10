#ifndef ALL_GLOBVARS.H;
#define ALL_GLOBVARS.H;

bool togglePlate = false;
bool toggleAngle = false;
bool toggleClamp = false;
bool toggleTilt = false;
bool toggleSlo = false;
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

bool goalUp = false;
bool goalDown = false;

bool intakeIn = false;
bool intakeOut = false;

bool pushOut = false;
bool tubesUp = false;

const int JOY_THRESH = 16;

//joystick activity vars
bool joy1Active = false;
bool joy2Active = false;

//auto program
const float ENCODER_CONV = PI * 10.16/1120.0;
const float dT = 0.02;
const float ANG_CONV = 7.62 * PI/600.0;
const float ENC_RAD_R = 11.5;
const float ENC_RAD_L = 7.2;
const float TUBE_LIFT_ROT = 5400; //4.9 rots
const float ROBOT_WID = 36.195;

float x = 0.0;
float y = 0.0;
float w = 0.0;

float delta_w = ENCODER_CONV * (nMotorEncoder[runBelt] - nMotorEncoder[driveL])/36.195;
float encDist = ENCODER_CONV * abs(nMotorEncoder[driveL] + nMotorEncoder[runBelt])/2.0;
float delta_x = encDist*cos(w);
float delta_y = encDist*sin(w);


#endif;
