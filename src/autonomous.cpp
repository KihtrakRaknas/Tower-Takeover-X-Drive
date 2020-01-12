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
void moveDistSide(double dist, double v);
 void lift(double d, double v);
 void move(double d, double v);
 void turnRight(double d, double v);
 void turnRightNonAsync(double d, double v);
 void stack();
 void delay(double d);
 void intake(double v);
 void intake(double d, double v);
 void liftPot(int leftVal, int rightVal);
 void moveDist(double dist, double v);
 double tileDistance = 400;
 double turn90 = 190;

 using namespace okapi;

void autonomous() {

  armRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  armLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  /*top_left_mtr.move_relative(500,30);
  top_right_mtr.move_relative(-500,30);
  bottom_left_mtr.move_relative(500,30);
  bottom_right_mtr.move_relative(-500,30);*/
  int FRONT_LEFT = 1;
 int FRONT_RIGHT = 19;
 int BACK_LEFT = 5;
 int BACK_RIGHT = 7;
 int auton = 5; //5 is small and 6 is Big
 int color = 1; //1 is blue and -1 is red
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
if(auton == 5){
  auto profileController = AsyncControllerFactory::motionProfile(
      0.35,  // Maximum linear velocity of the Chassis in m/s
      1.0,  // Maximum linear acceleration of the Chassis in m/s/s
      10.0, // Maximum linear jerk of the Chassis in m/s/s/s
      chassis // Chassis Controller
  );
}


armRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
armLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
if(auton==5){
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
}else if(auton == 6){
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},
    Point{4.0_ft, 0_ft, 0_deg}},
    "Blue Large First"
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},
    Point{0.8_ft, 0_ft, 0_deg}},
    "Blue Large First Second"
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},
    Point{3.5_ft, 0_ft, 0_deg}},
    "Blue Large Second"
  );
  profileController.generatePath({
    Point{0_ft, 0_ft, 0_deg},
    Point{1_ft, 0_ft, 0_deg}},
    "Blue Large Third"
  );
  //flip out
  intake(-650);
  pros::delay(200);
  lift(1000, 100);
  pros::delay(1200);
  intake(650);
  lift(350, 100);
  profileController.setTarget("Blue Large First");
  profileController.waitUntilSettled();
  delay(100);
  ChassisControllerFactory::create(
       -FRONT_LEFT, FRONT_RIGHT, -BACK_LEFT, BACK_RIGHT,
       AbstractMotor::gearset::green,
       {6.0_in, 20_in}
  );
  profileController.setTarget("Blue Large First Second");
  delay(500);
  //intake(0);
  profileController.waitUntilSettled();
  ChassisControllerFactory::create(
      FRONT_LEFT, -FRONT_RIGHT, BACK_LEFT, -BACK_RIGHT,
      AbstractMotor::gearset::green,
      {6.0_in, 20_in}
  );
  turnRightNonAsync((340*2-220) * color,40);
  profileController.setTarget("Blue Large Second");
  profileController.waitUntilSettled();
  intake(-1200,200);
  //delay(500);
  stack();
  intake(-200);
  delay(230);
  ChassisControllerFactory::create(
       -FRONT_LEFT, FRONT_RIGHT, -BACK_LEFT, BACK_RIGHT,
       AbstractMotor::gearset::green,
       {6.0_in, 20_in}
   );
  profileController.setTarget("Blue Large Third");
  profileController.waitUntilSettled();
  intake(0);
}else if(auton==0){//Big Red
moveDist(0.5,5);
//liftPot(240,3090);
//liftPot(220,3100);
lift(1500, 100);
pros::delay(1000);
intake(-650);
lift(-500, 100);
//pros::delay(1000);

//pros::delay(15000);
//liftPot(220,3100);
//liftPot(220,3100);
pros::delay(2000);
intake(0);
moveDistSide(1.75,20);
pros::delay(500);
moveDist(-5,30);
pros::delay(1000);
turnRight(195,40);
pros::delay(1000);
moveDist(-1,20);
pros::delay(500);
moveDistSide(4,30);
pros::delay(1000);
intake(750);
moveDist(5,30);
pros::delay(1500);
/*moveDist(13, 20);
pros::delay(3000);
moveDist(-7, 20);
pros::delay(2200);*/
turnRight(-195,40);
pros::delay(1000);
intake(650);
moveDist(9, 40);
pros::delay(1500);
turnRight(-97.5,40);
pros::delay(500);
lift(5000,200);
moveDist(7,30);
//ramp.move_velocity(-90);
pros::delay(500);
ramp.move_velocity(-90);
delay(2000);
ramp.move_velocity(0);
pros::delay(15000);
  /*lift(-1000);
  pros::delay(1000);*/
  //intake(0);
  //lift(5000,20);
/*  liftPot(260,3100);
  intake(650);
  pros::delay(2200);
  pros::delay(15000);

  intake(650);
  move(200,12);
  delay(5000);
  move(-50,20);
  delay(2000);
  move(400,10);
  delay(4500);
  move(-400,30);
  rollerLeft.move_velocity(0);
  lift(5000,20);
  delay(2500);

  turnRight(280,30);
  delay(4000);

  intake(0);
  move(100,20);
  delay(2000);
  stack();
  //ramp.move_velocity(50);
  move(50,10);
  delay(100);
  move(-200,30);
  delay(2000);*/
}
else if(auton==1){//BlueBig
  moveDist(0.5,5);
  //liftPot(240,3090);
  //liftPot(220,3100);
  lift(1500, 100);
  pros::delay(1000);
  intake(-650);
  lift(-500, 100);
  //pros::delay(1000);

  //pros::delay(15000);
  //liftPot(220,3100);
  //liftPot(220,3100);
  pros::delay(2000);
  intake(0);
  moveDistSide(-1.75,20);
  pros::delay(500);
  moveDist(-5,30);
  pros::delay(1000);
  turnRight(-195,40);
  pros::delay(1000);
  moveDist(-1,20);
  pros::delay(500);
  moveDistSide(-4,30);
  pros::delay(1000);
  intake(750);
  moveDist(5,30);
  pros::delay(1500);
  /*moveDist(13, 20);
  pros::delay(3000);
  moveDist(-7, 20);
  pros::delay(2200);*/
  turnRight(195,40);
  pros::delay(1000);
  intake(650);
  moveDist(9, 40);
  pros::delay(1500);
  turnRight(97.5,40);
  pros::delay(500);
  lift(5000,200);
  moveDist(7,30);
  //ramp.move_velocity(-90);
  pros::delay(500);
  ramp.move_velocity(-90);
  delay(1000);
  ramp.move_velocity(0);
  pros::delay(15000);
  }
  else if(auton==2){//RedSmall
    moveDist(0.5,5);
    lift(2000, 200);
    pros::delay(1000);
    lift(-2000,200);
    intake(650);
    move(200,12);
    delay(3000);
    move(-50,20);
    delay(700);
    move(400,15);
    delay(2000);
    move(-250,30);
    delay(1800);
    intake(0);
    turnRight(280,30);
    delay(2000);
    move(100,20);
    delay(1000);
    lift(5000,20);
    delay(2500);
    ramp.move_velocity(-90);
    pros::delay(1500);
    ramp.move_velocity(0);
    move(-50,20);
  }
  else if(auton==3){//BlueSmall

    moveDist(0.5,5);
    lift(1500, 100);
    pros::delay(1000);
    lift(-1500,100);
    intake(650);
    move(200,12);
    delay(3000);
    move(-50,20);
    delay(700);
    move(400,15);
    delay(2000);
    move(-250,30);
    delay(1800);
    intake(0);
    turnRight(-280,30);
    delay(2000);
    move(100,20);
    delay(1000);
    lift(5000,20);
    delay(2500);
    ramp.move_velocity(-90);
    pros::delay(1500);
    ramp.move_velocity(0);
    move(-50,20);
  }

  ChassisControllerFactory::create(
      FRONT_LEFT, FRONT_RIGHT, BACK_LEFT, BACK_RIGHT,
      AbstractMotor::gearset::green,
      {6.0_in, 20_in}
  );
}

