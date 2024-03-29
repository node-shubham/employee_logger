/*
 * msp.c
 *
 *  Created on: Jan 4, 2023
 *      Author: shubham
 */

#include "main.h"
#include "stm32f4xx_hal.h"


void HAL_MspInit(void)
{

	__HAL_RCC_SYSCFG_CLK_ENABLE();		// exti line controller clock
	__HAL_RCC_PWR_CLK_ENABLE();			// pwr  controller clock

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart;

	if(huart->Instance == USART1)		/* currently using for debugging */
	{
		// enable the peripheral clock
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_USART1_CLK_ENABLE();

		gpio_uart.Pin = GPIO_PIN_9 | GPIO_PIN_10;
		gpio_uart.Mode 	=GPIO_MODE_AF_PP;
		gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
		gpio_uart.Pull = GPIO_PULLUP;
		gpio_uart.Alternate = GPIO_AF7_USART1;

		HAL_GPIO_Init(GPIOA, &gpio_uart);

		// enable NVIC irq line
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		HAL_NVIC_SetPriority(USART1_IRQn, 15, 0);
	}
}


void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	GPIO_InitTypeDef spi_pins;

	if(hspi->Instance == SPI1)		/* using in RFID */
	{
		__HAL_RCC_SPI1_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();

		spi_pins.Pin = (GPIO_PIN_4 |GPIO_PIN_5);
		spi_pins.Mode = GPIO_MODE_AF_PP;
		spi_pins.Pull = GPIO_NOPULL;
		spi_pins.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		spi_pins.Alternate = GPIO_AF5_SPI1;

		HAL_GPIO_Init(GPIOB, &spi_pins);

		spi_pins.Pin = GPIO_PIN_5;
		HAL_GPIO_Init(GPIOA, &spi_pins);

	}

	if(hspi->Instance == SPI2)		/* using in touch  */
	{
		__HAL_RCC_SPI2_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();

		spi_pins.Pin = ( GPIO_PIN_13 |GPIO_PIN_14 |GPIO_PIN_15) ; // for SPI NSS select - NSS_HARD options
		spi_pins.Mode = GPIO_MODE_AF_PP;
		spi_pins.Pull = GPIO_NOPULL;
		spi_pins.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		spi_pins.Alternate = GPIO_AF5_SPI2;

		HAL_GPIO_Init(GPIOB, &spi_pins);
	}

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM5)		/* 100ms - TimeBase */
	{
		__HAL_RCC_TIM5_CLK_ENABLE();
		HAL_NVIC_SetPriority(TIM5_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(TIM5_IRQn);

	}

}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{

	GPIO_InitTypeDef i2c_pins ={0};
	if(hi2c->Instance == I2C1)
	{
		__HAL_RCC_I2C1_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		i2c_pins.Pin = (GPIO_PIN_6 | GPIO_PIN_7);
		i2c_pins.Mode = GPIO_MODE_AF_OD;
		i2c_pins.Pull = GPIO_NOPULL;
		i2c_pins.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		i2c_pins.Alternate = GPIO_AF4_I2C1;
		HAL_GPIO_Init(GPIOB, &i2c_pins);
	}
	if(hi2c->Instance == I2C2)
	{
		__HAL_RCC_I2C2_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		i2c_pins.Pin = GPIO_PIN_10 ;
		i2c_pins.Mode = GPIO_MODE_AF_OD;
		i2c_pins.Pull = GPIO_NOPULL;
		i2c_pins.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		i2c_pins.Alternate = GPIO_AF4_I2C2;
		HAL_GPIO_Init(GPIOB, &i2c_pins);

		i2c_pins.Pin = GPIO_PIN_3;
		i2c_pins.Alternate = GPIO_AF9_I2C2;
		HAL_GPIO_Init(GPIOB, &i2c_pins);

	}

}
