/*
 * joystick.c
 *
 * Created: 18.09.2015 15:28:18
 *  Author: chengbid
 */ 

#define F_CPU 4915200
#include "joystick.h"
#include "adc.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "math.h"

void joystick_Calibrate(void)
{
	
}

struct positions joystick_Get_Position(void)
{
	int16_t yValue = (int16_t) adc_Read(JOYAXIS1);
	int16_t xValue = (int16_t) adc_Read(JOYAXIS2);
	
	int16_t xPosition = toPositionPercent(xValue);
	int16_t yPosition = toPositionPercent(yValue);
	//printf("%i\n", xPosition);
	//printf("%i\n", yPosition);
	
	struct positions pos;
	pos.x = xPosition;
	pos.y = yPosition;
	
	return pos;
}


DirectionType joystick_Get_Direction(void)
{
	struct positions pos = joystick_Get_Position();
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

struct positions sliders_Get_Positions(void)
{
	int16_t lValue = adc_Read(LSLIDER);
	int16_t rValue = adc_Read(RSLIDER);
	_delay_ms(50);
	
	printf("%i\n", lValue);
	//printf("%i\n", rValue);
	
	int16_t lPosition = toPositionPercent(lValue);
	int16_t rPosition = toPositionPercent(rValue);
	
	struct positions pos;
	pos.l = lPosition;
	pos.r = rPosition;
	
	return pos;
}