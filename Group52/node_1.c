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


int main(void)
{
	/* Needs to be set when using external memory */
	MCUCR |= (1 << SRE);

	fdevopen(USART_transmit, USART_receive); // Sets printf to serial port
	USART_init(MYUBBR);
	OLED_init();
	JOYSTICK_init();
	CAN_init();
	
	OLED_reset();
	OLED_pos(2,20);
	
	menuNode *menu = OLED_generate_menu();
	OLED_print_menu(menu);
	
	uint8_t currentRow = 1;
	uint8_t lastRow = 0;
	Direction joydir = NEUTRAL;
	uint8_t buttonPressed = 0;
	
	/* MCP TEST */
	
	uint8_t status = MCP_read(MCP_CANCTRL);
	//printf("CANCTRL: %02x\n", status);
	
	uint8_t RXB0CTRL = MCP_read(MCP_RXB0CTRL);
	//printf("RXB0CTRL: %02x\n", RXB0CTRL);
	
	while(1)
	{	
		//CAN_message_send(&can_message);
		JOYSTICK_send_position();
		
		
		/* Create seperate function for this */
		/*
		position_t position = JOYSTICK_get_position();
		joydir = JOYSTICK_get_direction(position);
		
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
		*/
		//_delay_ms(50);
	}
	
	return 0;
}

/* Makes LED blink when called */
void blink()
{
	PORTC ^= (1 << PINC1);
	_delay_ms(300);
}