/*
 * led_control.c
 *
 *  Created on: Nov 15, 2024
 *      Author: ASUS
 */

#include "led_control.h"

#define NUM_BOX	5

/*
 * @brief:	Struct of circle led in traffic light
 */
typedef struct {
	uint16_t center_x;
	uint16_t center_y;
	uint16_t COLOR_FILL;
	uint16_t radius;
	uint8_t is_fill;
} circle;

/*
 * @brief:	Struct of number to show traffic time
 */
typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t num;
	uint8_t len;
	uint16_t fc;
	uint16_t bc;
	uint8_t sizey;
} number;

/*
 * @brief:	Struct of traffic light follow West and East
 */
struct {
	uint16_t x;
	uint16_t y;
	uint16_t height;
	uint16_t width;
	uint16_t COLOR_FILL;

	circle red;
	circle yellow;
	circle green;

	//num
	number num;
} traffic_WE;

/*
 * @brief:	Struct of traffic light follow North and South
 */
struct {
	uint16_t x;
	uint16_t y;
	uint16_t height;
	uint16_t width;
	uint16_t COLOR_FILL;

	circle red;
	circle yellow;
	circle green;
	//num
	number num;
} traffic_NS;

/*@brief:	function to init traffic light
 * @para:	none
 * @retval:	none*/
