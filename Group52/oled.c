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

	
void OLED_init(void)
{
	OLED_write_c(0xae); // display off
	OLED_write_c(0xa1); //segment remap
	OLED_write_c(0xda); //common pads hardware: alternative
	OLED_write_c(0x12);
	OLED_write_c(0xc8); //common output scan direction:com63~com0
	OLED_write_c(0xa8); //multiplex ration mode:63
	OLED_write_c(0x3f);
	OLED_write_c(0xd5); //display divide ratio/osc. freq. mode
	OLED_write_c(0x80);
	OLED_write_c(0x81); //contrast control
	OLED_write_c(0x50);
	OLED_write_c(0xd9); //set pre-charge period
	OLED_write_c(0x21);
	OLED_write_c(0x20); //Set Memory Addressing Mode
	OLED_write_c(0x00); //Horizontal mode
	OLED_write_c(0xdb); //VCOM deselect level mode
	OLED_write_c(0x30);
	OLED_write_c(0xad); //master configuration
	OLED_write_c(0x00);
	OLED_write_c(0xa4); //out follows RAM content
	OLED_write_c(0xa6); //set normal display
	OLED_write_c(0xaf); // display on
	
	for (int i = 0; i < 512; i++)
	{
		OLED_write_d(0xFF);
	}
}


void OLED_write_c(char chr)
{
	volatile char *oled = (char *) 0x1000;
	oled[0] = chr;
}

void OLED_write_d(char chr)
{
	volatile char *oled = (char *) 0x1200;
	oled[0] = chr;
}

int8_t OLED_read_status(void)
{
	volatile char *oled = (char *) 0x1000;
	return oled[0];
}

/* Prints a single character to the given display address */
void OLED_print(char c)
{
	uint8_t c;
	for (int i = 0; i < 4; i++) {
		c = pgm_read_byte_near(font + (number * 4) + i);
		OLED_write_c(c);
	}
}

void OLED_home(void)
{
	OLED_pos(0,0);
	// Should this just go to start of line, not (0,0)?
}

void OLED_goto_line(uint8_t line)
{
	/* Set page address */
	OLED_write_c(0x22);
	OLED_write_c(line);
	OLED_write_c(0x07);
}

void OLED_clear_line(uint8_t line)
{
	OLED_goto_line(line);

	/* Set column start and end address */
	OLED_write_c(0x21);
	OLED_write_c(0x00);
	OLED_write_c(0x7F);

	/* Write zeros to line */
	for (int i = 0; i < 128; i++) {
		OLED_write_d(0x00);
	}
}

void OLED_pos(uint8_t row, uint8_t column)
{
	/* Set page address */
	OLED_write_c(0x22);
	OLED_write_c(row);
	OLED_write_c(0x07);

	/* Set column start and end address */
	OLED_write_c(0x21);
	OLED_write_c(column);
	OLED_write_c(0x7F);
}

void OLED_reset(void)
{
	for (int i = 0; i < 8; i++) {
		OLED_clear_line(i);
	}
	OLED_pos(0,0);

	// Redraw from SRAM?
}