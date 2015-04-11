#ifndef ALL_GLOBVARS.H;
#define ALL_GLOBVARS.H;

//----[State Control Booleans]----//
bool plateOpen = false;
bool clampDown = false;
bool intakeDown = false;
bool sloMo = false;
bool headUp = false;
int lidClosed = 0;
bool valveOpen = false;

int plateAngleState = 0;
int tiltState = 0;

//----[Action Control Booleans]----//
bool goalUp = false;
bool goalDown = false;

bool centerUp = false;
bool centerDown = false;

bool intakeIn = false;
bool intakeOut = false;

bool pushOut = false;
bool tubesUp = false;

//----[KONSTANTS]----//
//Plate Angle Change Parameters//
const int ANGLE_GAIN = 5;
const int TILT_GAIN = 5;
const float ANGLE_MAX = 15.0;

//Drive Threshold//
const int JOY_THRESH = 16;

//Unit Conversion: Motor Encoder to distance in cm//
const float ENC_CONV = PI * 10.16/1120.0;

//Unit Conversion: Angle Sensor to distance in cm//
const float ANG_CONV = 7.62 * PI/600.0;

//Robot dimension constants//
const float ROBOT_WID_CM = 36.195;
const float ROBOT_H_WID_CM = 18.0975;
const float ROBOT_H_WID_IN = 7.125;

//Unit Conversion: Degrees to Radians//
const float DEG_TO_RAD = PI /180.0;

//Loop time variable//
const float dT = 0.032;

//Complementary Filter parameters//
const float TAU_PITCH = 0.95;
const float ALPHA_PITCH = TAU_PITCH/(TAU_PITCH + dT);
const float ALPHA_PITCH_COMP = 1.0 - ALPHA_PITCH;

//Sensor Values//
int x_offset = 0;
int y_offset = 0;
int z_offset = 0;

float pitch = 0.0;
float yaw = 0.0;

//IR Counters//
int irCounter1 = 0;
int irCounter2 = 0;
int irCounter3 = 0;

#endif;
