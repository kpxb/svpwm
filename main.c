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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "math.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define pi 3.14159
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
double ti;
uint8_t flag;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
  MX_TIM3_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1|TIM_CHANNEL_2|TIM_CHANNEL_3|TIM_CHANNEL_4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	float TX, TY, cha, chb, chc;
  while (1)
  {
		switch(flag)
		{
			case 1:
				TX = sin(pi/3 - ti*pi/180);
				TY = sin(ti*pi/180);
				cha = 1 - (1 - TX - TY)/2;
				chb = 1 - (1 + TX - TY)/2;
				chc = 1 - (1 + TX + TY)/2;
				break;
			case 2:
				TX = sin(ti*pi/180 - pi/3);
				TY = sin(pi*2/3 - ti*pi/180);
				cha = 1 - (1 - TX - TY)/2;
				chb = 1 - (1 + TX - TY)/2;
				chc = 1 - (1 + TX + TY)/2;
				break;
			case 3:
				TX = sin(ti*pi/180);
				TY = sin(ti*pi/180 - pi*2/3);
				cha = 1 - (1 + TX - TY)/2;
				chb = 1 - (1 - TX - TY)/2;
				chc = 1 - (1 + TX + TY)/2;
				break;
			case 4:
				TX = -sin(ti*pi/180);
				TY = sin(pi*4/3 - ti*pi/180);
				cha = 1 - (1 + TX + TY)/2;
				chb = 1 - (1 + TX - TY)/2;
				chc = 1 - (1 - TX - TY)/2;
				break;
			case 5:
				TX = sin(pi*5/3 - ti*pi/180);
				TY = sin(ti*pi/180 - pi*4/3);
				cha = 1 - (1 + TX - TY)/2;
				chb = 1 - (1 + TX + TY)/2;
				chc = 1 - (1 - TX - TY)/2;
				break;
			case 6:
				TX = sin(ti*pi/180 - pi*5/3);
				TY = -sin(ti*pi/180);
				cha = 1 - (1 - TX - TY)/2;
				chb = 1 - (1 + TX + TY)/2;
				chc = 1 - (1 + TX - TY)/2;
				break;
			default:
				TX = 0;
				TY = 0;
				cha = 0;
				chb = 0;
				chc = 0;
		}
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, cha*10000);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, chb*10000);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, chc*10000);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, chc*10000);
		printf("a:%f b:%f c:%f\r\n", cha*10000, chb*10000, chc*10000);
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  if(htim->Instance == TIM6)
	{
		ti++;
		if(ti > 360)
		{
			ti = 0;
		}
		if(ti >= 0 && ti<60)
		{
			flag = 1;
		}
		else if(ti >= 60 && ti<120)
		{
			flag = 2;
		}
		else if(ti >= 120 && ti<180)
		{
			flag = 3;
		}
		else if(ti >= 180 && ti<240)
		{
			flag = 4;
		}
		else if(ti >= 240 && ti<300)
		{
			flag = 5;
		}
		else
		{
			flag = 6;	
		}
	}
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
   */
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
