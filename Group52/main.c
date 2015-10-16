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
#include "spi.h"
#include "mcp.h"

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
	MCP_init();
	
	OLED_reset();
	OLED_pos(2,20);
	
	menuNode *menu = OLED_generate_menu();
	OLED_print_menu(menu);
	
	uint8_t currentRow = 1;
	uint8_t lastRow = 0;
	DirectionType joydir = NEUTRAL;
	uint8_t buttonPressed = 0;
	
	MCP_set_mode(LOOPBACK);
	// Turn mask off for both receive buffers
	MCP_modify_bit(0x60, 0b01100000, 0x00);
	MCP_modify_bit(0x70, 0b01100000, 0x00);
	
	// Set TXB0CTRL.TXREQ
	MCP_modify_bit(0x30, 0b00001000, 0b00001000);
	
	MCP_write(0b00110001, 'A');
	MCP_write(0b00110010, 'A');
	MCP_write(0b00110011, 'A');
	MCP_write(0b00110100, 'A');
	MCP_write(0b00110101, 'A');
	MCP_write(0b00110110, 'A');
	MCP_write(0b00110111, 'A');
	MCP_write(0b00111000, 'A');
	MCP_write(0b00111001, 'A');
	MCP_write(0b00111010, 'A');
	MCP_write(0b00111011, 'A');
	MCP_write(0b00111100, 'A');
	MCP_write(0b00111101, 'A');
	
	MCP_request_to_send();
	char response = MCP_read(0x0F);
	printf("CANSTAT: %d\n", response);
	
	while(1)
	{	
		joydir = JOYSTICK_get_direction();
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
		
	}
	
	return 0;
}

/* Makes LED blink when called */
void blink()
{
	PORTC ^= (1 << PINC1);
	_delay_ms(300);
}


void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with\n%4d errorsin write phase and\n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}

void SRAM_test2(void)
{
	volatile char *ext_ram = (char *) 0x1500; // Start address for the SRAM
	ext_ram[0] = 'f';
}