void init_traffic_light(void) {
	traffic_WE.x = 50;
	traffic_WE.y = 120;
	traffic_WE.width = 40;
	traffic_WE.height = 120;
	traffic_WE.COLOR_FILL = WHITE;
	//draw a black box
	lcd_DrawRectangle(traffic_WE.x, traffic_WE.y,
			traffic_WE.x + traffic_WE.width, traffic_WE.y + traffic_WE.height,
			traffic_WE.COLOR_FILL);
	lcd_Fill(traffic_WE.x, traffic_WE.y, traffic_WE.x + traffic_WE.width,
			traffic_WE.y + traffic_WE.height, traffic_WE.COLOR_FILL);

	//calculate center and radius of each light inside above black box
	traffic_WE.red.center_y = traffic_WE.y + traffic_WE.height / 6;
	traffic_WE.yellow.center_y = traffic_WE.y + 3 * traffic_WE.height / 6;
	traffic_WE.green.center_y = traffic_WE.y + 5 * traffic_WE.height / 6;

	traffic_WE.red.center_x = traffic_WE.x + traffic_WE.width / 2;
	traffic_WE.yellow.center_x = traffic_WE.red.center_x;
	traffic_WE.green.center_x = traffic_WE.red.center_x;

	traffic_WE.red.radius = (traffic_WE.width / 2) * 90 / 100;
	traffic_WE.yellow.radius = traffic_WE.red.radius;
	traffic_WE.green.radius = traffic_WE.red.radius;

	traffic_WE.red.is_fill = 1;
	if (traffic_WE.red.is_fill == 1) {
		traffic_WE.red.COLOR_FILL = RED;
	} else {
		traffic_WE.red.COLOR_FILL = BLACK;
	}
	traffic_WE.yellow.is_fill = 1;
	if (traffic_WE.yellow.is_fill == 1) {
		traffic_WE.yellow.COLOR_FILL = YELLOW;
	} else {
		traffic_WE.yellow.COLOR_FILL = BLACK;
	}
	traffic_WE.green.is_fill = 1;
	if (traffic_WE.green.is_fill == 1) {
		traffic_WE.green.COLOR_FILL = GREEN;
	} else {
		traffic_WE.green.COLOR_FILL = BLACK;
	}
	//draw red
	lcd_DrawCircle(traffic_WE.red.center_x, traffic_WE.red.center_y,
			traffic_WE.red.COLOR_FILL, traffic_WE.red.radius,
			traffic_WE.red.is_fill);
	//draw yellow
	lcd_DrawCircle(traffic_WE.yellow.center_x, traffic_WE.yellow.center_y,
			traffic_WE.yellow.COLOR_FILL, traffic_WE.yellow.radius,
			traffic_WE.yellow.is_fill);
	//draw green
	lcd_DrawCircle(traffic_WE.green.center_x, traffic_WE.green.center_y,
			traffic_WE.green.COLOR_FILL, traffic_WE.green.radius,
			traffic_WE.green.is_fill);

	//init num
	traffic_WE.num.len = 2;
	traffic_WE.num.fc = BLACK;
	traffic_WE.num.bc = WHITE;
	traffic_WE.num.sizey = 32;
	traffic_WE.num.x = traffic_WE.x;
	traffic_WE.num.y = traffic_WE.y - traffic_WE.num.sizey;
	traffic_WE.num.num = 99;
	lcd_ShowIntNum(traffic_WE.num.x, traffic_WE.num.y, traffic_WE.num.num,
			traffic_WE.num.len, traffic_WE.num.fc, traffic_WE.num.bc,
			traffic_WE.num.sizey);

	/*init NS    -------------------------------------------------------------*/
	traffic_NS.x = 150;
	traffic_NS.y = 120;
	traffic_NS.width = 40;
	traffic_NS.height = 120;
	traffic_NS.COLOR_FILL = WHITE;
	//draw a black box
	lcd_DrawRectangle(traffic_NS.x, traffic_NS.y,
			traffic_NS.x + traffic_NS.width, traffic_NS.y + traffic_NS.height,
			traffic_NS.COLOR_FILL);
	lcd_Fill(traffic_NS.x, traffic_NS.y, traffic_NS.x + traffic_NS.width,
			traffic_NS.y + traffic_NS.height, traffic_NS.COLOR_FILL);

	//calculate center and radius of each light inside above black box
	traffic_NS.red.center_y = traffic_NS.y + traffic_NS.height / 6;
	traffic_NS.yellow.center_y = traffic_NS.y + 3 * traffic_NS.height / 6;
	traffic_NS.green.center_y = traffic_NS.y + 5 * traffic_NS.height / 6;

	traffic_NS.red.center_x = traffic_NS.x + traffic_NS.width / 2;
	traffic_NS.yellow.center_x = traffic_NS.red.center_x;
	traffic_NS.green.center_x = traffic_NS.red.center_x;

	traffic_NS.red.radius = (traffic_NS.width / 2) * 90 / 100;
	traffic_NS.yellow.radius = traffic_NS.red.radius;
	traffic_NS.green.radius = traffic_NS.red.radius;

	traffic_NS.red.is_fill = 1;
	if (traffic_NS.red.is_fill == 1) {
		traffic_NS.red.COLOR_FILL = RED;
	} else {
		traffic_NS.red.COLOR_FILL = BLACK;
	}
	traffic_NS.yellow.is_fill = 1;
	if (traffic_NS.yellow.is_fill == 1) {
		traffic_NS.yellow.COLOR_FILL = YELLOW;
	} else {
		traffic_NS.yellow.COLOR_FILL = BLACK;
	}
	traffic_NS.green.is_fill = 1;
	if (traffic_NS.green.is_fill == 1) {
		traffic_NS.green.COLOR_FILL = GREEN;
	} else {
		traffic_NS.green.COLOR_FILL = BLACK;
	}
	//draw red
	lcd_DrawCircle(traffic_NS.red.center_x, traffic_NS.red.center_y,
			traffic_NS.red.COLOR_FILL, traffic_NS.red.radius,
			traffic_NS.red.is_fill);
	//draw yellow
	lcd_DrawCircle(traffic_NS.yellow.center_x, traffic_NS.yellow.center_y,
			traffic_NS.yellow.COLOR_FILL, traffic_NS.yellow.radius,
			traffic_NS.yellow.is_fill);
	//draw green
	lcd_DrawCircle(traffic_NS.green.center_x, traffic_NS.green.center_y,
			traffic_NS.green.COLOR_FILL, traffic_NS.green.radius,
			traffic_NS.green.is_fill);

	//init num
	traffic_NS.num.len = 2;
	traffic_NS.num.fc = BLACK;
	traffic_NS.num.bc = WHITE;
	traffic_NS.num.sizey = 32;
	traffic_NS.num.x = traffic_NS.x;
	traffic_NS.num.y = traffic_NS.y - traffic_NS.num.sizey;
	traffic_NS.num.num = 99;
	lcd_ShowIntNum(traffic_NS.num.x, traffic_NS.num.y, traffic_NS.num.num,
			traffic_NS.num.len, traffic_NS.num.fc, traffic_NS.num.bc,
			traffic_NS.num.sizey);
	/*End init NS-------------------------------------------------------------*/
}

