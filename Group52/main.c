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
#include <util/delay.h>
#include <stdlib.h>
#include "usart.h"
#include "joystick.h"

void blink();
void SRAM_test(void);
void SRAM_test2(void);

int main(void)
{
	/*Exercise 1*/
	fdevopen(usart_Transmit, usart_Receive);
	usart_Init(MYUBBR);
	
	/*Exercise 2*/
	MCUCR |= (1 << SRE);
	
	//DDRA = 0xFF;
	//DDRC = 0xFF;//(1 << PINC1);
	
	//PORTA = 0xFF;
	//PORTC = 0xFF;
	
	//SRAM_test();
	
	/*Exercise 3*/
	/*
	printf("test");
	volatile char *adc = (char *) 0x1500;
	uint8_t retrieved;
	*/
	
	position foo = joystick_Get_Position();
	int8_t xValue = foo.stick_positions[0];
	
	
	while(1)
	{
		foo = joystick_Get_Position();
		_delay_ms(100);
		xValue = foo.stick_positions[0];
		_delay_ms(100);
		//printf("%d\n", xValue);
		_delay_ms(100);
		/*
		adc[0] = 0b00000100;
		_delay_us(100);
		printf("%u\n",retrieved);
		retrieved = adc[0];
		
		//_delay_ms(1000);
		*/
		
	}
	
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
	ext_ram[0] = "foo";
}