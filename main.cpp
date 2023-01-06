/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "math.h"
using namespace vex;
#include <cmath>
#include <string>
#include <iostream>
#include <stdio.h>

#include "robot-config.h"
// A global instance of competition
competition Competition;


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void sleep(int time){
  vex::task::sleep(time);
}

int xp;
void touchPos(){
    xp = Brain.Screen.xPosition();
}    

bool teamBlue;
bool isLeft;

/*
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Brain.Screen.clearScreen(vex::color::black);
  Brain.Screen.drawRectangle(0,0,240,240,vex::color::blue);
  Brain.Screen.drawRectangle(240,0,240,240,vex::color::red);
  Brain.Screen.render();

  while(true){
    if(Brain.Screen.pressing()){
      Brain.Screen.pressed(touchPos);
    }
    if (xp<240){
      teamBlue = true;
      Brain.Screen.drawRectangle(0,0,480,240,vex::color::blue);
    }
    else{
      teamBlue = false;
      Brain.Screen.drawRectangle(0,0,480,240,vex::color::red);
    }
  }

  
}
*/


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          AUTONOMOUS FUNCTIONS                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//COLOR SENSOR
void spinRoller(){
  bool isBlue = false;
    Intake.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
    if(teamBlue == false){
      while(isBlue == false){
        Color.takeSnapshot(Color_RED);
        Brain.Screen.print(Color.objectCount);     
        if (Color.objectCount == 0) {
          isBlue = true;
        } 
      }
    }  
    if(teamBlue == true){
      while(isBlue == false){ 
        Color.takeSnapshot(Color_RED);
        Brain.Screen.print(Color.objectCount);
        if (Color.objectCount > 0){
          isBlue = true;
        }
      }  
    }         
  Intake.stop();
}



//AUTONOMOUS DRIVE FUNCTIONS

void stop(){
  LeftDrive.stop();
  RightDrive.stop();
}



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  DiskLoader.set(false);
  Expansion.set(false);

  if (isLeft == true){
    FullDrive.spinFor(vex::directionType::fwd, 1, vex::rotationUnits::rev, 20, vex::velocityUnits::pct);
    spinRoller();
    FullDrive.spinFor(vex::directionType::rev, 1, vex::rotationUnits::rev, 20, vex::velocityUnits::pct);
  }
  if (isLeft == false){

  }
}




/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                       DRIVER CONTROL FUNCTIONS                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

int deadzone(int num){
  return 0.5* num*pow(abs(num), 0.75)/(pow(127, 0.75));
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  Brain.Screen.clearScreen(vex::color::black);
  Brain.Screen.drawRectangle(0,0,240,240,vex::color::blue);
  Brain.Screen.drawRectangle(240,0,240,240,vex::color::red);
  Brain.Screen.setPenColor(white);
  Brain.Screen.drawLine(0, 120, 480, 120);
  Brain.Screen.printAt(100,180,"LEFT");
  Brain.Screen.printAt(100,60,"RIGHT");
  Brain.Screen.printAt(340,180,"LEFT");
  Brain.Screen.printAt(340,60,"RIGHT");
  Brain.Screen.render();
  while (1) {

  wait(5, msec);
  

  
  
    if(Brain.Screen.pressing()){
      if (Brain.Screen.xPosition()<240  && Brain.Screen.yPosition() > 120){
        teamBlue = true;
        isLeft = true;
        Brain.Screen.drawRectangle(0,0,480,240,vex::color::blue);
        Brain.Screen.printAt(200,120,"LEFT");
      }
      else if (Brain.Screen.xPosition()<240 && Brain.Screen.yPosition() < 120) {
        teamBlue = true;
        isLeft = false;
        Brain.Screen.drawRectangle(0,0,480,240,vex::color::blue);
        Brain.Screen.printAt(200,120,"RIGHT");
      }
      else if (Brain.Screen.xPosition()>240 && Brain.Screen.yPosition() > 120) {
        teamBlue = false;
        isLeft = true;
        Brain.Screen.drawRectangle(0,0,480,240,vex::color::red);
        Brain.Screen.printAt(200,120,"LEFT");
      }
      else if (Brain.Screen.xPosition()>240 && Brain.Screen.yPosition() < 120) {
        teamBlue = false;
        isLeft = false;
        Brain.Screen.drawRectangle(0,0,480,240,vex::color::red);
        Brain.Screen.printAt(200,120,"RIGHT");
      }
      Brain.Screen.render();
      
    }
    
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    wait(5, msec); // Sleep the task for a short amount of time to
    
    LeftDrive.spin(vex::directionType::fwd, 0.8*deadzone(Controller1.Axis3.value()), vex::velocityUnits::pct);
    RightDrive.spin(vex::directionType::fwd, 0.8*deadzone(Controller1.Axis2.value()), vex::velocityUnits::pct);

    if(Controller1.ButtonUp.pressing()){
      Expansion.set(true);
    }

    if(Controller1.ButtonDown.pressing()){
      Expansion.set(false);
    }

    while(Controller1.ButtonL1.pressing()){
      Intake.spin(vex::directionType::fwd, 70, vex::velocityUnits::pct);
    }

    while(Controller1.ButtonL2.pressing()){
      Intake.spin(vex::directionType::fwd, -70, vex::velocityUnits::pct);
    }

    if(Controller1.ButtonR2.pressing()){
      Launcher.spin(vex::directionType::fwd, 90, vex::velocityUnits::pct);
      wait(50, msec);
      DiskLoader.set(true);
      wait(5, msec);
      DiskLoader.set(false);
      wait(10, msec);
      Launcher.stop();

    }

    while(Controller1.ButtonY.pressing()){
      Intake.spin(vex::directionType::fwd, 70, vex::velocityUnits::pct);
    }

    if(Controller1.ButtonA.pressing()){
      spinRoller();
    }

  }
}

//
// Main will set up the competition functions and callbacks.
//
int main(){

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  //pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }

}  
