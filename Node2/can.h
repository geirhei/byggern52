/*
 * can.h
 *
 * Created: 21.10.2015 11:52:14
 *  Author: geirhei
 */ 


#ifndef CAN_H_
#define CAN_H_

#include "MCP2515.h"
#include "mcp_2.h"
#include "servo.h"

typedef struct {
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
	} can_message_t;

void CAN_init(void);
void CAN_message_send(can_message_t* msg);
can_message_t CAN_message_receive(void);
void CAN_message_handle(can_message_t msg);



#endif /* CAN_H_ */