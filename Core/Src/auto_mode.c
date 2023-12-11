/*
 * auto_mode.c
 *
 *  Created on: Dec 8, 2023
 *      Author: DELL
 */

#include "auto_mode.h"

uint8_t led_time[3] = {10, 4, 6};
uint8_t hor_countdown = 0;
uint8_t ver_countdown = 0;
StateNormal state_auto_mode = INIT;
int onPedes = 0;
int buzzerFlag = 0;

/*
 * Turn off all traffic light
 * Input: none
 * Output: none
 * */
void turn_off_light()
{
	HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, RESET);
	HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, RESET);
	HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, RESET);
	HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, RESET);
}

/*
 * Turn on led red in a vertical direction
 * Input: none
 * Output: none
 * */
void V_Green()
{
	HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, SET);
	HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, RESET);
}

/*
 * Turn on led yellow in a vertical direction
 * Input: none
 * Output: none
 * */
void V_Yellow()
{
	HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, SET);
	HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, SET);
}

/*
 * Turn on led green in a vertical direction
 * Input: none
 * Output: none
 * */
void V_Red()
{
	HAL_GPIO_WritePin(LED_1_1_GPIO_Port, LED_1_1_Pin, RESET);
	HAL_GPIO_WritePin(LED_1_2_GPIO_Port, LED_1_2_Pin, SET);
}

/*
 * Turn on led red in a horizontal direction
 * Input: none
 * Output: none
 * */
void H_Green()
{
	HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, SET);
	HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, RESET);
}

/*
 * Turn on led yellow in a horizontal direction
 * Input: none
 * Output: none
 * */
void H_Yellow()
{
	HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, SET);
	HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, SET);
}

/*
 * Turn on led green in a horizontal direction
 * Input: none
 * Output: none
 * */
void H_Red()
{
	HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, RESET);
	HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, SET);
}

void pedesOff()
{
	HAL_GPIO_WritePin(LED_PE_1_GPIO_Port, LED_PE_1_Pin, RESET);
	HAL_GPIO_WritePin(LED_PE_2_GPIO_Port, LED_PE_2_Pin, RESET);
}

void pedesGreen()
{
	HAL_GPIO_WritePin(LED_PE_1_GPIO_Port, LED_PE_1_Pin, SET);
	HAL_GPIO_WritePin(LED_PE_2_GPIO_Port, LED_PE_2_Pin, RESET);
}

void pedesRed()
{
	HAL_GPIO_WritePin(LED_PE_1_GPIO_Port, LED_PE_1_Pin, RESET);
	HAL_GPIO_WritePin(LED_PE_2_GPIO_Port, LED_PE_2_Pin, SET);
}



/*
 * Activate current traffic light state
 * Input: none
 * Output: none
 * */

void traffic_light(void)
{
	switch (state_auto_mode)
	{
	case INIT:
		turn_off_light();
		hor_countdown = led_time[RED];
		ver_countdown = led_time[GREEN];
		state_auto_mode = RED_GREEN;
		onPedes = 0;
		break;
	case RED_GREEN:
		hor_countdown--;
		ver_countdown--;
		V_Red();
		H_Green();
		if (ver_countdown <= 0)
		{
			state_auto_mode = RED_YELLOW;
			ver_countdown = led_time[YELLOW];
		}
		if (onPedes == 1){
			pedesGreen();
			if (hor_countdown <= 10) buzzerFlag = 1;
		}
		else{
			pedesOff();
		}
		clearScreen();
		printString("RED: ");
		printNumber(hor_countdown);
		printString("GREEN: ");
		printNumber(ver_countdown);
		break;
	case RED_YELLOW:
		hor_countdown--;
		ver_countdown--;
		V_Red();
		H_Yellow();
		if (hor_countdown <= 0)
		{
			state_auto_mode = GREEN_RED;
			hor_countdown = led_time[GREEN];
			ver_countdown = led_time[RED];
		}
		if (onPedes == 1){
			pedesGreen();
			if (hor_countdown <= 10) buzzerFlag = 1;
		}
		else{
			pedesOff();
		}
		clearScreen();
		printString("RED: ");
		printNumber(hor_countdown);
		printString("YELLOW: ");
		printNumber(ver_countdown);
		break;
	case GREEN_RED:
		hor_countdown--;
		ver_countdown--;
		V_Green();
		H_Red();
		if (hor_countdown <= 0)
		{
			state_auto_mode = YELLOW_RED;
			hor_countdown = led_time[YELLOW];
		}
		if (onPedes == 1){
			pedesRed();
			buzzerFlag = 0;
		}
		else{
			pedesOff();
		}
		clearScreen();
		printString("GREEN: ");
		printNumber(hor_countdown);
		printString("RED: ");
		printNumber(ver_countdown);
		break;
	case YELLOW_RED:
		hor_countdown--;
		ver_countdown--;
		V_Yellow();
		H_Red();
		if (hor_countdown <= 0)
		{
			state_auto_mode = RED_GREEN;
			hor_countdown = led_time[RED];
			ver_countdown = led_time[GREEN];
		}
		if (onPedes == 1){
			pedesRed();
			buzzerFlag = 0;
		}
		else{
			pedesOff();
		}
		clearScreen();
		printString("YELLOW: ");
		printNumber(hor_countdown);
		printString("RED: ");
		printNumber(ver_countdown);
		break;
	default:
		break;
	}
}
