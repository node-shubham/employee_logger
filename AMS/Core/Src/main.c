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
 *    project : Bio-metric attendance Monitoring system using finger print sensor & RFID cards
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

#include "ssd1963.h"
#include "xpt2046.h"
#include "mfrc522.h"

#include "FreeRTOS.h"
#include "task.h"

//#define SYSCLK_HSE_25MHZ
#define SYSCLK_PLL_84MHZ

#define  SSD1963_DISPLAY	1
#define  DEBUG_LED			0
#define  DEBUG_UART			0

#define DWT_CTRL 	(*(volatile int *)0xE0001000)

UART_HandleTypeDef uart1;
SPI_HandleTypeDef spi1;
SPI_HandleTypeDef spi2;
I2C_HandleTypeDef i2c2;
TIM_HandleTypeDef tim5;


void sysclock_config(void);
void error_handler(void);

void gpio_init(void);
void uart_init(void);
void spi1_init(void);
void spi2_init(void);
void i2c2_init(void);
void tim5_init(void);

static void read_touch(void);
extern uint8_t check_validcard(void);
void rfid_read(void);

static void rfid_handler(void * param);
static void display_handler(void * param);

extern uint16_t g_pos_x;
extern uint16_t g_pos_y;

uint32_t freq=0;
uint8_t rfid_id[4];
char card_auth[4]= {0x43,0xeb,0x79,0x03};
char msg[]="Approach your Proximate card\r\n";
char data[20]={0};

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
		vTaskDelay(pdMS_TO_TICKS(1000));

	}
}

int main()
{
	HAL_Init();
	sysclock_config();

	gpio_init();
	uart_init();
	spi1_init();
	spi2_init();
	//i2c2_init();
	//tim5_init();

	rc522_init();

#if (SSD1963_DISPLAY)
	/* Display & touch Init */

	ssd1963_setup();
	XPT2046_Init();
#endif
Front_Page();
Menu_Page();
Admin_Login();
Login_Page();


	while(1);
	/* Timebase start 100ms */
	//HAL_TIM_Base_Start_IT(&tim5);

#if (DEBUG_UART)
	HAL_UART_Transmit(&uart1,(uint8_t *)msg,sizeof(msg),1000);
#endif

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

#if (SSD1963_DISPLAY)


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

	SSD_CTRL_PINS.Pin = GPIO_PIN_8 | GPIO_PIN_9 ;

	HAL_GPIO_Init(GPIOB, &SSD_CTRL_PINS);
#endif


#if 1
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


void uart_init(void)
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
	spi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;


	if(HAL_SPI_Init(&spi1) != HAL_OK)
	{
		printf("SPI1 Init Failed\r\n");
	}

}

void spi2_init(void)
{

	spi2.Instance = SPI2;
	spi2.Init.Mode = SPI_MODE_MASTER;
	spi2.Init.Direction = SPI_DIRECTION_2LINES;
	spi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	spi2.Init.DataSize = SPI_DATASIZE_8BIT ;
	spi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	spi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	spi2.Init.NSS = SPI_NSS_HARD_OUTPUT ;
	spi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	spi2.Init.TIMode = SPI_TIMODE_DISABLE;

	if(HAL_SPI_Init(&spi2) != HAL_OK)
	{
		printf("SPI2 Init Failed\r\n");
	}
}

void i2c2_init()  //incomplete !!  please verify once before using it
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

}

void error_handler(void)
{
	printf("In Error Handler\r\n");
	while(1);
}
