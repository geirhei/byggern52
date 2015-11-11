/*
 * servo.c
 *
 * Created: 11.11.2015 17:00:40
 *  Author: geirhei
 */ 

#include <avr/io.h>
#include "servo.h"

void SERVO_init(void)
{
	uint8_t duty_cyc;
	
	/* Set PWM port as output */
	DDRB = (1 << PB5);
	
	// f_PWM = F_CPU / (1250 * 256) CORRECT?
	TCCR1A = 0b10001010; //Set TIMER1 register to Fast PWM 8 bit, Clear OCRA0 on compare match, SET on top
	TCNT1 = 0; // Reset TCNT0
	OCR1A = 0; // Initialize output compare register
	
}

void SERVO_write(position_t pos)
{
	
}

