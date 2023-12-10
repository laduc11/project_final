/*
 * auto_mode.c
 *
 *  Created on: Dec 8, 2023
 *      Author: DELL
 */

#include "auto_mode.h"

int led_time[3] = {10, 4, 6};
int hor_countdown = 0;
int ver_countdown = 0;


void traffic_light(void){
	switch(state_auto_mode){
		case Init:
			HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, RESET);
			HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, RESET);
			HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, RESET);
			HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, RESET);
			hor_countdown = led_time[RED];
			ver_countdown = led_time[GREEN];
			state_auto_mode = Red_Green;
			break;
		case Red_Green:
			hor_countdown--;
			ver_countdown--;
			HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, SET);
			HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, RESET);
			HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, RESET);
			HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, SET);
			if(ver_countdown <= 0){
				 state_auto_mode = Red_Yellow;
				 ver_countdown = led_time[YELLOW];
			}
			break;
		case Red_Yellow:
			hor_countdown--;
			ver_countdown--;
			HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, SET);
			HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, RESET);
			HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, SET);
			HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, SET);
			if(hor_countdown <= 0){
				 state_auto_mode = Green_Red;
				 hor_countdown = led_time[GREEN];
				 ver_countdown = led_time[RED];
			}
			break;
		case Green_Red:
			hor_countdown--;
			ver_countdown--;
			HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, RESET);
			HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, SET);
			HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, SET);
			HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, RESET);
			if(hor_countdown <= 0){
				 state_auto_mode = Yellow_Red;
				 hor_countdown = led_time[YELLOW];
			}
			break;
		case Yellow_Red:
			hor_countdown--;
			ver_countdown--;
			HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, SET);
			HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, SET);
			HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, SET);
			HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, RESET);
			if(hor_countdown <= 0){
				 state_auto_mode = Red_Green;
				 hor_countdown = led_time[RED];
				 ver_countdown = led_time[GREEN];
			}
			break;
		default:
			break;
	}
}

