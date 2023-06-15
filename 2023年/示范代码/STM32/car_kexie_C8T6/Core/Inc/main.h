/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


#include "stdio.h"
#include "kalman.h"
#include "pid.h"
#include "Moto.h"
#include "oled.h"
#include "scan_red.h"
#include "follow.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

 #define Kal_Scale_factor 10 //卡尔曼滤波缩放系数
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M1A_Pin GPIO_PIN_0
#define M1A_GPIO_Port GPIOA
#define M1B_Pin GPIO_PIN_1
#define M1B_GPIO_Port GPIOA
#define M2A_Pin GPIO_PIN_2
#define M2A_GPIO_Port GPIOA
#define M2B_Pin GPIO_PIN_3
#define M2B_GPIO_Port GPIOA
#define RR_Pin GPIO_PIN_7
#define RR_GPIO_Port GPIOA
#define MM_Pin GPIO_PIN_0
#define MM_GPIO_Port GPIOB
#define LL_Pin GPIO_PIN_1
#define LL_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
