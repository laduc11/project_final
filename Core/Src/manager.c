/*
 * manager.c
 *
 *  Created on: Dec 10, 2023
 *      Author: DELL
 */

#include "manager.h"



STATE_MODE state_mode = auto_mode;


void manager_state(){
	switch(state_mode){
	case auto_mode:
		traffic_light();
		if(get_button_flag(0) == PRESSED || get_button_flag(0) == LONG_PRESSED) {
			state_mode = red_changing;
		}
		if(get_button_flag(1) == PRESSED || get_button_flag(1) == LONG_PRESSED) {
			//set_flag_pedes = 1;
		}
		break;
	case red_changing:
		if(get_button_flag(0) == PRESSED || get_button_flag(0) == LONG_PRESSED) {
			state_mode = yellow_changing;
		}

		if(get_button_flag(1) == PRESSED || get_button_flag(1) == LONG_PRESSED) {
			led_time[RED]++;
		}
		break;
	case yellow_changing:
		if(get_button_flag(0) == PRESSED || get_button_flag(0) == LONG_PRESSED) {
			state_mode = green_changing;
		}

		if(get_button_flag(1) == PRESSED || get_button_flag(1) == LONG_PRESSED) {
			led_time[YELLOW]++;
		}
		break;
	case green_changing:
		if(get_button_flag(0) == PRESSED || get_button_flag(0) == LONG_PRESSED) {
			state_mode = auto_mode;
		}

		if(get_button_flag(1) == PRESSED || get_button_flag(1) == LONG_PRESSED) {
			led_time[GREEN]++;
		}
		break;
	default:
		break;
	}
}
