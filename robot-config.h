using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;

extern digital_out DiskLoader;
extern digital_out Expansion;

extern motor_group RightDrive;
extern motor_group LeftDrive;
extern motor_group FullDrive;

extern motor Intake;

extern motor Launcher;

using signature = vision::signature;
extern signature Color_BLUE;
extern signature Color_RED;
extern vision Color;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
