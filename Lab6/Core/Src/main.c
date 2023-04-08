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
#include <string.h>
#include <stdio.h>
#include "config.h"
#include "ov7670.h"


/* USER CODE BEGIN PV */
#define PREAMBLE "\r\n!START!\r\n"
#define DELTA_PREAMBLE "\r\n!DELTA!\r\n"
#define SUFFIX "!END!\r\n"

uint16_t snapshot_buff[IMG_ROWS * IMG_COLS];
uint8_t old_snapshot_buff[IMG_ROWS * IMG_COLS];
uint8_t prev_frame[IMG_ROWS * IMG_COLS];
//uint8_t frame_diff[IMG_ROWS * IMG_COLS];
//uint8_t truncated_snapshot[(IMG_ROWS * IMG_COLS)/2];
uint8_t rle_snapshot[IMG_ROWS * IMG_COLS];
//uint8_t tx_buff[sizeof(PREAMBLE) + 2 * IMG_ROWS * IMG_COLS + sizeof(SUFFIX)];
//size_t tx_buff_len = 0;

volatile uint8_t dma_flag = 0;

// Your function definitions here
void print_buf(void);
void print_img(void);
// i<(IMG_ROWS * IMG_COLS)
void truncate(uint8_t* snapshot, uint8_t* result, int size){
	int i;
	uint8_t first;
	uint8_t second;
	uint8_t combined;
	int j = 0;
	for(i=0; i<size; i=i+2){
		first = snapshot[i];
		second = snapshot[i+1];
		first = first&0xf0;
		second = second&0xf0;
		second = second>>4;
		combined = first|second;
		result[j] = combined;
		j++;
	}
}

unsigned int rle(uint8_t* snapshot, uint8_t* result, int size){
	uint8_t count = 1;
	int i;
	unsigned int j = 0;
	uint8_t prev = snapshot[0]&0xf0;
	for(i=1; i<size; i++){
		uint8_t current = snapshot[i]&0xf0;
		
		if(current == prev){
			count += 1;
		}
		else{
			uint8_t first = prev;
			uint8_t second = count&0x0f;
			result[j] = first|second;
			j++;
			count = 1;
		}
		if(count>15){
			uint8_t first = prev;
			uint8_t second = (count-1)&0x0f;
			result[j] = first|second;
			j++;
			count = 1;
		}
		prev = current;
	}
	uint8_t first = snapshot[size-1]&0xf0;
	uint8_t second = count&0x0f;
	result[j] = first|second;
	
	return j;
}

