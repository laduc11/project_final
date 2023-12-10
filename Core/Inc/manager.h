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

typedef enum {auto_mode, red_changing, yellow_changing, green_changing} STATE_MODE;

extern STATE_MODE state_mode;



#endif /* INC_MANAGER_H_ */
