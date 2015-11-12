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
	
	// initialize compare value (servo to middle, 206)
	//OCR1A = 0x00CE;
	OCR1A = 0x020D; //max
	
	// Enable compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	// Set PWM port as output
	DDRB = (1 << PB5);
}

/*
void timer1_init(void)
{
	uint8_t duty_cyc;
	
	// Set PWM port as output 
	DDRB = (1 << PB5);
	
	// f_PWM = F_CPU / (1250 * 256) CORRECT?
	TCCR1A = 0b10001010; //Set TIMER1 register to Fast PWM 8 bit, Clear OCRA0 on compare match, SET on top
	TCNT1 = 0; // Reset TCNT0
	OCR1A = 0; // Initialize output compare register
	
}
*/

void SERVO_write(position_t pos)
{
	// Update compare register
	OCR1A = 0x0600;
}

/* Interrupt handler for TIMER1 compare */
ISR(TIMER1_COMPA_vect) {

	// pin toggle
	PORTB ^= (1 << PB5);
}