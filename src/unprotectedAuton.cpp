#include "main.h"
#include "global.h"
#include "lcd.h"
#include "autonomous.h"
#include "unprotectedAuton.h"

using namespace okapi;


/*
void preUnprotectedAuton(){

  ChassisControllerIntegrated chassis = ChassisControllerFactory::create(
      FRONT_LEFT, -FRONT_RIGHT, BACK_LEFT, -BACK_RIGHT,
      AbstractMotor::gearset::green,
      {6.0_in, 20_in}
  );

  auto profileController = AsyncControllerFactory::motionProfile(
      0.35,  // Maximum linear velocity of the Chassis in m/s
      1.0,  // Maximum linear acceleration of the Chassis in m/s/s
      10.0, // Maximum linear jerk of the Chassis in m/s/s/s
      chassis // Chassis Controller
  );

  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{3.8_ft, 0_ft, 0_deg}},//3.8
    "Blue Small First" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{2.2_ft, 0_ft, 0_deg}},//2.3
    "Blue Small First Second" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{1.2_ft, 0_ft, 0_deg}},
    "Blue Small Second" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{1_ft, 0_ft, 0_deg}},
    "Blue Small Third" // Profile name
  );
}

void unprotectedAuton(){
  //flip out
  intake(-650);
  pros::delay(200);
  lift(1000, 100);
  pros::delay(1200);
  intake(650);
  lift(400, 100);
  pros::delay(100);
  profileController.setTarget("Blue Small First");
  profileController.waitUntilSettled();
  delay(100);
  ChassisControllerFactory::create(
       -FRONT_LEFT, FRONT_RIGHT, -BACK_LEFT, BACK_RIGHT,
       AbstractMotor::gearset::green,
       {6.0_in, 20_in}
  );
  profileController.setTarget("Blue Small First Second");
  //delay(500);
  //intake(0);
  profileController.waitUntilSettled();
  ChassisControllerFactory::create(
      FRONT_LEFT, -FRONT_RIGHT, BACK_LEFT, -BACK_RIGHT,
      AbstractMotor::gearset::green,
      {6.0_in, 20_in}
  );
  turnRightNonAsync((-340*2+213) * color,40);
  profileController.setTarget("Blue Small Second");
  profileController.waitUntilSettled();
  intake(-900,200);
  delay(100);
  stack();
  delay(100);
  intake(-200);
  delay(250);
  ChassisControllerFactory::create(
       -FRONT_LEFT, FRONT_RIGHT, -BACK_LEFT, BACK_RIGHT,
       AbstractMotor::gearset::green,
       {6.0_in, 20_in}
   );
  profileController.setTarget("Blue Small Third");
  profileController.waitUntilSettled();
  intake(0);
}
*/
