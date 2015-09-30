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

void joystick_Calibrate(void);
struct positions joystick_Get_Position(void);
DirectionType joystick_Get_Direction(void);
struct positions sliders_Get_Positions(void);
int16_t toPositionPercent(int16_t value);



#endif /* JOYSTICK_H_ */