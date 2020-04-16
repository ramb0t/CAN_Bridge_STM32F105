/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "can.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"

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

CAN_TxHeaderTypeDef   TxHeader1;
CAN_TxHeaderTypeDef   TxHeader2;
CAN_RxHeaderTypeDef   RxHeader1;
CAN_RxHeaderTypeDef   RxHeader2;
uint8_t               TxData1[8];
uint8_t               TxData2[8];
uint8_t               RxData1[8];
uint8_t               RxData2[8];
uint32_t              TxMailbox1;
uint32_t              TxMailbox2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}
void debugPrint();
void debugPrintln();

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
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  //HAL_CAN_Start(&hcan1);
  uint8_t count = 0;

  /* Output a message on Hyperterminal using printf function */
  printf("\n\r UART Printf Example: retarget the C library printf function to the UART\n\r");
  printf("** Test finished successfully. ** \n\r");

  /* Configure Transmission process */
  TxHeader1.StdId = 0x321;
  TxHeader1.ExtId = 0x01;
  TxHeader1.RTR = CAN_RTR_DATA;
  TxHeader1.IDE = CAN_ID_STD;
  TxHeader1.DLC = 2;
  TxHeader1.TransmitGlobalTime = DISABLE;

  /* Configure Transmission process */
  TxHeader2.StdId = 0x322;
  TxHeader2.ExtId = 0x01;
  TxHeader2.RTR = CAN_RTR_DATA;
  TxHeader2.IDE = CAN_ID_STD;
  TxHeader2.DLC = 2;
  TxHeader2.TransmitGlobalTime = DISABLE;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_GPIO_TogglePin(LEDR_GPIO_Port,LEDR_Pin); //Toggle LED

	  HAL_Delay(250); //Delay 1 Seconds

	  HAL_GPIO_TogglePin(LEDG_GPIO_Port,LEDG_Pin); //Toggle LED

	  HAL_Delay(250); //Delay 1 Seconds

	  HAL_GPIO_TogglePin(LEDB_GPIO_Port,LEDB_Pin); //Toggle LED

	  HAL_Delay(250); //Delay 1 Seconds

	  HAL_GPIO_TogglePin(LEDO_GPIO_Port,LEDO_Pin); //Toggle LED

	  HAL_Delay(250); //Delay 1 Seconds

//	  HAL_GPIO_TogglePin(LEDCAN1_GPIO_Port,LEDCAN1_Pin); //Toggle LED
//
//	  HAL_Delay(250); //Delay 1 Seconds
//
//	  HAL_GPIO_TogglePin(LEDCAN2_GPIO_Port,LEDCAN2_Pin); //Toggle LED
//
//	  HAL_Delay(250); //Delay 1 Seconds

	  TxData1[0] = 0xBE;
	  TxData1[1] = count++;

	  TxData2[0] = 0xEF;
	  TxData2[1] = count++;

	  HAL_GPIO_TogglePin(LEDCAN1_GPIO_Port,LEDCAN1_Pin);
      /* Start the Transmission process */
      if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader1, TxData1, &TxMailbox1) != HAL_OK)
      {
        /* Transmission request Error */
        Error_Handler();
      }
      printf("\n\r TxData1: %x - %x \n\r", TxData1[0], TxData1[1]);

      HAL_GPIO_TogglePin(LEDCAN1_GPIO_Port,LEDCAN1_Pin);

      HAL_Delay(10);

	  HAL_GPIO_TogglePin(LEDCAN2_GPIO_Port,LEDCAN2_Pin);
      /* Start the Transmission process */
      if (HAL_CAN_AddTxMessage(&hcan2, &TxHeader2, TxData2, &TxMailbox2) != HAL_OK)
      {
        /* Transmission request Error */
        Error_Handler();
      }
 	  printf("\n\r TxData2: %x - %x \n\r", TxData2[0], TxData2[1]);

      HAL_GPIO_TogglePin(LEDCAN2_GPIO_Port,LEDCAN2_Pin);

      HAL_Delay(10);

      /* Receive */
      if (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) != 0){
		 if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader1, RxData1) != HAL_OK)
		 {
		   /* Reception Error */
		   Error_Handler();
		   printf("CAN1 RX: Error!");

		 }
		 printf("CAN1 RX: %lx:%x%x \n\r", RxHeader1.StdId, RxData1[0], RxData1[1]);

      }

      if (HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO1) != 0){
		 if (HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO1, &RxHeader2, RxData2) != HAL_OK)
		 {
		   /* Reception Error */
		   Error_Handler();
		   printf("CAN2 RX: Error!");
		 }
		 printf("CAN2 RX: %lx:%x%x \n\r", RxHeader2.StdId, RxData2[0], RxData2[1]);

      }





      //debugPrint(&huart1, "oi, mate!");        // print
      //debugPrint(&huart1, "\r\n");            // manual new line
      //debugPrintln(&huart1, "how are you?");  // print full line

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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  /** Configure the Systick interrupt time 
  */
  __HAL_RCC_PLLI2S_ENABLE();
}

/* USER CODE BEGIN 4 */

void debugPrint(UART_HandleTypeDef *huart, char _out[])
{
	HAL_UART_Transmit(huart, (uint8_t *) _out, strlen(_out), 10);
}


void debugPrintln(UART_HandleTypeDef *huart, char _out[])
{
	HAL_UART_Transmit(huart, (uint8_t *) _out, strlen(_out), 10);
	char newline[2] = "\r\n";
	HAL_UART_Transmit(huart, (uint8_t *) newline, 2, 10);
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
