/*
 * joystick.c
 *
 * Created: 18.09.2015 15:28:18
 *  Author: chengbid
 */ 

#include "joystick.h"
#include <avr/io.h>
#include <util/delay.h>

position joystick_Get_Position(void)
{
	volatile char *adc = (char *) 0x1500;
	/* Select CH1 */
	adc[0] = 0b00000100;
	_delay_us(70);
	uint8_t xValue = adc[0];
	
	/* Select CH2 */
	adc[0] = 0b00000101;
	_delay_us(70);
	uint8_t yValue = adc[0];
	
	int8_t xPosition;
	int8_t yPosition;
	int8_t foo;
	
	if (xValue < 128) {
		foo = 128 - xValue;
		printf("%i\n", xValue);
		xPosition = (128 - xValue) / 128 * 100;
		
	} else if (xValue >= 128) {
		xPosition = (xValue - 128) / 128 * 100;
	}
	
	if (yValue < 128) {
		yPosition = (128 - yValue) / 128 * 100;
	} else if (yValue >= 128) {
		yPosition = (yValue - 128) / 128 * 100;
	}
	
	position pos;
	pos.stick_positions[0] = xPosition;
	pos.stick_positions[1] = yPosition;
	return pos;
}