#include "main.h"
#include "global.h"
#include "lcd.h"
#include "autonomous.h"
#include "progSkills.h"

using namespace okapi;

ChassisControllerIntegrated chassis = ChassisControllerFactory::create(
    FRONT_LEFT, -FRONT_RIGHT, BACK_LEFT, -BACK_RIGHT,
    AbstractMotor::gearset::green,
    {6.0_in, 20_in}
);

AsyncMotionProfileController profileController = AsyncControllerFactory::motionProfile(
    0.35,  // Maximum linear velocity of the Chassis in m/s
    0.35,  // Maximum linear acceleration of the Chassis in m/s/s
    5, // Maximum linear jerk of the Chassis in m/s/s/s
    chassis // Chassis Controller
);

void preProgSkills(){//
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{8_ft, 0_ft, 0_deg}},//3.8
    "InFirst8" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{4.5_ft, 0_ft, 0_deg}},//3.8
    "InFirst4" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{1.2_ft, 0_ft, 0_deg}},//3.8
    "InMiddle1" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{4.4_ft, 0_ft, 0_deg}},//3.8
    "InEnd4" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{0.5_ft, 0_ft, 0_deg}},//3.8
    "revB4Stack" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{2.0_ft, 0_ft, 0_deg}},//3.8
    "for4Stack" // Profile name
  );
}

void progSkills(){
  lift(200, 100);
  intake(650);
  int turnAmmount = 75;
  profileController.setTarget("InFirst4");
  profileController.waitUntilSettled();
  delay(100);
  turnRightNonAsync(-turnAmmount,20,2);
  delay(100);
  profileController.setTarget("InMiddle1");
  profileController.waitUntilSettled();
  delay(100);
  turnRightNonAsync(turnAmmount*2,20,2);
  delay(100);
  profileController.setTarget("InMiddle1");
  profileController.waitUntilSettled();
  delay(100);
  turnRightNonAsync(-turnAmmount,20,2);
  delay(100);
  profileController.setTarget("InEnd4");
  profileController.waitUntilSettled();
  delay(100);
  reverseDrive();
  profileController.setTarget("revB4Stack");
  profileController.waitUntilSettled();
  delay(100);
  forwardDrive();
  turnRightNonAsync(-150,20,2);
  delay(100);
  profileController.setTarget("for4Stack");
  profileController.waitUntilSettled();

  intake(-500,200);
  delay(100);
  stackSkills();
  delay(100);
  intake(-200);
  delay(250);
  ramp.move_relative(-1000,50);

  reverseDrive();

  profileController.setTarget("for4Stack");
  profileController.waitUntilSettled();

  intake(0);
  //stack();
}
