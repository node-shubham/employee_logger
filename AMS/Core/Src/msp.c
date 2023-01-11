/*
 * msp.c
 *
 *  Created on: Jan 4, 2023
 *      Author: shubham
 */

#include "main.h"
#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef spi2;
extern TIM_HandleTypeDef tim5;

void HAL_MspInit(void)
{

	__HAL_RCC_SYSCFG_CLK_ENABLE();		// exti line controller clock
	__HAL_RCC_PWR_CLK_ENABLE();			// pwr  controller clcok

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	// enable the peripheral clock
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART1_CLK_ENABLE();

	GPIO_InitTypeDef gpio_uart;

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


void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	GPIO_InitTypeDef spi_pins;

	if(hspi->Instance == SPI1)
	{
		__HAL_RCC_SPI1_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();

		spi_pins.Pin = (GPIO_PIN_5 | GPIO_PIN_6 |GPIO_PIN_7);
		spi_pins.Mode = GPIO_MODE_AF_PP;
		spi_pins.Pull = GPIO_NOPULL;
		spi_pins.Alternate = GPIO_AF5_SPI1;

		HAL_GPIO_Init(GPIOA, &spi_pins);
	}

	if(hspi->Instance == SPI2)
	{
		__HAL_RCC_SPI2_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();

		spi_pins.Pin = (GPIO_PIN_12 | GPIO_PIN_13 |GPIO_PIN_14 |GPIO_PIN_15) ; // for SPI NSS select - NSS_HARD options
		spi_pins.Mode = GPIO_MODE_AF_PP;
		spi_pins.Pull = GPIO_NOPULL;
		spi_pins.Alternate = GPIO_AF5_SPI2;

		HAL_GPIO_Init(GPIOB, &spi_pins);
	}

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM5)
	{
		__HAL_RCC_TIM5_CLK_ENABLE();
		HAL_NVIC_SetPriority(TIM5_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(TIM5_IRQn);

	}

}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
	__HAL_RCC_I2C2_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef i2c2_pins;

	i2c2_pins.Pin = (GPIO_PIN_10 | GPIO_PIN_11);
	i2c2_pins.Mode = GPIO_MODE_AF_OD;
	i2c2_pins.Pull = GPIO_PULLUP;
	i2c2_pins.Alternate = GPIO_AF4_I2C2;

	HAL_GPIO_Init(GPIOB, &i2c2_pins);
}
