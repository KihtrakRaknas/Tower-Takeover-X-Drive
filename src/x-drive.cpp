#include "main.h"
#include "global.h"
#include "x-drive.h"
#include <cmath>

double thresh(double num, double thresh){
  if(abs(num)<thresh)
    return 0;
  return num;
}

double truncate(double number_val, int n)
{
    double factor = 1;
    double previous = std::trunc(number_val); // remove integer portion
    number_val -= previous;
    for (int i = 0; i < n; i++) {
        number_val *= 10;
        factor *= 10;
    }
    number_val = std::trunc(number_val);
    number_val /= factor;
    number_val += previous; // add back integer portion
    return number_val;
}

double forceCircleCords(double mainCord, double secondaryCord){
  if(sqrt(mainCord*mainCord+secondaryCord*secondaryCord)>=1){
    //master.rumble(". ");
    //partner.rumble(". ");
    double theta = atan(mainCord/secondaryCord);
    pros::lcd::print(2, "theta: %f s",theta);
    if(secondaryCord>0)//positive
      return truncate(sin(theta),5);
    //negitive
    return truncate(-1*sin(theta),5);
  }
  return mainCord;
}

double mapCircleToSquare(double mainCord, double secondaryCord){
  //mainCord is the coordinate you would like to scale
  //secondaryCord is the other coordinate
  //cordinates must be within circle with a radius of 1 around the orgin
  return .5 * sqrt(2+2*mainCord*sqrt(2)+mainCord*mainCord-secondaryCord*secondaryCord) - .5 * sqrt(2-2*mainCord*sqrt(2)+mainCord*mainCord-secondaryCord*secondaryCord);
}

void moveDrive(double xPos, double yPos, double turn, double angle){
  pros::lcd::print(6, "X: %f, Y:%f   ",xPos,yPos);
  //Get the X and Y coordinates from the controller
  double oldXPos = xPos;
  //Use a rotation matrix to get new coordinates
  xPos = ((cos(angle) * xPos) - (sin(angle) * yPos));
  yPos = ((sin(angle) * oldXPos) + (cos(angle) * yPos));

  //scale down the numbers
  xPos /=127;
  yPos /=127;

  //Force circle
  oldXPos = xPos;
  xPos = forceCircleCords(xPos,yPos);
  yPos = forceCircleCords(yPos,oldXPos);

  pros::lcd::print(7, "X: %f, Y:%f  s",xPos,yPos);

  //optimize speed by scaling from a circle to a mapCircleToSquare
  oldXPos = xPos;
  xPos = mapCircleToSquare(xPos,yPos);
  yPos = mapCircleToSquare(yPos,oldXPos);



  //scale up

  xPos *=200;
  yPos *=200;

  //pros::lcd::print(7, "X: %f, Y:%f   ",xPos,yPos);
  /*
  top_left_mtr.move(turn);
  top_right_mtr.move(-1*turn);
  bottom_left_mtr.move(turn);
  bottom_right_mtr.move(-1*turn);
  */

  pros::lcd::print(3, "TL: %d; TR: %d; BL: %d; BR: %d; ", top_left_mtr.get_actual_velocity(),top_right_mtr.get_actual_velocity(),bottom_left_mtr.get_actual_velocity(),bottom_right_mtr.get_actual_velocity());

  top_left_mtr.move_velocity(yPos+turn);
  top_right_mtr.move_velocity(xPos+turn);
  bottom_left_mtr.move_velocity(-1*xPos+turn);
  bottom_right_mtr.move_velocity(-yPos+turn);

}
