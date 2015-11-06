/*
 * joystick.c
 *
 * Created: 18.09.2015 15:28:18
 *  Author: chengbid
 */ 

#define F_CPU 4915200
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "math.h"
#include "joystick.h"
#include "adc.h"
#include "can.h"

void JOYSTICK_init(void)
{
	/* Set PB2 as input for button*/
	DDRB &= ~(1 << PB2);
	PORTB &= (1 << PB2);
	
}

void JOYSTICK_calibrate(void)
{
	
}

PositionsType JOYSTICK_get_position(void)
{
	int16_t yValue = (int16_t) adc_read(JOYAXIS1);
	int16_t xValue = (int16_t) adc_read(JOYAXIS2);
	
	printf("%i\n", yValue);
	
	int16_t xPosition = toPositionPercent(xValue);
	int16_t yPosition = toPositionPercent(yValue);
	
	PositionsType pos;
	pos.x = xPosition;
	pos.y = yPosition;
	
	return pos;
}


DirectionType JOYSTICK_get_direction(void)
{
	PositionsType pos = JOYSTICK_get_position();
	int8_t THRESHOLD = 25;
	
	if (pos.y < THRESHOLD && pos.y > -THRESHOLD) {
		
		if (pos.x < -THRESHOLD) {
			return LEFT;
		} else if (pos.x > THRESHOLD) {
			return RIGHT;
		}
		
	} else if (pos.x < THRESHOLD && pos.x > -THRESHOLD) {
		
		if (pos.y < -THRESHOLD) {
			return DOWN;
		} else if (pos.y > THRESHOLD) {
			return UP;
		}
		
	}
	
	return NEUTRAL;
}

int16_t toPositionPercent(int16_t value)
{
	value -= 127;
	int16_t percentValue = round((float)value / 127 * 100);
	return percentValue;
}

PositionsType SLIDERS_get_positions(void)
{
	int16_t lValue = adc_read(LSLIDER);
	int16_t rValue = adc_read(RSLIDER);
	_delay_ms(50);
	
	//printf("%i\n", lValue);
	//printf("%i\n", rValue);
	
	int16_t lPosition = toPositionPercent(lValue);
	int16_t rPosition = toPositionPercent(rValue);
	
	PositionsType pos;
	pos.l = lPosition;
	pos.r = rPosition;
	
	return pos;
}

uint8_t JOYSTICK_read_button(void)
{
	return (PINB & (1 << PB2)) == 0;
}

/* Sends a message containing position values in percentage for joystick and sliders, and direction
	over the CAN bus.*/
void JOYSTICK_send_position(void)
{
	DirectionType joydir = JOYSTICK_get_direction();
	PositionsType joypos = JOYSTICK_get_position();
	PositionsType sliderpos = SLIDERS_get_positions();
	
	can_message_t can_message;
	can_message.data[0] = joydir;
	can_message.data[1] = joypos.x;
	can_message.data[2] = joypos.y;
	can_message.data[3] = sliderpos.l;
	can_message.data[4] = sliderpos.r;
	can_message.length = 5;
	can_message.id = 1;
	
	
	CAN_message_send(&can_message);
}