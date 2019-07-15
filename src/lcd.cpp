#include "global.h"
#include "lcd.h"

std::string tempStr = "";
int masterBattery = 0;
int partnerBattery = 0;

void updateTempWarning(){
  int maxTemp = 0;
  std::string motorName = "";
  for(auto motor: ALL_MOTORS) {
    int temp = motor.second.get_temperature();
    if(temp>=55){
      //Motor will start to get throtled
      //master.rumble("- - - -");
      //partner.rumble("- - - -");
    }
    if(temp>maxTemp){
      maxTemp=temp;
      motorName = motor.first;
    }
  }
  if(tempStr!=motorName + std::string(" is at ") + std::to_string(maxTemp)){
    tempStr = motorName + std::string(" is at ") + std::to_string(maxTemp);
    pros::lcd::print(4, "%s",tempStr);
    master.print(0, 0, "%s: %d      ",motorName,maxTemp);
    partner.print(0, 0, "%s: %d      ",motorName,maxTemp);
  }
}

void updateControllerBattery(){
  //NOTE: FIX col
  if(masterBattery!=master.get_battery_level()||partnerBattery!=partner.get_battery_level()){
    masterBattery=master.get_battery_level();
    partnerBattery=partner.get_battery_level();
    pros::lcd::print(5, "M: %d, P:%d     ",masterBattery,partnerBattery);
    partner.print(1, 0, "M: %d, P:%d     ",masterBattery,partnerBattery);
    //master.print(0, 21, "%d",masterBattery);
  }

}

void displayInformation(){
  updateTempWarning();
  updateControllerBattery();
}
