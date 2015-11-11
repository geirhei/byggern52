/*
 * joystick.h
 *
 * Created: 18.09.2015 15:28:40
 *  Author: chengbid
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <avr/io.h>

typedef enum {
	NEUTRAL = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
} Direction;

typedef struct {
	uint8_t x, y, l, r;
} position_t;

void JOYSTICK_init(void);
void JOYSTICK_calibrate(void);
position_t JOYSTICK_get_position(void);
Direction JOYSTICK_get_direction(position_t pos);
position_t SLIDERS_get_positions(void);
int16_t toPositionPercent(int16_t value);
uint8_t JOYSTICK_read_button(void);
void JOYSTICK_send_position(void);



#endif /* JOYSTICK_H_ */