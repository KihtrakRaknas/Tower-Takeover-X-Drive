#include "main.h"
#include "x-drive.h"
#include "global.h"
#include "lcd.h"
#include "autonomous.h"

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

	pros::ADIGyro gyro (GYRO_PORT);
	//okapi::ADIGyro gyro2 ('B');
	//myChassis.turnAngle(100);
	//myChassis.moveDistance(3000);
	int loopCount = 0;
  double pos = 0;
  int liftSpeed = 200;
	while (true) {

		double gyroVal = gyro.get_value()/10;

		moveDrive((double)master.get_analog(ANALOG_LEFT_X),master.get_analog(ANALOG_LEFT_Y),thresh(master.get_analog(ANALOG_RIGHT_X),10)+thresh(partner.get_analog(ANALOG_RIGHT_X),10),(45-gyroVal)*PI/180);
    /*if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      armRight.move_velocity(-200);
    }
    else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      armRight.move_velocity(200);
    }

    if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
      armLeft.move_velocity(-175);
    }
    else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
      armLeft.move_velocity(175);
    }*/

    armRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    armLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    //0.1*abs(armRight.get_position()-pos)

		pros::lcd::print(2, "L: %d; R: %d", potLeft.get_value(), potRight.get_value());

    //pros::lcd::print(3, "pos: %f",pos);

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      //if(pos<5500)
        armRight.move_velocity(100);
    }
    else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
      //if(pos>0)
        armRight.move_velocity(-100);
    }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
			armRight.move_velocity(30);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
			armRight.move_velocity(-30);
		}else{
			armRight.move_velocity(0);
		}


    if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      //if(pos<5500)
        pos+=100;
        liftSpeed=200;
    }
    else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
      //if(pos>0
        pos-=100;
        liftSpeed=100;
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      rollerLeft.move_velocity(300);
      rollerRight.move_velocity(-300);
    }
    else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
      rollerLeft.move_velocity(-80);
      rollerRight.move_velocity(80);
    }
    else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      rollerLeft.move_velocity(300);
      rollerRight.move_velocity(-300);
    }
    else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
      rollerLeft.move_velocity(-100);
      rollerRight.move_velocity(100);
    }
    else{
      rollerLeft.move_velocity(0);
      rollerRight.move_velocity(0);
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
      ramp.move_velocity(70);
    }
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			ramp.move_velocity(-100);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
      ramp.move_velocity(-150);
    }
    else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
      ramp.move_velocity(200);
    }
    else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
      ramp.move_velocity(-100);
    }else {
      ramp.move_velocity(0);
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
      autonomous();
    }



		//default code
		/*pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);*/
	  //END DEFAULT

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
			gyro.reset();
		}

		if(!(loopCount%3))
			displayInformation();

		loopCount++;

		pros::delay(20);
	}
}
