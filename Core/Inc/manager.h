/*
 * manager.h
 *
 *  Created on: Dec 10, 2023
 *      Author: DELL
 */

#ifndef INC_MANAGER_H_
#define INC_MANAGER_H_

#include "auto_mode.h"
#include "manual_mode.h"
#include "button.h"
#include <stdio.h>
#include "string.h"

#define MAX_COUNTER 100 // 100*10ms = 1000ms

typedef enum
{
	AUTO_MODE = 0,
	RED_CHANGING = 1,
	YELLOW_CHANGING = 2,
	GREEN_CHANGING = 3
} STATE_MODE;

extern STATE_MODE state_mode;

void manager_state();
void stateUI();
void clearScreen();
void printString(const char *str);
void printNumber(int val);

#endif /* INC_MANAGER_H_ */
