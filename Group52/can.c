/*
 * can.c
 *
 * Created: 21.10.2015 11:52:02
 *  Author: geirhei
 */ 

#include "mcp.h"
#include "MCP2515.h"
#include "can.h"

void CAN_init(void)
{
	MCP_init();
}

/* High level function for sending a message on the CAN bus */
void CAN_message_send(can_message_t* msg)
{
	/* Only transmit buffer TXB0 is used */
	
	/* Loop until TXREQ is cleared */
	uint8_t status = MCP_read_status();
	uint8_t TXREQ = (status & (1 << 2));
	//printf("TXREQ: %02x\n", TXREQ);
	while (TXREQ) {
		status = MCP_read_status();
		TXREQ = (status & (1 << 2));
	}
	
	/* Set message ID, standard mode*/
	MCP_write(MCP_TXB0CTRL + 2, 0); // High level identifier
	MCP_write(MCP_TXB0CTRL + 3, (msg->id << 5)); // Low level identifier
	//printf("msgid: %02x\n", value);
	
	/* Set data length */
	MCP_write(MCP_TXB0CTRL + 6, msg->length);
	
	/* Load message data */
	for (uint8_t i = 0; i < msg->length; i++) {
		MCP_write(MCP_TXB0CTRL + 7 + i, msg->data[i]);
	}
	
	/* Request to send contents of TXB0 */
	MCP_request_to_send(MCP_RTS_TX0);
}