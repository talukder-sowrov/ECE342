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
#include <stdio.h>
#include <math.h>
#include "config.h"
#include "fixedpt.h"

float square_wave(float x, int n) {
		float sum = 0;
		int i;
		for (i = 0; i < n; i++) {
			float sin_output = sin((2*i + 1) * x);
			sum += (float)sin_output * (1.0/(2*i+1.0));
		}
		return 4.0/3.14 * sum;
}

fixedpt square_wave_fixed(float x, int n) {
		fixedpt sum = FXD_FROM_FLOAT(0.0);
		int i;
		for (i = 0; i < n; i++) {
			float sin_output = sin((2*i + 1) * x);
			fixedpt sin_fixed = FXD_FROM_FLOAT(sin_output);
			
			fixedpt denominator = FXD_ADD(FXD_MUL(FXD_FROM_FLOAT(2.0), FXD_FROM_INT(i)), FXD_FROM_FLOAT(1.0));
			fixedpt frac = FXD_DIV(FXD_FROM_FLOAT(1.0), denominator);
			
			sum = FXD_ADD(sum, FXD_MUL(frac, sin_fixed));
		}
		fixedpt result = FXD_MUL(FXD_DIV(FXD_FROM_FLOAT(4.0), FIXEDPT_PI), sum);
		return result;
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DAC_Init();
  MX_TIM6_Init();
  MX_USART3_Init();
	HAL_DAC_Init(&hdac);
	
	double LUT[62];
	fixedpt fixed_LUT[62];
	double x;
	x = 0;
	int y = 0;
	uint16_t initial_time, final_time;
	volatile double output;
	HAL_TIM_Base_Start(&htim6);
	initial_time = __HAL_TIM_GET_COUNTER(&htim6);
  while (1)
  {	
		// Part 2.1 Just Sin
//		if (x>6.28) {
//			x = 0;
//		}
//		else {
//			x += 0.01;
//		}
//	  output = sin(x)*1.65 + 1.65;
//		double ratio; 
//		ratio = 4095/3.3;
//		uint16_t fixed_point;
//		fixed_point = (uint16_t)floor(output * ratio);
//		HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
//		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, fixed_point);

		// Part 2.1 Time
//			output = sin(x)*1.65 + 1.65;
//			double ratio; 
//			ratio = 4095/3.3;
//		
//			if (x>6.28) {
//				x = 0;
//				final_time = __HAL_TIM_GET_COUNTER(&htim6);
//				char message[100];
//				sprintf(message, "time=%d\r\n", final_time - initial_time);
//				print_msg(message);
//			}
//			else {
//				x += 0.01;
//			}
//			uint16_t fixed_point;
//			fixed_point = (uint16_t)floor(output * ratio);
//			HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
//			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, fixed_point);
			
			// Part 2.2 Just Sin LUT
//			output = sin(x)*1.65 + 1.65;	
//			double ratio; 
//			ratio = 4095/3.3;
//			HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
//			if (x>6.28) {
//				for(y=0; y<62; y++){
//					uint16_t fixed_point;
//					fixed_point = (uint16_t)floor(LUT[y] * ratio);
//					HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, fixed_point);
//				}
//			}
//			else {
//				LUT[y] = output;
//				y += 1;
//				x += 0.1;
//			}
			
			// Part 2.2 Sin LUT Time
//			output = sin(x)*1.65 + 1.65;	
//			double ratio; 
//			ratio = 4095/3.3;
//			HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
//			if (x>6.28) {
//				initial_time = __HAL_TIM_GET_COUNTER(&htim6);
//				for(y=0; y<62; y++){
//					uint16_t fixed_point;
//					fixed_point = (uint16_t)floor(LUT[y] * ratio);
//					HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, fixed_point);
//				}
//				final_time = __HAL_TIM_GET_COUNTER(&htim6);
//				char message[100];
//				sprintf(message, "time=%d\r\n", final_time - initial_time);
//				print_msg(message);
//			}
//			else {
//				LUT[y] = output;
//				y += 1;
//				x += 0.1;
//			}
	
		// Part 3
//		if (x>6.28) {
//			x = 0;
//		}
//		else {
//			x += 0.01;
//		}
//		output = square_wave(x, 6) + 1.65;
//		double ratio; 
//		ratio = 4095/5;
//		uint16_t fixed_point;
//		fixed_point = (uint16_t)floor(output * ratio);
//		HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
//		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, fixed_point);

	// Part 4.01
//		double test1, test2, solution_float, solution_float_from_fixed;
//		test1 = 2.2;
//		test2 = 1.3;
//		
//		fixedpt test3, test4, solution_fixed;
//		test3 = FXD_FROM_FLOAT(test1);
//		test4 = FXD_FROM_FLOAT(test2);
//		
//		solution_fixed = FXD_MUL(test3, test4);
//		solution_float = test1 * test2;
//		
//		solution_float_from_fixed = FXD_TO_FLOAT(solution_fixed);
//		
//		char message[100];
//		sprintf(message, "fixed: %f float: %f\r\n", solution_float_from_fixed, solution_float);
//	  print_msg(message);
//		return 0;

		// Part 4.1 Fixed Point Sin\ Wave
//			output = sin(x) + 1.65;	
//			if (x>6.28) {
//				for(y=0; y<62; y++){
//					uint16_t dac_ouput = FXD_MUL(fixed_LUT[y], FXD_FROM_FLOAT(819.0)) >> 16;
//					HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
//					HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_ouput);
//				}
//			}
//			else {
//				fixedpt fixed_output = FXD_FROM_FLOAT(output);
//				fixed_LUT[y] = fixed_output;
//				y += 1;
//				x += 0.1;
//			}
			
			// Fixed Sin LUT Time
//			output = sin(x) + 1.65;	
//			if (x>6.28) {
//				for(y=0; y<62; y++){
//					uint16_t dac_ouput = FXD_MUL(fixed_LUT[y], FXD_FROM_FLOAT(819.0)) >> 16;
//					HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
//					HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_ouput);
//				}
//				final_time = __HAL_TIM_GET_COUNTER(&htim6);
//				char message[100];
//				sprintf(message, "time=%d\r\n", final_time - initial_time);
//				print_msg(message);
//				return 0;
//			}
//			else {
//				fixedpt fixed_output = FXD_FROM_FLOAT(output);
//				fixed_LUT[y] = fixed_output;
//				y += 1;
//				x += 0.1;
//			}

	//  Part 4.1
			if (x>6.28) {
				x = 0;
			}
			else {
				x += 0.01;
			}
			fixedpt fixed_output;
			fixed_output = FXD_ADD(square_wave_fixed(x, 6), FXD_FROM_FLOAT(1.65));
			uint16_t dac_ouput = FXD_MUL(fixed_output, FXD_FROM_FLOAT(819.0)) >> 16;
			HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_ouput);

	}
}