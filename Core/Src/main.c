/*
 * main.c
 *
 *  Created on: Jan 4, 2023
 *      Author: shubham saha ray
 *
 *   	  Team:	shubham saha ray
 *   	  	  : Naveen Prakash
 * 			  : deepak
 *
 *    project : Bio-metric attendance Monitoring system using finger-print sensor & RFID cards
 *  	   	  : MQTT transmit to cloud option
 *  		  : RTOS based task scheduling and using WFI -sleep mode
 *  		  : SSD1963 display for application and touch based logging and monitoring.
 *
 *
 *  	 Pins :	PA0-PA7 (Display data pins)
 *  	 	  :	PC13,PC14,PC15,PB8,PB9 (Display ctrl pins)
 *  	 	  :	PB12,PB13,PB14,PB15, (SPI2 - Display touch pins)
 *
 *		!!! please update pin section
 */

#include "main.h"
#include "user_global.h"

#if (USE_SSD1963_DISPLAY)
	#include "ssd1963.h"
	#include "xpt2046.h"
#endif

#if (USE_RFID)
	#include "mfrc522.h"
#endif

#if (USE_FINGERPRINT)
	#include "fpm.h"
	#include "uart_drv.h"
	//#include "r307_config.h"
#endif

#if (USE_FREERTOS)
	#include "FreeRTOS.h"
	#include "task.h"
#endif

#if (USE_EEPROM)
	#include "24c256_config.h"
#endif


//#define SYSCLK_HSE_25MHZ
#define SYSCLK_PLL_84MHZ

#if (USE_FREERTOS)
#define DWT_CTRL 	(*(volatile int *)0xE0001000)
#endif

#if (USE_FINGERPRINT)
int __io_putchar(int ch)
{
    return uart_write(USART1, (uint8_t *)&ch, 1);
}
#endif

UART_HandleTypeDef uart1;
SPI_HandleTypeDef spi1;
SPI_HandleTypeDef spi2;
I2C_HandleTypeDef i2c2;
I2C_HandleTypeDef i2c1;
TIM_HandleTypeDef tim5;

extern uint8_t dev_addr;
extern uint8_t dev_addr1;
extern uint16_t next_emp_id;
extern uint16_t last_emp_id;
extern uint16_t scanned_EMPLO_ID;
extern uint16_t calculate_addr;
extern uint32_t scanned_UID;
extern char emp_name[19];
extern uint16_t next_emp_id;
extern uint16_t last_emp_id;

uint8_t value = 0;
char str1[40]={'\0'};
char str2[40]={'\0'};
char str3[40]={'\0'};
char str4[40]={'\0'};
char tmp_str[65]={'\0'};

u_char status, cardstr[MAX_LEN+1];
u_char card_data[17];
uint32_t delay_val = 1000;
uint16_t result = 0;
u_char UID[5];


// a private key to scramble data writing/reading to/from RFID card:
u_char Mx1[7][5]={{0x12,0x45,0xF2,0xA8},{0xB2,0x6C,0x39,0x83},{0x55,0xE5,0xDA,0x18},
				{0x1F,0x09,0xCA,0x75},{0x99,0xA2,0x50,0xEC},{0x2C,0x88,0x7F,0x3D}};
u_char SectorKey[7];

uint8_t char_cnt=0;
uint8_t curr_page = 1;
uint8_t admin_page = 0;
uint8_t view_page = 0;
uint8_t setting_page = 0;
uint8_t idx =0;

char str[50]={0};

extern uint16_t touchX;
extern uint16_t touchY;

unsigned char char_key[3][10] = {{'Q','W','E','R','T','Y','U','I','O','P'},{'A','S','D','F','G','H','J','K','L'},{'Z','X','C','V','B','N','M'}};
unsigned char symbol_key[3][10] = {{'1','2','3','4','5','6','7','8','9','0'},{'!','#','_','&','-','+','(',')','/'},{'*','"',':',';','!','[',']'}};
char *dropdown_desgn[4] = {"EMBEDDED","SOFTWARE","DESIGN","LEGAL"};
char *dropdown_role[3] = {"EMPLOYEE","ADMIN","SUPER USER",};
char *dropdown_CardThumb[2] = {"CARD","THUMB"};

//char emp_name[19] = {0};
char *desgn_ptr =	"EMBEDDED";
char *role_ptr = "EMPLOYEE";
char *card_ptr = "CARD";

uint8_t active_role=0;
uint8_t active_page =0;
uint8_t sub_page = 0;

unsigned char string[100];

//#define ALL_ZERO 		1
#define	DEBUG_UART	1
bool UC_FLAG = 0;
bool NUM_FLAG = 0;
bool SAVE_EDIT_FLAG =0;
bool drop_btn;
uint8_t keypad_down = 0;

//uint32_t ADMIN[4] = {95,385,55,225};

int onetime =1;

/*************************************************************/
uint16_t emp_id_read=11;
uint8_t test_id=0;

uint8_t desgn_id =0;
uint8_t role_id =0;

/*********temp************/

 u_char uid_read[4] ={0};
 int ia=128;
 uint8_t temp_str[100]={0};

/**************************************************************/

void sysclock_config(void);
void error_handler(void);

void gpio_init(void);
void uart1_init(void);
void spi1_init(void);
void spi2_init(void);
void i2c1_init(void);
void i2c2_init(void);
void tim5_init(void);

static void read_touch(void);
//extern
uint8_t check_validcard(uint16_t);
void rfid_read(void);

#if (USE_FREERTOS)
static void rfid_handler(void * param);
static void display_handler(void * param);
#endif

/*//static bool chek_employee (void);
void display_Employee (void);
void add_Employee (void);
void erase_EEPROM (void);*/

extern uint16_t g_pos_x;
extern uint16_t g_pos_y;




uint8_t pos =0;

uint32_t freq=0;
uint8_t rfid_id[4];
uint8_t issue_uid[4];

char card_auth[4]= {0x43,0xeb,0x79,0x03};
char msg[]="Approach your Proximate card\r\n";
char data[20]={0};

void assign_card(void);

#if (USE_FREERTOS)
BaseType_t status;
TaskHandle_t rfid_handle,display_handle;

