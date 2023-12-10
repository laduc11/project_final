/*
 * manual_mode.c
 *
 *  Created on: Dec 8, 2023
 *      Author: DELL
 */

#include "manual_mode.h"
// Led blink with frequency 2Hz

uint8_t toggleLED = 0;

/*
 * Initial all start parameter
 * Input: none
 * Output: none
 * */
void init_manual()
{
	toggleLED = 0;
	turn_off_light();
}

/*
 * Display modified led red
 * Input: none
 * Output: none
 * */
void red_changing_UI()
{
    if (toggleLED == 1)
    {
        // turn on all led red
        V_Red();
        H_Red();
    }
    else
    {
        // turn off all led
        turn_off_light();
    }
    toggleLED = 1 - toggleLED;
}

/*
 * Display modified led yellow
 * Input: none
 * Output: none
 * */
void yellow_changing_UI()
{
    if (toggleLED == 1)
    {
        // turn on all led yellow
        V_Yellow();
        H_Yellow();
    }
    else
    {
        // turn off all led
        turn_off_light();
    }
    toggleLED = 1 - toggleLED;
}

/*
 * Display modified led green
 * Input: none
 * Output: none
 * */
void green_changing_UI()
{
    if (toggleLED == 1)
    {
        // turn on led green
        V_Green();
        H_Green();
    }
    else
    {
        // turn off all led
        turn_off_light();
    }
    toggleLED = 1 - toggleLED;
}

/*
 * Increase the period of led red one time unit
 * Input: none
 * Output: none
 * */
void increase_led_red()
{
	led_time[RED] = led_time[RED] + 1;
}

/*
 * Increase the period of led yellow one time unit
 * Input: none
 * Output: none
 * */
void increase_led_yellow()
{
	if (led_time[YELLOW] + led_time[GREEN] == led_time[RED])
		return;
	led_time[YELLOW] = led_time[YELLOW] + 1;
}

/*
 * Increase the period of led red one time unit
 * Input: none
 * Output: none
 * */
void increase_led_green()
{
	if (led_time[YELLOW] + led_time[GREEN] == led_time[RED])
		return;
	led_time[GREEN] = led_time[GREEN] + 1;
}
