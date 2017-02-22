#include "reg52.h"
#include "motor.h"
#include "route_track.h"
#include "fire.h"
#include "Boebot.h"

int main() {
  motor_init();
  motor_speed(3);
	EA = 1;
  while (1) {
		/*
    //route_track_track();
    if (fire_detected() != 0) {
      while(fire_detected() != 3);
      fire_fan_test(0);
      if (fire_detected() == 0) {
        fire_fan_test(1);
      }
    }
    else{
      fire_fan_test(1);
    }

    //fire_fan_test(1);

    motor_stop();
		*/
		motor_stop();
		while (1) {
			motor_forward();

			delay_nms(1000);
			if (1) {
				break;
			}
		}
		//测试代码，检测是否能够成功break出大的while1
  }
  return 0;
}

void T1interrupt() interrupt 3 {
	EA = 0;
  motor_interrupt();
	EA = 1;
}
