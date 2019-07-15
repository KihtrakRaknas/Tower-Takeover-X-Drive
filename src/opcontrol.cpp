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

 using namespace okapi;

 int FRONT_LEFT = 1;
int FRONT_RIGHT = -2;
int BACK_LEFT = -6;
int BACK_RIGHT = 8;
auto myChassis = ChassisControllerFactory::create(
	FRONT_LEFT, FRONT_RIGHT, BACK_LEFT, BACK_RIGHT,
	AbstractMotor::gearset::green,
	{4_in, 11_in}
);

void opcontrol() {

	pros::ADIGyro gyro (GYRO_PORT);
	//okapi::ADIGyro gyro2 ('B');
	//myChassis.turnAngle(100);
	//myChassis.moveDistance(3000);
	int loopCount = 0;
	while (true) {

		double gyroVal = gyro.get_value()/10;

		moveDrive((double)master.get_analog(ANALOG_LEFT_X),master.get_analog(ANALOG_LEFT_Y),thresh(master.get_analog(ANALOG_RIGHT_X),10)+thresh(partner.get_analog(ANALOG_RIGHT_X),10),(45-gyroVal)*PI/180);

    cube_holder_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      pros::lcd::print(3, "BTN ORES");
      cube_holder_mtr.move_velocity(20);
    }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      cube_holder_mtr.move_velocity(-20);
    }else{
      cube_holder_mtr.move_velocity(0);
    }

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
