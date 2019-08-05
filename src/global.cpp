#include "main.h"
#include "global.h"

pros::Motor top_left_mtr(1);
pros::Motor top_right_mtr(2);
pros::Motor bottom_left_mtr(8);
pros::Motor bottom_right_mtr(6);
pros::Motor ramp(5);
pros::Motor rollerLeft(3);
pros::Motor rollerRight(4);
pros::Motor armLeft(9);
pros::Motor armRight(10);

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

std::map<std::string,pros::Motor> ALL_MOTORS {{"top_left", top_left_mtr}, {"top_right", top_right_mtr}, {"down_left", bottom_left_mtr}, {"down_right", bottom_right_mtr}, {"ramp",ramp}, {"armright",armRight},{"armLeft",armLeft},{"rollerL",rollerLeft},{"rollerR",rollerRight}};
