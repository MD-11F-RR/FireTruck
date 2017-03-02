#include "reg52.h"
#include "motor.h"
#include "route_track.h"
#include "fire.h"
#include "delay.h"
#include "qti_sensor.h"

int main() {
  motor_init();
  motor_speed(3);
	EA = 1;
  while (1) {

    
    if (fire_detected())  {
      fire_putout_3(fire_detected());
    }
		else{
		route_track_track();
		}
		
    
  }
  return 0;
}

void T1interrupt() interrupt 3 {
	EA = 0;
  motor_interrupt();
	EA = 1;
}
