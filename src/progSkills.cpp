#include "main.h"
#include "global.h"
#include "lcd.h"
#include "autonomous.h"
#include "initialize.h"
#include "progSkills.h"


using namespace okapi;

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
    Point{1.7_ft, 0_ft, 0_deg}},//3.8
    "for4Stack" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{0.3_ft, 0_ft, 0_deg}},//3.8
    "for4StackSmol" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{2_ft, 0_ft, 0_deg}},//3.8
    "leftIntoWall" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{0.5_ft, 0_ft, 0_deg}},//3.8
    "rightFromWall" // Profile name
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    Point{10_ft, 0_ft, 0_deg}},//3.8
    "goToZone" // Profile name
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


  turnRightNonAsync(350,20,2);
  delay(1000);

  forwardDrive();
  int v = 30;
  top_left_mtr.move_velocity(-v);
  bottom_left_mtr.move_velocity(v);
  top_right_mtr.move_velocity(v);
  bottom_right_mtr.move_velocity(-v);
  delay(5000);
  top_left_mtr.move_velocity(0);
  top_right_mtr.move_velocity(0);
  bottom_left_mtr.move_velocity(0);
  bottom_right_mtr.move_velocity(0);
  delay(500);
  rightDrive();
  profileController.setTarget("rightFromWall");
  profileController.waitUntilSettled();

  forwardDrive();
  profileController.setTarget("goToZone");
  profileController.waitUntilSettled();


  lift(-100, 100);

  intake(-200,200);
  delay(500);
  int initialPos = ramp.get_position();
  ramp.move_relative(1700,100);
  waitUntilTarget(ramp, 1700+initialPos);
  initialPos = ramp.get_position();
  ramp.move_relative(600,20);
  waitUntilTarget(ramp, 600+initialPos);
  //intake(-100,200);
  //ramp.move_relative(400,30);
  //waitUntilTarget(ramp, 2200+initialPos);
  delay(100);
  profileController.setTarget("for4StackSmol");
  profileController.waitUntilSettled();
  delay(750);
  reverseDrive();
  profileController.setTarget("for4Stack");
  delay(1000);
  ramp.move_relative(-2000,50);
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