void delay(double d){
  pros::delay(d);
}
void move(double d, double v){
    top_left_mtr.move_relative(d,v);
    top_right_mtr.move_relative(d*-1,v);
    bottom_left_mtr.move_relative(-d*-1,v);
    bottom_right_mtr.move_relative(-d,v);
}
void moveDist(double dist, double v){
    double tickNum = (90.0 / 3.14) * dist;
    top_right_mtr.move_relative(tickNum*-1, v);
    bottom_right_mtr.move_relative(-tickNum, v);
    top_left_mtr.move_relative(tickNum, v);
    bottom_left_mtr.move_relative(-tickNum*-1, v);
}
void moveDistSide(double dist, double v){ //to right
  double tickNum = (90.0 / 3.14) * dist;
  top_right_mtr.move_relative(-tickNum*-1, v);
  bottom_right_mtr.move_relative(-tickNum, v);
  top_left_mtr.move_relative(tickNum, v);
  bottom_left_mtr.move_relative(tickNum*-1, v);
}
void moveDistControl(double dist, double v){
  double target_tick = (90.0 / PI) * dist;
}


#define THRESH 10
void waitUntilTarget(int topLeftTarget,int topRightTarget,int bottomLeftTarget,int bottomRightTarget){
  while(abs(top_left_mtr.get_position()-topLeftTarget)>THRESH && abs(top_right_mtr.get_position()-topRightTarget)>THRESH && abs(bottom_left_mtr.get_position()-bottomLeftTarget)>THRESH && abs(bottom_right_mtr.get_position()-bottomRightTarget)>THRESH ){
    pros::delay(20);
  }
  return;
}

