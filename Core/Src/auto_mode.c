/*
 * auto_mode.c
 *
 *  Created on: Dec 8, 2023
 *      Author: DELL
 */

#include "auto_mode.h"

int led_time[3] = {10, 4, 6};
int horizontal_countdown = 0;
int vertical_countdown = 0;


void traffic_light(void){
	switch(light_state){
		case Init:
			HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, RESET);
			HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, RESET);
			HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, RESET);
			HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, RESET);
			horizontal_countdown = led_time[RED];
			vertical_countdown = led_time[GREEN];
			light_state = Red_Green;
			break;
		case Red_Green:
			horizontal_countdown--;
			vertical_countdown--;
			HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, SET);
			HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, RESET);
			HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, RESET);
			HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, SET);
			HAL_GPIO_WritePin(HORN_GPIO_Port, HORN_Pin, RESET);
			if(vertical_countdown <= 0){
				 light_state = Red_Yellow;
				 vertical_countdown = led_time[YELLOW];
			}
			break;
		case Red_Yellow:
			horizontal_countdown--;
			vertical_countdown--;
			HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, SET);
			HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, RESET);
			HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, SET);
			HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, SET);
			HAL_GPIO_WritePin(HORN_GPIO_Port, HORN_Pin, SET);
			if(horizontal_countdown <= 0){
				 light_state = Green_Red;
				 horizontal_countdown = led_time[GREEN];
				 vertical_countdown = led_time[RED];
			}
			break;
		case Green_Red:
			horizontal_countdown--;
			vertical_countdown--;
			HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, RESET);
			HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, SET);
			HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, SET);
			HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, RESET);
			HAL_GPIO_WritePin(HORN_GPIO_Port, HORN_Pin, RESET);
			if(horizontal_countdown <= 0){
				 light_state = Yellow_Red;
				 horizontal_countdown = led_time[YELLOW];
			}
			break;
		case Yellow_Red:
			horizontal_countdown--;
			vertical_countdown--;
			HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, SET);
			HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, SET);
			HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, SET);
			HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, RESET);
			if(horizontal_countdown <= 0){
				 light_state = Red_Green;
				 horizontal_countdown = led_time[RED];
				 vertical_countdown = led_time[GREEN];
			}
			break;
		default:
			break;
	}
}

