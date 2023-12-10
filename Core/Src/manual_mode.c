/*
 * manual_mode.c
 *
 *  Created on: Dec 8, 2023
 *      Author: DELL
 */

#include "manual_mode.h"

int toggleLED = 0;

void red_changing_UI(){
	if(get_flag(0) == 1){
		if(toggleLED == 1){
			// sang do
		}else{
			// tat do
		}
		toggleLED = 1 - toggleLED;
		set_timer(0, 100);
	}
}

void yellow_changing_UI(){
	if(get_flag(0) == 1){
		if(toggleLED == 1){
			// sang vang
		}else{
			// tat vang
		}
		toggleLED = 1 - toggleLED;
		set_timer(0, 100);
	}
}

void green_changing_UI(){
	if(get_flag(0) == 1){
		if(toggleLED == 1){
			// sang xanh
		}else{
			// tat xanh
		}
		toggleLED = 1 - toggleLED;
		set_timer(0, 100);
	}
}

