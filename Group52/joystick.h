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
} DirectionType;

struct positions {
	int16_t x, y, l, r;
};

void JOYSTICK_init(void);
void JOYSTICK_calibrate(void);
struct positions JOYSTICK_get_position(void);
DirectionType JOYSTICK_get_direction(void);
struct positions SLIDERS_get_positions(void);
int16_t toPositionPercent(int16_t value);
uint8_t JOYSTICK_read_button(void);



#endif /* JOYSTICK_H_ */