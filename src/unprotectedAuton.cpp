#include "main.h"
#include "global.h"
#include "lcd.h"
#include "autonomous.h"
#include "initialize.h"
#include "unprotectedAuton.h"

using namespace okapi;



void preUnprotectedAuton(){
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
    Point{4.1_ft, 0_ft, 0_deg}},//3.8
    "Blue Small First" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{2.5_ft, 0_ft, 0_deg}},//2.3
    "Blue Small First Second" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{1.4_ft, 0_ft, 0_deg}},
    "Blue Small Second" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{3_ft, 0_ft, 0_deg}},
    "Blue Small Third" // Profile name
  );
}

void unprotectedAuton(){
  //flip out
  ramp.set_brake_mode(MOTOR_BRAKE_HOLD);
  top_left_mtr.set_brake_mode(MOTOR_BRAKE_HOLD);
  top_right_mtr.set_brake_mode(MOTOR_BRAKE_HOLD);
  bottom_left_mtr.set_brake_mode(MOTOR_BRAKE_HOLD);
  bottom_right_mtr.set_brake_mode(MOTOR_BRAKE_HOLD);
  lift(1450, 100);
  pros::delay(200);
  intake(-650);
  pros::delay(1200);
  lift(100, 100);
  pros::delay(125);
  intake(650);
  top_left_mtr.set_brake_mode(MOTOR_BRAKE_COAST);
  top_right_mtr.set_brake_mode(MOTOR_BRAKE_COAST);
  bottom_left_mtr.set_brake_mode(MOTOR_BRAKE_COAST);
  bottom_right_mtr.set_brake_mode(MOTOR_BRAKE_COAST);
  forwardDrive();
  profileController.setTarget("Blue Small First");
  delay(2000);
  if(lineSensor.get_value()>1400)
    delay(15*1000);
  profileController.waitUntilSettled();
  reverseDrive();
  profileController.setTarget("Blue Small First Second");
  delay(1500);
  intake(0);
  profileController.waitUntilSettled();

  forwardDrive();
  turnRightNonAsync((-340*2+250) * color,46); //40 mmmmmmmmjh213
  profileController.setTarget("Blue Small Second");
  profileController.waitUntilSettled();

  lift(-30, 100);
  intake(-1400,200);
  delay(300);
  int initialPos = ramp.get_position();
  ramp.move_relative(2350,150); //100
  waitUntilTarget(ramp, 2350+initialPos);
  initialPos = ramp.get_position();
  ramp.move_relative(700,40);
  delay(300);
  intake(-1000,350); //100 spd
  delay(150); //500
  reverseDrive();
  profileController.setTarget("Blue Small Third");
  intake(-100);
  profileController.waitUntilSettled();
  intake(0);
}
