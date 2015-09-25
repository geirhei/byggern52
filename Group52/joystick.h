/*
 * joystick.h
 *
 * Created: 18.09.2015 15:28:40
 *  Author: chengbid
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <avr/io.h>

typedef struct {
	int8_t stick_positions[2];
} position;


position joystick_Get_Position(void);



#endif /* JOYSTICK_H_ */