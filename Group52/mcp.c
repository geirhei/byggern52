/*
 * mcp.c
 *
 * Created: 09.10.2015 15:56:14
 *  Author: chengbid
 */ 

#include <avr/io.h>

void MCP_init(void)
{
	MCP_reset();
}

void MCP_reset(void)
{
	PORTB &= ~(1 << PB4);
	SPI_master_transmit(0xC0);
	PORTB |= (1 << PB4);
}

void MCP_read(char addr)
{
	PORTB &= ~(1 << PB4);
	SPI_master_transmit(0x03);
	SPI_master_transmit(addr);
	PORTB |= (1 << PB4);
}

void MCP_write(char addr, char data)
{
	PORTB &= ~(1 << PB4);
	SPI_master_transmit(0x02);
	SPI_master_transmit(addr);
	SPI_master_transmit(data);
	PORTB |= (1 << PB4);
}

char MCP_read_status(void)
{
	PORTB &= ~(1 << PB4);
	char status = SPI_master_transmit(0xA0);
	PORTB |= (1 << PB4);
	return status;
}

void MCP_set_mode(char mode)
{
	
}

