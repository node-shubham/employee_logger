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
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);


#endif /* INC_IT_H_ */
