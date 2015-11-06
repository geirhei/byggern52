/*
 * spi.h
 *
 * Created: 09.10.2015 15:13:32
 *  Author: chengbid
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_master_init(void);
void SPI_master_transmit(uint8_t cData);
uint8_t SPI_master_read(void);


#endif /* SPI_H_ */