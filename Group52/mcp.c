/*
 * mcp.c
 *
 * Created: 09.10.2015 15:56:14
 *  Author: chengbid
 */ 

#include <avr/io.h>

char MCP_read(void)
{
	/* Set CS low */
	DDRD &= ~(1 << PB4);
	SPI_master_transmit(0x03);
	
	
	/* Set CS high */
	DDRD = (1 << PB4);
}