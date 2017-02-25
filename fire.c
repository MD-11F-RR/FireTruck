#include "AT89X52.H"
#include "motor.h"
#include "delay.h"
#include "qti_sensor.h"
#include <stdio.h>
#include "serial.h"

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
  if (fire_sensor_R1 == 0) {
		delay_nus(50);
		if (fire_sensor_R1 == 0){
			return 5;
		}
  }
  else if (fire_sensor_R2 == 0) {
		delay_nus(50);
		if (fire_sensor_R2 == 0){
			return 4;
		}
  }
  else if (fire_sensor_M == 0) {
		delay_nus(50);
		if (fire_sensor_M == 0){
			return 3;
		}
  }
  else if (fire_sensor_L1 == 0) {
		delay_nus(50);
		if (fire_sensor_L1 == 0){
			return 1;
		}
  }
  else if (fire_sensor_L2 == 0) {
		delay_nus(50);
		if (fire_sensor_L2 == 0){
			return 2;
		}
  }

  return 0;
  //检测函数，任意一个火焰传感器检测到火，消去抖动后即返回检测到火的传感器
	//从左到右L1	L2	M	R2	R1	分别返回1	2	3	4	5
	//返回0代表没有检测到火焰
}
/*
void fire_putout() {
  char fire_before = 0;
  char fire_passline = 0;

	bit fire_direction = 0;
	//左转为0，右转为1
  motor_stop();
  if (QTI_L1() == 1) {
    delay_nus(15);
    if (QTI_L1() == 1){
      fire_before = 1;
    }
  }
  else if (QTI_R1() == 1) {
    delay_nus(15);
    if (QTI_R1() == 1){
      fire_before = 2;
    }
  }

//以上内容为检测



  while (1) {
        switch (fire_detected()) {
					case 1:
      		case 2:
      		motor_ccw();
					fire_direction = 0;
      		continue;

					case 5:
      		case 4:
      		motor_cw();
					fire_direction = 1;
      		continue;
    			//靠内两个传感器检测到火焰后减速转向

    			default:
    			//default不做任何动作，延续之前动作
    			break;
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

bit fire_QTI_L1(){
	if (QTI_L1() == 1) {
		delay_nus(15);
		if (QTI_L1() == 1){
			//fire_before_L1 = 1;
			return 1;
		}
	}
	return 0;
}

bit fire_QTI_R1(){
	if (QTI_R1() == 1) {
		delay_nus(15);
		if (QTI_R1() == 1){
			//fire_before_R1 = 1;
			return 1;
		}
	}
	return 0;
}


void fire_putout_2(const char spot) {
	bit fire_before_L1 = 0;
	bit fire_before_R1 = 0;
	bit fire_passline_L1 = 0;
	bit fire_passline_R1 = 0;

	motor_stop();
	fire_before_L1 = fire_QTI_L1();
	fire_before_R1 = fire_QTI_R1();
	//以上内容为检测初始值


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
			if (fire_QTI_R1()) {
				fire_passline_R1 = 1;
			}
			break;

			case 4:
			case 5:
			if (fire_QTI_L1()) {
				fire_passline_L1 = 1;
			}
			break;
		}
	}
	motor_stop();

	fire_fan = 0;
	while(!fire_detected());
	delay_nms(2500);
	fire_fan = 1;
	//开风扇流程

	if (fire_passline_L1 || fire_passline_R1) {
		switch (spot) {
			case 1:
			case 2:
			motor_cw();
			while (!fire_QTI_R1()) {
			}
			while (fire_QTI_R1()) {
			}
			//天啊，这能取下降沿嘛…………
			return;
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!return可能会破坏程序逻辑！！！！
			break;

			case 4:
			case 5:
			motor_ccw();
			while (!fire_QTI_L1()) {
			}
			while (fire_QTI_L1()) {
			}
			//天啊，这能取下降沿嘛…………
			return;
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!return可能会破坏程序逻辑！！！！
			break;
		}
	}
	//RTB流程
}
*/

void fire_putout_3(const char spot) {
	bit fire_passline_R1 = 0;
	bit fire_passline_L1 = 0;

  serial_init();
  printf("fire detected,spot %d\n",spot);

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
	//转向
	while (fire_detected() != 3) {
		switch (spot) {
			case 1:
			case 2:
			if (QTI_R1() == 1) {
				fire_passline_R1 = 1;
        printf("passlineR1\n");
			}
			break;

			case 4:
			case 5:
			if (QTI_L1() == 1) {
				fire_passline_L1 = 1;
        printf("passlineL1\n");
			}
			break;
		}

		if (fire_passline_R1) {
			if (QTI_L1()) {
				motor_cw();
        delay_nms(20);
				while(!QTI_R2() || !QTI_L2());
				return;
				//!!!!!!!!!!!!!!!!!!!!!!!
			}
		}
		if (fire_passline_L1) {
			if (QTI_R1()) {
				motor_ccw();
        delay_nms(20);
				while(!QTI_R2() || !QTI_L2());
				return;
				//!!!!!!!!!!!!!!!!!!!!!!!
			}
		}

	}
	//记录是否越线，有黑即检测


	motor_stop();
	fire_fan = 0;
	while(!fire_detected());
	delay_nms(2000);
	fire_fan = 1;
	//停车灭火
  printf("start to RTB\n");
	switch (spot) {
		case 1:
		case 2:
		if (fire_passline_R1 == 1) {
			motor_cw();
      while(!QTI_R2() || !QTI_L2());
		}
    break;


		case 4:
		case 5:
		if (fire_passline_L1 == 1) {
			motor_ccw();
			while(!QTI_R2() || !QTI_L2());
		}
    break;
	}
}



/*

void fire_fan_test(bit key) {
  if (key) {
    fire_fan = 1;
  }
  else{
    fire_fan = 0;
  }
}
*/
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



/*
if (fire_before_R1) {
	while (fire_QTI_R1()) {	//#1
		if (fire_detected() == 3) {
			break;	//break #1 while
		}
	}

	if (!fire_QTI_R1()) {
		fire_passline_R1 = 1;
	}
}

*/
