/*
 * uart.h
 *
 *  Created on: Jan 18, 2025
 *      Author: steve
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

void initUart(UART_HandleTypeDef *);
char getChar();
char *getMessage();

#endif /* INC_UART_H_ */
