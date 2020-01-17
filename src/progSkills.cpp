#include "main.h"
#include "global.h"
#include "lcd.h"
#include "autonomous.h"

using namespace okapi;

void progSkills(){
  auto chassis = ChassisControllerFactory::create(
      FRONT_LEFT, -FRONT_RIGHT, BACK_LEFT, -BACK_RIGHT,
      AbstractMotor::gearset::green,
      {6.0_in, 20_in}
  );
  auto profileController = AsyncControllerFactory::motionProfile(
      5,  // Maximum linear velocity of the Chassis in m/s
      1.0,  // Maximum linear acceleration of the Chassis in m/s/s
      10.0, // Maximum linear jerk of the Chassis in m/s/s/s
      chassis // Chassis Controller
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{4_ft, 0_ft, 0_deg}},//3.8
    "InFirst4" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{2_ft, 0_ft, 0_deg}},//3.8
    "InMiddle1" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{4.2_ft, 0_ft, 0_deg}},//3.8
    "InEnd4" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{2_ft, 0_ft, 0_deg}},//3.8
    "revB4Stack" // Profile name
  );
  lift(200, 100);
  intake(650);
  profileController.setTarget("InFirst4");
  profileController.waitUntilSettled();
  turnRightNonAsync(-100,20,5);
  profileController.setTarget("InMiddle1");
  profileController.waitUntilSettled();
  turnRightNonAsync(200,20,5);
  profileController.setTarget("InMiddle1");
  profileController.waitUntilSettled();
  turnRightNonAsync(-100,20,5);
  profileController.setTarget("InEnd4");
  profileController.waitUntilSettled();
  reverseDrive();
  profileController.setTarget("revB4Stack");
  profileController.waitUntilSettled();
  turnRightNonAsync(-200,20,5);
  stack();
}
