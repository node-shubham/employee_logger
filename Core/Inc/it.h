/*
 * it.h
 *
 *  Created on: Jan 4, 2023
 *      Author: shubham
 */

#ifndef INC_IT_H_
#define INC_IT_H_

#include "main.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void DebugMon_Handler(void);

void TIM1_TRG_COM_TIM11_IRQHandler(void);		// Timebase source

#endif /* INC_IT_H_ */
