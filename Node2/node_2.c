/*
 * Node2.c
 *
 * Created: 06.11.2015 09:17:29
 *  Author: geirhei
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>

#include "usart_2.h"
#include "can.h"
#include "servo.h"



int main(void)
{
	sei(); // Enable global interrupts
	
	timer1_init(); // initialize timer
	fdevopen(USART_transmit, USART_receive); // Sets printf to serial port
	USART_init(MYUBBR);
	CAN_init();
	
	uint8_t status, msg_arrived;
	can_message_t received_message;
	
	while(1) {	
		
		status = MCP_read_status();
		//printf("Status: %02x\n", status);
		msg_arrived = (status & 1);
		if (msg_arrived) {
			received_message = CAN_message_receive();
			CAN_message_handle(received_message);
		} else {
			//printf("%s\n", "No message in buffer");
		}
		
		_delay_ms(50);
	}
	
	return 0;
}