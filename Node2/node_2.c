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

#include "servo.h"
#include "usart_2.h"
#include "can.h"
#include "ir.h"
#include "motor.h"

int main(void)
{
	sei(); // Enable global interrupts
	
	SERVO_init();
	fdevopen(USART_transmit, USART_receive); // Sets printf to serial port
	USART_init(MYUBBR);
	CAN_init();
	IR_init();
	MOTOR_init();
	
	uint8_t status, msg_arrived;
	can_message_t received_message, new_msg;
	uint8_t ir = IR_read();
	int16_t pos_test;
	
	while(1) {

		status = MCP_read_status();
		msg_arrived = (status & 1);
		if (msg_arrived) {
			received_message = CAN_message_receive();
			CAN_message_handle(received_message);
		} else {
			//printf("%s\n", "No message in buffer");
		}
		
		// MOTOR POSITION TEST
		/*
		MOTOR_dir_set(LEFT);
		MOTOR_speed_set(100);
		MOTOR_pos_read();
		printf("Motor position: %d\n", pos_test);
		*/
		
		// CAN SEND TEST
		/*
		new_msg.id = 5;
		new_msg.length = 2;
		new_msg.data[0] = 0;
		new_msg.data[1] = 1;
		CAN_message_send(&new_msg);
		*/
		
		// IR TEST
		/*
		ir = IR_read();
		//printf("IR: %d\n", ir);
		if (ir < 20)
			printf("Goal!\n");
		*/
		
	}
	
	return 0;
}