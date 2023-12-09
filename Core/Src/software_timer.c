/*
 * software_timer.c
 *
 *  Created on: Dec 8, 2023
 *      Author: DELL
 */

#include "software_timer.h"

int flag[MAX_TIMER] = {0};
int timer_counter[MAX_TIMER] = {0};

/*
Get flag of timer
input: ID of timer
output: flag of this timer
*/
int get_flag(int idx_timer)
{
    return flag[idx_timer];
}

/*
Count down and trigger the flag when counter = 0
input: ID of timer
output: none
*/
void run_timer(int idx)
{
    if (timer_counter[idx] > 0)
    {
        timer_counter[idx]--;
        if (timer_counter[idx] == 0)
        {
            flag[idx] = 1;
        }
    }
}

/*
Set the time for timer
input: ID of timer and duration of this timer
output: none
*/
void set_timer(int idx_timer, int duration)
{
    flag[idx_timer] = 0;
    timer_counter[idx_timer] = duration;
}
