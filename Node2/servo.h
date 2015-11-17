/*
 * servo.h
 *
 * Created: 11.11.2015 17:01:11
 *  Author: geirhei
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#include <avr/io.h>
#include <avr/interrupt.h>

typedef struct {
	uint8_t x, y;
} position_t;

void SERVO_init(void);
void timer1_init(void);
void SERVO_write(position_t pos);
ISR(TIMER1_COMPA_vect);



#endif /* SERVO_H_ */