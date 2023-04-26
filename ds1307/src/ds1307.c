
#include "ds1307.h"

static uint8_t bin_to_bcd(uint8_t ); 
static uint8_t bcd_to_bin(uint8_t number);
static void ds1307_write(uint8_t value, uint8_t reg_addr);
static uint8_t ds1307_read(uint8_t reg_addr);

/* 
	return 1 : CH = 1 ;  init failed
	return 0 : CH = 0 ;  init pass

*/

uint8_t ds1307_init(void)
{
	/*oscillator start*/
	ds1307_write(0x00,DS1307_ADDR_SEC);
	uint8_t clock_state =	ds1307_read(DS1307_ADDR_SEC);
	return ((clock_state >>7)&0x1);
}

void ds1307_set_time(rtc_time_t * rtc_time)
{
	uint8_t seconds, hours;
	seconds = bin_to_bcd(rtc_time->sec);
	seconds &= ~(1<<7);
	ds1307_write(seconds,DS1307_ADDR_SEC);
	ds1307_write(bin_to_bcd(rtc_time->min),DS1307_ADDR_MIN);
	hours = bin_to_bcd(rtc_time->hour);
	if(rtc_time->time_format ==	TIME_FORMAT_24HR)
	{
		hours &= ~(1<<6);	
	}
	else
	{
		hours |= (1<<6);
		if(rtc_time->time_format ==	TIME_FORMAT_12HR_PM)
		{
			hours |= (1<<5);
		}
		else
		{
			hours &= ~(1<<5);
		}			
	}
	ds1307_write(hours,DS1307_ADDR_HOUR);	
}

void ds1307_get_time(rtc_time_t *rtc_time)
{
	uint8_t seconds, hours;
	seconds = ds1307_read(DS1307_ADDR_SEC);
	seconds &= ~(1<<7);
	rtc_time->sec = bcd_to_bin(seconds);
	rtc_time->min = bcd_to_bin(ds1307_read(DS1307_ADDR_MIN));
	hours = ds1307_read(DS1307_ADDR_HOUR);
	if(hours & (1<<6))
	{
			if(hours & (1<<5))
			{
				rtc_time->time_format = TIME_FORMAT_12HR_PM;
			}	
			else
			{
				rtc_time->time_format = TIME_FORMAT_12HR_AM;
			}
			hours &= ~(0x3<<5);
	}
	else
	{
		rtc_time->time_format = TIME_FORMAT_24HR;
	}	
	rtc_time->hour = bcd_to_bin(hours);	
	
}

void ds1307_set_date(rtc_date_t * rtc_date)
{
	ds1307_write(bin_to_bcd(rtc_date->day),DS1307_ADDR_DAY);
	ds1307_write(bin_to_bcd(rtc_date->date),DS1307_ADDR_DATE);
	ds1307_write(bin_to_bcd(rtc_date->month),DS1307_ADDR_MONTH);
	ds1307_write(bin_to_bcd(rtc_date->year),DS1307_ADDR_YEAR);
}	
void ds1307_get_date(rtc_date_t * rtc_date)
{
	rtc_date->day = bcd_to_bin(ds1307_read(DS1307_ADDR_DAY));
	rtc_date->date = bcd_to_bin(ds1307_read(DS1307_ADDR_DATE));
	rtc_date->month = bcd_to_bin(ds1307_read(DS1307_ADDR_MONTH));
	rtc_date->year = bcd_to_bin(ds1307_read(DS1307_ADDR_YEAR));	
}

static void ds1307_write(uint8_t value, uint8_t reg_addr)
{
	uint8_t tx[2];
	tx[0] = reg_addr;
	tx[1] =value;
	HAL_I2C_Master_Transmit(&I2C_HANDLE,DS1307_SLAVE_ADDR,tx,2,100);
}

static uint8_t ds1307_read(uint8_t reg_addr)
{
	uint8_t data;
	HAL_I2C_Master_Transmit(&I2C_HANDLE,DS1307_SLAVE_ADDR,&reg_addr,1,100);
	HAL_I2C_Master_Receive(&I2C_HANDLE,DS1307_SLAVE_ADDR,&data,1,100);
	return data;
}

static uint8_t bin_to_bcd(uint8_t number)
{
	uint8_t nibble_r,nibble_l;
	uint8_t bcd= number;
	if(number >= 10){
		nibble_r = number%10;
		nibble_l = number/10;
		bcd = (nibble_l<<4 | nibble_r) ;
	}
	return bcd;	
}

static uint8_t bcd_to_bin(uint8_t number)
{
	uint8_t digit_a,digit_b;
	uint8_t bin=0;
	digit_a = number & (uint8_t)(0x0f);
	digit_b = (number >> 4)*10;
	bin = digit_b+ digit_a ;
	return bin;
}


