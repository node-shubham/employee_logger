/*
 * it.c
 *
 *  Created on: Jan 4, 2023
 *      Author: shubham
 */


#include "it.h"


extern TIM_HandleTypeDef tim5;
extern TIM_HandleTypeDef htim11;

/*
void SysTick_Handler(void)
{
	HAL_IncTick();
}
*/

void TIM5_IRQHandler(void)
{

	HAL_TIM_IRQHandler(&tim5);

}

void TIM1_TRG_COM_TIM11_IRQHandler(void)	// Timebase source
{
  HAL_TIM_IRQHandler(&htim11);

}


