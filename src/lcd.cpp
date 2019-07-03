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
      master.rumble("- - - -");
      partner.rumble("- - - -");
    }
    if(temp>maxTemp){
      maxTemp=temp;
      motorName = motor.first;
    }
  }
  if(tempStr!=motorName + std::string(" is at ") + std::to_string(maxTemp)){
    tempStr = motorName + std::string(" is at ") + std::to_string(maxTemp);
    master.print(0, 0, "%s is at %d",motorName,maxTemp);
    partner.print(0, 0, "%s is at %d",motorName,maxTemp);
  }
}

void updateControllerBattery(){
  //NOTE: FIX col
  if(masterBattery!=master.get_battery_level()){
    masterBattery=master.get_battery_level();
    master.print(0, 15, "%d%",masterBattery);
  }
  if(partnerBattery!=partner.get_battery_level()){
    partnerBattery=partner.get_battery_level();
    partner.print(1, 0, "%d%",partnerBattery);
  }

}

void displayInformation(){
  updateTempWarning();
  updateControllerBattery();
}
