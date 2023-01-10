/*
 * it.c
 *
 *  Created on: Jan 4, 2023
 *      Author: shubham
 */


#include "it.h"


extern TIM_HandleTypeDef tim5;
extern TIM_HandleTypeDef htim10;
/*
void SysTick_Handler(void)
{
	HAL_IncTick();
}
*/

void TIM5_IRQHandler(void)
{
	//HAL_NVIC_ClearPendingIRQ(TIM5_IRQn);
	//user_handler();
	HAL_TIM_IRQHandler(&tim5);

}

void TIM1_UP_TIM10_IRQHandler(void)
{

  HAL_TIM_IRQHandler(&htim10);

}
