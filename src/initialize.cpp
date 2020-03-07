#include "main.h"
#include "global.h"
#include "progSkills.h"
#include "unprotectedAuton.h"
#include "protectedAuton.h"
using namespace okapi;

ChassisControllerIntegrated chassis = ChassisControllerFactory::create(
    FRONT_LEFT, -FRONT_RIGHT, BACK_LEFT, -BACK_RIGHT,
    AbstractMotor::gearset::green,
    {6.0_in, 20_in}
);
//skillz
///*
AsyncMotionProfileController profileController = AsyncControllerFactory::motionProfile(
    0.4,  // Maximum linear velocity of the Chassis in m/s
    0.35,  // Maximum linear acceleration of the Chassis in m/s/s
    1, // Maximum linear jerk of the Chassis in m/s/s/s
    chassis // Chassis Controller
);
//*/

//UnprotectedAuton
/*
AsyncMotionProfileController profileController = AsyncControllerFactory::motionProfile(
    1.0,  // Maximum linear velocity of the Chassis in m/s
    .6,  // Maximum linear acceleration of the Chassis in m/s/s
    .6, // Maximum linear jerk of the Chassis in m/s/s/s
    chassis // Chassis Controller
);
*/

//ProtectedAuton
/*
AsyncMotionProfileController profileController = AsyncControllerFactory::motionProfile(
    2.4,  // Maximum linear velocity of the Chassis in m/s // 1.7
    1,  // Maximum linear acceleration of the Chassis in m/s/s
    1, // Maximum linear jerk of the Chassis in m/s/s/s
    chassis // Chassis Controller
);
*/

void on_left_button() {
  if(auton != -5){
  	pros::lcd::set_text(4, "red");
    color = -1;
    auton = -5;
    pros::lcd::set_text(1, "1st btn - unprot - small; 2nd - prot - big");
  }else{
    auton = 5;
    pros::lcd::set_text(4, "SMOL");
    pros::lcd::set_text(1, "re-running init");
    initialize();
  }
}

void on_center_button() {
  if(auton != -5){
  	pros::lcd::set_text(4, "blue");
    color = 1;
    auton = -5;
    pros::lcd::print(1, "1st btn - unprot - small; 2nd - prot - big");
  }else{
    auton = 6;
    pros::lcd::set_text(4, "BIG");
    pros::lcd::set_text(1, "re-running init");
    initialize();
  }
}

void on_right_button() {
	auton = 0;
  initialize();
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	//pros::ADIGyro gyro (GYRO_PORT);
	//pros::delay(5000);
	pros::lcd::initialize();
  pros::lcd::register_btn0_cb(on_left_button);
  pros::lcd::register_btn1_cb(on_center_button);
  pros::lcd::register_btn2_cb(on_right_button);
	pros::lcd::set_text(1, "Starting Initialization");
  if(auton ==5)
    lineSensor.calibrate();
  imuSensor.reset();
  armRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  armLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rollerRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rollerLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  std::string autonTxt = "";
  if(color == 1 && (auton == 5 || auton == 6))
    autonTxt = "BLUE";
  else if(color == -1 && (auton == 5 || auton == 6))
    autonTxt = "RED";

  if(auton == 5)
    autonTxt += "UNPROTECTED - SMALL";
  else if(auton == 6)
    autonTxt += "PROTECTED - BIG BOI";

  pros::lcd::print(0, "%s %d %d",autonTxt, auton, color);
	if(auton == -1)
		preProgSkills();
	else if(auton == 5)
		preUnprotectedAuton();
  else if(auton == 6)
    preProtectedAuton();
  int iter = 0;
  while (imuSensor.is_calibrating()) {
      pros::lcd::print(3, "IMU calibrating... %d", iter);
      iter += 10;
      pros::delay(10);
  }
	pros::lcd::set_text(1, "Finished Initialization");
  pros::lcd::set_text(1, "1st btn - RED; 2nd - BLUE; 3rd - NONE");
	master.rumble(".");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
