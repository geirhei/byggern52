/*
 * ir.h
 *
 * Created: 13.11.2015 14:09:47
 *  Author: chengbid
 */ 

#ifndef IR_H_
#define IR_H_

#include <avr/io.h>
#include <avr/delay.h>


void IR_init(void);
uint8_t IR_read(void);



#endif /* IR_H_ */