void vApplicationIdleHook (void)
{
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

static void rfid_handler(void * param)
{
	while(1)
	{
		rfid_read();
		SEGGER_SYSVIEW_PrintfTarget("RFID Read");
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

static void display_handler(void * param)
{
	while(1)
	{
		read_touch();
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		SEGGER_SYSVIEW_PrintfTarget("Toggle Blue LED");
		vTaskDelay(pdMS_TO_TICKS(300));

	}
}
#endif


uint8_t check_validcard(uint16_t emp_id){

	/*
	scanned_EMPLO_ID = emp_id;
	if(chek_employee())
	{
		return 1;
	}
	return 0;
	*/

	///*

#if 1
	memset(uid_read,0,sizeof(uid_read));
	calculate_addr = FIRST_EMP_ADDR+(32*(emp_id-1))+4;
	HAL_I2C_Mem_Read(&i2c1, dev_addr1, calculate_addr, 2, (uint8_t *)&uid_read, 4, 100);
	sprintf(str1,"UID FROM EEPROM :%x %x %x %x\r\n",uid_read[0],uid_read[1],uid_read[2],uid_read[3]);
	HAL_UART_Transmit(&uart1,(uint8_t *)str1,strlen(str1),1000);
	if((uid_read[3]==cardstr[0])&&(uid_read[2]==cardstr[1])&&(uid_read[1]==cardstr[2])&&(uid_read[0]==cardstr[3]))
	{
		char msg[] = "Access Granted\r\n";
		HAL_UART_Transmit(&uart1,(uint8_t *)msg,sizeof(msg),1000);
		return 1;
	}
	char msg[] = "Access Denied\r\n";
	HAL_UART_Transmit(&uart1,(uint8_t *)msg,sizeof(msg),1000);
	return 0;
	 //*/
#endif

}


void read_card(void)
{
	//if(rc522_checkCard(rfid_id))
	{
		memset(data,0,sizeof(data));
		memset(issue_uid,0,sizeof(issue_uid));
#if (DEBUG_UART)
	HAL_UART_Transmit(&uart1,(uint8_t *)"RFID UID :",strlen("RFID UID :"),1000);
	sprintf(data,"%x %x %x %x\r\n",rfid_id[0],rfid_id[1],rfid_id[2],rfid_id[3]);
	HAL_UART_Transmit(&uart1,(uint8_t *)data,sizeof(data),1000);
#endif
		if(rfid_id[0] !=	0x26)
		{
			for(int i=0;i<4;i++)
				issue_uid[i]= rfid_id[i];
		}
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);
	}
}

int main()
{
	HAL_Init();
	sysclock_config();
	gpio_init();
	uart1_init();
	spi1_init();
	spi2_init();
	i2c1_init();
	//i2c2_init();
	//tim5_init();



	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
	MFRC522_Init();

	/* Display & touch Init */
#if (USE_SSD1963_DISPLAY)
	ssd1963_setup();
	XPT2046_Init();
#endif
	Front_screen();
	curr_page = 1 ;

#if (USE_FINGERPRINT)
  uart_init(USART1,9600);
  uart_init(USART6,57600);

  /* disable stdout buffering */
  setvbuf(stdout, NULL, _IONBF, 0);

	r307_init();
	fingerprint_match_loop();

	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);
	HAL_Delay(50);
#endif

#if (USE_EEPROM)
	HAL_I2C_Mem_Write(&i2c1,dev_addr,0x00,2,(uint8_t *)&emp_id_read,2,100);
	HAL_Delay(100);
	HAL_I2C_Mem_Read(&i2c1, dev_addr1, 0x00, 2, (uint8_t *)&test_id, 2, 100);
#endif
	HAL_UART_Transmit(&uart1,(uint8_t *)msg,sizeof(msg),1000);


//erase_EEPROM();

#if (USE_RFID)
status = Read_MFRC522(VersionReg);
sprintf(str1,"Running RC522");
sprintf(str2,"\r\t version:%x\r\n", status);
HAL_UART_Transmit(&uart1,(uint8_t *)str1,strlen(str1),1000);
HAL_UART_Transmit(&uart1,(uint8_t *)str2,strlen(str2),1000);
#endif


calculate_addr = FIRST_EMP_ADDR+(32*(11-1));
HAL_I2C_Mem_Read(&i2c1, dev_addr1, calculate_addr, 2, (uint8_t *)&read_details, sizeof(read_details), 100);
//while(1);
//collect_id();
while(1)
{
	touchX = (getX() + 12);
	touchY = (470 - getY());

	HAL_Delay(200);
	read_touch();
	rfid_read();
	/*****************************************  CURRENT PAGE 1 ****************************************************/

	if(curr_page == 1)
	{
		Admin_screen();
		curr_page = 2;
		/*
		if(1==check_validcard())
		{
			Tick_logo();
		}
		if(touchX >= 0 && touchX <= 800 && touchY >= 0 && touchY <= 480)
		{
			Admin_screen();
			curr_page = 2;
		}
		touchX=0;
		touchY=0;
		*/
	}

/*****************************************  CURRENT PAGE 2 ****************************************************/
	if(curr_page == 2){
		if(isTouched(200, 300, 85, 205)){	// USER MANAGEMENT
			User_Management();
			curr_page = 3;
		}

		if(isTouched( 500, 600, 85, 205))  // SEARCH ATTENDANCE
		{
			attendence_search();
			scanned_EMPLO_ID =1;
			calculate_addr = 128+(32*(scanned_EMPLO_ID-1));
			for(ia=0;ia<5;ia++)
			{
				calculate_addr = 128+(32*(scanned_EMPLO_ID-1));
//				display_Employee();
				print_string(170,194+ia*52,read_details.rd_EMPLO_name,BLACK);
				scanned_EMPLO_ID++;
			}
			curr_page = 7;
		}
		if(isTouched(200, 300, 275, 395))  // USER ROLE
		{
			Role_Page();
			curr_page = 8;
		}
		if(isTouched( 500, 600, 275, 395))  // SETTING
		{
			//fill_screen(PURPLE);
			//fill_roundrect(200, 350, 200, 250, YELLOW_2, PURPLE);
			//print_string(210, 205, "SYSTEM RESET", WHITE);

			//if(touchX >= 200 && touchX <= 350 && touchY >= 200 && touchY <= 250) // SYSTEM RESET
		   {
			    erase_EEPROM();
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
				HAL_Delay(200);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);
			  //HAL_I2C_Mem_Write(&i2c1,dev_addr,0x00,2,0,1,100);
				int val=0;
				HAL_I2C_Mem_Write(&i2c1,dev_addr,0x00,2,(uint8_t *)&val,1,100);
		   }
		}
	}

/*****************************************  CURRENT PAGE 3 ****************************************************/

	if(curr_page == 3)
	{
		if(isTouched( 327, 580, 115, 195)) // NEW USER
		{
			NewEntry_page();
			curr_page = 4;
		}
		if(isTouched( 327, 580, 280, 360)) // ALL USER
		{
			AllUser_Page();
			scanned_EMPLO_ID = 1;
			calculate_addr = 128+(32*(scanned_EMPLO_ID-1));
			for(ia=0;ia<emp_id_read;ia++)
			{
				calculate_addr = 128+(32*(scanned_EMPLO_ID-1));
//				display_Employee();
				print_string(170,194+ia*52,read_details.rd_EMPLO_name,BLACK);
				scanned_EMPLO_ID++;
			}
			//print_string(170,194,emp_name,0x9900ff);
			curr_page = 5;
		}
		if(isTouched( 8, 72, 10, 70)) // BACK
		{
			Admin_screen();

			curr_page = 2;
		}
		//print_int(next_emp_id, 620, 150, 0, 0, BLACK);


	}

/*****************************************  CURRENT PAGE 4 ****************************************************/
	if(curr_page == 4)
	{
		print_int(test_id, 590, 100, 0, 0, GREY);
		if(isTouched( 197, 503, 69, 135)) // NAME
		{
			curr_page =6;
			sub_page =7;
			PageKeyPad();
			keypad_down = 1;
			fill_area(210,400,80,120,0xe7eefe);
			Set_Font(&Font12x18);
			print_string(220,90,emp_name,0x737373);
		}
		if(isTouched( 450, 500, 170, 220)) // DESGI.
		{
			sub_page =1;
			drop_btn = !drop_btn;
			if(drop_btn)
			{
				NewUser_Name();
				NewUser_Desig(0,0,0,0);
				dropdown(&dropdown_desgn[0],4,0,0,0);
			}
			else
			{
				sub_page=0;
				fill_area(197,503,234,280+120,WHITE);
				NewUser_Role();
				NewUser_Card();
			}
		}
		if(isTouched( 450, 500, 260, 310)) // ROLE
		{
			sub_page =2;
			drop_btn = !drop_btn;
			if(drop_btn)
			{
				NewUser_Role();
				NewUser_Card();
				dropdown(&dropdown_role[0],3,0,0,-120);
			}
			else
			{
				sub_page=0;
				fill_area(197,503,124,170+80,WHITE);
				NewUser_Name();
				NewUser_Desig(0,0,0,0);
			}
		}
		if(isTouched( 450, 500, 355, 405)) // CARD/THUMB
		{
			sub_page =3;
			drop_btn = !drop_btn;
			if(drop_btn)
			{
				NewUser_Name();
				NewUser_Desig(0,0,0,0);
				NewUser_Card();
				dropdown(&dropdown_CardThumb[0],2,0,0,10);
			}
			else
			{
				sub_page=0;
				fill_area(197,503,244,300+40,WHITE);
				NewUser_Role();
			}
		}

		if(isTouched( 550, 650, 348, 408)) 	// SCAN
		{
			sub_page=3;
			if(active_role == 0)
			{
				//read_card();
				assign_card();
			}
			if(active_role == 1)
			{
				Front_screen();
			}
		}

		if(isTouched( 550, 650, 248, 308)) 	// SAVE
		{
			HAL_Delay(500);
			scanned_EMPLO_ID = emp_id_read;
			scanned_UID = (((0xffffffff & issue_uid[0])<<24)|((0xffffffff & issue_uid[1])<<16)|((0xffffffff & issue_uid[2])<<8)|issue_uid[3]);
			calculate_addr = 128+(32*(scanned_EMPLO_ID-1));

			/////////////////  data access section in structure by user  //////////////////////

			strcpy(write_details.wr_EMPLO_name, emp_name);
			write_details.wr_employee_code = 'E';
			write_details.wr_EMPLO_id = scanned_EMPLO_ID;
			write_details.wr_EMPLO_desig = desgn_id;
			write_details.wr_EMPLO_role = role_id;
			write_details.wr_EMPLO_RFID = scanned_UID;

			HAL_I2C_Mem_Write(&i2c1, dev_addr, calculate_addr, 2, (uint8_t *) &(write_details), sizeof(write_details), 100);  ///  write employee_id
			HAL_Delay(5);

		//	add_Employee();

			//HAL_I2C_Mem_Write(&i2c1,dev_addr,0x00,2,(uint8_t *)&scanned_EMPLO_ID,1,100);
			Set_Font(&Font12x18);
			print_string(550,240,"saved",RED);
		}
		if(isTouched( 8, 72, 10, 70)) //back
		{
			pos=0;
			memset(emp_name,'\0',17);
			User_Management();
			curr_page = 3;
		}

		if((sub_page ==1))
		{

			if(touchX >= 197 && touchX <= 503)
			{
				 if(touchY >= 234 && touchY <= 280)
				 {
					active_role =0;
					desgn_ptr =	dropdown_desgn[0];
					fill_area(210,400,180,210,0xe7eefe);
					fill_area(212,398,182,208,0xe7eefe);
					print_string(220,190,desgn_ptr,0x737373);
					dropdown(&dropdown_desgn[0],4,0,0,0);
					desgn_id =0;
				 }
				 if(touchY >= 234+40 && touchY <= 280+40)
				 {
					active_role =1;
					desgn_ptr =	dropdown_desgn[1];
					fill_area(210,400,180,210,0xe7eefe);
					print_string(220,190,desgn_ptr,0x737373);
					dropdown(&dropdown_desgn[0],4,0,0,0);
					desgn_id =1;
				 }
				 if(touchY >= 234+80 && touchY <= 280+80)
				 {
					 active_role =2;
					 desgn_ptr =	dropdown_desgn[2];
					 fill_area(210,400,180,210,0xe7eefe);
					 print_string(220,190,desgn_ptr,0x737373);
					 dropdown(&dropdown_desgn[0],4,0,0,0);
					 desgn_id =2;
				 }
				 if(touchY >= 234+120 && touchY <= 280+120)
				 {
					 active_role =3;
					 desgn_ptr = dropdown_desgn[3];
					 fill_area(210,400,180,210,0xe7eefe);
					 print_string(220,190,desgn_ptr,0x737373);
					 dropdown(&dropdown_desgn[0],4,0,0,0);
					 desgn_id =3;
				 }
			}
		}

		if(sub_page ==2)
		{
			//active_role=0;
			if(touchX >= 197 && touchX <= 503)
			{
				 if(touchY >= 124 && touchY <= 170)
				 {
					 active_role =0;
					 role_ptr =	dropdown_role[0];
					 fill_area(210,400,270,310,0xe7eefe);
					 print_string(220,280,role_ptr,0x737373);
					 dropdown(&dropdown_role[0],3,0,0,-120);
					 role_id =0;
				 }
				 if(touchY >= 124+40 && touchY <= 170+40)
				 {
					active_role =1;
					role_ptr =	dropdown_role[1];
					fill_area(210,400,270,310,0xe7eefe);
					print_string(220,280,role_ptr,0x737373);
					dropdown(&dropdown_role[0],3,0,0,-120);
					role_id =1;
				 }
				 if(touchY >= 124+80 && touchY <= 170+80)
				 {
					active_role =2;
					role_ptr =	dropdown_role[2];
					fill_area(210,400,270,310,0xe7eefe);
					print_string(220,280,role_ptr,0x737373);
					 dropdown(&dropdown_role[0],3,0,0,-120);
					role_id =2;
				 }
			}
		}

		if(sub_page ==3)
		{
			//active_role=0;
			if(touchX >= 197 && touchX <= 503)
			{
				 if(touchY >= 254 && touchY <= 300)
				 {
					active_role =0;
					card_ptr = dropdown_CardThumb[0];
					fill_area(210,400,370,400,0xe7eefe);
					print_string(220,375,card_ptr,0x737373);
					dropdown(&dropdown_CardThumb[0],2,0,0,10);
				 }
				 if(touchY >= 254+40 && touchY <= 300+40)
				 {
					active_role =1;
					card_ptr = dropdown_CardThumb[1];
					fill_area(210,400,370,400,0xe7eefe);
					print_string(220,375,card_ptr,0x737373);
					dropdown(&dropdown_CardThumb[0],2,0,0,10);
				 }
			}
		}

	}


/*****************************************  CURRENT PAGE 5 ****************************************************/
		//###################################   FOR ALL USER   ################################################
	if(curr_page == 5)
	{
		if(isTouched( 630, 720, 121, 169))  //SAVE
		{
		}
		if(isTouched( 590, 670, 121, 169))   //EDIT
		{
			SAVE_EDIT_FLAG = !SAVE_EDIT_FLAG;
			if(SAVE_EDIT_FLAG)
			{
				active_page = 1;
				fill_roundrect(593,667,124,166,0xe7eefe,0xcedcfd);
				print_string(610,138,"SAVE",0x737373);
				NewUser_Desig1(0xe7eefe);
				NewUser_Role1(0xe7eefe);
				NewUser_Card1(0xe7eefe);

			}
			else
			{
				active_page = 0;
				fill_roundrect(593,667,124,166,0xe7eefe,0xcedcfd);
				print_string(610,138,"EDIT",0x737373);
				NewUser_Desig1(0xcedcfd);
				NewUser_Role1(0xcedcfd);
				NewUser_Card1(0xcedcfd);
			}
		}

		if(active_page == 1)
			{
			 if(isTouched( 620,670,199,259))      //desig
				{
					sub_page =4;
					drop_btn = !drop_btn;
					if(drop_btn)
					{
					//	NewUser_Name();
						NewUser_Desig1(0xe7eefe);
						dropdown(&dropdown_desgn[0],4,297,167,32);
					}
					else
					{
				    	sub_page=0;
						fill_area(494,670,266,320+120,0xfffafa);
							//AllUser_Page();
						NewUser_Role1(0xe7eefe);
						NewUser_Card1(0xe7eefe);
					}
				}
				if(isTouched( 620,670,289,349))		//role
				{
					   sub_page =5;
					   drop_btn = !drop_btn;
					   if(drop_btn)
						{
							NewUser_Role1(0xe7eefe);
							NewUser_Card1(0xe7eefe);
							dropdown(&dropdown_role[0],3,297,167,-80);
						}
						else
						{
							sub_page=0;
							fill_area(494,670,154,200+80,0xfffafa);
							//AllUser_Page();
							//NewUser_Name();
							NewUser_Desig1(0xe7eefe);
							SaveAndEdit();
						}
					}
		if(isTouched( 620,670,379,439))//	494,720,379,439 // card
			{
				sub_page =6;
				drop_btn = !drop_btn;
				if(drop_btn)
				{
					//NewUser_Name();
					NewUser_Desig1(0xe7eefe);
					NewUser_Card1(0xe7eefe);
					dropdown(&dropdown_CardThumb[0],2,297,167,50);
				}
				else
				{
					sub_page=0;
					fill_area(494,670,284,330+40,0xfffafa);
					//AllUser_Page();
					NewUser_Role1(0xe7eefe);
				}
			}
		}
		if(isTouched( 8, 72, 10, 70)) //back
		{
			fill_area(25, 725, 96, 464,PURPLE);
			User_Management();
			curr_page = 3;
		}

		if((sub_page ==4))
		{
			if(touchX >= 494 && touchX <= 720)
			{
			 if(touchY >= 266 && touchY <= 312)
			 {
				active_role =0;
				desgn_ptr =	dropdown_desgn[0];
				fill_area(499,630,204,254,0xe7eefe);//0xe7eefe
				print_string(510,214,desgn_ptr,0x737373);
				dropdown(&dropdown_desgn[0],4,297,167,32);
			 }
			 if(touchY >= 266+40 && touchY <= 312+40)
			 {
				active_role =1;
				desgn_ptr =	dropdown_desgn[1];
				fill_area(499,630,204,254,0xe7eefe);
				print_string(510,214,desgn_ptr,0x737373);
				dropdown(&dropdown_desgn[0],4,297,167,32);
			 }
			 if(touchY >= 266+80 && touchY <= 312+80)
			 {
				active_role =2;
				desgn_ptr =	dropdown_desgn[2];
				fill_area(499,630,204,254,0xe7eefe);
				print_string(510,214,desgn_ptr,0x737373);
				dropdown(&dropdown_desgn[0],4,297,167,32);
			 }
			 if(touchY >= 266+120 && touchY <= 312+120)
			 {
				active_role =3;
				desgn_ptr =	dropdown_desgn[3];

				fill_area(499,630,204,254,0xe7eefe);
				print_string(510,214,desgn_ptr,0x737373);
				dropdown(&dropdown_desgn[0],4,297,167,32);
			 }
			}
		}

		if(sub_page ==5)
		{
			//active_role=0;
			if(touchX >= 494 && touchX <= 720)
			{
				 if(touchY >= 154 && touchY <= 200)
				 {
					active_role =0;
					role_ptr =	dropdown_role[0];
					fill_area(499,630,294,344,0xe7eefe);
					print_string(510,307,role_ptr,0x737373);
					dropdown(&dropdown_role[0],3,297,167,-80);
				 }
				 if(touchY >= 154+40 && touchY <= 200+40)
				 {
					active_role =1;
					role_ptr =	dropdown_role[1];
					fill_area(499,630,294,344,0xe7eefe);
					print_string(510,307,role_ptr,0x737373);
					dropdown(&dropdown_role[0],3,297,167,-80);
				 }
				 if(touchY >= 154+80 && touchY <= 200+80)
				 {
					active_role =2;
					role_ptr =	dropdown_role[2];
					fill_area(499,630,294,344,0xe7eefe);
					print_string(510,307,role_ptr,0x737373);
					dropdown(&dropdown_role[0],3,297,167,-80);
				 }
			}
		}
		if(sub_page ==6)
		{
			//active_role=0;
			if(touchX >= 494 && touchX <= 720)
			{
				 if(touchY >= 284 && touchY <= 330)
				 {
					active_role =0;
					card_ptr = dropdown_CardThumb[0];
					fill_area(499,630,384,434,0xe7eefe);
					print_string(510,400,card_ptr,0x737373);
					dropdown(&dropdown_CardThumb[0],2,297,167,50);
				 }
				 if(touchY >= 284+40 && touchY <= 330+40)
				 {
					active_role =1;
					card_ptr = dropdown_CardThumb[1];
					fill_area(499, 630, 384,434,0xe7eefe);
					print_string(510,400,card_ptr,0x737373);
					dropdown(&dropdown_CardThumb[0],2,297,167,50);
				 }
			}
		}
	}

/****************************  CURRENT PAGE 6 ***  KEYPAD_TOUCH**************************/
	if(curr_page == 6)
	{
		Set_Font(&Font12x18);
		//Set_Font(&Font16x24);
		//HAL_Delay(500);
		static uint8_t pos =0;
		int x=0,x1=0,y=31,y1=0,k=0;
		if(isTouched(197, 503, 69, 135)) // hide keypad  197, 503, 69, 135
		{
			keypad_down=!keypad_down;
			if(keypad_down == 1)
			 {
				//clear_area();
					fill_area(0,800,200,480,PURPLE);
					NewEntry_page();
					curr_page = 4;
			 }




			if(curr_page == 7)
			{
			}
		}

		if(isTouched(150, 215, 290+y, 330+y)) //caps  150,215,310+y,350+y
		{
			UC_FLAG = !UC_FLAG;
		}
		if(isTouched(275, 515, 340+y, 380+y))		// space 275,515,360+y,400+y
		{
			HAL_Delay(100);

			print_char(220+(pos*12),85,32,0xe7eefe);
			*(emp_name+pos) =32;
			pos++;
		}
		if(isTouched( 575, 640, 290+y, 330+y)) //backspace  575,640,310+y,350+y
		{
			pos--;
			fill_area(220+(pos*12),235+(pos*12),85,115,0xe7eefe);
		}

		for(int idx1=0; idx1<3; idx1++)
		{
			x1+=25*idx1;
			for(int idx2=0; idx2<=9-(idx1*2-k); idx2++)
			{
				if(isTouched( x1+150+x, x1+190+x, y1+190+y, y1+230+y))  //keys x1+105+x,x1+155+x,y1+205+y,y1+255+y
				{
							print_char(220+(pos*12),90,char_key[idx1][idx2],RED);
							*(emp_name+pos) =char_key[idx1][idx2];
						pos++;
				}
				x+=50;
			}
			x=0;
			k=1;
			y1+=50;
		}
		*(emp_name+pos+1)= '\0';

		}

/*****************************************  CURRENT PAGE 7 *********************************************/
	if(curr_page == 7)
	{
		if(isTouched( 190, 590, 36, 84)) //190,590,36,84 search attendance
		{
			PageKeyPad();
			keypad_down = 2;
			curr_page = 6;
			print_string(200,50,emp_name,0x737373); //190,590,36,84,
		}
		if(isTouched( 190, 590, 36, 84)) // HIDE KEYPAD
		{

		}

		if(isTouched( 8, 72, 10, 70)) // back
		{
			pos=0;
			memset(emp_name,'\0',17);
			Admin_screen();
			curr_page = 2;
		}
	}
/*****************************************  CURRENT PAGE 8 ****************************************************/
	if(curr_page == 8)
	{
		if(isTouched( 8, 72, 10, 70)) // back
		{
			Admin_screen();
			curr_page = 2;
		}
	}
}



	/* Timebase start 100ms */
	//HAL_TIM_Base_Start_IT(&tim5);

#if (DEBUG_UART)
	HAL_UART_Transmit(&uart1,(uint8_t *)msg,sizeof(msg),1000);
#endif

#if (USE_FREERTOS)
	DWT_CTRL |= (1<<0);
	//SEGGER_SYSVIEW_Conf();
	//SEGGER_SYSVIEW_Start();	 /* disable this while continuous recording*/

	status=xTaskCreate(rfid_handler,"RFID TASK", 200, NULL, 2, &rfid_handle);
	configASSERT(status ==pdPASS);

	status=xTaskCreate(display_handler,"DISPLAY TASK", 200, NULL, 2, &display_handle);
	configASSERT(status ==pdPASS);

	vTaskStartScheduler();

	while(1)
	{

	}
#endif

	return 0;
}

