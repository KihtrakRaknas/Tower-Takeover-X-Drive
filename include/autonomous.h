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
 void stack();
 void delay(double d);
 void intake(double v);
 void intake(double d, double v);
 void liftPot(int leftVal, int rightVal);
 void moveDist(double dist, double v);
 void stackSkills();

#endif
