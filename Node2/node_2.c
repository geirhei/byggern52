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
	//CAN_init();
	
	position_t pos_test;
	pos_test.y = 100;
	//SERVO_write(pos_test);
	
	uint8_t status, msg_arrived;
	can_message_t received_message;
	can_message_t can_message;
	can_message.data[0] = 0x01;
	can_message.data[1] = 0x02;
	can_message.data[2] = 0x03;
	can_message.data[3] = 0x04;
	can_message.data[4] = 0x05;
	can_message.data[5] = 0x06;
	can_message.data[6] = 0x07;
	can_message.data[7] = 0x08;
	can_message.length = 8;
	can_message.id = 2;
	
	while(1) {	
		
		
		/* CAN test begin */
		//CAN_message_send(&can_message);
		
		/*
		status = MCP_read_status();
		printf("Status: %02x\n", status);
		msg_arrived = (status & 1);
		if (msg_arrived) {
			received_message = CAN_message_receive();
			printf("ID: %02x\n", received_message.id);
			printf("length: %02x\n", received_message.length);
			printf("Message type: %s\n", received_message.data[0]);
			printf("Direction: %i\n", received_message.data[1]);
			printf("X: %i\n", received_message.data[2]);
			printf("Y: %i\n", received_message.data[3]);
			printf("Slider l: %i\n", received_message.data[4]);
			printf("Slider r: %i\n", received_message.data[5]);
			
			/*
			for (uint8_t i = 0; i < received_message.length; i++) {
				printf("Received: %02x\n", received_message.data[i]);
			}
			*/
			/*
		} else {
			printf("%s\n", "No message in buffer");
		}
		
		
		/* CAN test end */
		_delay_ms(500);
	}
	
	return 0;
}