#include "at89x52.h"
#include "delay.h"


  sbit qti_L1 = P1^5;
  sbit qti_L2 = P1^4;
  sbit qti_R2 = P1^3;
  sbit qti_R1 = P1^2;
  //4个QTI传感器定位
  //从左到右
  //  L1  L2  R2  R1
	//黑色返回高电平


	bit QTI_L1(){
		if (qti_L1 == 1) {
			delay_nus(15);
			if (qti_L1 == 1){
				fire_before_L1 = 1;
				return 1;
			}
		}
		return 0;
	}

	bit QTI_R1(){
		if (qti_R1 == 1) {
			delay_nus(15);
			if (qti_R1 == 1){
				fire_before_R1 = 1;
				return 1;
			}
		}
		return 0;
	}

	bit QTI_L2(){
		if (qti_L2 == 1) {
			delay_nus(15);
			if (qti_L2 == 1){
				fire_before_R1 = 1;
				return 1;
			}
		}
		return 0;
	}

	bit QTI_R2(){
		if (qti_L2 == 1) {
			delay_nus(15);
			if (qti_R2 == 1){
				fire_before_R2 = 1;
				return 1;
			}
		}
		return 0;
	}