void sysclock_config(void)
{
	RCC_OscInitTypeDef osc;
	RCC_ClkInitTypeDef clock;

#if defined(SYSCLK_HSE_25MHZ)

	osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc.HSEState = RCC_HSE_ON;

	if(HAL_RCC_OscConfig(&osc) != HAL_OK)
	{
		printf("HSE Init failed\n\r");
	}


	clock.ClockType = RCC_CLOCKTYPE_SYSCLK;
	clock.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	clock.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clock.APB1CLKDivider = RCC_HCLK_DIV1;
	clock.APB2CLKDivider = RCC_HCLK_DIV1;

	if(HAL_RCC_ClockConfig(&clock, FLASH_LATENCY_0)!=HAL_OK)
	{
		printf("clock config failed\n\r");
	}

#elif defined(SYSCLK_PLL_84MHZ)

	osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc.HSEState = RCC_HSE_ON;

	osc.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	osc.PLL.PLLState = RCC_PLL_ON;
	osc.PLL.PLLM = 25;
	osc.PLL.PLLN = 168;
	osc.PLL.PLLP = RCC_PLLP_DIV2;

	if(HAL_RCC_OscConfig(&osc) != HAL_OK)
	{
		printf("PLL Init failed\n\r");
	}

	clock.ClockType = RCC_CLOCKTYPE_SYSCLK;
	clock.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clock.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clock.APB1CLKDivider = RCC_HCLK_DIV2;
	clock.APB2CLKDivider = RCC_HCLK_DIV1;

	if(HAL_RCC_ClockConfig(&clock, FLASH_LATENCY_2)!=HAL_OK)
	{
		printf("clock config failed\n\r");
	}
#else
	printf("No clock source selected !! HSI Running by default\n\r");
#endif

	//uint32_t freq=HAL_RCC_GetSysClockFreq();
	freq=HAL_RCC_GetSysClockFreq();
	printf("Sysclock frequency : %lu \r\n",freq);
}

