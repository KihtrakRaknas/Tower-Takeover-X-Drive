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
    1, // Maximum linear jerk of the Chassis in m/s/s/s
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
    Point{0.4_ft, 0_ft, 0_deg}},//3.8
    "strafeTower" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{1.8_ft, 0_ft, 0_deg}},//3.8
    "InMiddle1" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{4.1_ft, 0_ft, 0_deg}},//3.8
    "InEnd4" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{0.5_ft, 0_ft, 0_deg}},//3.8
    "revB4Stack" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{1.4_ft, 0_ft, 0_deg}},//3.8
    "for4Stack" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{0.3_ft, 0_ft, 0_deg}},//3.8
    "for4StackSmol" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{1_ft, 0_ft, 0_deg}},//3.8
    "for4StackSmol" // Profile name
  );
}

void progSkills(){
  lift(200, 100);
  intake(650);
  profileController.setTarget("InFirst4");
  profileController.waitUntilSettled();
  delay(100);
  leftDrive();
  profileController.setTarget("strafeTower");
  profileController.waitUntilSettled();
  delay(100);
  forwardDrive();
  profileController.setTarget("InMiddle1");
  profileController.waitUntilSettled();
  delay(100);
  rightDrive();
  profileController.setTarget("strafeTower");
  profileController.waitUntilSettled();
  delay(100);
  forwardDrive();
  profileController.setTarget("InEnd4");
  profileController.waitUntilSettled();
  delay(100);
  reverseDrive();
  profileController.setTarget("revB4Stack");
  profileController.waitUntilSettled();
  delay(100);
  forwardDrive();
  turnRightNonAsync(-140,20,2);
  delay(100);
  intake(100);
  profileController.setTarget("for4Stack");
  profileController.waitUntilSettled();

  intake(-50,200);
  delay(100);
  int initialPos = ramp.get_position();
  ramp.move_relative(2000,100);
  waitUntilTarget(ramp, 2000+initialPos);
  initialPos = ramp.get_position();
  ramp.move_relative(200,20);
  waitUntilTarget(ramp, 200+initialPos);
  //intake(-100,200);
  //ramp.move_relative(400,30);
  //waitUntilTarget(ramp, 2200+initialPos);
  delay(100);
  profileController.setTarget("for4StackSmol");
  profileController.waitUntilSettled();
  delay(750);
  ramp.move_relative(-1000,50);

  reverseDrive();
  profileController.setTarget("for4Stack");
  delay(100);
  intake(-200);
  profileController.waitUntilSettled();

  forwardDrive();
  turnRightNonAsync(400,20,2);

  intake(200);

  /*profileController.setTarget("InFirst4");
  profileController.waitUntilSettled();*/

  delay(3000);
  intake(0);
  //stack();
}
