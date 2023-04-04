

#ifndef __EEPROM_STORE_H__
#define __EEPROM_STORE_H__

#include "main.h"
#include "stdio.h"
#include "string.h"
#include "ssd1963.h"
#include "stdbool.h"

#define LAST_EMP_ADDR         32736
#define EEPROM_LAST_ADDR      32767

extern I2C_HandleTypeDef i2c1;

#if 1
struct WRITE_DETAILS
{
	uint16_t wr_EMPLO_id;
	uint8_t wr_employee_code;  // employee code - 'E'
	uint8_t wr_EMPLO_desig;
	uint32_t wr_EMPLO_RFID;
	uint8_t wr_EMPLO_role;
	uint8_t wr_entry_HH;
	uint8_t wr_entry_MM;
	uint8_t wr_exit_HH;
	uint8_t wr_exit_MM;
	char wr_EMPLO_name[19];
};

struct READ_DETAILS
{
	uint16_t rd_EMPLO_id;
	uint8_t rd_employee_code;  // employee code - 'E'
	uint8_t rd_EMPLO_desig;
	uint32_t rd_EMPLO_RFID;
	uint8_t rd_EMPLO_role;
	uint8_t rd_entry_HH;
	uint8_t rd_entry_MM;
	uint8_t rd_exit_HH;
	uint8_t rd_exit_MM;
	char rd_EMPLO_name[19];
};

#endif

//////*********************************** Function Prototype ****************////////////


bool chek_employee (void);
void collect_id (void);
void display_Employee (void);
void add_Employee (void);
void erase_EEPROM (void);
void search_Employee (void);
void delete_Employee (void);


//////*********************************** Global variable ***************////////////




#endif   ///  last endif
