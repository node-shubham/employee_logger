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
#include "string.h"
#include "mfrc522.h"
#include "ds1307.h"
#include "24c256_config.h"


extern UART_HandleTypeDef uart1;
extern SPI_HandleTypeDef spi1;
extern I2C_HandleTypeDef i2c1;

extern u_char status;
extern u_char cardstr[MAX_LEN+1];
extern u_char issue_uid[MAX_LEN+1];
extern u_char card_data[17];
extern u_char UID[5];

extern uint8_t value;
extern char str1[40];
extern char str2[40];
extern char str3[40];
extern char str4[40];
extern char tmp_str[65];

extern u_char Mx1[7][5];
extern u_char SectorKey[7];

extern rtc_time_t current_time;
extern rtc_date_t current_date;


extern uint8_t dev_addr;
extern uint8_t dev_addr1;
extern uint16_t next_emp_id;
extern uint16_t last_emp_id;
extern uint16_t scanned_EMPLO_ID;
extern uint16_t calculate_addr;
extern uint32_t scanned_UID;
extern char emp_name[19];


extern u_char uid_read[4];

extern bool FLAG_SCAN ;



uint8_t check_validcard(uint16_t emp_id);
void rfid_read(void);
bool assign_card(void);


#endif /* INC_MFRC522_CONFIG_H_ */
