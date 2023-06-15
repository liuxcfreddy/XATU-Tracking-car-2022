/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "pfunc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

TypeADC_temp ADC;                  // 传感器顺序为 R M L
TypeADC_temp ADCData;              // 初始化ADC采样值
TypeADC_temp ADCRelay;             // 初始化ADC采样准备值
Kalman KalRT, KalRR, KalMM, KalLL; // 卡尔曼滤波结构体
POWER_PP_Typedef POWER_PP;         // 初始化电机传参结构体

float L2R_Difference;  // 偏移距离
uint8_t Mode_mark = 0; // 模式切换标志，依靠外部中断切换
float PID_POWER;       // 电机驱动中间变量
float Adjust;          // 偏移量调节中间量
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
/* USER CODE BEGIN PFP */
void follow_task_init(void);
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init();
  PWM_OUT_Init();
  GO_Power_Set(0, 0);
  OLED_ShowString(1, 1, "System_Init");
  follow_task_init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  OLED_Clear();
  while (1)
  {
    POWER_PP.POWERA = POWER_PP.POWERB = 40;//基准速度，可自行调节选择
    if (Mode_mark == 0)
    {
      main_follw_task();
    }
    if (Mode_mark == 1)
    {
      GO_Power_Set(0, 0);//停车以方便调试等动作
      OLED_ShowString(1, 1, "Debug ");
      OLED_ShowString(2, 1, "      ");
      // OLED_ShowNum(3,1,pid_params.Kp*10,3);OLED_ShowNum(3,4,pid_params.Ki*10,3);OLED_ShowNum(3,7,pid_params.Kd*10,3);
      OLED_ShowString(4, 1, "**");
      OLED_ShowString(4, 4, "  ");
      OLED_ShowString(4, 7, "  ");
      if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
      {
        //  此处可以写你想要的动作函数
        HAL_Delay(40);
      }
      if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
      {
        //  此处可以写你想要的动作函数
        HAL_Delay(40);
      }
    }
    if (Mode_mark == 2)
    {
      OLED_ShowString(1, 1, "Debug ");
      OLED_ShowString(2, 1, "      ");
      // OLED_ShowNum(3,1,pid_params.Kp*10,3);OLED_ShowNum(3,4,pid_params.Ki*10,3);OLED_ShowNum(3,7,pid_params.Kd*10,3);
      OLED_ShowString(4, 1, "  ");
      OLED_ShowString(4, 4, "**");
      OLED_ShowString(4, 7, "  ");
      if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
      {
        //  此处可以写你想要的动作函数
        HAL_Delay(40);
      }
      if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
      {
        //  此处可以写你想要的动作函数
        HAL_Delay(40);
      }
    }
    if (Mode_mark == 3)
    {
      OLED_ShowString(1, 1, "Debug ");
      OLED_ShowString(2, 1, "      ");
      // OLED_ShowNum(3,1,pid_params.Kp*10,3);OLED_ShowNum(3,4,pid_params.Ki*10,3);OLED_ShowNum(3,7,pid_params.Kd*10,3);
      OLED_ShowString(4, 1, "  ");
      OLED_ShowString(4, 4, "  ");
      OLED_ShowString(4, 7, "**");
      if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
      {
        //  此处可以写你想要的动作函数
        HAL_Delay(40);
      }
      if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
      {
        //  此处可以写你想要的动作函数
        HAL_Delay(40);
      }
    }
  }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void follow_task_init(void)
{
  Kalman_Init(&KalRT, 0.5f, 1.0f);
  Kalman_Init(&KalRR, 0.0051, 0.01);
  Kalman_Init(&KalMM, 0.0051, 0.01);
  Kalman_Init(&KalLL, 0.0051, 0.01);

  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&ADC, 3);

  while (1)
  {
    ADCData.ADC_R = UserKalFil(&KalRR, ADC.ADC_R, Kal_Scale_factor);
    ADCData.ADC_M = UserKalFil(&KalMM, ADC.ADC_M, Kal_Scale_factor);
    ADCData.ADC_L = UserKalFil(&KalLL, ADC.ADC_L, Kal_Scale_factor);
    HAL_Delay(10);
    ADCRelay.ADC_R = UserKalFil(&KalRR, ADC.ADC_R, Kal_Scale_factor);
    ADCRelay.ADC_M = UserKalFil(&KalMM, ADC.ADC_M, Kal_Scale_factor);
    ADCRelay.ADC_L = UserKalFil(&KalLL, ADC.ADC_L, Kal_Scale_factor);
    OLED_ShowNum(2, 1, ADC.ADC_R, 4);
    if (
        (((int)ADCData.ADC_R) == ((int)ADCRelay.ADC_R)) && (((int)ADCData.ADC_M) == ((int)ADCRelay.ADC_M)) && (((int)ADCData.ADC_L) == ((int)ADCRelay.ADC_L)))
    {
      // printf("初始化已完成\n");
      OLED_ShowString(1, 1, "SYS_Init_END");
      break;
    }
  }
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

#ifdef USE_FULL_ASSERT
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
