#include "main.h"
#include "global.h"
#include "lcd.h"
#include "autonomous.h"
#include "initialize.h"
#include "protectedAuton.h"

using namespace okapi;



void preProtectedAuton(){
  /*
  auto profileController = AsyncControllerFactory::motionProfile(
      0.35,  // Maximum linear velocity of the Chassis in m/s
      1.0,  // Maximum linear acceleration of the Chassis in m/s/s
      10.0, // Maximum linear jerk of the Chassis in m/s/s/s
      chassis // Chassis Controller
  );
  */
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{0.2_ft, 0_ft, 0_deg}},//3.8
    "Shift" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{0.8_ft, 0_ft, 0_deg}},//2.3
    "Left Shift" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{1.5_ft, 0_ft, 0_deg}},
    "Next Cube 1" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{2.3_ft, 0_ft, 0_deg}},
    "Next Cube 2" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{0.2_ft, 0_ft, 0_deg}},//3.8
    "Smol Shift" // Profile name
  );
}

void protectedAuton(){
  //flip out
  lift(1500, 100);
  pros::delay(200);
  intake(-650);
  pros::delay(1200);
  lift(400, 100);

  pros::delay(100);

  intake(650);

  pros::delay(50);

  leftDrive();
  profileController.setTarget("Left Shift");
  profileController.waitUntilSettled();
  forwardDrive();
  profileController.setTarget("Shift");
  profileController.waitUntilSettled();
  reverseDrive();
  profileController.setTarget("Shift");
  profileController.waitUntilSettled();
  rightDrive();
  profileController.setTarget("Next Cube 1");
  profileController.waitUntilSettled();
  forwardDrive();
  profileController.setTarget("Shift");
  profileController.waitUntilSettled();
  reverseDrive();
  profileController.setTarget("Shift");
  profileController.waitUntilSettled();
  rightDrive();
  profileController.setTarget("Next Cube 2");
  profileController.waitUntilSettled();
  forwardDrive();
  profileController.setTarget("Shift");
  profileController.waitUntilSettled();
  reverseDrive();
  profileController.setTarget("Smol Shift");
  profileController.waitUntilSettled();


  turnRightNonAsync(-340, 40, 2);
  forwardDrive();
  profileController.setTarget("Shift");
  profileController.waitUntilSettled();
  lift(-100, 100);

  intake(-400,50);
  delay(300);
  int initialPos = ramp.get_position();
  ramp.move_relative(1700,100);
  waitUntilTarget(ramp, 1700+initialPos);
  initialPos = ramp.get_position();
  ramp.move_relative(600,20);
  delay(500);
  intake(-600,100);
  delay(500);
  reverseDrive();
  profileController.setTarget("Next Cube 2");
  profileController.waitUntilSettled();
  intake(0);


  /*profileController.setTarget("Blue Small First Second");
  //delay(500);
  //intake(0);
  profileController.waitUntilSettled();
  forwardDrive();
  turnRightNonAsync((-340*2+213) * color,40);
  profileController.setTarget("Blue Small Second");
  profileController.waitUntilSettled();

  lift(-100, 100);

  intake(-400,50);
  delay(300);
  int initialPos = ramp.get_position();
  ramp.move_relative(1700,100);
  waitUntilTarget(ramp, 1700+initialPos);
  initialPos = ramp.get_position();
  ramp.move_relative(600,20);
  delay(500);
  intake(-600,100);
  delay(500);
  reverseDrive();
  profileController.setTarget("Blue Small Third");
  profileController.waitUntilSettled();
  intake(0);*/
}
