/*
 * spi.h
 *
 * Created: 09.10.2015 15:13:32
 *  Author: chengbid
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_master_init(void);
void SPI_master_transmit(char cData);
//void SPI_slave_init(void);
//char SPI_slave_receive(void);


#endif /* SPI_H_ */