void gpio_init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

#if (USE_SSD1963_DISPLAY)


	GPIO_InitTypeDef SSD_DATA_PINS ={0};

	SSD_DATA_PINS.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 \
						| GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;

	SSD_DATA_PINS.Mode = GPIO_MODE_OUTPUT_PP;
	SSD_DATA_PINS.Pull = GPIO_NOPULL;
	SSD_DATA_PINS.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &SSD_DATA_PINS);

	GPIO_InitTypeDef SSD_CTRL_PINS ={0};

	SSD_CTRL_PINS.Pin = GPIO_PIN_13 | GPIO_PIN_14| GPIO_PIN_15;

	SSD_CTRL_PINS.Mode = GPIO_MODE_OUTPUT_PP;
	SSD_CTRL_PINS.Pull = GPIO_NOPULL;
	SSD_CTRL_PINS.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOC, &SSD_CTRL_PINS);

	SSD_CTRL_PINS.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_12 ;

	HAL_GPIO_Init(GPIOB, &SSD_CTRL_PINS);
#endif


#if (USE_RFID)
	GPIO_InitTypeDef RFID_SPI ={0};
	RFID_SPI.Pin = (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2) ;
	RFID_SPI.Mode = GPIO_MODE_OUTPUT_PP;
	RFID_SPI.Pull = GPIO_NOPULL;
	RFID_SPI.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOB, &RFID_SPI);
