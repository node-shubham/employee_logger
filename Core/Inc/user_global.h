/*
 * user_global.h
 *
 *  Created on: 11-Jan-2023
 *      Author: shubham
 */

#ifndef INC_USER_GLOBAL_H_
#define INC_USER_GLOBAL_H_



#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

extern int arr[4];

#define  USE_SSD1963_DISPLAY	1
#define  USE_RFID				1
#define  USE_FINGERPRINT		0
#define  USE_EEPROM				1
#define	 USE_RTC				1
#define  USE_DEBUG_LED			0
#define	 USE_DEBUG_UART			1
#define	 USE_FREERTOS			0

bool isTouched(uint16_t touchX1,uint16_t touchX2,uint16_t touchY1,uint16_t touchY2);

#endif

