/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f4xx_it.h"
#include <stdio.h>
#include "main.h"
#include "config.h"

/* External variables --------------------------------------------------------*/
extern int8_t current_col;

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
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
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
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

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  if (__HAL_GPIO_EXTI_GET_FLAG(COL0_Pin)) {
		if(HAL_GPIO_ReadPin(ROW0_GPIO_Port, ROW0_Pin) == GPIO_PIN_SET){
			char message[100];
			sprintf(message, "3");
			print_msg(message);
		}
		else if(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin) == GPIO_PIN_SET){
			char message[100];
			sprintf(message, "7");
			print_msg(message);
		}
		else if(HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin) == GPIO_PIN_SET){
			char message[100];
			sprintf(message, "B");
			print_msg(message);
		}
		else if(HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin) == GPIO_PIN_SET){
			char message[100];
			sprintf(message, "F");
			print_msg(message);
		}
  }

  HAL_GPIO_EXTI_IRQHandler(COL0_Pin);
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
		if (__HAL_GPIO_EXTI_GET_FLAG(COL1_Pin)) {
			if(HAL_GPIO_ReadPin(ROW0_GPIO_Port, ROW0_Pin) == GPIO_PIN_SET){
				char message[100];
				sprintf(message, "2");
				print_msg(message);
			}
			else if(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin) == GPIO_PIN_SET){
				char message[100];
				sprintf(message, "6");
				print_msg(message);
			}
			else if(HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin) == GPIO_PIN_SET){
				char message[100];
				sprintf(message, "A");
				print_msg(message);
			}
			else if(HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin) == GPIO_PIN_SET){
				char message[100];
				sprintf(message, "E");
				print_msg(message);
			}
		}
		else if (__HAL_GPIO_EXTI_GET_FLAG(COL2_Pin)) {
			if(HAL_GPIO_ReadPin(ROW0_GPIO_Port, ROW0_Pin) == GPIO_PIN_SET){
				char message[100];
				sprintf(message, "1");
				print_msg(message);
			}
			else if(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin) == GPIO_PIN_SET){
				char message[100];
				sprintf(message, "5");
				print_msg(message);
			}
			else if(HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin) == GPIO_PIN_SET){
				char message[100];
				sprintf(message, "9");
				print_msg(message);
			}
			else if(HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin) == GPIO_PIN_SET){
				char message[100];
				sprintf(message, "D");
				print_msg(message);
			}
		}
		if (__HAL_GPIO_EXTI_GET_FLAG(COL3_Pin)) {
			if(HAL_GPIO_ReadPin(ROW0_GPIO_Port, ROW0_Pin) == GPIO_PIN_SET){
				char message[100];
				sprintf(message, "0");
				print_msg(message);
			}
			else if(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin) == GPIO_PIN_SET){
				char message[100];
				sprintf(message, "4");
				print_msg(message);
			}
			else if(HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin) == GPIO_PIN_SET){
				char message[100];
				sprintf(message, "8");
				print_msg(message);
			}
			else if(HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin) == GPIO_PIN_SET){
				char message[100];
				sprintf(message, "C");
				print_msg(message);
			}
		}
	HAL_GPIO_EXTI_IRQHandler(COL1_Pin);
  HAL_GPIO_EXTI_IRQHandler(COL2_Pin);
  HAL_GPIO_EXTI_IRQHandler(COL3_Pin);
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  if (__HAL_GPIO_EXTI_GET_FLAG(USER_Btn_Pin)) {
    HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
  }

  HAL_GPIO_EXTI_IRQHandler(USER_Btn_Pin);
}
