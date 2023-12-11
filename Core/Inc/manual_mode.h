/*
 * manual_mode.h
 *
 *  Created on: Dec 8, 2023
 *      Author: DELL
 */

#ifndef INC_MANUAL_MODE_H_
#define INC_MANUAL_MODE_H_

#include "main.h"
#include "software_timer.h"
#include "auto_mode.h"
#include "manager.h"
#include <stdio.h>
#include "string.h"

void init_manual();
void red_changing_UI(void);
void yellow_changing_UI(void);
void green_changing_UI(void);
void increase_led_red();
void increase_led_yellow();
void increase_led_green();

#endif /* INC_MANUAL_MODE_H_ */
