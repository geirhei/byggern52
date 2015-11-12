/*
 * servo.c
 *
 * Created: 11.11.2015 17:00:40
 *  Author: geirhei
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "servo.h"

void timer1_init(void)
{
	// Set up timer in Fast PWM mode 14
	TCCR1A |= (1 << COM1A1)|(1 << WGM11);
	
	// Set up timer with prescaler = 64 and PWM fast mode 14
	TCCR1B |= (1 << WGM13)|(1 << WGM12)|(1 << CS11)|(1 << CS10);
	
	// Set up timer with TOP value = 5000 (0x1388)
	ICR1 = 0x1388;
	
	// initialize counter
	TCNT1 = 0;
	
	// initialize compare value (servo to middle, 0x0177)
	OCR1A = 0x0177; //middle
	
	// Enable compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	// Set PWM port as output
	DDRB = (1 << PB5);
}

void SERVO_write(position_t pos)
{
	const uint8_t min = 225;
	const uint8_t max = 525;
	const uint8_t delta = max-min;
	uint8_t ref = pos.y * delta/255;
	uint8_t new_pos = min + ref;
	
	// Update compare register
	//printf("new_pos: %d\n", new_pos);
	OCR1A = new_pos;
}

/* Interrupt handler for TIMER1 compare */
ISR(TIMER1_COMPA_vect) {

	// pin toggle
	PORTB ^= (1 << PB5);
}