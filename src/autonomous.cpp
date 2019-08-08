#include "main.h"
#include "global.h"
#include "lcd.h"
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  rollerLeft.move_velocity(350);
  rollerRight.move_velocity(-350);
  top_left_mtr.move_relative(1200,30);
  top_right_mtr.move_relative(-1200,30);
  bottom_left_mtr.move_relative(1200,30);
  bottom_right_mtr.move_relative(-1200,30);
  pros::delay(3500);
  top_left_mtr.move_relative(-900,50);
  top_right_mtr.move_relative(900,50);
  bottom_left_mtr.move_relative(-900,50);
  bottom_right_mtr.move_relative(900,50);
  pros::delay(2200);
  //Red
  top_left_mtr.move_relative(1200,60);
  top_right_mtr.move_relative(1200,60);
  bottom_left_mtr.move_relative(1200,60);
  bottom_right_mtr.move_relative(1200,60);

  //Blue
  /*top_left_mtr.move_relative(-1250,60);
  top_right_mtr.move_relative(-1250,60);
  bottom_left_mtr.move_relative(-1250,60);
  bottom_right_mtr.move_relative(-1250,60);*/
  pros::delay(1800);
  top_left_mtr.move_relative(720,50);
  top_right_mtr.move_relative(-720,50);
  bottom_left_mtr.move_relative(720,50);
  bottom_right_mtr.move_relative(-720,50);
  pros::delay(1800);
  rollerLeft.move_velocity(0);
  rollerRight.move_velocity(0);
  ramp.move_relative(-980,17);
  pros::delay(3300);
  rollerLeft.move_velocity(-100);
  rollerRight.move_velocity(100);
  pros::delay(250);
  top_left_mtr.move_relative(-1400,50);
  top_right_mtr.move_relative(1400,50);
  bottom_left_mtr.move_relative(-1400,50);
  bottom_right_mtr.move_relative(1400,50);
}

void move(double d, double v){
  top_left_mtr.move_relative(d,v);
  top_right_mtr.move_relative(-d,v);
  bottom_left_mtr.move_relative(d,v);
  bottom_right_mtr.move_relative(-d,v);
}
