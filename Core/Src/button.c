/*
 * button.c
 *
 *  Created on: Dec 8, 2023
 *      Author: DELL
 */

#include "button.h"

// Time cycle = 10ms
#define WAITING_TIME 200	// press and hold in 2 seconds

typedef struct
{
	GPIO_TypeDef *port;
	uint16_t pin;
} listButton;

// List of button
listButton button[MAX_BUTTON];
statusButton buttonFlag[MAX_BUTTON];
statusButton previousStatus[MAX_BUTTON][3];
uint16_t counter[MAX_BUTTON];
uint8_t isPressed;

/*
 * Initial start value for all attribute
 * Input: none
 * Output: none
 * */
void init_button()
{
	button[0].port = BUTTON1_GPIO_Port;
	button[0].pin = BUTTON1_Pin;
	button[1].port = BUTTON2_GPIO_Port;
	button[1].pin = BUTTON2_Pin;

	isPressed = 0;

	for (int i = 0; i < MAX_BUTTON; i++)
	{
		counter[i] = WAITING_TIME;
		buttonFlag[i] = NORMAL;
		for (int j = 0; j < 3; j++)
		{
			previousStatus[i][j] = NORMAL;
		}
	}
}

/*
 * Get input signal from all button
 * Input: none
 * Output: none
 * */
void get_key()
{
	for (int i = 0; i < MAX_BUTTON; i++)
	{
		previousStatus[i][0] = previousStatus[i][1];
		previousStatus[i][1] = previousStatus[i][2];
		previousStatus[i][2] = (HAL_GPIO_ReadPin(button[i].port, button[i].pin) == GPIO_PIN_RESET) ? PRESSED : NORMAL;
	}

	// Process key
	for (int i = 0; i < MAX_BUTTON; i++)
	{
        if ((previousStatus[i][0] == PRESSED) &&
            (previousStatus[i][1] == PRESSED) &&
            (previousStatus[i][2] == PRESSED))
        {
            if (isPressed)
            {
            	counter[i]--;
            	if (counter[i] == 0)
            	{
            		counter[i] = WAITING_TIME;
            		buttonFlag[i] = LONG_PRESSED;
            	}
            }
            else
            {
            	isPressed = 1;
            	buttonFlag[i] = PRESSED;
            }
        }
        else
        {
        	isPressed = 0;
        	counter[i] = WAITING_TIME;
        	buttonFlag[i] = NORMAL;
        }
	}
}

/*
 * Process 4 nearest input read from button
 * Input: none
 * Output: none
 * */
void processKey()
{
	for (int i = 0; i < MAX_BUTTON; i++)
	{
        if ((previousStatus[i][0] == PRESSED) &&
            (previousStatus[i][1] == PRESSED) &&
            (previousStatus[i][2] == PRESSED))
        {
            if (isPressed)
            {
            	counter[i]--;
            	if (counter[i] == 0)
            	{
            		counter[i] = WAITING_TIME;
            		buttonFlag[i] = LONG_PRESSED;
            	}
            }
            else
            {
            	isPressed = 1;
            	buttonFlag[i] = PRESSED;
            }
        }
        else
        {
        	isPressed = 0;
        	counter[i] = WAITING_TIME;
        	buttonFlag[i] = NORMAL;
        }
	}
}

/*
 * Get status of chosen button
 * Input: Index of button
 * Output: Status of button
 * */
statusButton get_button_flag(uint8_t buttonIdx)
{
	statusButton temp = buttonFlag[buttonIdx];
	if (temp != NORMAL)
	{
		isPressed = 1;
	}
	buttonFlag[buttonIdx] = NORMAL;
	return temp;
}
