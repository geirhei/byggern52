/*
 * spi.c
 *
 * Created: 09.10.2015 15:13:20
 *  Author: chengbid
 
 
	Port configuration for NODE 2
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/delay.h>

void SPI_master_init(void)
{
	/* Set ~SS, MOSI and SCK output, all others input */
	DDRB = (1 << PB0)|(1 << PB2)|(1 << PB1); // Setting ~SS necessary?
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE)|(1 << MSTR)|(1 << SPR0);
}

void SPI_master_transmit(uint8_t cData)
{
	/* Start transmission */
	SPDR = cData;
	
	/* Wait for transmission to complete */
	while (!(SPSR & (1 << SPIF))) {
		;
	}
}

uint8_t SPI_master_read(void)
{
	uint8_t data = SPDR;
	return data;
}