/*
 * timer.c
 *
 *  Created on: Aug 8, 2024
 *      Author: coffe
 */

#include "timer.h"

volatile uint8_t FatFsCnt = 0;
volatile uint8_t Timer1, Timer2;

void SDTimer_Handler(void)
{
  if(Timer1 > 0)
    Timer1--;

  if(Timer2 > 0)
    Timer2--;
}

void SystickCallback() {
	FatFsCnt++;
	if(FatFsCnt >= 10)
	{
		FatFsCnt = 0;
		SDTimer_Handler();
	}
}
