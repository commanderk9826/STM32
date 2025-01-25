/*
 * uart.c
 *
 *  Created on: Jan 18, 2025
 *      Author: steve
 */

#include "uart.h"
#include <string.h>

UART_HandleTypeDef *myHuart;

#define rxBufferMax	100

char rxChar;
char rxBuffer[rxBufferMax];
uint8_t	rxBufferWriteIndex;
uint8_t rxBufferReadIndex;

int _write(int file, char* p, int len){
	HAL_UART_Transmit(myHuart, p, len, 10);
	return len;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	rxBuffer[rxBufferWriteIndex++] = rxChar;
	rxBufferWriteIndex %= rxBufferMax;
	HAL_UART_Receive_IT(myHuart, (uint8_t *)&rxChar,	1);
}

void initUart(UART_HandleTypeDef *inHuart) {
	myHuart = inHuart;
	HAL_UART_Receive_IT(myHuart, (uint8_t *)&rxChar, 1);
}

char getChar() {
	char result;
	if(rxBufferWriteIndex == rxBufferReadIndex) return 0;
	result = rxBuffer[rxBufferReadIndex++];
	rxBufferReadIndex %= rxBufferMax;
	return result;
}

char *getMessage() {
	static char message[100];
	static uint8_t	messageCount = 0;
	char ch = getChar();
	if(ch != 0) {
		if(ch == '\n' || ch == '\r') {
			memset(message, 0, 100);
			messageCount = 0;
		}
		else if(ch >= 0x20) {
			message[messageCount++] = ch;
		}
	}
	return message;
}