#endif

#if 0
	RFID_SPI.Pin = (GPIO_PIN_8|GPIO_PIN_0);
	HAL_GPIO_Init(GPIOA, &RFID_SPI);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
#endif




#if (DEBUG_LED)
	GPIO_InitTypeDef LED;

	LED.Pin = GPIO_PIN_13;

	LED.Mode = GPIO_MODE_OUTPUT_PP;
	LED.Pull = GPIO_NOPULL;
	LED.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOC, &LED);
#endif

}

void uart1_init(void)
{
	uart1.Instance = USART1;
	uart1.Init.BaudRate =9600;
	uart1.Init.Parity=UART_PARITY_NONE;
	uart1.Init.Mode =UART_MODE_TX_RX;
	uart1.Init.StopBits= UART_STOPBITS_1;
	uart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart1.Init.WordLength = UART_WORDLENGTH_8B;
	uart1.Init.OverSampling= UART_OVERSAMPLING_16;

	if(HAL_UART_Init(&uart1)!= HAL_OK)
	{
		printf("Uart 1 Init Failed\r\n");
	}
}

void tim5_init(void)
{
	tim5.Instance = TIM5;

	tim5.Init.Prescaler = 2499;		// for 25 MHz - 1tick : 100us
	tim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	tim5.Init.Period = 1000;		// period : 100ms

	if(HAL_TIM_Base_Init(&tim5) != HAL_OK)
	{
		printf("Timer 5 base Init Failed\r\n");
	}
}

