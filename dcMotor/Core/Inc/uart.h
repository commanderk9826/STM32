/*
 * uart.h
 *
 *  Created on: Jan 16, 2025
 *      Author: ch.lee
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include <stdio.h>
#include <string.h>

//Prototype 선언
void initUart(UART_HandleTypeDef *);//변수명 생략가능
char getUart();
char* getMessage();

#endif /* INC_UART_H_ */
