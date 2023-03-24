
#ifndef __EEPROM_STORE_H__
#define __EEPROM_STORE_H__

#include "main.h"
#include "stdbool.h"

extern I2C_HandleTypeDef hi2c1;


extern struct WRITE_DETAILS write_details;
extern struct READ_DETAILS read_details;


extern bool availble_employee;
extern bool	chek_wr;
extern uint16_t scanned_EMPLO_ID;
extern uint32_t scanned_UID;
extern uint16_t erase_addr_cnt;
extern uint8_t dev_addr;
extern uint8_t dev_addr1;
extern  uint16_t calculate_addr;

#endif