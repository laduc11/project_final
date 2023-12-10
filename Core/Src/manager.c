/*
 * manager.c
 *
 *  Created on: Dec 10, 2023
 *      Author: DELL
 */

#include "manager.h"

STATE_MODE state_mode = AUTO_MODE;

int buzzerDuty = 0;
int buzzerFlag = 0;
int buzzerFaster = 0;

void clearScreen()
{
	char clr[] = "\033[2J";
	HAL_UART_Transmit(&huart2, (uint8_t *)clr, sizeof(clr) - 1, HAL_MAX_DELAY);
}
void printString(const char *str)
{
	HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}
void printNumber(int val)
{
	char str[100];
	HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "%d\r\n", val), HAL_MAX_DELAY);
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

void buzzerReset()
{
	buzzerDuty = 0;
}

void BuzzerLouder()
{
	if (buzzerFlag == 1)
	{
		if (buzzerDuty < 100)
		{
			buzzerDuty += 10;
		}
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, buzzerDuty);
		buzzerFlag = 0;
	}

	if (buzzerFlag == 0)
	{
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
		buzzerFlag = 1;
	}
}

void pedesRun()
{
	switch (state_auto_mode)
	{
	case INIT:
	case RED_GREEN:
		if (hor_countdown <= 10)
			BuzzerLouder();
		pedesGreen();
		break;
	case RED_YELLOW:
		if (hor_countdown <= 10)
			BuzzerLouder();
		pedesGreen();
		break;
	case GREEN_RED:
		buzzerDuty = 0;
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
		pedesRed();
		break;
	case YELLOW_RED:
		buzzerDuty = 0;
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
		pedesRed();
		break;
	}
}

void stateUI()
{
	switch (state_mode)
	{
	case AUTO_MODE:
		traffic_light();
		break;
	case RED_CHANGING:
		red_changing_UI();
		break;
	case YELLOW_CHANGING:
		yellow_changing_UI();
		break;
	case GREEN_CHANGING:
		green_changing_UI();
		break;
	}
}

/*
 * Finite state machine to change mode of traffic light
 * Input: none
 * Output: none
 * */
void manager_state()
{
	switch (state_mode)
	{
	case AUTO_MODE:
		traffic_light();

		if (get_button_flag(0) == PRESSED || get_button_flag(0) == LONG_PRESSED)
		{
			state_mode = RED_CHANGING;
			init_manual();
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		}

		if (get_button_flag(1) == PRESSED || get_button_flag(1) == LONG_PRESSED)
		{
			// set_flag_pedes = 1;
		}
		break;
	case RED_CHANGING:
		if (get_button_flag(0) == PRESSED || get_button_flag(0) == LONG_PRESSED)
		{
			state_mode = YELLOW_CHANGING;
			init_manual();
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		}

		if (get_button_flag(1) == PRESSED || get_button_flag(1) == LONG_PRESSED)
		{
			increase_led_red();
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		}
		break;
	case YELLOW_CHANGING:
		if (get_button_flag(0) == PRESSED || get_button_flag(0) == LONG_PRESSED)
		{
			state_mode = GREEN_CHANGING;
			init_manual();
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		}

		if (get_button_flag(1) == PRESSED || get_button_flag(1) == LONG_PRESSED)
		{
			increase_led_yellow();
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		}
		break;
	case GREEN_CHANGING:
		if (get_button_flag(0) == PRESSED || get_button_flag(0) == LONG_PRESSED)
		{
			state_mode = AUTO_MODE;
			state_auto_mode = INIT;
			if (led_time[RED] != led_time[YELLOW] + led_time[GREEN])
			{
				led_time[RED] = led_time[YELLOW] + led_time[GREEN];
			}

			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		}

		if (get_button_flag(1) == PRESSED || get_button_flag(1) == LONG_PRESSED)
		{
			increase_led_green();
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		}
		break;
	default:
		break;
	}
}
