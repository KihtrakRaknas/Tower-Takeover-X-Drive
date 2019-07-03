#include "main.h"
#include "x-drive.h"
#include "global.h"
#include "lcd.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	auto myChassis = okapi::ChassisControllerFactory::create(
	  1, -2, -6, 8
	);
	pros::ADIGyro gyro (GYRO_PORT);
	//okapi::ADIGyro gyro2 ('B');
	//myChassis.turnAngle(100);
	//myChassis.moveDistance(-3000);
	int loopCount = 0;
	while (true) {

		double gyroVal = gyro.get_value()/10;

		moveDrive((double)master.get_analog(ANALOG_LEFT_X),master.get_analog(ANALOG_LEFT_Y),thresh(master.get_analog(ANALOG_RIGHT_X),10)+thresh(partner.get_analog(ANALOG_RIGHT_X),10),(45-gyroVal)*PI/180);

		pros::lcd::print(3, "Gyro: %f",gyroVal);

		//default code
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
	  //END DEFAULT

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
			gyro.reset();
		}

		if(!(loopCount%3))
			displayInformation();

		loopCount++;

		pros::delay(20);
	}
}