void spi1_init(void)
{

	spi1.Instance = SPI1;
	spi1.Init.Mode = SPI_MODE_MASTER;
	spi1.Init.Direction = SPI_DIRECTION_2LINES;
	spi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	spi1.Init.DataSize = SPI_DATASIZE_8BIT ;
	spi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	spi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	spi1.Init.NSS = SPI_NSS_SOFT ;
	spi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;

	if(HAL_SPI_Init(&spi1) != HAL_OK)
	{
		printf("SPI1 Init Failed\r\n");
	}

}

void spi2_init(void) 		/* SPI2 : XPT2048 Touch Sensor */
{

	spi2.Instance = SPI2;
	spi2.Init.Mode = SPI_MODE_MASTER;
	spi2.Init.Direction = SPI_DIRECTION_2LINES;
	spi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	spi2.Init.DataSize = SPI_DATASIZE_8BIT ;
	spi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	spi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	spi2.Init.NSS = SPI_NSS_SOFT ;
	spi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	spi2.Init.TIMode = SPI_TIMODE_DISABLE;

	if(HAL_SPI_Init(&spi2) != HAL_OK)
	{
		printf("SPI2 Init Failed\r\n");
	}
}

void i2c1_init(void)  		// 	using in eeprom
{

	i2c1.Instance = I2C1;
	i2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	i2c1.Init.ClockSpeed = 1000000;
	i2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	i2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;

	if(HAL_I2C_Init(&i2c1) != HAL_OK)
	{
		printf("I2C1 Init Failed\r\n");
	}
}