void frame_difference(uint8_t* prev_snapshot,  uint8_t* current_snapshot, uint8_t* frame_difference, int size){
	int i;
	
	for(i=0; i<size; i++){
		uint8_t cur = current_snapshot[i]&0xf0;
		uint8_t prev = prev_snapshot[i]&0xf0;
		uint8_t difference = cur - prev;
		frame_difference[i] = difference;
	}
	
}

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
  int count = 0;
  ov7670_init();
  HAL_Delay(100);
  ov7670_capture(snapshot_buff);
  // Your startup code here
  
  while (1)
  {	
// 		VIDEO COMPRESSION ALGO
//		
		if(count == 4){
			unsigned int size;
			while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
			HAL_DCMI_Stop(&hdcmi);
			print_msg("\r\n!START!\r\n");
			int i;
			uint8_t* ptr = (uint8_t*)snapshot_buff;
			for(i=0; i<(IMG_ROWS*IMG_COLS); i++) {
				old_snapshot_buff[i] = *(ptr+(2*i+1));
			}
			memcpy(prev_frame, old_snapshot_buff, IMG_ROWS * IMG_COLS);
			size = rle(old_snapshot_buff, rle_snapshot, IMG_ROWS * IMG_COLS);
			ov7670_capture(snapshot_buff);
			while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
			uart_send_bin(rle_snapshot, size+1);
			while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
			print_msg("!END!\r\n");
			count = 0;
		}
		else{	
			unsigned int size;
			while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
			HAL_DCMI_Stop(&hdcmi);
			print_msg("\r\n!DELTA!\r\n");
			int i;
			uint8_t* ptr = (uint8_t*)snapshot_buff;
			for(i=0; i<(IMG_ROWS*IMG_COLS); i++) {
				old_snapshot_buff[i] = *(ptr+(2*i+1));
			}
			frame_difference(prev_frame, old_snapshot_buff, rle_snapshot, IMG_ROWS * IMG_COLS);
			memcpy(prev_frame, old_snapshot_buff, IMG_ROWS * IMG_COLS);
			size = rle(rle_snapshot, rle_snapshot, IMG_ROWS * IMG_COLS);
			ov7670_capture(snapshot_buff);
			while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
			uart_send_bin(rle_snapshot, size+1);
			while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
			print_msg("!END!\r\n");
			count += 1;
		}

//    4 BIT PIXELS RLE		
//		unsigned int size;
//		while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
//		HAL_DCMI_Stop(&hdcmi);
//		print_msg("\r\n!START!\r\n");
//		int i;
//		uint8_t* ptr = (uint8_t*)snapshot_buff;
//		for(i=0; i<(IMG_ROWS*IMG_COLS); i++) {
//			old_snapshot_buff[i] = *(ptr+(2*i+1));
//		}
//		size = rle(old_snapshot_buff, rle_snapshot, IMG_ROWS * IMG_COLS);
//		ov7670_capture(snapshot_buff);
//		while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
//		uart_send_bin(rle_snapshot, size+1);
//		while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
//		print_msg("!END!\r\n");
		
			
//		4 BIT PIXELS
		
//		unsigned int size;
//		while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
//		HAL_DCMI_Stop(&hdcmi);
//		print_msg("\r\n!START!\r\n");
//		int i;
//		uint8_t* ptr = (uint8_t*)snapshot_buff;
//		for(i=0; i<(IMG_ROWS*IMG_COLS); i++) {
//			old_snapshot_buff[i] = *(ptr+(2*i+1));
//		}
//		truncate(old_snapshot_buff, truncated_snapshot, IMG_ROWS * IMG_COLS);
//		ov7670_capture(snapshot_buff);
//		while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
//		uart_send_bin(truncated_snapshot, sizeof(truncated_snapshot));
//		while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
//		print_msg("!END!\r\n");
			
//    PART 3
		
//		while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
//		HAL_DCMI_Stop(&hdcmi);
//		print_msg("\r\n!START!\r\n");
//		int i;
//		uint8_t* ptr = (uint8_t*)snapshot_buff;
//		for(i=0; i<(IMG_ROWS*IMG_COLS); i++) {
//			old_snapshot_buff[i] = *(ptr+(2*i+1));
//		}
//		ov7670_capture(snapshot_buff);
//		while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
//		uart_send_bin(old_snapshot_buff, sizeof(old_snapshot_buff));
//		while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY){}
//		print_msg("!END!\r\n");
//		
	
//    BASELINE
					
//		HAL_DCMI_Stop(&hdcmi);
////		print_msg("Snap!\r\n");
//		print_img();
//		ov7670_capture(snapshot_buff);
//		dma_flag = 0;
    // Your code here

//    if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin)) {
//      HAL_Delay(100);  // debounce

////      print_msg("Snap!\r\n");
//			print_buf();
//    }
  }
}

void print_img() {
	int i;
	int j;
	uint8_t* ptr = (uint8_t*)snapshot_buff;
	print_msg("\r\n!START!\r\n");
	for(i=0; i<(IMG_ROWS*IMG_COLS); i++) {
		uart_send_bin(ptr+(2*i+1), 1);
	}
	print_msg("!END!\r\n");
}

void print_buf() {
  // Send image data through serial port.
  // Your code here
	int i;
	for (i=0; i <(IMG_ROWS*IMG_COLS); i++){
		old_snapshot_buff[i] = 0xff;
	}
//	print_msg("\r\nPREAMBLE!\r\n");
	print_msg("\r\n!START!\r\n");
	for(i=0; i<(IMG_ROWS*IMG_COLS); i++) {
		uart_send_bin(&old_snapshot_buff[i], 1);
	}
	print_msg("!END!\r\n");
//	print_msg("\r\n!START!\r\n");
//	uart_send_bin(old_snapshot_buff, 25056);
//	print_msg("!END!\r\n");
}