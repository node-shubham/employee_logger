
#ifndef __DS1307_H__
#define __DS1307_H__

#include "stdint.h"
#include "stm32f4xx.h"

/* Application configurable items */

extern I2C_HandleTypeDef i2c2;
#define I2C_HANDLE		i2c2

/* Register addresses */

#define DS1307_ADDR_SEC  		0x00
#define DS1307_ADDR_MIN  		0x01
#define DS1307_ADDR_HOUR  		0x02
#define DS1307_ADDR_DAY  		0x03
#define DS1307_ADDR_DATE  		0x04
#define DS1307_ADDR_MONTH  		0x05
#define DS1307_ADDR_YEAR  		0x06
#define DS1307_ADDR_CTRL  		0x07

#define TIME_FORMAT_12HR_AM		0
#define TIME_FORMAT_12HR_PM		1
#define TIME_FORMAT_24HR		2

//#define DS1307_SLAVE_ADDR		0x68
#define DS1307_SLAVE_ADDR		0xD0

#define MONDAY 				1
#define	TUESDAY 			2
#define WEDNESDAY			3
#define THURSDAY			4
#define FRIDAY				5
#define SATURDAY			6
#define SUNDAY				7

typedef struct
{
	uint8_t date;
	uint8_t month;
	uint8_t year;
	uint8_t day;

}rtc_date_t;	

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t time_format;

}rtc_time_t;

uint8_t ds1307_init(void);
void ds1307_set_time(rtc_time_t *);
void ds1307_get_time(rtc_time_t *);

void ds1307_set_date(rtc_date_t *);
void ds1307_get_date(rtc_date_t *);


#endif
