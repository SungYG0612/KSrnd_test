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
unsigned int uiADC_Time = 0;
unsigned int uiRx_Sel = 0;
unsigned int uiTx_Sel = 1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc;
extern UART_HandleTypeDef huart5;
/* USER CODE BEGIN EV */
extern int bADC_Flag;
extern int bRx_Flag;
extern int bTx_Flag;
extern unsigned char ucReceive_Buf[];
extern unsigned char ucTransmit_Buf[];
extern unsigned int uiADC_Buf[16];
extern unsigned int uiADC_Buf_Sel;
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
	if(uiADC_Time >= 10)
	{
		HAL_ADC_Start_IT(&hadc);
		uiADC_Time -= 10;
	}
	uiADC_Time ++;
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

/**
  * @brief This function handles ADC, COMP1 and COMP2 interrupts (COMP interrupts through EXTI lines 21 and 22).
  */
void ADC1_COMP_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_COMP_IRQn 0 */
	uiADC_Buf[uiADC_Buf_Sel]=HAL_ADC_GetValue(&hadc);
	uiADC_Buf_Sel ++;
	if(uiADC_Buf_Sel >= 16)
	{
		bADC_Flag = 1;
		uiADC_Buf_Sel = 0;
	}
  /* USER CODE END ADC1_COMP_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc);
  /* USER CODE BEGIN ADC1_COMP_IRQn 1 */

  /* USER CODE END ADC1_COMP_IRQn 1 */
}

/**
  * @brief This function handles USART4 and USART5 interrupt.
  */
void USART4_5_IRQHandler(void)
{
  /* USER CODE BEGIN USART4_5_IRQn 0 */
	if(bRx_Flag == 0)
	{
		if(__HAL_UART_GET_FLAG(&huart5,UART_FLAG_RXNE) == True)
		{
			unsigned char ucReceive_Data = USART5->RDR;
			if(ucReceive_Data == '<')
			{
				ucReceive_Buf[0] = ucReceive_Data;
				uiRx_Sel = 1;
			}
			else if(ucReceive_Data == '>' && ucReceive_Buf[0] == '<')
			{
				ucReceive_Buf[uiRx_Sel] = ucReceive_Data;
				uiRx_Sel = 0;
				bRx_Flag = 1;
			}
			else
			{
				ucReceive_Buf[uiRx_Sel] = ucReceive_Data;
				uiRx_Sel ++;
			}
			return;
		}
	}
	if(bTx_Flag == 0)
	{
		if(__HAL_UART_GET_FLAG(&huart5,UART_FLAG_TC) == True)
		{
			if(uiTx_Sel == 0)
			{
				uiTx_Sel = 1;
				USART5->ICR |= 0x0040;
				bTx_Flag = 1;
			}
			else if(ucTransmit_Buf[uiTx_Sel] == '>')
			{
				USART5->TDR = ucTransmit_Buf[uiTx_Sel];
				uiTx_Sel = 0;
			}
			else
			{
				USART5->TDR = ucTransmit_Buf[uiTx_Sel];
				uiTx_Sel ++;
			}
		}
		return;
	}
  /* USER CODE END USART4_5_IRQn 0 */
  HAL_UART_IRQHandler(&huart5);
  /* USER CODE BEGIN USART4_5_IRQn 1 */

  /* USER CODE END USART4_5_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
