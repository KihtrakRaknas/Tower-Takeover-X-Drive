#include "main.h"
#include "global.h"
#include "x-drive.h"
#include <cmath>

double thresh(double num, double thresh){
  if(abs(num)<thresh)
    return 0;
  return num;
}

double mapCircleToSquare(double mainCord, double secondaryCord){
  //mainCord is the coordinate you would like to scale
  //secondaryCord is the other coordinate
  //cordinates must be within circle with a radius of 1 around the orgin
  return .5 * sqrt(2+2*mainCord*sqrt(2)+mainCord*mainCord-secondaryCord*secondaryCord) - .5 * sqrt(2-2*mainCord*sqrt(2)+mainCord*mainCord-secondaryCord*secondaryCord);
}
void moveDrive(double xPos, double yPos, double turn, double angle){
  //Get the X and Y coordinates from the controller
  double oldXPos = xPos;
  //Use a rotation matrix to get new coordinates
  xPos = ((cos(angle) * xPos) - (sin(angle) * yPos));
  yPos = ((sin(angle) * oldXPos) + (cos(angle) * yPos));

  //optimize speed by scaling from a circle to a mapCircleToSquare
  oldXPos = xPos;
  xPos = mapCircleToSquare(xPos,yPos);
  yPos = mapCircleToSquare(yPos,oldXPos);


  /*
  top_left_mtr.move(turn);
  top_right_mtr.move(-1*turn);
  bottom_left_mtr.move(turn);
  bottom_right_mtr.move(-1*turn);
  */

  top_left_mtr.move_velocity(yPos+turn);
  top_right_mtr.move_velocity(-1*xPos-turn);
  bottom_left_mtr.move_velocity(-1*xPos+turn);
  bottom_right_mtr.move_velocity(yPos-turn);

}
