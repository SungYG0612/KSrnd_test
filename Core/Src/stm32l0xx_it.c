/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l0xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
unsigned int uiPin_value = 0;
unsigned int uiSel = 0;
unsigned int uiPrev_Pin_value = 0;
unsigned int uiKey_Time = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */
extern int bShort_Button_Flag;
extern int bLong_Button_Flag;
extern int bSet_Flag;
extern int bBlink_Flag;

extern const unsigned int FND_Port_Table[4];
extern unsigned int uiButton_Data;
extern unsigned int uiDisplay_Data[4];
extern unsigned int uiBlink_Time;
extern unsigned int uiBlink_Sel;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable Interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
	uiPin_value = GPIOD->IDR;
	uiPin_value = (uiPin_value & 0x7c00) ^ 0x7c00;
	if(uiPin_value == uiPrev_Pin_value && uiPin_value)
	{
		uiKey_Time ++;
		if(uiKey_Time==1000)
		{
			uiButton_Data = uiPrev_Pin_value;
			bLong_Button_Flag = 1;
		}
	}
	else if(uiPrev_Pin_value && uiPin_value ==0)
	{
		if(uiKey_Time < 1000)
		{
			uiButton_Data = uiPrev_Pin_value;
			bShort_Button_Flag = 1;
		}
		uiKey_Time = 0;
	}
	uiPrev_Pin_value = uiPin_value;
	//////////////////////////////////////////////////////
	/*FND Blink*/
	if(bSet_Flag)
	{
		if(uiBlink_Time >= 500)
		{
			bBlink_Flag ^= 1;
			uiBlink_Time = 0;
		}
		uiBlink_Time++;
	}
	else
	{
		bBlink_Flag = 0;
	}
	//////////////////////////////////////////////////////
	/*FND 출력*/
	GPIOB->BSRR = FND_Port_Table[uiSel];
	if(bBlink_Flag && uiSel == uiBlink_Sel)
	{
		GPIOE->BSRR = 0xff000000;
	}
	else
	{
		GPIOE->BSRR = uiDisplay_Data[uiSel];
	}
	uiSel ++;
	uiSel %= 4;
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l0xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
