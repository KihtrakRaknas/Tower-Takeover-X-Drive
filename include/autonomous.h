#include "main.h"
#ifndef AUTONOMOUS_H

void autonomous();

void moveDistSide(double dist, double v);
 void lift(double d, double v);
 void move(double d, double v);
 void turnRight(double d, double v);
 void turnRightNonAsync(double d, double v);
 void turnRightNonAsync(double d, double v, double thresh);
 void reverseDrive();
  void forwardDrive();
  void leftDrive();
   void rightDrive();
 void stack();
 void delay(double d);
 void intake(double v);
 void intake(double d, double v);
 void liftPot(int leftVal, int rightVal);
 void moveDist(double dist, double v);
 void stackSkills();
 void waitUntilTarget(int topLeftTarget,int topRightTarget,int bottomLeftTarget,int bottomRightTarget, double thresh);
 void waitUntilTarget(int topLeftTarget,int topRightTarget,int bottomLeftTarget,int bottomRightTarget);
 void waitUntilTarget(pros::Motor motor, int target);
 void driveBrakeHold(bool hold);
 void turnPID(double);
void turnPID(double, double);
void turnPIDABS(double deg, double MAX_SPEED);

#endif
