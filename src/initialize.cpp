#include "main.h"
#include "global.h"
using namespace okapi;
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
	pros::ADIGyro gyro (GYRO_PORT);
	//pros::delay(5000);
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!!");
	/*int FRONT_LEFT = 1;
	int FRONT_RIGHT = 19;
	int BACK_LEFT = 5;
	int BACK_RIGHT = 7;
	int auton = 5;
	pros::lcd::register_btn1_cb(on_center_button);
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
	      0.5,  // Maximum linear velocity of the Chassis in m/s
	      1.0,  // Maximum linear acceleration of the Chassis in m/s/s
	      10.0, // Maximum linear jerk of the Chassis in m/s/s/s
	      chassis // Chassis Controller
	  );
	}
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
	  Point{1.0_ft, 0_ft, 0_deg}},
	  "Blue Small Second" // Profile name
	);
	profileController.generatePath({
	  Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
	  Point{1_ft, 0_ft, 0_deg}},
	  "Blue Small Third" // Profile name
	);
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
	);*/

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
