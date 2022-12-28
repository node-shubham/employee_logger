/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <ssd1963.h>
#include <xpt2046.h>
#include "fonts.h"
#include <stdbool.h>
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t char_cnt=0;
char str[50]={0};

uint16_t touchX = 0;
uint16_t touchY = 0;


unsigned char key1[] = {'Q','W','E','R','T','Y','U','I','O','P'};
unsigned char key2[] = {'A','S','D','F','G','H','J','K','L'};
unsigned char key3[] = {'Z','X','C','V','B','N','M'};
unsigned char symbol_key[] = {'!','#','%','_','&','-','+','(',')','/'};
unsigned char symbol_key1 = {'@'};
unsigned char num = {'0'};
unsigned char string[100];

bool UC_FLAG =0;
bool BTN_FLAG =0;



	
	/*if(UC_FLAG)
		{
			char_data=key3[6]- 32;
		}
		else
		{
			char_data=key3[6]+ 32;
		}
	*/
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
	ssd1963_setup();
	XPT2046_Init();
	//front_page();
	keypad2();
	
  /* USER CODE BEGIN 2 */
	

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		touchX = (getX() + 12);	
		touchY = (470 - getY());
		HAL_Delay(100);
		
		int temp,x=0,y=150,k=0,l=0,p=0;
		Set_Font(&Font16x24);
		
		
		if(touchX >= 50 && touchX <= 145 && touchY >= 340 && touchY <= 400)
		{
			if(BTN_FLAG == 0)
			{
				UC_FLAG = !UC_FLAG;
				keypad2();
			}	
		}
		if(touchX >= 50 && touchX <= 145 && touchY >= 410 && touchY <= 470)
		{
			BTN_FLAG = !BTN_FLAG;
			keypad2();
		}
		int a =0;

		for(int i=0; i<10; i++)
		{
			
			temp = string[i];
			string[i] = string[a];
			string[a] = temp;
	  }		
		
		/*****************************************************************************/
		#if 1
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<=9-(i*2-k); j++)
			{
				if(i == 0)
				{
					if(touchX >= 50+x && touchX <= 110+x && touchY >= 50+y && touchY <= 110+y)
					{
						HAL_Delay(200);						
						str[char_cnt]= key1[j];
						if(UC_FLAG)
						{				      
							print_char(200+(char_cnt*20),110,str[char_cnt],BLUE);							
						}
						else
						{
							print_char(200+(char_cnt*20),110,str[char_cnt]+32,BLUE);
						}
						char_cnt++;

					
					}
				}
				if(i == 1)
				{
					
				}
				
				x+=70;

			}
			k=1;
			
		}
		#endif
		/*****************************************************************************/
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//int x1=50,x2=110,y1=50,y2=110;


void keypad(void)
{	
//	Set_Font(&Font16x26);
//	fill_screen(WHITE);
//	int x=0,y=150;
//	for(int i=0; i<10; i++)                           //First line
//	{
//		draw_rect(x1+x,x2+x,y1+y,y2+y,KEY_COLOR);
//		if(UC_FLAG)
//		{
//			if(BTN_FLAG)
//			{
//				print_char(87+x,73+y,num+i,BLACK);
//			}
//			else
//			{
//				print_char(87+x,73+y,key1[i],BLACK);
//			}	
//		}
//		else
//		{
//			if(BTN_FLAG)
//			{
//				print_char(87+x,73+y,num+i,BLACK);
//			}
//			else
//			{
//				print_char(87+x,73+y,key1[i]+32,BLACK);
//			}
//		}
//		
//		
//		if(x<630)                                       // Second line
//		{
//			draw_rect(85+x,145+x,120+y,180+y,KEY_COLOR);
//			if(UC_FLAG)
//			{
//				if(BTN_FLAG)
//				{
//					print_char(122+x,143+x,symbol_key[i],BLACK);
//				}
//				else
//				{
//					print_char(122+x,143+y,key2[i],BLACK);
//				}	
//			}
//			else
//			{	
//				print_char(122+x,143+y,key2[i]+32,BLACK);
//			}	
//		}
//		
//		if(x<490)
//		{
//			draw_rect(155+x,215+x,190+y,250+y,KEY_COLOR);
//			if(UC_FLAG)
//			{
//				print_char(192+x,213+y,key3[i],BLACK);
//			}
//			else
//			{	
//				print_char(192+x,213+y,key3[i]+32,BLACK);
//			}		
//		}
//		x+=70;
//	}
//	
//	
//	
//	
//	draw_rect(50,145,190+y,250+y,KEY_COLOR);
//	draw_rect(645,740,190+y,250+y,KEY_COLOR);
//	
//	//////////////FORTH LINE////////////////
//	
//	draw_rect(50,145,260+y,320+y,KEY_COLOR);   //side
//	draw_rect(645,740,260+y,320+y,KEY_COLOR);
//	
//	draw_rect(155,215,260+y,320+y,KEY_COLOR);   //middle
//	draw_rect(575,635,260+y,320+y,KEY_COLOR);
//	
//	draw_rect(225,565,260+y,320+y,KEY_COLOR);
//	//draw_vl(395,410,60,BLUE);
//	print_string(370,430,"SPACE",BLACK);
}



