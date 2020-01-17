#include "main.h"
#include "global.h"

int FRONT_LEFT = 1;
int FRONT_RIGHT = 19;
int BACK_LEFT = 5;
int BACK_RIGHT = 7;

pros::Motor top_left_mtr(1);
pros::Motor top_right_mtr(19);
pros::Motor bottom_left_mtr(5);
pros::Motor bottom_right_mtr(7);
pros::Motor ramp(9);
pros::Motor rollerLeft(3);
pros::Motor rollerRight(8);
pros::Motor armLeft(10);
pros::Motor armRight(20);

pros::ADIPotentiometer potRight(7);
pros::ADIPotentiometer potLeft(6);

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

std::map<std::string,pros::Motor> ALL_MOTORS {{"top_left", top_left_mtr}, {"top_right", top_right_mtr}, {"down_left", bottom_left_mtr}, {"down_right", bottom_right_mtr}, {"ramp",ramp}, {"armright",armRight},/*{"armLeft",armLeft},*/{"rollerL",rollerLeft},{"rollerR",rollerRight}};
