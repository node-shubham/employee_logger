/*
 * r307_conifg.h
 *
 *  Created on: 22-Mar-2023
 *      Author: shubh
 */

#ifndef INC_R307_CONFIG_H_
#define INC_R307_CONFIG_H_

#include "fpm.h"
#include "uart_drv.h"

#include "ssd1963.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

bool fingerMatchFlag =0;
FPM finger;
FPM_System_Params params;


void r307_init(void);

/* tested functions */
void enroll_finger(int16_t fid);
uint8_t get_free_id(int16_t * fid);
uint16_t read_template(uint16_t fid, uint8_t * buffer, uint16_t buff_sz);
void match_prints(int16_t fid, int16_t otherfid);
void search_database(void);


void fingerprint_match_loop(void);	/* app specific */

void enroll_mainloop(void);
void templates_mainloop(void);
void matchprints_mainloop(void);
void searchdb_mainloop(void);


/* UART interface prototypes needed for FPM library */
uint16_t uart6_avail(void);
uint16_t uart6_read(uint8_t * bytes, uint16_t len);
void uart6_write(uint8_t * bytes, uint16_t len);

#endif /* INC_R307_CONFIG_H_ */
