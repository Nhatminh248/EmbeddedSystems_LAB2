/*
 * software_timer.h
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "tim.h"
#include "led_7seg.h"
#include "type.h"

#define FREQUENCY_OF_TIM	1000    // Hz
#define SCAN_7SEGLED_TIME	50      // 50ms
#define ONE_SECOND			1000    // 1s
#define TOGGLE_TIME			250
#define INCREASE_TIME		250
#define NUMBER_OF_TIMER 	5


void set_timer(unsigned i, unsigned int time);
void run_timer(void);
bool flag_timer(unsigned i);

#endif /* INC_SOFTWARE_TIMER_H_ */
