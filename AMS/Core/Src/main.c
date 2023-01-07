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
 *  		  : RTOS based task scheduling and using sleep modes
 *  		  : SSD1963 display for application and touch based logging and monitoring.
 *
 */


#include "main.h"
#include "global.h"

#include "ssd1963.h"
#include "xpt2046.h"

#define DEBUG	1

void sysclock_config(void);
void error_handler(void);

void gpio_init(void);
void spi2_init(void);
void i2c2_init(void);
void tim5_init(void);


SPI_HandleTypeDef spi2;
I2C_HandleTypeDef i2c2;
TIM_HandleTypeDef tim5;


extern uint16_t g_pos_x;
extern uint16_t g_pos_y;

uint32_t freq=0;

static void read_touch(void);

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

	while(!(TIM5->SR & TIM_SR_UIF)){}; 		// delay from time base
	TIM5->SR = 0;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
#if (DEBUG_LED)
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
#endif

}

int main()
{
	HAL_Init();
	sysclock_config();
	gpio_init();
	spi2_init();
	i2c2_init();
	tim5_init();

#if (SSD1963_DISPLAY)
	/* Display & touch Init */
	ssd1963_setup();
	XPT2046_Init();
#endif

	/* Timebase start 100ms */
	HAL_TIM_Base_Start_IT(&tim5);

	while(1)
	{
		read_touch();

	}


	return 0;
}

void sysclock_config(void)
{
	RCC_OscInitTypeDef osc;

	osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc.HSEState = RCC_HSE_ON;

	if(HAL_RCC_OscConfig(&osc) != HAL_OK)
	{
		printf("HSE Init failed\n\r");
	}

	RCC_ClkInitTypeDef clock;

	clock.ClockType = RCC_CLOCKTYPE_SYSCLK;
	clock.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	clock.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clock.APB1CLKDivider = RCC_HCLK_DIV1;
	clock.APB2CLKDivider = RCC_HCLK_DIV1;

	if(HAL_RCC_ClockConfig(&clock, FLASH_LATENCY_0)!=HAL_OK)
	{
		printf("clock config failed\n\r");
	}

	uint32_t freq=HAL_RCC_GetSysClockFreq();
	printf("Sysclock frequency : %lu \r\n",freq);
}


void gpio_init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

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

#if (DEBUG_LED)
	GPIO_InitTypeDef LED;

	LED.Pin = GPIO_PIN_13;

	LED.Mode = GPIO_MODE_OUTPUT_PP;
	LED.Pull = GPIO_NOPULL;
	LED.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOC, &LED);
#endif

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


void error_handler(void)
{
	printf("In Error Handler\r\n");
	while(1);
}
