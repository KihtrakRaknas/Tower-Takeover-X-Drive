#include "main.h"
#ifndef GLOBAL_H_

#define GYRO_PORT 'B'

#endif


extern pros::Motor top_left_mtr;
extern pros::Motor top_right_mtr;
extern pros::Motor bottom_left_mtr;
extern pros::Motor bottom_right_mtr;
extern pros::Motor ramp;
extern pros::Motor rollerLeft;
extern pros::Motor rollerRight;
extern pros::Motor armLeft;
extern pros::Motor armRight;

extern pros::ADIPotentiometer potRight;
extern pros::ADIPotentiometer potLeft;


extern pros::Controller master;
extern pros::Controller partner;

extern std::map<std::string,pros::Motor> ALL_MOTORS;
