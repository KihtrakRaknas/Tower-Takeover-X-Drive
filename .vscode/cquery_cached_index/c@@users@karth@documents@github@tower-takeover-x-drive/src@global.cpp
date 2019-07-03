#include "main.h"
#include "global.h"

pros::Motor top_left_mtr(1);
pros::Motor top_right_mtr(2);
pros::Motor bottom_left_mtr(8);
pros::Motor bottom_right_mtr(6);

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

std::map<std::string,pros::Motor> ALL_MOTORS {{"top_left", top_left_mtr}, {"top_right", top_right_mtr}, {"bottom_left", bottom_left_mtr}, {"bottom_right", bottom_right_mtr}};
