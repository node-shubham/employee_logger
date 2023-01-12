/*
 * mfrc522_config.h
 *
 *  Created on: 09-Jan-2023
 *      Author: shubham
 */

#ifndef INC_MFRC522_CONFIG_H_
#define INC_MFRC522_CONFIG_H_

#include "main.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"

extern uint8_t rfid_id[4];
extern char card_auth[4];

extern UART_HandleTypeDef uart1;
extern SPI_HandleTypeDef spi1;

#define MFRC522_CS_PORT		GPIOB
#define MFRC522_CS_PIN		(1<<0)

#define MFRC522_RST_PORT	GPIOB
#define MFRC522_RST_PIN		(1<<1)


uint8_t check_validcard(void);


#endif /* INC_MFRC522_CONFIG_H_ */
