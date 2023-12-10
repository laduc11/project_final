/*
 * auto_mode.h
 *
 *  Created on: Dec 8, 2023
 *      Author: DELL
 */

#ifndef INC_AUTO_MODE_H_
#define INC_AUTO_MODE_H_

#include "main.h"

#define RED 	0
#define YELLOW	1
#define GREEN	2

#define HORI 	0
#define VERTI 	1

typedef enum {
	INIT = 0,
	RED_GREEN = 1,
	RED_YELLOW = 2,
	GREEN_RED = 3,
	YELLOW_RED = 4
} StateNormal;

extern int led_time[3];
extern int hor_countdown;
extern int ver_countdown;
extern StateNormal state_auto_mode;

void traffic_light(void);

#endif /* INC_AUTO_MODE_H_ */
