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

extern uint8_t led_time[3];
extern uint8_t hor_countdown;
extern uint8_t ver_countdown;
extern StateNormal state_auto_mode;
extern int onPedes;

void traffic_light(void);
void turn_off_light();
void V_Red();
void V_Yellow();
void V_Green();
void H_Red();
void H_Yellow();
void H_Green();

#endif /* INC_AUTO_MODE_H_ */
