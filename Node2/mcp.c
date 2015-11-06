/*
 * mcp.c
 *
 * Created: 09.10.2015 15:56:14
 *  Author: chengbid
 
	Port configuration for NODE 2
 
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "MCP2515.h"
#include "mcp.h"

void MCP_init(void)
{
	SPI_master_init();
	MCP_reset();
	
	MCP_modify_bit(MCP_RXB0CTRL, 0b01100000, 0xFF); // Turns masks/filters off for RX0
	MCP_modify_bit(MCP_RXB1CTRL, 0b01100000, 0xFF); // Turns masks/filters off for RX1
	//MCP_set_mode(MODE_LOOPBACK); // Sets loopback operation mode for testing
	MCP_set_mode(MODE_NORMAL); // Sets normal operation mode
}

void MCP_reset(void)
{
	PORTB &= ~(1 << PB0);
	SPI_master_transmit(MCP_RESET);
	PORTB |= (1 << PB0);
}

/* Returns the content of a register */
uint8_t MCP_read(uint8_t addr)
{
	PORTB &= ~(1 << PB0);
	SPI_master_transmit(MCP_READ);
	SPI_master_transmit(addr);
	SPI_master_transmit(0x00);
	char data = SPDR;
	PORTB |= (1 << PB0);
	return data;
}

void MCP_write(uint8_t addr, uint8_t data)
{
	PORTB &= ~(1 << PB0);
	SPI_master_transmit(MCP_WRITE);
	SPI_master_transmit(addr);
	SPI_master_transmit(data);
	PORTB |= (1 << PB0);
}

/* Returns the content of the specified buffer. Reduces overhead of MCP_read */
uint8_t MCP_read_rx_buffer(uint8_t buffer)
{
	PORTB &= ~(1 << PB0);
	SPI_master_transmit(buffer);
	SPI_master_transmit(0x00);
	char data = SPDR;
	PORTB |= (1 << PB0);
	return data;
}

/* Loads the specified transmit buffer with data. Reduces overhead of MCP_write */
void MCP_load_tx_buffer(uint8_t buffer, uint8_t data)
{
	PORTB &= ~(1 << PB0);
	SPI_master_transmit(buffer);
	SPI_master_transmit(data);
	PORTB |= (1 << PB0);
}

/* Instructs controller to begin message transmission for the selected buffers */
void MCP_request_to_send(uint8_t buffer)
{
	PORTB &= ~(1 << PB0);
	SPI_master_transmit(buffer);
	PORTB |= (1 << PB0);
}

/* Returns some status bits for transmit and receive functions */
uint8_t MCP_read_status(void)
{
	PORTB &= ~(1 << PB0);
	SPI_master_transmit(MCP_READ_STATUS);
	SPI_master_transmit(0x00); // Unneccessary because of "repeat data out"?
	char status = SPDR;
	PORTB |= (1 << PB0);
	return status;
}

/* Returns info about whether a message is in the receive buffer(s), message type and filter match */
uint8_t MCP_rx_status(void)
{
	PORTB &= ~(1 << PB0);
	SPI_master_transmit(MCP_RX_STATUS);
	//SPI_master_transmit(0x00); // Unneccessary because of "repeat data out"?
	char status = SPDR;
	PORTB |= (1 << PB0);
	return status;
}

/* Set MCP mode of operation */
void MCP_set_mode(uint8_t mode)
{
	uint8_t mask = 0b11100000;
	
	uint8_t data = 0b00000000;
	switch (mode) {
		case MODE_NORMAL:
			break;
		case MODE_CONFIG:
			break;
		case MODE_SLEEP:
			data = 0b00100000;
			break;
		case MODE_LISTENONLY:
			data = 0b01100000;
			break;
		case MODE_LOOPBACK:
			data = 0b01000000;
			break;
		default:
			break;
	}
	
	MCP_modify_bit(MCP_CANCTRL, mask, mode);
}

/* Changes the value of the register bits specified by the mask */
void MCP_modify_bit(uint8_t addr, uint8_t mask, uint8_t data)
{
	PORTB &= ~(1 << PB0);
	SPI_master_transmit(MCP_BITMOD);
	SPI_master_transmit(addr);
	SPI_master_transmit(mask);
	SPI_master_transmit(data);
	PORTB |= (1 << PB0);
}