/*
 * mcp.h
 *
 * Created: 09.10.2015 15:56:23
 *  Author: chengbid
 */ 


#ifndef MCP_H_
#define MCP_H_

	void MCP_init(void);
	void MCP_reset(void);
	char MCP_read(char addr);
	void MCP_write(char addr, char data);
	char MCP_read_status(void);
	void MCP_set_mode(uint8_t mode);
	void MCP_modify_bit(char addr, char mask, char data);
	void MCP_request_to_send(char buffer);
	char MCP_read_rx_buffer(char buffer);
	void MCP_load_tx_buffer(char buffer, char data);
	char MCP_rx_status(void);
	

#endif /* MCP_H_ */