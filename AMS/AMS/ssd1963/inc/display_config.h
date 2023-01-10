#ifndef __DISPLAY_CONFIG_H__
#define __DISPLAY_CONFIG_H__

#include "ssd1963.h"
#include "main.h"

#define SSD1963_PIN_CS	(1 << 15)
#define SSD1963_PIN_RS	(1 << 14)
#define SSD1963_PIN_RD	(1 << 8)
#define SSD1963_PIN_WR	(1 << 13)
#define SSD1963_PIN_RST	(1 << 9)

#define CS_PORT  GPIOC
#define RS_PORT  GPIOC
#define WR_PORT  GPIOC

#define RD_PORT  GPIOB
#define RST_PORT  GPIOB

#define SSD1963_DATAPORT	GPIOA


/*@fn	write_8bit(data) :  first reset data port
 * 					extract LSB and shift it assigned D0 pin
 * 					e,g if D0 is at PA3 then extract LSB from given data and shift it thrice
 * 					extract all bits and perform shift until MSB
 * 					e,g if D5 is at PA9  --> (data &(1<<5))<<4;  A9 : 5+4
 *
 */

#define write_8bit(data) \
		{ \
	SSD1963_DATAPORT->BSRR = (0x00FF <<16); \
	GPIOA->BSRR = (((data) & (1<<0)) <<0); \
	GPIOA->BSRR = (((data) & (1<<1)) <<0); \
	GPIOA->BSRR = (((data) & (1<<2)) <<0); \
	GPIOA->BSRR = (((data) & (1<<3)) <<0); \
	GPIOA->BSRR = (((data) & (1<<4)) <<0); \
	GPIOA->BSRR = (((data) & (1<<5)) <<0); \
	GPIOA->BSRR = (((data) & (1<<6)) <<0); \
	GPIOA->BSRR = (((data) & (1<<7)) <<0); \
		}


///////////////////////////  APLLICATION SPECIFIC FUNCTIONS  /////////////////////////

void test_color(void);
void test_pixel(void);
void test_increment(u32 p, s16 q);
void v_slider(u32 x, u32 y,u32 len, u32 color);
void h_slider(u32 x, u32 y,u32 len, u32 color);
void print_grid(void);
void test_point(void);
void test_point1(void);
void background_page(void);
void Front_Page(void);

////////////////////////////// THEME SPECIFIC COLORS  //////////////////////////////

#define bg_color	0xDF711B
#define button_fill_color 0xd9611d
#define button2_fill_color 0x52b788
#define border_color 0xad4d17
#define card_border_color 0xb7fff8
#define slider_fill_color 0x083434

#define table_color 0xb7e4c7
#define table_color_2 0xd8f3dc
#define table_border_color 0x52b788

#endif

