#include "main.h"
#ifndef GLOBAL_H_

#define GYRO_PORT 'B'

#endif


extern pros::Motor top_left_mtr;
extern pros::Motor top_right_mtr;
extern pros::Motor bottom_left_mtr;
extern pros::Motor bottom_right_mtr;

extern pros::Controller master;
extern pros::Controller partner;

extern std::map<std::string,pros::Motor> ALL_MOTORS;