/*
 * @brief: 	display traffic light function
 * @para:	i - id of traffic light(0: WE, 1: NS)
 * 			red, yellow, green - state of red, yellow and green led (1: on, 0: off)
 * @retval:	none*/
void control_traffic_light(uint8_t i, uint8_t red, uint8_t yellow,
		uint8_t green) {
	if (i == 0) {
		//draw red
		if (!red) {
			traffic_WE.red.COLOR_FILL = BLACK;
		} else {
			traffic_WE.red.COLOR_FILL = RED;
		}
		if (!yellow) {
			traffic_WE.yellow.COLOR_FILL = BLACK;
		} else {
			traffic_WE.yellow.COLOR_FILL = YELLOW;
		}
		if (!green) {
			traffic_WE.green.COLOR_FILL = BLACK;
		} else {
			traffic_WE.green.COLOR_FILL = GREEN;
		}
		lcd_DrawCircle(traffic_WE.red.center_x, traffic_WE.red.center_y,
				traffic_WE.red.COLOR_FILL, traffic_WE.red.radius, 1);
		//draw yellow
		lcd_DrawCircle(traffic_WE.yellow.center_x, traffic_WE.yellow.center_y,
				traffic_WE.yellow.COLOR_FILL, traffic_WE.yellow.radius, 1);
		//draw green
		lcd_DrawCircle(traffic_WE.green.center_x, traffic_WE.green.center_y,
				traffic_WE.green.COLOR_FILL, traffic_WE.green.radius, 1);
	} else {
		if (!red) {
			traffic_NS.red.COLOR_FILL = BLACK;
		} else {
			traffic_NS.red.COLOR_FILL = RED;
		}
		if (!yellow) {
			traffic_NS.yellow.COLOR_FILL = BLACK;
		} else {
			traffic_NS.yellow.COLOR_FILL = YELLOW;
		}
		if (!green) {
			traffic_NS.green.COLOR_FILL = BLACK;
		} else {
			traffic_NS.green.COLOR_FILL = GREEN;
		}
		//draw red
		lcd_DrawCircle(traffic_NS.red.center_x, traffic_NS.red.center_y,
				traffic_NS.red.COLOR_FILL, traffic_NS.red.radius, 1);
		//draw yellow
		lcd_DrawCircle(traffic_NS.yellow.center_x, traffic_NS.yellow.center_y,
				traffic_NS.yellow.COLOR_FILL, traffic_NS.yellow.radius, 1);
		//draw green
		lcd_DrawCircle(traffic_NS.green.center_x, traffic_NS.green.center_y,
				traffic_NS.green.COLOR_FILL, traffic_NS.green.radius, 1);
	}
}

/*
 * @brief: 	update traffic light time value and show mode function
 * @para:	val1 is value of WE time, val2 is value of NS time
 * 			mode is mode of traffic system described in the request
 * @retval:	none*/
void update_led_buf(unsigned val1, unsigned val2, unsigned mode) {
	if (mode == 4 || mode == 3 || mode == 2) {
		lcd_ShowIntNum(140, 280, mode, 1, RED, GRAY, 32);
	} else {
		lcd_ShowIntNum(140, 280, mode, 1, RED, GRAY, 32);
	}
	traffic_WE.num.num = val1;
	traffic_NS.num.num = val2;
}

/*
 * @brief: 	display number function
 * @para:	noe
 * @retval:	none*/
void LCD_DisplayNum() {
	lcd_ShowStr(60, 280, "MODE:", RED, GRAY, 32, 0);
	lcd_ShowIntNum(traffic_WE.num.x, traffic_WE.num.y, traffic_WE.num.num,
			traffic_WE.num.len, traffic_WE.num.fc, traffic_WE.num.bc,
			traffic_WE.num.sizey);
	lcd_ShowIntNum(traffic_NS.num.x, traffic_NS.num.y, traffic_NS.num.num,
			traffic_NS.num.len, traffic_NS.num.fc, traffic_NS.num.bc,
			traffic_NS.num.sizey);

	// other graphic
	lcd_ShowStr(50, 20, "TRAFFIC LIGHT", BLACK, WHITE, 24, 1);
}
