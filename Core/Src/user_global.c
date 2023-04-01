/*
 * user_global.c
 *
 *  Created on: 11-Jan-2023
 *      Author: shubham
 */

#include "user_global.h"




uint16_t g_pos_x = 0;
uint16_t g_pos_y = 0;

int arr[4]={1,2,3,5};

uint16_t touchX = 0;
uint16_t touchY = 0;

bool isTouched(uint16_t touchX1,uint16_t touchX2,uint16_t touchY1,uint16_t touchY2)
{
	if(touchX >= touchX1 && touchX <= touchX2 && touchY >= touchY1 && touchY <= touchY2){
		return 1;
	}
	return 0;
}
