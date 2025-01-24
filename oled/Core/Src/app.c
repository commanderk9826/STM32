/*
 * app.c
 *
 *  Created on: Jan 16, 2025
 *      Author: ch.lee
 */

#include "app.h"

//외부 장치 선언
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;

uint16_t adcValue[2];

void app(){
	//uart 초기
	initUart(&huart2);
	//ssd1306 초기화
	ssd1306_Init();
	ssd1306_Fill(0);

	// adc 초기화
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcValue, 2);
	while(1){
		scrollLeftBySoft();
		ssd1306_DrawPixel(127, adcValue[0]/65, 1);
		ssd1306_UpdateScreen();
		HAL_Delay(10);
	}

}
