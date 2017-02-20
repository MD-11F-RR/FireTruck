#include "reg52.h"
#include "motor.h"

  sbit route_track_qti_L1 = P1^5;
  sbit route_track_qti_L2 = P1^4;
  sbit route_track_qti_R2 = P1^3;
  sbit route_track_qti_R1 = P1^2;
  //4个QTI传感器定位
  //从左到右
  //  L1  L2  R2  R1
	//黑色返回高电平


void route_track_track() {
  	if (route_track_qti_R1 == 0 && route_track_qti_L1 == 0) {
      //条件未编译测试，，要留意
  		if (route_track_qti_R2 == route_track_qti_L2) {
  			motor_forward();
  		}
			else if (route_track_qti_L2 == 0 && route_track_qti_R2 == 1) {
				motor_right();
			}
			else{
				motor_left();
			}
  	}
		//当外侧两QTI检测全为白色信号时使用内侧进行微调，，全黑或全白均前进，一边黑时
		//差速转弯

		else {
  			if (route_track_qti_L1 == 1 && route_track_qti_R1 == 0) {
  				motor_ccw();
  			}

				else if(route_track_qti_L1 == 0 && route_track_qti_R1 == 1){
					motor_cw();
				}
        //当外侧两QTI检测到黑色时采用比较激进的转弯方式
        else{
          motor_stop();
        }
  	}
}

void route_track_shutdown() {
  motor_stop();
  motor_shutdown();
}
//停止寻迹函数，停止电机并关闭计时器
