/*
 * can.h
 *
 * Created: 21.10.2015 11:52:14
 *  Author: geirhei
 */ 


#ifndef CAN_H_
#define CAN_H_

typedef struct {
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
	} can_message_t;

void CAN_init(void);
void CAN_message_send(can_message_t* msg);



#endif /* CAN_H_ */