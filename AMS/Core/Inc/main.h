/*
 * main.h
 *
 *  Created on: Jan 4, 2023
 *      Author: shubham
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#define WR_Pin GPIO_PIN_13
#define WR_GPIO_Port GPIOC
#define RS_Pin GPIO_PIN_14
#define RS_GPIO_Port GPIOC
#define CS_Pin GPIO_PIN_15
#define CS_GPIO_Port GPIOC
#define D0_Pin GPIO_PIN_0
#define D0_GPIO_Port GPIOA
#define D1_Pin GPIO_PIN_1
#define D1_GPIO_Port GPIOA
#define D2_Pin GPIO_PIN_2
#define D2_GPIO_Port GPIOA
#define D3_Pin GPIO_PIN_3
#define D3_GPIO_Port GPIOA
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOA
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOA
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOA
#define D7_Pin GPIO_PIN_7
#define D7_GPIO_Port GPIOA
#define XPT_CS_Pin GPIO_PIN_12
#define XPT_CS_GPIO_Port GPIOB
#define RD_Pin GPIO_PIN_8
#define RD_GPIO_Port GPIOB
#define RST_Pin GPIO_PIN_9
#define RST_GPIO_Port GPIOB

#endif /* INC_MAIN_H_ */
