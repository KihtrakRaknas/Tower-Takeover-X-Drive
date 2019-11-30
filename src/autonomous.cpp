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
 void lift(double d, double v);
 void move(double d, double v);
 void turnRight(double d, double v);
 void stack();
 void delay(double d);
 void intake(double v);

 double tileDistance = 400;
 double turn90 = 190;

 using namespace okapi;

void autonomous() {
  pros::lcd::print(3, "AUTON 2START");
  pros::lcd::print(4, "AUTON START");
  pros::lcd::print(5, "AUTON START");

  armRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  armLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  /*top_left_mtr.move_relative(500,30);
  top_right_mtr.move_relative(-500,30);
  bottom_left_mtr.move_relative(500,30);
  bottom_right_mtr.move_relative(-500,30);*/
  int FRONT_LEFT = 1;
 int FRONT_RIGHT = -19;
 int BACK_LEFT = -5;
 int BACK_RIGHT = 7;

  auto chassis  = ChassisControllerFactory::create(
  	Motor(FRONT_LEFT), Motor(FRONT_RIGHT), Motor(BACK_LEFT), Motor(BACK_RIGHT)
  );

  //chassis.moveDistance(10000);
  /*lift(3000);
  pros::delay(2000);
  lift(-1000);*/

  /*lift(-1000);
  pros::delay(1000);*/
  intake(0);
  lift(5000,20);
  pros::delay(2200);
  pros::delay(15000);

  intake(650);
  move(200,12);
  delay(5000);
  move(-50,20);
  delay(2000);
  move(400,10);
  delay(4500);
  move(-300,30);
  rollerLeft.move_velocity(0);
  lift(5000,20);
  delay(2500);

  //Red
  turnRight(280,30);
  delay(4000);

  //Blue
  /*turnRight(-280,30);
  pros::delay(3000);*/
  intake(0);
  move(100,20);
  delay(2000);
  stack();
  ramp.move_velocity(50);
  move(50,10);
  delay(100);
  move(-200,30);
  delay(2000);

  /*//RedClose
  intake(650);
  move(tileDistance*.5,20);
  delay(3000);
  turnRight(-turn90);
  delay(3000,25);
  move(tileDistance,20);
  delay(3000);
  turnRight(-turn90*1.5,20);
  delay(3000);intake(0);
  move(100,20);
  delay(2000);
  stack();
  ramp.move_velocity(50);
  move(50,10);
  delay(100);
  move(-200,30);
  delay(2000);
  */

  /*//BlueClose
  intake(650);
  move(tileDistance*.5,20);
  delay(3000);
  turnRight(turn90);
  delay(3000,25);
  move(tileDistance,20);
  delay(3000);
  turnRight(turn90*1.5,20);
  delay(3000);intake(0);
  move(100,20);
  delay(2000);
  stack();
  ramp.move_velocity(50);
  move(50,10);
  delay(100);
  move(-200,30);
  delay(2000);
  */

  /*//Backup
  lift(5000,30);
  delay(6000);
  ramp.move_velocity(100);
  delay(2000);
  ramp.move_velocity(0);
  move(-200,20);
  delay(3000);
  */
}

void delay(double d){
  pros::delay(d);
}
void move(double d, double v){
    top_left_mtr.move_relative(d,v);
    top_right_mtr.move_relative(d,v);
    bottom_left_mtr.move_relative(-d,v);
    bottom_right_mtr.move_relative(-d,v);
}
void intake(double v){
  rollerLeft.move_velocity(v);
}
void stack(){
  ramp.move_velocity(100);
  pros::delay(500);
  move(100,25);
  delay(5000);
  ramp.move_velocity(0);
}
void lift(double d, double v){
  armRight.move_absolute(d, v);
  armLeft.move_absolute(-d, v);
}

void turnRight(double d, double v){
  top_left_mtr.move_relative(d,v);
  top_right_mtr.move_relative(-d,v);
  bottom_left_mtr.move_relative(-d,v);
  bottom_right_mtr.move_relative(d,v);
}
