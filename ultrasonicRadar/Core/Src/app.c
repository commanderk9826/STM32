/*
 * app.c
 *
 *  Created on: Jan 16, 2025
 *      Author: ch.lee
 */

#include "app.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


//장치 선언
extern TIM_HandleTypeDef htim1;// for Servo
extern TIM_HandleTypeDef htim3;// for UltraSonic
extern TIM_HandleTypeDef htim11;// for delay_us
extern UART_HandleTypeDef huart2;

//us동안 지연
void delay_us(uint16_t time){
		htim11.Instance->CNT=0;
		while(htim11.Instance->CNT < time);
}

long map(long x, long in_min, long in_max, long out_min, long out_max){
	return (x-in_min)*(out_max - out_min)/(in_max-in_min) + out_min;
}

void setServo(uint16_t angle){
	 htim1.Instance->CCR1=map(angle, 0 , 180, 800, 2400);
}

void app(){
	//uart 수신 인터럽트 시작
	initUart(&huart2);
	initUltrasonic(&htim3);
	HAL_TIM_Base_Start(&htim11);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

	while(1){
		// 각도 수신
		char *msg = getMessage();
		if(strlen(msg)> 3){
			if(msg[0]=='A'){
				//parse
				int angle = atoi(&msg[1]);
				//서보를 수신 각도로 이동
				setServo(angle);
				//서보의 움직임을 고려한 시간 지연
				HAL_Delay(200);
				//거리 측정
				int distance = getDistance();
				printf("D%03d\n", distance);
			}

		}
	}
}
