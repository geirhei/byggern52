/*
 * Node2.c
 *
 * Created: 06.11.2015 09:17:29
 *  Author: geirhei
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>

#include "usart.h"
#include "can.h"

int main(void)
{
	fdevopen(USART_transmit, USART_receive);
	USART_init(MYUBRR);
	CAN_init();
	
	while(1)
	{
		uint8_t status = MCP_read(MCP_CANCTRL);
		printf("CANCTRL: %02x\n", status);
		_delay_ms(500);
		
		/* CAN test begin */
		
		
		
		can_message_t received_message = CAN_message_receive();
		printf("ID: %02x\n", received_message.id);
		printf("length: %02x\n", received_message.length);
		for (uint8_t i = 0; i < received_message.length; i++) {
			printf("Received: %02x\n", received_message.data[i]);
		}
		
		/* CAN test end */
	}

}