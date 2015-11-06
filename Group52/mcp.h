/*
 * mcp.h
 *
 * Created: 09.10.2015 15:56:23
 *  Author: chengbid
 */ 

#ifndef MCP_H_
#define MCP_H_

	#include <avr/io.h>
	#include "spi.h"

	void MCP_init(void);
	void MCP_reset(void);
	uint8_t MCP_read(uint8_t addr);
	void MCP_write(uint8_t addr, uint8_t data);
	uint8_t MCP_read_status(void);
	void MCP_set_mode(uint8_t mode);
	void MCP_modify_bit(uint8_t addr, uint8_t mask, uint8_t data);
	void MCP_request_to_send(uint8_t buffer);
	uint8_t MCP_read_rx_buffer(uint8_t buffer);
	void MCP_load_tx_buffer(uint8_t buffer, uint8_t data);
	uint8_t MCP_rx_status(void);
	

#endif /* MCP_H_ */