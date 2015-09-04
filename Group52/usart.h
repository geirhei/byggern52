/*
 * usart.h
 *
 * Created: 04.09.2015 12:32:04
 *  Author: geirhei
 */ 


#ifndef USART_H_
#define USART_H_

#define BAUD 9600
#define MYUBBR F_CPU/16/BAUD-1


void usart_Init(unsigned int ubrr);
void usart_Transmit(unsigned char data);
unsigned char usart_Receive(void);
void usart_Flush(void);

#endif /* USART_H_ */