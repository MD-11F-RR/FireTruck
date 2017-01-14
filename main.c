#include "reg52.h"
#include "motor.h"
#include "route_track.h"

int main() {
  motor_init();
  motor_speed(2);
	EA = 1;
  while (1) {
    route_track_track();
  }
  return 0;
}

void T1interrupt() interrupt 3 {
	EA = 0;
  motor_interrupt();
	EA = 1;
}