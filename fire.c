#include "AT89X52.H"
#include <stdbool.h>

sbit fire_sensor_L1 = ;
sbit fire_sensor_L2 = ;
sbit fire_sensor_M = ;
sbit fire_sensor_R2 = ;
sbit fire_sensor_R1 = ;

/*
火焰传感器排布（由左到右）
L1  L2  M R2  R1
检测到火焰返回低电平
*/

bool fire_detected(){
  if (fire_sensor_R1 == 0) {
    return true;
  }
  else if (fire_sensor_R2 == 0) {
    return true;
  }
  else if (fire_sensor_M == 0) {
    return true;
  }
  else if (fire_sensor_L1 == 0) {
    return true;
  }
  else if (fire_sensor_L2 == 0) {
    return true;
  }
  else{
    return false;
  }
  //检测函数，任意一个火焰传感器检测到火焰就返回true
}
