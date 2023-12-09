/*
 * software_timer.h
 *
 *  Created on: Dec 8, 2023
 *      Author: DELL
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

#define MAX_TIMER 5

int get_flag(int idx_timer);
void run_timer(int idx);
void set_timer(int idx_timer, int duration);

#endif /* INC_SOFTWARE_TIMER_H_ */
