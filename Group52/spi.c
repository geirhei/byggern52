/*
 * spi.c
 *
 * Created: 09.10.2015 15:13:20
 *  Author: chengbid
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>

void SPI_master_init(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRD = (1 << PB5)|(1 << PB7);
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE)|(1 << MSTR)|(1 << SPR0);
	
}

void SPI_master_transmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission to complete */
	while (!(SPSR & (1 << SPIF))) {
		;
	}
}

void SPI_slave_init(void)
{
	/* Set MISO output, all others input */
	DDRD = (1 << PB6);
	/* Enable SPI */
	SPCR = (1 << SPIF);
}

char SPI_slave_receive(void)
{
	/* Wait for reception to complete */
	while (!(SPSR & (1 << SPIF))) {
		;
	}
	/* Return data register */
	return SPDR;
}