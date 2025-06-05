/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
#define D_Pin GPIO_PIN_8
#define D_GPIO_Port GPIOE
#define DP_Pin GPIO_PIN_9
#define DP_GPIO_Port GPIOE
#define C_Pin GPIO_PIN_10
#define C_GPIO_Port GPIOE
#define E_Pin GPIO_PIN_11
#define E_GPIO_Port GPIOE
#define F_Pin GPIO_PIN_12
#define F_GPIO_Port GPIOE
#define B_Pin GPIO_PIN_13
#define B_GPIO_Port GPIOE
#define A_Pin GPIO_PIN_14
#define A_GPIO_Port GPIOE
#define G_Pin GPIO_PIN_15
#define G_GPIO_Port GPIOE
#define LED_Pin GPIO_PIN_11
#define LED_GPIO_Port GPIOB
#define S1_Pin GPIO_PIN_12
#define S1_GPIO_Port GPIOB
#define S2_Pin GPIO_PIN_13
#define S2_GPIO_Port GPIOB
#define S3_Pin GPIO_PIN_14
#define S3_GPIO_Port GPIOB
#define S4_Pin GPIO_PIN_15
#define S4_GPIO_Port GPIOB
#define PRT_Pin GPIO_PIN_10
#define PRT_GPIO_Port GPIOD
#define SEL_Pin GPIO_PIN_11
#define SEL_GPIO_Port GPIOD
#define HOLD_Pin GPIO_PIN_12
#define HOLD_GPIO_Port GPIOD
#define SELD13_Pin GPIO_PIN_13
#define SELD13_GPIO_Port GPIOD
#define DSP_Pin GPIO_PIN_14
#define DSP_GPIO_Port GPIOD
#define BUZ_Pin GPIO_PIN_15
#define BUZ_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