void i2c2_init(void)  		// please verify config once before using it
{
	i2c2.Instance = I2C2;
	i2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	i2c2.Init.ClockSpeed = 4000000;
	i2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	i2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;

	if(HAL_I2C_Init(&i2c2) != HAL_OK)
	{
		printf("I2C2 Init Failed\r\n");
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if (htim->Instance == TIM11)	/* TimeBase for HAL Layer */
	{
		HAL_IncTick();
	}

	if(htim->Instance == TIM5)
	{
#if (DEBUG_LED)
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
#endif
	}
}

/**********************************************************************
 * @fn : 	void read_touch(void);
 * @desc: 	read and calibrate current x & y position from touch sensor
 * @ret:	None
 * @arg: 	None
 */

static void read_touch(void)
{
	g_pos_x = getX()+12;	// calibration
	g_pos_y = 470-getY();

	/*
	while(!(TIM5->SR & TIM_SR_UIF)){}; 		// delay from time base
	TIM5->SR = 0;
	*/
}


void rfid_read(void)
{
	status = 0;
	status = MFRC522_Request(PICC_REQIDL, cardstr);
	if(status == MI_OK)
	{
		sprintf(str1,"Card:%x,%x,%x", cardstr[0], cardstr[1], cardstr[2]);
		HAL_Delay(2);
		status = MFRC522_Anticoll(cardstr);
		if(status == MI_OK) {
			uint16_t read_empId=0;
			sprintf(str2,"UID:%x %x %x %x \r\n", cardstr[0], cardstr[1], cardstr[2], cardstr[3]);
			HAL_UART_Transmit(&uart1,(uint8_t *)str2,strlen(str2),1000);
			UID[0] = cardstr[0];
			UID[1] = cardstr[1];
			UID[2] = cardstr[2];
			UID[3] = cardstr[3];
			UID[4] = cardstr[4];
			HAL_Delay(10);
			status = MFRC522_SelectTag(cardstr);
			if (status > 0){
			  SectorKey[0] = ((Mx1[0][0])^(UID[0])) + ((Mx1[0][1])^(UID[1])) + ((Mx1[0][2])^(UID[2])) + ((Mx1[0][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[1] = ((Mx1[1][0])^(UID[0])) + ((Mx1[1][1])^(UID[1])) + ((Mx1[1][2])^(UID[2])) + ((Mx1[1][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[2] = ((Mx1[2][0])^(UID[0])) + ((Mx1[2][1])^(UID[1])) + ((Mx1[2][2])^(UID[2])) + ((Mx1[2][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[3] = ((Mx1[3][0])^(UID[0])) + ((Mx1[3][1])^(UID[1])) + ((Mx1[3][2])^(UID[2])) + ((Mx1[3][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[4] = ((Mx1[4][0])^(UID[0])) + ((Mx1[4][1])^(UID[1])) + ((Mx1[4][2])^(UID[2])) + ((Mx1[4][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[5] = ((Mx1[5][0])^(UID[0])) + ((Mx1[5][1])^(UID[1])) + ((Mx1[5][2])^(UID[2])) + ((Mx1[5][3])^(UID[3]));// 0x11; //KeyA[0]
			  HAL_Delay(10);
			  status = MFRC522_Auth(0x60, 3, SectorKey, cardstr);
			  unsigned char user_bytes[16]={0};
			  status =MFRC522_Read(3, user_bytes);
			  if(status == MI_OK) {
				sprintf(str2,"DATA:%x %x %x %x \r\n", user_bytes[9], user_bytes[10], user_bytes[11], user_bytes[12]);
				HAL_UART_Transmit(&uart1,(uint8_t *)str2,strlen(str2),1000);

				read_empId = (((user_bytes[10]& 0xffff)<<8)| (user_bytes[11]& 0x00ff));
				sprintf(str2,"employee id in card : %d\r\n", read_empId);
				HAL_UART_Transmit(&uart1,(uint8_t *)str2,strlen(str2),1000);
			  }
			}
			if(1==check_validcard(read_empId))
			{
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
				HAL_Delay(100);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);
#if (DEBUG_UART)
				//HAL_UART_Transmit(&uart1,(uint8_t *)"Authorised Access\r\n",strlen("Authorised Access\r\n"),1000);
#endif
			}
			MFRC522_StopCrypto1();
			MFRC522_Halt();
		}
	}
	/*
	if(rc522_checkCard(rfid_id))
		{
			memset(data,0,sizeof(data));
#if (DEBUG_UART)
			HAL_UART_Transmit(&uart1,(uint8_t *)"RFID UID :",strlen("RFID UID :"),1000);
			sprintf(data,"%x %x %x %x\r\n",rfid_id[0],rfid_id[1],rfid_id[2],rfid_id[3]);
			HAL_UART_Transmit(&uart1,(uint8_t *)data,sizeof(data),1000);
#endif
			if(1==check_validcard())
			{
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
				HAL_Delay(100);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);
#if (DEBUG_UART)
				HAL_UART_Transmit(&uart1,(uint8_t *)"Authorised Access\r\n",strlen("Authorised Access\r\n"),1000);
#endif
			}
		}
	*/

}



void assign_card(void)
{
	status = 0;
	status = MFRC522_Request(PICC_REQIDL, cardstr);
	if(status == MI_OK)
	{
		sprintf(str1,"Card:%x,%x,%x", cardstr[0], cardstr[1], cardstr[2]);
		HAL_Delay(2);
		status = MFRC522_Anticoll(cardstr);
		if(status == MI_OK) {
			sprintf(str2,"UID:%x %x %x %x \r\n", cardstr[0], cardstr[1], cardstr[2], cardstr[3]);
			HAL_UART_Transmit(&uart1,(uint8_t *)str2,strlen(str2),1000);
			UID[0] = cardstr[0];
			UID[1] = cardstr[1];
			UID[2] = cardstr[2];
			UID[3] = cardstr[3];
			UID[4] = cardstr[4];
			HAL_Delay(2);
			status = MFRC522_SelectTag(cardstr);
			if (status > 0){
			  SectorKey[0] = ((Mx1[0][0])^(UID[0])) + ((Mx1[0][1])^(UID[1])) + ((Mx1[0][2])^(UID[2])) + ((Mx1[0][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[1] = ((Mx1[1][0])^(UID[0])) + ((Mx1[1][1])^(UID[1])) + ((Mx1[1][2])^(UID[2])) + ((Mx1[1][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[2] = ((Mx1[2][0])^(UID[0])) + ((Mx1[2][1])^(UID[1])) + ((Mx1[2][2])^(UID[2])) + ((Mx1[2][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[3] = ((Mx1[3][0])^(UID[0])) + ((Mx1[3][1])^(UID[1])) + ((Mx1[3][2])^(UID[2])) + ((Mx1[3][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[4] = ((Mx1[4][0])^(UID[0])) + ((Mx1[4][1])^(UID[1])) + ((Mx1[4][2])^(UID[2])) + ((Mx1[4][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[5] = ((Mx1[5][0])^(UID[0])) + ((Mx1[5][1])^(UID[1])) + ((Mx1[5][2])^(UID[2])) + ((Mx1[5][3])^(UID[3]));// 0x11; //KeyA[0]
			  HAL_Delay(2);
			  status = MFRC522_Auth(0x60, 3, SectorKey, cardstr);
			  if (status == MI_OK){
				  sprintf(str3, "Auth. OK");
				  HAL_UART_Transmit(&uart1,(uint8_t *)str3,strlen(str3),1000);
				  // Clean-Up the Card:
				  card_data[0] = 0xFF;
				  card_data[1] = 0xFF;
				  card_data[2] = 0xFF;
				  card_data[3] = 0xFF;
				  card_data[4] = 0xFF;
				  card_data[5] = 0xFF;
				  card_data[6] = 0xFF; //Access_bits[6]
				  card_data[7] = 0x07; //Access_bits[7]
				  card_data[8] = 0x80; //Access_bits[8]
				  card_data[9] = 0x00;  //user_byte[9]
				  card_data[10] = 0x00; //user_byte[10]
				  card_data[11] = 0x00; //user_byte[11]
				  HAL_Delay(2);
				  status = MFRC522_Write(3, card_data);
				  if(status == MI_OK) {
					  result++;
					  sprintf(str3, "                ");
					  sprintf(str4, "Card Cleared!");
					  HAL_UART_Transmit(&uart1,(uint8_t *)str3,strlen(str3),1000);
					  HAL_UART_Transmit(&uart1,(uint8_t *)str4,strlen(str4),1000);
				  }
			  }
		   }
		}
	}
	MFRC522_StopCrypto1();
	HAL_Delay(20);
	MFRC522_Halt();

	uint8_t e_id[2]={0};
	e_id[0] =	(emp_id_read>>8)& 0xff;
	e_id[1] = 	emp_id_read & 0xff;

	for (int i = 0; i < 16; i++) {cardstr[i] = 0;}
	status = 0;
	// Find cards
	HAL_Delay(2);
	status = MFRC522_Request(PICC_REQIDL, cardstr);
	HAL_Delay(2);
	status = MFRC522_Anticoll(cardstr);
	HAL_Delay(2);
	status = MFRC522_SelectTag(cardstr);
	SectorKey[0] = 0xFF;
	SectorKey[1] = 0xFF;
	SectorKey[2] = 0xFF;
	SectorKey[3] = 0xFF;
	SectorKey[4] = 0xFF;
	SectorKey[5] = 0xFF;
	HAL_Delay(2);
	status = MFRC522_Auth(0x60, 3, SectorKey, cardstr);
	if (status == MI_OK){
	  card_data[0] = ((Mx1[0][0])^(UID[0])) + ((Mx1[0][1])^(UID[1])) + ((Mx1[0][2])^(UID[2])) + ((Mx1[0][3])^(UID[3]));// 0x11; //KeyA[0]
	  card_data[1] = ((Mx1[1][0])^(UID[0])) + ((Mx1[1][1])^(UID[1])) + ((Mx1[1][2])^(UID[2])) + ((Mx1[1][3])^(UID[3]));// 0x11; //KeyA[0]
	  card_data[2] = ((Mx1[2][0])^(UID[0])) + ((Mx1[2][1])^(UID[1])) + ((Mx1[2][2])^(UID[2])) + ((Mx1[2][3])^(UID[3]));// 0x11; //KeyA[0]
	  card_data[3] = ((Mx1[3][0])^(UID[0])) + ((Mx1[3][1])^(UID[1])) + ((Mx1[3][2])^(UID[2])) + ((Mx1[3][3])^(UID[3]));// 0x11; //KeyA[0]
	  card_data[4] = ((Mx1[4][0])^(UID[0])) + ((Mx1[4][1])^(UID[1])) + ((Mx1[4][2])^(UID[2])) + ((Mx1[4][3])^(UID[3]));// 0x11; //KeyA[0]
	  card_data[5] = ((Mx1[5][0])^(UID[0])) + ((Mx1[5][1])^(UID[1])) + ((Mx1[5][2])^(UID[2])) + ((Mx1[5][3])^(UID[3]));// 0x11; //KeyA[0]
	  card_data[6] = 0xFF; //Access_bits[6]
	  card_data[7] = 0x07; //Access_bits[7]
	  card_data[8] = 0x80; //Access_bits[8]

	  card_data[9] = 0x00; //user_byte[9]
	  card_data[10] = e_id[0]; //user_byte[10]
	  card_data[11] = e_id[1]; //user_byte[11]
	  HAL_Delay(2);
	  status = MFRC522_Write(3, card_data);
	  if(status == MI_OK) {
		  sprintf(str3, "Card Set!");
		  HAL_UART_Transmit(&uart1,(uint8_t *)str3,strlen(str3),1000);
	  }
	  else{
		  sprintf(str4, "New Card!");
		  HAL_UART_Transmit(&uart1,(uint8_t *)str4,strlen(str4),1000);
	  }
	  unsigned char user_bytes[16]={0};
	  status =MFRC522_Read(3, user_bytes);
	  if(status == MI_OK) {
		sprintf(str2,"DATA:%x %x %x %x \r\n", user_bytes[9], user_bytes[10], user_bytes[11], user_bytes[12]);
		HAL_UART_Transmit(&uart1,(uint8_t *)str2,strlen(str2),1000);
	  }
	}
}




/***************************************************************************************************************************/

void error_handler(void)
{
	printf("In Error Handler\r\n");
	while(1);
}
