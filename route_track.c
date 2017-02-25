#include "reg52.h"
#include "motor.h"
#include "qti_sensor.h"


void route_track_track() {
  	if (QTI_R1() == 0 && QTI_L1() == 0) {
      //条件未编译测试，，要留意
  		if (QTI_R2() == QTI_L2()) {
  			motor_forward();
  		}
			else if (QTI_L2() == 0 && QTI_R2() == 1) {
				motor_right();
			}
			else{
				motor_left();
			}
  	}
		//当外侧两QTI检测全为白色信号时使用内侧进行微调，，全黑或全白均前进，一边黑时
		//差速转弯

		else {
  			if (QTI_L1() == 1 && QTI_R1() == 0) {
  				motor_ccw();
  			}

				else if(QTI_L1() == 0 && QTI_R1() == 1){
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
