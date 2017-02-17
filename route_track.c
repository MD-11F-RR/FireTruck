#include "reg52.h"
#include "motor.h"

  sbit route_track_qti_L1 = P1^5;
  sbit route_track_qti_L2 = P1^4;
  sbit route_track_qti_R2 = P1^3;
  sbit route_track_qti_R1 = P1^2;
  //4个QTI传感器定位


void route_track_track() {
/*
  if (route_track_qti_L1 == 1 && route_track_qti_R1 == 0) {
    motor_cw();
  }

  if (route_track_qti_L2 == 1 && route_track_qti_R2 == 0) {
    motor_left();
  }

  if (route_track_qti_R2 == 1 && route_track_qti_L2 == 0) {
    motor_right();
  }

  if (route_track_qti_R1 == 1 && route_track_qti_L1 == 0) {
    motor_ccw();
  }

  if (route_track_qti_L2 == 0 && route_track_qti_R2 == 0) {
    motor_forward();
  }
*/
  if (route_track_qti_L1 == 1 && route_track_qti_R1 == 0) {
    motor_ccw();
  }
  else if (route_track_qti_L1 == 0 && route_track_qti_R1 == 1) {
    motor_cw();
  }
  else{
    motor_forward();
  }
}

void route_track_shutdown() {
  motor_stop();
  motor_shutdown();
}
