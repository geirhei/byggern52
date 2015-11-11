/*
 * usart.h
 *
 * Created: 04.09.2015 12:32:04
 *  Author: geirhei
 */ 


#ifndef USART_H_
#define USART_H_

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1


void USART_init(unsigned int ubrr);
void USART_transmit(unsigned char data);
unsigned char USART_receive(void);
void USART_flush(void);

#endif /* USART_H_ */