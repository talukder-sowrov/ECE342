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

#include "dfr0151.h"
#include "config.h"

#include <stdio.h>
#include <string.h>

void get_eeprom(uint8_t *hour, uint8_t *min, uint8_t *sec, uint8_t *week_day, uint8_t *day, uint8_t *month, uint8_t *year){
	*sec = eeprom_read(0x0000);
	*min = eeprom_read(0x0001);
	*hour = eeprom_read(0x0002);
	*week_day = eeprom_read(0x0003);
	*day = eeprom_read(0x0004);
	*month = eeprom_read(0x0005);
	*year = eeprom_read(0x0006);
}

void get_eeprom_alarm(uint8_t *hour, uint8_t *min, uint8_t *sec, uint8_t *week_day, uint8_t *day, uint8_t *month, uint8_t *year){
	*sec = eeprom_read(0x0007);
	*min = eeprom_read(0x0008);
	*hour = eeprom_read(0x0009);
	*week_day = eeprom_read(0x000A);
	*day = eeprom_read(0x000B);
	*month = eeprom_read(0x000C);
	*year = eeprom_read(0x000D);
}

int main(void)
{
  /* Reset of all peripherals. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();  
  rtc_init();
	uint8_t ch = rtc_read(0x00);
	ch &= ~(1 << 7);
	rtc_write(0x00, ch);
	const char *weekday[7];
	weekday[0] = "Su";
	weekday[1] = "M";
	weekday[2] = "T";
	weekday[3] = "W";
	weekday[4] = "Th";
	weekday[5] = "F";
	weekday[6] = "Sa";

  // Your start up code here

	// Part 2
//	uint8_t sec, min, hour;
//	uint8_t week_day, day, month, year;
//	get_eeprom(&hour, &min, &sec, &week_day, &day, &month, &year);
//	rtc_set_time(hour, min, sec);
//	rtc_set_date(week_day, day, month, year);

  // part 3
	const uint8_t alarm_sec = 0, alarm_min = 0, alarm_hour = 10, alarm_weekday = 1, alarm_day = 1, alarm_month = 7, alarm_year = 23;
	uint8_t comp_sec, comp_min, comp_hour, comp_weekday, comp_day, comp_month, comp_year;
	uint8_t sec, min, hour;
	uint8_t week_day, day, month, year;
	get_eeprom(&hour, &min, &sec, &week_day, &day, &month, &year);
	rtc_set_time(hour, min, sec);
	rtc_set_date(week_day, day, month, year);

  while (1)
  {
    // Your code here
//    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
//    HAL_Delay(500);
//    print_msg("\b\b\b\btick");

//    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
//    HAL_Delay(500);
//    print_msg("\b\b\b\btock");

		// Part 1
//			uint8_t sec, min, hour;
//			uint8_t week_day, day, month, year;
//			if (__HAL_GPIO_EXTI_GET_FLAG(USER_Btn_Pin)) {
//				hour = 4;
//				min = 11;
//				sec = 30;
//				week_day = 3;
//				day = 12;
//				month = 3;
//				year = 15;
//				rtc_set_time(hour, min, sec);
//				rtc_set_date(week_day, day, month, year);
//				HAL_GPIO_EXTI_IRQHandler(USER_Btn_Pin);
//			}
//			rtc_get_time(&hour, &min, &sec);
//			rtc_get_date(&week_day, &day, &month, &year);
//			char message[100];
//			sprintf(message, "%s %u-%u-%u %u:%u:%u\n",weekday[week_day], month, day, year, hour, min, sec);
//			print_msg(message);

	// Part 2
//			if (__HAL_GPIO_EXTI_GET_FLAG(USER_Btn_Pin)) {
//				rtc_get_time(&hour, &min, &sec);
//				rtc_get_date(&week_day, &day, &month, &year);
//				uint8_t data[7];
//				data[0] = sec;
//				data[1] = min;
//				data[2] = hour;
//				data[3] = week_day;
//				data[4] = day;
//				data[5] = month;
//				data[6] = year;
//				eeprom_write(0x0000, data, 7);
//				HAL_GPIO_EXTI_IRQHandler(USER_Btn_Pin);
//			}
//			rtc_get_time(&hour, &min, &sec);
//			rtc_get_date(&week_day, &day, &month, &year);
//			char message[100];
//			sprintf(message, "%s %u-%u-%u %u:%u:%u\n",weekday[week_day], month, day, year, hour, min, sec);
//			print_msg(message);

		// Part 3
			if (__HAL_GPIO_EXTI_GET_FLAG(USER_Btn_Pin)) {
				rtc_set_time(alarm_hour, alarm_min, alarm_sec);
				rtc_set_date(alarm_weekday, alarm_day, alarm_month, alarm_year);
				HAL_Delay(10);

				uint8_t data[7];
				data[0] = alarm_sec;
				data[1] = alarm_min;
				data[2] = alarm_hour;
				data[3] = alarm_weekday;
				data[4] = alarm_day;
				data[5] = alarm_month;
				data[6] = alarm_year;
				eeprom_write(0x0000, data, 7);
				HAL_Delay(100);
				data[0] = alarm_sec;
				data[1] = alarm_min + 1;
				data[2] = alarm_hour;
				data[3] = alarm_weekday;
				data[4] = alarm_day;
				data[5] = alarm_month;
				data[6] = alarm_year;
				eeprom_write(0x0007, data, 7);
				HAL_Delay(10);
				HAL_GPIO_EXTI_IRQHandler(USER_Btn_Pin);
			}
			rtc_get_time(&hour, &min, &sec);
			rtc_get_date(&week_day, &day, &month, &year);
			char message[100];
			sprintf(message, "%s %u-%u-%u %u:%u:%u\n",weekday[week_day], month, day, year, hour, min, sec);
			print_msg(message);
			
			get_eeprom_alarm(&comp_hour, &comp_min, &comp_sec, &comp_weekday, &comp_day, &comp_month, &comp_year);
			
			if(hour == comp_hour && min == comp_min && sec == comp_sec && week_day == comp_weekday && day == comp_day && month == comp_month && year == comp_year ) {
				sprintf(message, "ALARM\n");
				print_msg(message);
				rtc_get_time(&hour, &min, &sec);
				while(sec != comp_sec + 10){
					HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
					HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
					HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
					HAL_Delay(1000);
					rtc_get_time(&hour, &min, &sec);
				}	
				HAL_GPIO_EXTI_IRQHandler(USER_Btn_Pin);
			}
			HAL_Delay(100);
	}
}