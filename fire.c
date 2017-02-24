#include "AT89X52.H"
#include "motor.h"
#include "delay.h"

sbit fire_sensor_L1 = P1^6;
sbit fire_sensor_L2 = P1^7;
sbit fire_sensor_M  = P2^1;
sbit fire_sensor_R2 = P2^2;
sbit fire_sensor_R1 = P2^3;
/*
火焰传感器排布（由左到右）
L1  L2  M R2  R1
检测到火焰返回低电平
*/


extern sbit route_track_qti_L1 = P1^5;
extern sbit route_track_qti_L2 = P1^4;
extern sbit route_track_qti_R2 = P1^3;
extern sbit route_track_qti_R1 = P1^2;
  //4个QTI传感器定位
  //从左到右
  //  L1  L2  R2  R1
	//黑色返回高电平

sbit fire_fan = P2^4;
//灭火风扇，给低电平时转

char fire_detected() {
  if (fire_sensor_R1 == 0) {
		delay_nus(20);
		if (fire_sensor_R1 == 0){
			return 5;
		}
  }
  else if (fire_sensor_R2 == 0) {
		delay_nus(20);
		if (fire_sensor_R2 == 0){
			return 4;
		}
  }
  else if (fire_sensor_M == 0) {
		delay_nus(20);
		if (fire_sensor_M == 0){
			return 3;
		}
  }
  else if (fire_sensor_L1 == 0) {
		delay_nus(20);
		if (fire_sensor_L1 == 0){
			return 1;
		}
  }
  else if (fire_sensor_L2 == 0) {
		delay_nus(20);
		if (fire_sensor_L2 == 0){
			return 2;
		}
  }

  return 0;
  //检测函数，任意一个火焰传感器检测到火，消去抖动后即返回检测到火的传感器
	//从左到右L1	L2	M	R2	R1	分别返回1	2	3	4	5
	//返回0代表没有检测到火焰
}

void fire_putout() {
  char fire_before = 0;
  char fire_passline = 0
  char 
  motor_stop();
  if (route_track_qti_L1 == 1) {
    delay_nus(15);
    if (route_track_qti_L1 == 1){
      fire_before = 1;
    }
  }
  else if (route_track_qti_R1 == 1) {
    delay_nus(15);
    if (route_track_qti_R1 == 1){
      fire_before = 2;
    }
  }

//以上内容为检测



  while (1) {

      while(fire_detected() != 3){

        switch (fire_detected()) {
      		case 2:
      		motor_speed(2);
      		motor_ccw();
      		break;

      		case 4:
      		motor_speed(2);
      		motor_cw();
      		break;
    			//靠内两个传感器检测到火焰后减速转向

          case 1:
      		motor_speed(3);
      		motor_ccw();
      		break;

          case 5:
          motor_speed(3);
          motor_cw();
          break;

    			default:
    			//default不做任何动作，延续之前动作
    			break;
			}
		}
    motor_stop();

    if (fire_detected() == 3) {
      fire_fan = 0;
      while(!fire_detected());
      delay_nms(2000);
      fire_fan = 1;

      break;
			//break大的while1
    }
  }


}
void fire_fan_test(bit key) {
  if (key) {
    fire_fan = 1;
  }
  else{
    fire_fan = 0;
  }
}

/*

  motor_stop();
  while (1) {

      while(fire_detected() != 3){

        switch (fire_detected()) {
      		case 2:
      		motor_speed(2);
      		motor_ccw();
      		break;

      		case 4:
      		motor_speed(2);
      		motor_cw();
      		break;
    			//靠内两个传感器检测到火焰后减速转向

          case 1:
      		motor_speed(3);
      		motor_ccw();
      		break;

          case 5:
          motor_speed(3);
          motor_cw();
          break;

    			default:
    			//default不做任何动作，延续之前动作
    			break;
			}
		}
    motor_stop();

    if (fire_detected() == 3) {
      fire_fan = 0;
      while(!fire_detected());
      delay_nms(2000);
      fire_fan = 1;

      break;
			//break大的while1
    }
  }

*/
