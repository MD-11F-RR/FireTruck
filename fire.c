#include "AT89X52.H"
#include <stdbool.h>
#include "motor.h"

sbit fire_sensor_L1 = ;
sbit fire_sensor_L2 = ;
sbit fire_sensor_M = ;
sbit fire_sensor_R2 = ;
sbit fire_sensor_R1 = ;
sbit fire_fan = ;

/*
火焰传感器排布（由左到右）
L1  L2  M R2  R1
检测到火焰返回低电平
*/

char fire_detected(){
  if (fire_sensor_R1 == 0) {
    return 1;
  }
  else if (fire_sensor_R2 == 0) {
    return 2;
  }
  else if (fire_sensor_M == 0) {
    return 3;
  }
  else if (fire_sensor_L1 == 0) {
    return 4;
  }
  else if (fire_sensor_L2 == 0) {
    return 5;
  }
  else{
    return 0;
  }
  //检测函数，任意一个火焰传感器检测到火焰就返回true
}

void fire_putout() {

	motor_stop();
	switch (fire_detected()) {
		case 1:
		motor_speed(3);
		motor_ccw();
		break;

		case 2:
		motor_speed(2);
		motor_ccw();
		break;

		case 3:
		motor_stop();
		break;

		case 4:
		motor_speed(2);
		motor_cw();
		break;

		case 5:
		motor_speed(3);
		motor_cw();
		break;
	}


}
