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
#include "usart.h"

int main(void)
{
	DDRA = 0x02;
	PORTA = (1 << PA1);
	
	fdevopen(usart_Transmit, usart_Receive);
	
	usart_Init(MYUBBR);
	
	while(1)
	{
		//usart_Transmit(56);
		printf("test123");
		_delay_ms(1000);
	}
	
}