/*
 * app.c
 *
 *  Created on: Jan 16, 2025
 *      Author: ch.lee
 */

#include "app.h"

//외부 장치 핸들 선언
extern TIM_HandleTypeDef htim1;// Rotary
extern TIM_HandleTypeDef htim3;// Servo

extern UART_HandleTypeDef huart2;

void app(){
	initUart(&huart2);
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

	while(1){
		static uint16_t oldCount, curCount;
		curCount = htim1.Instance->CNT;
		if(oldCount !=curCount){
			printf("count = %5d\n", curCount);
			htim3.Instance->CCR1=curCount+1000;
			oldCount=curCount;
		}
	}

}
