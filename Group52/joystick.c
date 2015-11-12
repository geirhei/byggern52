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

position_t JOYSTICK_get_position(void)
{
	uint8_t x_value = adc_read(JOYAXIS2);
	uint8_t y_value = adc_read(JOYAXIS1);
	
	position_t position;
	position.x = x_value;
	position.y = y_value;
	return position;
}

Direction JOYSTICK_get_direction(position_t pos)
{
	const uint8_t THRESHOLD = 64;
	
	if (pos.y < 127+THRESHOLD && pos.y > 127-THRESHOLD) {
		if (pos.x < 127-THRESHOLD) {
			return LEFT;
		} else if (pos.x > 127+THRESHOLD) {
			return RIGHT;
		}
		
	} else if (pos.x < 127+THRESHOLD && pos.x > 127-THRESHOLD) {
		if (pos.y < 127-THRESHOLD) {
			return DOWN;
		} else if (pos.y > 127+THRESHOLD) {
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

position_t SLIDERS_get_positions(void)
{
	uint8_t l_value = adc_read(LSLIDER);
	uint8_t r_value = adc_read(RSLIDER);
	_delay_ms(50);
	
	position_t pos;
	pos.l = l_value;
	pos.r = r_value;
	return pos;
}

uint8_t JOYSTICK_read_button(void)
{
	return (PINB & (1 << PB2)) == 0;
}

/* Sends a message containing position values 0-255 for joystick and sliders, and direction
	over the CAN bus.*/
void JOYSTICK_send_position(void)
{
	position_t joypos = JOYSTICK_get_position();
	Direction joydir = JOYSTICK_get_direction(joypos);
	position_t sliderpos = SLIDERS_get_positions();
	
	can_message_t can_message;
	can_message.data[0] = 'j';
	can_message.data[1] = joydir;
	can_message.data[2] = joypos.x;
	can_message.data[3] = joypos.y;
	can_message.data[4] = sliderpos.l;
	can_message.data[5] = sliderpos.r;
	can_message.length = 6;
	can_message.id = 1;
	
	printf("msg_type: %i\n", can_message.data[0]);
	CAN_message_send(&can_message);
}