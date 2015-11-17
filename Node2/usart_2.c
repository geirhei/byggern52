/*
 * usart.c
 *
 * Created: 04.09.2015 12:31:22
 *  Author: geirhei
 */ 

#include "usart_2.h"

void USART_init(unsigned int ubrr)
{
	/* Set baud rate*/
	UBRR0H = (unsigned char)(ubrr >> 8 );
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter*/
	UCSR0B = (1 << RXEN0)|(1 << TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << USBS0)|(3 << UCSZ10);
}

void USART_transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while (!( UCSR0A & (1 << UDRE0)))
		;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char USART_receive(void)
{
	/* Wait for data to be received */
	while ( !(UCSR0A & ( 1 << RXC0)) )
		;
	/* Get and return received data from buffer */
	return UDR0;
}

void USART_flush(void)
{
	volatile unsigned char dummy;
	while( UCSR0A & (1 << RXC0) ) dummy = UDR0;
}

