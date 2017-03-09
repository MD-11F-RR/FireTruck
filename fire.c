#include "AT89X52.H"
#include "motor.h"
#include "delay.h"
#include "qti_sensor.h"
#include <stdio.h>
#include "serial.h"
#ifndef FIRE_DETACT_DELAY
#define FIRE_DETACT_DELAY 100
#endif


sbit fire_sensor_L1 = P2^1;
sbit fire_sensor_L2 = P2^3;
sbit fire_sensor_M  = P2^5;
sbit fire_sensor_R2 = P2^7;
sbit fire_sensor_R1 = P2^0;
/*
火焰传感器排布（由左到右）
L1  L2  M R2  R1
检测到火焰返回低电平
*/

sbit fire_fan = P2^4;
//灭火风扇，给低电平时转

char fire_detected() {
  if (fire_sensor_M == 0) {
		delay_nus(FIRE_DETACT_DELAY);
		if (fire_sensor_M == 0){
			return 3;
		}
  }
  else if (fire_sensor_R1 == 0) {
		delay_nus(FIRE_DETACT_DELAY);
		if (fire_sensor_R1 == 0){
			return 5;
		}
  }
  else if (fire_sensor_L1 == 0) {
		delay_nus(FIRE_DETACT_DELAY);
		if (fire_sensor_L1 == 0){
			return 1;
		}
  }
  else if (fire_sensor_R2 == 0) {
		delay_nus(FIRE_DETACT_DELAY);
		if (fire_sensor_R2 == 0){
			return 4;
		}
  }
    else if (fire_sensor_L2 == 0) {
		delay_nus(FIRE_DETACT_DELAY);
		if (fire_sensor_L2 == 0){
			return 2;
		}
  }

  return 0;
  //检测函数，任意一个火焰传感器检测到火，消去抖动后即返回检测到火的传感器
	//从左到右L1	L2	M	R2	R1	分别返回1	2	3	4	5
	//返回0代表没有检测到火焰
}


void fire_putout_3(const char spot) {
  bit fire_passline_R1 = 0;
  bit fire_passline_L1 = 0;

  switch (spot) {
    case 1:
    case 2:
    motor_ccw();
    break;

    case 4:
    case 5:
    motor_cw();
    break;

    case 3:
    motor_stop();
    break;
  }

  while (fire_detected() != 3) {
    switch (spot) {
      case 1:
      case 2:
      if (QTI_R1()) {
        fire_passline_R1 = 1;
      }
      break;

      case 4:
      case 5:
      if (QTI_L1()) {
        fire_passline_L1 = 1;
      }
      break;
    }
    //越线检测

    if (fire_passline_R1) {
      if (QTI_L1()) {
        motor_cw();
        while (1) {
          if (QTI_R2()) {
            break;
          }
        }
        motor_stop();
        return;
      }
    }
    if (fire_passline_L1) {
      if (QTI_R1()) {
        motor_ccw();
        while (1) {
          if (QTI_L2()) {
            break;
          }
        }
        motor_stop();
        return;
      }
    }
    //miss检测
  }
  motor_stop();
  motor_shutdown();
	fire_fan = 0;
	while(!fire_detected());
	delay_nms(3000);
	fire_fan = 1;
	//停车灭火
  motor_init();

  if (fire_passline_R1 || fire_passline_L1) {
    switch (spot) {
      case 1:
      case 2:
      motor_cw();
      while (1) {
        if (QTI_L2()) {
          break;
        }
        if (QTI_R2()) {
          break;
        }
      }
      motor_stop();
      break;

      case 4:
      case 5:
      motor_ccw();
      while (1) {
        if (QTI_R2()) {
          break;
        }
        if (QTI_L2()) {
          break;
        }
      }
      motor_stop();
      break;
    }
  }
}
