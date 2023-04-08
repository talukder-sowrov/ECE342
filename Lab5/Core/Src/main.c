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
#include "main.h"

#include "config.h"
#include "ov7670.h"

#include <stdio.h>
#include <string.h>

//uint16_t buffer1[IMG_ROWS * IMG_COLS];
//uint16_t buffer2[IMG_ROWS * IMG_COLS];
//uint16_t* current_buffer = buffer1;
uint16_t snapshot_buff[IMG_ROWS * IMG_COLS];
uint8_t screen_buff[IMG_ROWS * IMG_COLS];
volatile uint8_t dma_flag = 0;


void print_buf(void);

void print_img(void);

int main(void)
{
  /* Reset of all peripherals */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DCMI_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_I2C2_Init();
  MX_TIM1_Init();
  MX_TIM6_Init();

  char msg[100];

  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  ov7670_init();
	HAL_Delay(100); 
	ov7670_capture(snapshot_buff);
  while (1)
  {	
			while(dma_flag != 1){}
			HAL_DCMI_Stop(&hdcmi);
			print_msg("Snap!\r\n");
			print_img();
			ov7670_capture(snapshot_buff);
			dma_flag = 0;
		
//		if(dma_flag == 1){
//			print_msg("Snap!\r\n");
//			print_img();
//			dma_flag = 0;
//		}
    // Your code here
//    if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin)) {
//      HAL_Delay(100);  // debounce
//      print_msg("Snap!\r\n");
//			
//			ov7670_snapshot(snapshot_buff);
//			HAL_Delay(1000); 
//			print_img();
//    }
  }
}

void print_img() {
	int i;
	int j;
	print_msg("PREAMBLE!\r\n");
	uint8_t* ptr = (uint8_t*)snapshot_buff;
	for(i=0; i<(IMG_ROWS*IMG_COLS); i++) {
		uart_send_bin(ptr+(2*i+1), 1);
	}
}

void print_buf() {
  // Send image data through serial port.
	int i;
	for (i=0; i <(IMG_ROWS*IMG_COLS); i++){
		screen_buff[i] = 0x00;
	}
	print_msg("\r\nPREAMBLE!\r\n");
	HAL_Delay(1000);
	uart_send_bin(screen_buff, 25056);
  // Your code here
}
