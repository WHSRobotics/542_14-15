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
int ANGLE_GAIN = 5;
int tiltState = 0;
int TILT_GAIN = 5;
int headState = 0;
int HEAD_GAIN = 10;

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
const float TUBE_LIFT_ROT = 5125; //4.9 rots
const float ROBOT_WID = 36.195;

float encDist = ENCODER_CONV * abs(nMotorEncoder[driveL] + nMotorEncoder[runBelt])/2.0;

int IR_A, IR_B, IR_C, IR_D, IR_E;


#endif;
