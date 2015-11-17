/*
 * can.c
 *
 * Created: 21.10.2015 11:52:02
 *  Author: geirhei
 */ 

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
	while (TXREQ) {
		status = MCP_read_status();
		TXREQ = (status & (1 << 2));
	}
	
	/* Set message ID, standard mode*/
	MCP_write(MCP_TXB0CTRL + 1, 0); // High level identifier
	MCP_write(MCP_TXB0CTRL + 2, (msg->id << 5)); // Low level identifier
	
	/* Set data length */
	MCP_write(MCP_TXB0CTRL + 5, msg->length & 0x0F);
	
	/* Load message data */
	for (uint8_t i = 0; i < msg->length; i++) {
		MCP_write(MCP_TXB0CTRL + 6 + i, msg->data[i]);
	}
	
	/* Request to send contents of TXB0 */
	MCP_request_to_send(MCP_RTS_TX0);
}

can_message_t CAN_message_receive(void)
{
	/* Only RXB0 is used */
	
	can_message_t message;
	uint8_t buffer = MCP_read(MCP_RXB0SIDH + 1);
	message.id = (buffer >> 5);
	buffer = MCP_read(MCP_RXB0CTRL + 5);
	message.length = (buffer & 0x0F);
	for (uint8_t i = 0; i < message.length; i++) {
		message.data[i] = MCP_read(MCP_RXB0CTRL + 6 + i);
	}
	
	/* Clear CANINTF.RX0IF */
	MCP_modify_bit(MCP_CANINTF, 0x01, 0x00);
	
	return message;
}

/* Processes a received CAN-message */
void CAN_message_handle(can_message_t msg)
{
	//printf("Message handle entered\n");
	uint8_t msg_type = msg.data[0];
	//printf("msg_type: %i\n", msg_type);
	position_t received_pos;
	switch (msg_type) {
		case 'j':
			//printf("Case 'j' entered\n");
			received_pos.x = msg.data[2]; // Movite into servo_write
			received_pos.y = msg.data[3];
			//printf("received_pos.x: %d\n", received_pos.x);
			//printf("received_pos.y: %d\n", received_pos.y);
			
			SERVO_write(received_pos);
			MOTOR_write(msg);
			break;
		default:
			break;
	}
}