void waitUntilTarget(pros::Motor motor, int target){
  while(abs(motor.get_position()-target)>THRESH){
    pros::delay(20);
  }
  return;
}


void intake(double v){
  rollerLeft.move_velocity(v);
  rollerRight.move_velocity(-v);
}
void intake(double d,double v){
  rollerLeft.move_relative(d,v);
  rollerRight.move_relative(-d,-v);
}
void stack(){
  int initialPos = ramp.get_position();
  ramp.move_relative(3000,200);
  waitUntilTarget(ramp, 3000+initialPos);
  ramp.move_relative(500,200);
  waitUntilTarget(ramp, 3500+initialPos);
  ramp.move_relative(-4000,200);
}

void lift(double d, double v){
  armRight.move_absolute(d, v);
  armLeft.move_absolute(-d, v);
}

void turnRight(double d, double v){
  top_left_mtr.move_relative(d,v);
  top_right_mtr.move_relative(-d,v);
  bottom_left_mtr.move_relative(d,v);
  bottom_right_mtr.move_relative(-d,v);
}

void turnRightNonAsync(double d, double v){ // 340 is a perfect right turn
  turnRight(d,v);
  waitUntilTarget(top_left_mtr.get_position()+d,top_right_mtr.get_position()-d,bottom_left_mtr.get_position()+d,bottom_right_mtr.get_position()-d);
}

void liftPot(int leftVal, int rightVal){
  if(leftVal>potLeft.get_value()){
    while(leftVal>potLeft.get_value() || rightVal<potRight.get_value()){
      pros::lcd::print(1, "UP 7START");
      pros::lcd::print(2, "L: %d; R: %d", potLeft.get_value(), potRight.get_value());
      std::cout << "r" << std::endl;
      if(leftVal>potLeft.get_value())
        armLeft.move_velocity(-100); //UP
      else
        armLeft.move_velocity(0); //UP

      if(rightVal<potRight.get_value())
        armRight.move_velocity(100); //UP
      else
        armRight.move_velocity(0);
    }
  }else{
    while(leftVal<potLeft.get_value() || rightVal>potRight.get_value()){
      pros::lcd::print(1, "DOWN 5START");
      if(leftVal<potLeft.get_value())
        armLeft.move_velocity(100); //DOWN
      else
        armLeft.move_velocity(0); //UP
      if(rightVal>potRight.get_value())
        armRight.move_velocity(-100); //DOWN
      else
        armRight.move_velocity(0);
    }
  }
  armLeft.move_velocity(0);
  armRight.move_velocity(0);
}
