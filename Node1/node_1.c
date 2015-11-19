/*
 * Group52.c
 *
 * Created: 28.08.2015 10:15:40
 *  Author: geirhei
 *
 *	Main function for Node 1
 */ 

#define F_CPU 4915200

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>

#include "usart.h"
#include "joystick.h"
#include "adc.h"
#include "oled.h"
#include "can.h"

int main(void)
{
	/* Needs to be set when using external memory */
	MCUCR |= (1 << SRE);

	fdevopen(USART_transmit, USART_receive); // Sets printf to serial port
	USART_init(MYUBBR);
	OLED_init();
	JOYSTICK_init();
	CAN_init();
	
	menuNode *menu = OLED_generate_menu();
	OLED_print_menu(menu);
	
	uint8_t currentRow = 1;
	uint8_t lastRow = 0;
	uint8_t buttonPressed = 0;
	uint8_t lslider, rslider, spi_data, spi_rec; // Variables used for testing
	Direction joydir = NEUTRAL;
	can_message_t received;
	
	while(1)
	{	
		JOYSTICK_send_position(); // Sends current position values over CAN
		
		/**********************************************************************************
		 Updates OLED display and position arrow according to current joystick position 
		 ***********************************************************************************/
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
		/***********************************************************************************/
		
		// SLIDER TEST
		/*
		lslider = ADC_read(LSLIDER);
		rslider = ADC_read(RSLIDER);
		printf("LSLIDER: %d\n", lslider);
		printf("RSLIDER: %d\n", rslider);
		*/
		
		// SPI TEST
		/*
		spi_data = 0xFF;
		SPI_master_transmit(spi_data);
		SPI_master_transmit(0x00);
		spi_rec = SPI_master_read();
		printf("SPI_rec: %d\n", spi_rec);
		*/
		
		// CAN RECEIVE TEST
		/*
		received = CAN_message_receive();
		printf("CAN ID: %d\n", received.id);
		printf("Message length: %d\n", received.length);
		printf("Data: %d\n", received.data);
		*/
		
	}
	
	return 0;
}