#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);

digital_out DiskLoader = digital_out(Brain.ThreeWirePort.A);
digital_out Expansion = digital_out(Brain.ThreeWirePort.B);

motor RightDriveBack = motor(PORT1, ratio18_1, false);
motor RightDriveMid = motor(PORT2, ratio18_1, false);
motor RightDriveFront = motor(PORT3, ratio18_1, false);
motor_group RightDrive = motor_group(RightDriveBack, RightDriveMid, RightDriveFront);
motor LeftDriveBack = motor(PORT4, ratio18_1, false);
motor LeftDriveMid = motor(PORT5, ratio18_1, false);
motor LeftDriveFront = motor(PORT6, ratio18_1, false);
motor_group LeftDrive = motor_group(LeftDriveBack, LeftDriveMid, LeftDriveFront);
motor_group FullDrive = motor_group(LeftDriveBack, LeftDriveMid, LeftDriveFront, RightDriveBack, RightDriveMid, RightDriveFront);

motor Intake = motor(PORT9, ratio18_1, false);

motor Launcher = motor(PORT10, ratio6_1, false);

inertial Inertial = inertial(PORT8);

signature Color_BLUE = signature(1, -3441, -2785, -3113, 8975, 10355, 9665, 2.5, 0);
signature Color_RED = signature(3, 8099, 8893, 8496, -1505, -949, -1227, 2.5, 0);
vision Color = vision (PORT7, 50, Color_BLUE, Color_RED);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}