void keypad2(void)
{
	Set_Font(&Font16x26);
	fill_screen(WHITE);
	int x=0,y=150,k=0;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<=9-(i*2-k); j++)
		{
			if(i == 0)
			{
				draw_rect(50+x,110+x,50+y,110+y,KEY_COLOR);
				if(UC_FLAG)
				{
					if(BTN_FLAG)
					{
						print_char(87+x,73+y,num+j,BLACK);
						
					}
					else
					{
						print_char(87+x,73+y,key1[j],BLACK);
						
					}	
				}
				else
				{
					if(BTN_FLAG)
					{
						print_char(87+x,73+y,num+j,BLACK);
					}
					else
					{
						print_char(87+x,73+y,key1[j]+32,BLACK);
					}
				}
			}
			if(i == 1)
			{
				draw_rect(85+x,145+x,120+y,180+y,KEY_COLOR);
				if(UC_FLAG)
				{
					if(BTN_FLAG)
					{
						print_char(122+x,143+y,symbol_key[j],BLACK);
					}
					else
					{
						print_char(122+x,143+y,key2[j],BLACK);
					}
				}
				else
				{
					if(BTN_FLAG)
					{
						print_char(122+x,143+y,symbol_key[j],BLACK);
					}
					else
					{
						print_char(122+x,143+y,key2[j]+32,BLACK);
					}	
				}
			}
			if(i == 2)
			{
				draw_rect(155+x,215+x,190+y,250+y,KEY_COLOR);
				if(UC_FLAG)
				{
					if(BTN_FLAG)
					{
						print_char(192+x,213+y,symbol_key1-j,BLACK);
					}
					else
					{
						print_char(192+x,213+y,key3[j],BLACK);
					}		
				}
				else
				{
					if(BTN_FLAG)
					{
						print_char(192+x,213+y,symbol_key1-j,BLACK);
					}
					else
					{
						print_char(192+x,213+y,key3[j]+32,BLACK);
					}						
				}	
			}
			x+=70;
		}
		k=1;
		x=0;
	}
	draw_rect(50,145,190+y,250+y,KEY_COLOR); // Caps
	print_string(80,210+y,"Caps",BLACK);
	
	draw_rect(645,740,190+y,250+y,KEY_COLOR); // BackSpace
	
	draw_rect(50,145,260+y,320+y,KEY_COLOR);   //Num
	print_string(90,280+y,"Num",BLACK);
	
	draw_rect(645,740,260+y,320+y,KEY_COLOR);  // search
	
	draw_rect(155,215,260+y,320+y,KEY_COLOR);   // coma (,)
	print_char(190,270+y,',',BLACK);
	
	draw_rect(575,635,260+y,320+y,KEY_COLOR); //Dot (.) 
	print_char(612,275+y,'.',BLACK);
	
	draw_rect(225,565,260+y,320+y,KEY_COLOR); // space
	print_string(375,275+y,"Space",BLACK);
	
	draw_rect(190,600,100,140,BLUE);
	draw_rect(190,600,150,190,BLUE);

}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
