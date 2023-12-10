/*
 * auto_mode.h
 *
 *  Created on: Dec 8, 2023
 *      Author: DELL
 */

#ifndef INC_AUTO_MODE_H_
#define INC_AUTO_MODE_H_

#define RED 	0
#define YELLOW	1
#define GREEN	2

#define HORI 	0
#define VERTI 	1

extern int led_time[3];
extern int hor_countdown;
extern int ver_countdown;

enum StateNormal {Init, Red_Green, Red_Yellow, Green_Red, Yellow_Red};
extern enum StateNormal state_auto_mode;

void traffic_light(void);

#endif /* INC_AUTO_MODE_H_ */
