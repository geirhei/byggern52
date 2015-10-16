/*
 * mcp.h
 *
 * Created: 09.10.2015 15:56:23
 *  Author: chengbid
 */ 


#ifndef MCP_H_
#define MCP_H_

typedef enum {
	CONFIGURATION = 1,
	NORMAL = 2,
	SLEEP = 3,
	LISTEN = 4,
	LOOPBACK = 5
	} OperatingMode;
	
	
	void MCP_init(void);
	void MCP_reset(void);
	char MCP_read(char addr);
	void MCP_write(char addr, char data);
	char MCP_read_status(void);
	void MCP_set_mode(OperatingMode mode);
	void MCP_modify_bit(char addr, char mask, char data);
	void MCP_request_to_send(void);
	
/* Register bit definitions */

// CANCTRL - CAN control register
#define CANCTRL 0xF
#define CLKPRE0 0
#define CLKPRE1 1
#define CLKEN	2
#define OSM		3
#define ABAT	4
#define REQOP0	5
#define REQOP1	6
#define REQOP2	7

// CANSTAT - CAN status register
#define CANSTAT 0xE
#define ICOD0	1
#define ICOD1	2
#define ICOD2	3
#define OPMOD0	5
#define OPMOD1	6
#define OPMOD2	7


#endif /* MCP_H_ */