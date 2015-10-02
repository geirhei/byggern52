/*
 * oled.c
 *
 * Created: 02.10.2015 12:50:51
 *  Author: chengbid
 */ 

#include "oled.h"
#include "font.h"
#include <util/delay.h>
#include <avr/pgmspace.h>

	
void oled_init(void)
{
	oled_write_c(0xae); // display off
	oled_write_c(0xa1); //segment remap
	oled_write_c(0xda); //common pads hardware: alternative
	oled_write_c(0x12);
	oled_write_c(0xc8); //common output scan direction:com63~com0
	oled_write_c(0xa8); //multiplex ration mode:63
	oled_write_c(0x3f);
	oled_write_c(0xd5); //display divide ratio/osc. freq. mode
	oled_write_c(0x80);
	oled_write_c(0x81); //contrast control
	oled_write_c(0x50);
	oled_write_c(0xd9); //set pre-charge period
	oled_write_c(0x21);
	oled_write_c(0x20); //Set Memory Addressing Mode
	oled_write_c(0x00); // Horizontal
	oled_write_c(0xdb); //VCOM deselect level mode
	oled_write_c(0x30);
	oled_write_c(0xad); //master configuration
	oled_write_c(0x00);
	oled_write_c(0xa4); //out follows RAM content
	oled_write_c(0xa6); //set normal display
	oled_write_c(0xaf); // display on
	
	for (int i = 0; i < 1028; i++)
	{
		oled_write_d(0x00);
	}
}


void oled_write_c(char chr)
{
	volatile char *oled = (char *) 0x1000;
	oled[0] = chr;
}

void oled_write_d(char chr)
{
	volatile char *oled = (char *) 0x1200;
	oled[0] = chr;
}

int8_t oled_read_status(void)
{
	volatile char *oled = (char *) 0x1000;
	return oled[0];
}

/* Prints a single character to the given display address */
void oled_print_character(uint8_t number, uint8_t address)
{
	uint8_t c;
	for (int i = 0; i < 4; i++) {
		c = pgm_read_byte_near(font + (number * 4) + i);
	
	}
}