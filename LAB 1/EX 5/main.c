/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  void display7SEG(int num){
  	//tao mang de luu cac gia tri cua cac so tu 0 den 9
  	char led7seg[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
  	//cho bien i chay tu 0 den 6 tuong duong voi 7 doan tren led7doan
  	//muc dich cua vong lap nay la de bat hoac tat cac led tren led 7 doan
  	for (int i=0; i < 7; i++){
  		/*dich bit sang phai de tien hanh and voi bit 1 de xac dinh trang thai led
  		 0 la bat 1 la tat
  		 */
  		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 <<i, (led7seg[num]>>i) & 1);

  	}
  }
  int counter = 9;
  while (1)
  {
    switch (counter){
    //CHIA DEN LED THAY 2 DAY, DAY 1 VA DAY 2, MOI DAY CO 3 DEN
    	case 9: //DEN DO DAY 1 SANG DAY 2 DEN XANH SANG
    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, RESET); // DEN DO SANG
    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, SET);
    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, SET);

    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, SET);
    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET); //DEN XANH SANG

    		display7SEG(4);
    		HAL_Delay(1000);
    		counter--;
    		break;
    	case 8:
    		display7SEG(3);
    		HAL_Delay(1000);
    		counter--;
    		break;
    	case 7:
    		display7SEG(2);
    		HAL_Delay(1000);
    		counter--;
    		break;
    	case 6: //1 TURN ON LED RED, 2 TURN ON LED YELLOW
    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
    		display7SEG(1);
    		HAL_Delay(1000);
    		counter--;
    		break;
    	case 5:
    		display7SEG(0);
    		HAL_Delay(1000);
    		counter--;
    		break;
    	case 4: //2 TURN ON RED, 1 TURN ON GREEN
    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, SET);
    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, RESET);

    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, RESET);
    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);

    		display7SEG(2);
    		HAL_Delay(1000);
    		counter--;
    		break;
    	case 3:
    		display7SEG(1);
    		HAL_Delay(1000);
    		counter--;
    		break;
    	case 2:
    		display7SEG(0);
    		HAL_Delay(1000);
    		counter--;
    		break;
    	case 1:
    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, RESET);
    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, SET);
    		display7SEG(1);
    		HAL_Delay(1000);
    		counter--;
    		break;
    	case 0:
    		display7SEG(0);
    		HAL_Delay(1000);
    		counter = 9;
    		break;

    }
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA2 PA3 PA4
                           PA5 PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB3
                           PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
