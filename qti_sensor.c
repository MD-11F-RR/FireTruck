#include "at89x52.h"
#include "delay.h"
//bit返回值为1就为检测到黑线

sbit QTI_sensor_L1 = P1^5;
sbit QTI_sensor_L2 = P1^4;
sbit QTI_sensor_R2 = P1^3;
sbit QTI_sensor_R1 = P1^2;
//4个QTI传感器定位
//从左到右
//  L1  L2  R2  R1
//黑色返回高电平

#ifndef QTI_SENSOR_DELAY
#define QTI_SENSOR_DELAY 30
#endif


bit QTI_L1(){
	if (QTI_sensor_L1 == 1) {
		delay_nus(QTI_SENSOR_DELAY);
		if (QTI_sensor_L1 == 1){
      return 1;
		}
	}
	return 0;
}

bit QTI_R1(){
	if (QTI_sensor_R1 == 1) {
		delay_nus(QTI_SENSOR_DELAY);
		if (QTI_sensor_R1 == 1){
			return 1;
		}
	}
	return 0;
}

bit QTI_L2(){
	if (QTI_sensor_L2 == 1) {
		delay_nus(QTI_SENSOR_DELAY);
		if (QTI_sensor_L2 == 1){
			return 1;
		}
	}
	return 0;
}

bit QTI_R2(){
	if (QTI_sensor_R2 == 1) {
		delay_nus(QTI_SENSOR_DELAY);
		if (QTI_sensor_R2 == 1){
			return 1;
		}
	}
	return 0;
}
