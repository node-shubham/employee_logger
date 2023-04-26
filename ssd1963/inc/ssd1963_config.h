	#ifndef __SSD1963_CONFIG_H__
	#define __SSD1963_CONFIG_H__

	
	#include "types.h"
	#include "fonts.h"
	#include "stdlib.h"
	#include "main.h"
	#include "stdbool.h"

    extern struct WRITE_DETAILS write_details;
    extern struct READ_DETAILS read_details;

	extern char emp_name[19];
	extern char *desgn_ptr;
	extern char *role_ptr;
	extern char *card_ptr;

	extern bool UC_FLAG;
	extern bool NUM_FLAG;
	extern bool drop_btn;


	extern unsigned char symbol_key[3][10];
	extern unsigned char char_key[3][10];

	extern uint8_t active_role;
	extern uint8_t sub_page;
	extern uint8_t idx;
		

	/*@fn	write_8bit(data) :  first reset data port
	 * 					extract LSB and shift it assigned D0 pin
	 * 					e,g if D0 is at PA3 then extract LSB from given data and shift it thrice
	 * 					extract all bits and perform shift until MSB
	 * 					e,g if D5 is at PA9  --> (data &(1<<5))<<4;  A9 : 5+4
	 *
	 */

	#define write_8bit(data) \
			{ \
		SSD1963_DATAPORT->BSRR = (0x01DF <<16); \
		GPIOA->BSRR = (((data) & (1<<0)) <<0); \
		GPIOA->BSRR = (((data) & (1<<1)) <<0); \
		GPIOA->BSRR = (((data) & (1<<2)) <<0); \
		GPIOA->BSRR = (((data) & (1<<3)) <<0); \
		GPIOA->BSRR = (((data) & (1<<4)) <<0); \
		GPIOA->BSRR = (((data) & (1<<5)) <<3); \
		GPIOA->BSRR = (((data) & (1<<6)) <<0); \
		GPIOA->BSRR = (((data) & (1<<7)) <<0); \
			}
	
///////////////////////  APLLICATION SPECIFIC FUNCTIONS  /////////////////////////

	void test_color(void); 		 
	void test_pixel(void);
	void test_increment(u32 p, s16 q);
	void v_slider(u32 x, u32 y,u32 len, u32 color);
	void h_slider(u32 x, u32 y,u32 len, u32 color);
	void print_grid(void);
	void test_point(void);
	void test_point1(void);
	void background_page(void);
	void logo_page(void);


	void thumb_screen(void);
	void Admin_screen(void);
	void User_Management(void);
	void login_page(s16 x, s16 y);
	void thumb_page(void);
	void admin_menu(void);
  void PageKeyPad(void);

	void BackBtn(void);
	void touchBack(void);
	void Tick_logo(void);
	void table_page(void);
	void cursor(void);
	void dropdown(char * arr[],u32 NumOfBox,s16 x1,s16 x2,s16 y1);
	void clear_dropdown(void);
	void attendence_search(void);
	void Role_Page(void);
	void AllUser_Page(void);
	void BackSpaceBtn(u32 x, u32 y);


	void NewEntry_page(void);
	void NewUser_Name(void);
	void NewUser_Desig(s32 x1, s32 x2, s32 y1, s32 y2);
	void NewUser_Role(void);
	void NewUser_Card(void);
	void NewUserSideBtn(void);
	void search_table(void);

	void NewUser_Desig1(u32 Fill_colour);
	void NewUser_Role1(u32 Fill_colour);
	void NewUser_Card1(u32 Fill_colour);
	void SaveAndEdit (void);


	void table_page(void);
	void therapy_timer(void);
	void beauty_health(void);
	void time_calc(uint32_t therapy_time);

	void table_button(void);
	void table_element(void);

	void fill_UpTriangle(s16 x, s16 y, u16 size, u32 colour);   /// created by naveen
	void fill_DownTriangle(s16 x, s16 y, u16 size, u32 colour);   /// created by naveen
	void fill_LeftTriangle(s16 x, s16 y, u16 size, u32 colour);   /// created by naveen
	void fill_RightTriangle(s16 x, s16 y, u16 size, u32 colour);   /// created by naveen
	void symbol_dwn_Arrow (u32 x, u32 y, u32 color);

	void Up_Button(s16 x, s16 y, u16 size, u32 circle_colour, u32 Button_colour);   /// created by naveen
	void Down_Button(s16 x, s16 y, u16 size, u32 circle_colour, u32 Button_colour);   /// created by naveen
	void Left_Button(s16 x, s16 y, u16 size, u32 circle_colour, u32 Button_colour);   /// created by naveen
	void Right_Button(s16 x, s16 y, u16 size, u32 circle_colour, u32 Button_colour);   /// created by naveen


	void table_init(void);
	void table_update(u32 touchX, u32 touchY);

	//////////////////////////////////THEME SPECIFIC COLORS ////////////////////////////////////////
	
	#define bg_color	0xDF711B			//0x007267
	#define button_fill_color 0xd9611d//0xB61919
	#define button2_fill_color 0x52b788//0x74c69d//0x40916c//0x52b788//0xB61919
	#define border_color 0xad4d17	//0xc3571a//0xFFB740		//0xb7fff8
	#define card_border_color 0xb7fff8	
	#define slider_fill_color 0x083434
	
	#define table_color 0xf7f9fe//d9d9d9//0xbfbfbf
	#define table_color_2 0xf0f4ff//e7eefe//fffafa//cee6fd//bfbfbf//0xd9d9d9
	#define table_border_color  0x99b1ff//0xe6e6e6//0x52b788//0x40916c

	
	#endif
	
	
