/*
 * button.h
 *
 *  Created on: Dec 8, 2023
 *      Author: DELL
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define MAX_BUTTON 2

typedef enum
{
	NORMAL = 0,
	PRESSED = 1,
	LONG_PRESSED = 2
} statusButton;

void init_button();
void get_key();
void processKey();
statusButton get_button_flag(uint8_t buttonIdx);

#endif /* INC_BUTTON_H_ */
