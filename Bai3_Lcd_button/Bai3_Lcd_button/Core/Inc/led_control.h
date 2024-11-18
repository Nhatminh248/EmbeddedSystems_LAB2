/*
 * led_control.h
 *
 *  Created on: Nov 15, 2024
 *      Author: ASUS
 */

#ifndef INC_LED_CONTROL_H_
#define INC_LED_CONTROL_H_

#include <stdint.h>
#include "lcd.h"


void init_traffic_light(void);
void control_traffic_light(uint8_t i, uint8_t red, uint8_t yellow, uint8_t green);
void update_led_buf(unsigned val1, unsigned val2, unsigned mode);
void LCD_DisplayNum();

#endif /* INC_LED_CONTROL_H_ */
