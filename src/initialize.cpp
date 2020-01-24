#include "main.h"
#include "global.h"
#include "progSkills.h"
#include "unprotectedAuton.h"
using namespace okapi;

ChassisControllerIntegrated chassis = ChassisControllerFactory::create(
    FRONT_LEFT, -FRONT_RIGHT, BACK_LEFT, -BACK_RIGHT,
    AbstractMotor::gearset::green,
    {6.0_in, 20_in}
);
//skillz
///*
AsyncMotionProfileController profileController = AsyncControllerFactory::motionProfile(
    0.35,  // Maximum linear velocity of the Chassis in m/s
    0.35,  // Maximum linear acceleration of the Chassis in m/s/s
    1, // Maximum linear jerk of the Chassis in m/s/s/s
    chassis // Chassis Controller
);
//*/

//UnprotectedAuton
/*
AsyncMotionProfileController profileController = AsyncControllerFactory::motionProfile(
    .65,  // Maximum linear velocity of the Chassis in m/s
    1,  // Maximum linear acceleration of the Chassis in m/s/s
    1, // Maximum linear jerk of the Chassis in m/s/s/s
    chassis // Chassis Controller
);
*/
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed...");
	} else {
		pros::lcd::clear_line(2);
	}
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
	pros::lcd::set_text(1, "Starting Initialization");
  armRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  armLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rollerRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rollerLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	if(auton == -1)
		preProgSkills();
	else if(auton == 5)
		preUnprotectedAuton();
	pros::lcd::set_text(1, "Finished Initialization");
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
