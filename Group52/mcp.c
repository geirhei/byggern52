/*
 * mcp.c
 *
 * Created: 09.10.2015 15:56:14
 *  Author: chengbid
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "mcp.h"

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

char MCP_read(char addr)
{
	PORTB &= ~(1 << PB4);
	SPI_master_transmit(0x03);
	SPI_master_transmit(addr);
	SPI_master_transmit(0x00);
	char data = SPDR;
	PORTB |= (1 << PB4);
	return data;
}

void MCP_write(char addr, char data)
{
	PORTB &= ~(1 << PB4);
	SPI_master_transmit(0x02);
	SPI_master_transmit(addr);
	SPI_master_transmit(data);
	PORTB |= (1 << PB4);
}

/*
void MCP_load_tx_buffer(char buffer, char data)
{
	char address = 
}
*/

void MCP_request_to_send(void)
{
	char command = 0b10000000;
	//command = (1 << 1);
	PORTB &= ~(1 << PB4);
	SPI_master_transmit(command);
	PORTB |= (1 << PB4);
}

char MCP_read_status(void)
{
	PORTB &= ~(1 << PB4);
	SPI_master_transmit(0xA0);
	char status = SPI_master_read();
	PORTB |= (1 << PB4);
	return status;
}

void MCP_set_mode(OperatingMode mode)
{
	char mask = 0b11100000;
	char data = 0b00000000;
	switch (mode) {
		case NORMAL:
			break;
		case CONFIGURATION:
			data = 0b10000000;
			break;
		case SLEEP:
			data = 0b00100000;
			break;
		case LISTEN:
			data = 0b01100000;
			break;
		case LOOPBACK:
			data = 0b01000000;
			break;
		default:
			break;
	}
	MCP_modify_bit(CANCTRL, mask, data);
}


void MCP_modify_bit(char addr, char mask, char data)
{
	PORTB &= ~(1 << PB4);
	SPI_master_transmit(0x05);
	SPI_master_transmit(addr);
	SPI_master_transmit(mask);
	SPI_master_transmit(data);
	PORTB |= (1 << PB4);
}


/*
void MCP_modify_bit(char addr, char bit, char value)
{
	PORTB &= ~(1 << PB4);
	SPI_master_transmit(0x05);
	SPI_master_transmit(addr);
	char mask = (1 << bit);
	SPI_master_transmit(mask);
	char data = 0;
	data ^= (-value ^ data) & (1 << bit);
	PORTB |= (1 << PB4);
}
*/