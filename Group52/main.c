/*
 * Group52.c
 *
 * Created: 28.08.2015 10:15:40
 *  Author: geirhei
 */ 

#define F_CPU 4915200
/* Macros for bit manipulation */
#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) )

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>

#include "usart.h"
#include "joystick.h"
#include "adc.h"
#include "oled.h"
#include "can.h"

void blink();
void SRAM_test(void);
void SRAM_test2(void);


int main(void)
{
	/* Needs to be set when using external memory */
	MCUCR |= (1 << SRE);

	fdevopen(USART_transmit, USART_receive);
	USART_init(MYUBBR);
	OLED_init();
	JOYSTICK_init();
	SPI_master_init();
	CAN_init();
	
	OLED_reset();
	OLED_pos(2,20);
	
	menuNode *menu = OLED_generate_menu();
	OLED_print_menu(menu);
	
	uint8_t currentRow = 1;
	uint8_t lastRow = 0;
	DirectionType joydir = NEUTRAL;
	uint8_t buttonPressed = 0;
	
	/* MCP TEST */
	
	char status = MCP_read(MCP_CANCTRL);
	printf("CANCTRL: %02x\n", status);
	
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
	CAN_message_send(&can_message);
	
	uint8_t RXB0CTRL = MCP_read(MCP_RXB0CTRL);
	printf("RXB0CTRL: %02x\n", RXB0CTRL);
	
	can_message_t received_message = CAN_message_receive();
	//uint8_t received_data[8];
	//memcpy(received_data, received_message.data, 8);
	
	printf("ID: %02x\n", received_message.id);
	printf("length: %02x\n", received_message.length);
	for (uint8_t i = 0; i < received_message.length; i++) {
		printf("Received: %02x\n", received_message.data[i]);
	}
	
	
	
	printf("\n");

	
	/* MCP TEST END */
	
	can_message_t joydata;
	can_message_t joydata_received;
	
	while(1)
	{	
		
				
		/* Create seperate function for this */
		joydir = JOYSTICK_get_direction();
		
		joydata.id = 1;
		joydata.length = 2;
		joydata.data[0] = (uint8_t) 'J';
		joydata.data[1] = joydir;
		
		CAN_message_send(&joydata);
		
		lastRow = currentRow;
		if (joydir == UP) {
			if (currentRow == 1) {
				currentRow = 7;
			} else {
				currentRow -= 1;
			}
			
		} else if (joydir == DOWN) {
			if (currentRow == 7) {
				currentRow = 1;
			} else {
				currentRow += 1;
			}
		}
		
		OLED_move_arrow(currentRow, 20, lastRow, 20);
		buttonPressed = JOYSTICK_read_button();
	
		if (buttonPressed) {
			menu = menu->children[currentRow];
		}
		
		
		joydata_received = CAN_message_receive();
		for (uint8_t i = 0; i < received_message.length; i++) {
			printf("Received: %02x\n", received_message.data[i]);
		}
	}
	
	return 0;
}

/* Makes LED blink when called */
void blink()
{
	PORTC ^= (1 << PINC1);
	_delay_ms(300);
}