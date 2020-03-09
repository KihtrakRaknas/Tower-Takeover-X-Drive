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
using namespace okapi;

void checkHoldRamp(){
	if(ramp.get_position()>600)
		ramp.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	else
		ramp.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void opcontrol() {
	master.rumble("-");
	//autonomous();
	pros::ADIGyro gyro (GYRO_PORT);
	//okapi::ADIGyro gyro2 ('B');
	//myChassis.turnAngle(100);
	//myChassis.moveDistance(3000);
	int loopCount = 0;
  double pos = 0;
  int liftSpeed = 200;
	int FRONT_LEFT = 1;
 int FRONT_RIGHT = 19;
 int BACK_LEFT = 5;
 int BACK_RIGHT = 7;
 int stackLoop = 0;
 int liftMacro = 0;
 bool deployed = false;
 bool macroLiftBtnPressed = false;
 bool headless = false;
 double gyroVal = 0;

	auto chassis = ChassisControllerFactory::create(
	    FRONT_LEFT, FRONT_RIGHT, BACK_LEFT, BACK_RIGHT,
	    AbstractMotor::gearset::green,
	    {6.0_in, 20_in}
	);


	driveBrakeHold(false);

//auto deploy
/*
	lift(1500, 100);
	pros::delay(200);
	intake(-650);
	pros::delay(1200);
	lift(400, 100);
	pros::delay(1000);
	*/
	while (true) {
		if(headless)
			gyroVal =  -imuSensor.get_heading(); //(360+imuSensor.get_heading())%360;
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B) && master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
      headless = true;
		driveBrakeHold(false);
		moveDrive((double)master.get_analog(ANALOG_LEFT_X),master.get_analog(ANALOG_LEFT_Y),master.get_analog(ANALOG_RIGHT_X),(45-gyroVal)*PI/180);
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

		ramp.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    armRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		if(ramp.get_position()<800){
			rollerRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			rollerLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}else{
			rollerRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			rollerLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		}
    //0.1*abs(armRight.get_position()-pos)

		pros::lcd::print(2, "L: %d; IMU: %f; M: %d", lineSensor.get_value(), imuSensor.get_rotation(), liftMacro);

    //pros::lcd::print(3, "pos: %f",pos);

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !macroLiftBtnPressed){
      liftMacro++;
			if(liftMacro>3)
				liftMacro = 3;
			macroLiftBtnPressed = true;
			ramp.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    }
    else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && !macroLiftBtnPressed){
      liftMacro--;
			if(liftMacro<0)
				liftMacro = 0;
			macroLiftBtnPressed = true;
			ramp.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
			if(liftMacro<0){
				liftMacro = -1;
				armRight.move_velocity(-20);
			}
			ramp.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    }else{
			if(!master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
				macroLiftBtnPressed = false;
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
			liftMacro = -1;
			armRight.move_velocity(200);
			ramp.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
			liftMacro = -1;
			armRight.move_velocity(-200);
			ramp.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		}else{
			if(liftMacro == -1){
				armRight.move_velocity(0);
				checkHoldRamp();
			}else{
				int targetDeg = 0;
				if(liftMacro == 0){
					targetDeg = 0;
				}else if(liftMacro == 1){
					targetDeg = 200;
				}else if(liftMacro == 2){
					targetDeg = 1670;
				}else if(liftMacro == 3){
					targetDeg = 2150;
				}
				if(abs(armRight.get_position() - targetDeg) < 30){
					armRight.move_velocity(0);
					checkHoldRamp();
				}else{
					armRight.move_absolute(targetDeg, 200);
					ramp.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				}
			}
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
    }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
			if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
				rollerLeft.move_velocity(-50);
	      rollerRight.move_velocity(50);
			}else{
				rollerLeft.move_velocity(-100);
				rollerRight.move_velocity(100);
			}
    }else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      rollerLeft.move_velocity(300);
      rollerRight.move_velocity(-300);
    }else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
      rollerLeft.move_velocity(-100);
      rollerRight.move_velocity(100);
    }else{
      rollerLeft.move_velocity(0);
      rollerRight.move_velocity(0);
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
			int MIN_SPEED = 30;
			int speed = 1600+MIN_SPEED-ramp.get_position();
			speed = pow((speed/200),0.4)*200;
			if(speed<MIN_SPEED)
				speed = MIN_SPEED;
			/*if(ramp.get_position()>750)
				ramp.move_velocity(40);
			else*/
      	ramp.move_velocity(speed);
    }
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			//ramp.move_velocity(-100);
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

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)&&master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
      autonomous();
    }

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)&&deployed==false){
			deployed = true;
			//flip out
			lift(1500, 100);
			pros::delay(200);
			intake(-650);
			pros::delay(1200);
			lift(400, 100);

			pros::delay(500);
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
