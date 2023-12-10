/*
 * manager.c
 *
 *  Created on: Dec 10, 2023
 *      Author: DELL
 */

#include "manager.h"

STATE_MODE state_mode = AUTO_MODE;
UART_HandleTypeDef huart2;

void clearTerminal(){
	char clr[] = "\033[2J";
	HAL_UART_Transmit(&huart2, (uint8_t *)clr, sizeof(clr) - 1, HAL_MAX_DELAY);
}
void printString(const char *str){
	HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}
void printValue(int val){
	char str[100];
	HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "%d\r\n", val), HAL_MAX_DELAY);
}

/*
 * Finite state machine to change mode of traffic light
 * Input: none
 * Output: none
 * */
void manager_state(){
	switch(state_mode){
	case AUTO_MODE:
		traffic_light();

		if(get_button_flag(0) == PRESSED || get_button_flag(0) == LONG_PRESSED) {
			state_mode = RED_CHANGING;
			init_manual();
		}

		if(get_button_flag(1) == PRESSED || get_button_flag(1) == LONG_PRESSED) {
			//set_flag_pedes = 1;
		}
		break;
	case RED_CHANGING:
		red_changing_UI();

		if(get_button_flag(0) == PRESSED || get_button_flag(0) == LONG_PRESSED) {
			state_mode = YELLOW_CHANGING;
			init_manual();
		}

		if(get_button_flag(1) == PRESSED || get_button_flag(1) == LONG_PRESSED) {
			increase_led_red();
		}
		break;
	case YELLOW_CHANGING:
		yellow_changing_UI();

		if(get_button_flag(0) == PRESSED || get_button_flag(0) == LONG_PRESSED) {
			state_mode = GREEN_CHANGING;
			init_manual();
		}

		if(get_button_flag(1) == PRESSED || get_button_flag(1) == LONG_PRESSED) {
			increase_led_yellow();
		}
		break;
	case GREEN_CHANGING:
		green_changing_UI();

		if(get_button_flag(0) == PRESSED || get_button_flag(0) == LONG_PRESSED) {
			state_mode = AUTO_MODE;
			state_auto_mode = INIT;
			if (led_time[RED] != led_time[YELLOW] + led_time[GREEN]) {
				led_time[RED] = led_time[YELLOW] + led_time[GREEN];
			}
		}

		if(get_button_flag(1) == PRESSED || get_button_flag(1) == LONG_PRESSED) {
			increase_led_green();
		}
		break;
	default:
		break;
	}
}
