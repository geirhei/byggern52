/*
 * ir.c
 *
 * Created: 13.11.2015 14:09:37
 *  Author: chengbid
 */ 

#include "ir.h"

#include <avr/io.h>
#include <avr/delay.h>

void IR_init(void)
{
	// 16Mhz/128 = 125kHZ for ADC reference clock
	// Enable ADC, set ADC prescaler = 128
	ADCSRA |= (1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);
	
	// Set voltage reference to Avcc (5V), set left adjusted
	ADMUX |= (1 << REFS0)|(1 << ADLAR);
	
	// Turn on ADC
	ADCSRA |= (1 << ADEN);

	// Set channel ADC0
	ADCSRB |= (1 << MUX5);
	
	// Do an initial conversion
	ADCSRA |= (1 << ADSC);
	
	// Set ADC0 pin as input - necessary?
	//DDRF &= ~(1 << PF0);
	
}

uint8_t IR_read(void)
{
	// Set channel ADC0
	ADCSRB |= (1 << MUX5);

	ADCSRA |= (1 << ADSC); // Start conversion
	
	while (ADCSRA & (1 << ADSC)); // Wait until conversion is done
	return ADCH; // Return ADC value from high register
}