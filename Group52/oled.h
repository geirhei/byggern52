/*
 * oled.h
 *
 * Created: 02.10.2015 12:51:02
 *  Author: chengbid
 */ 

#include <avr/io.h>

#ifndef OLED_H_
#define OLED_H_


void oled_init(void);
void oled_write_c(char chr);
void oled_write_d(char chr);
int8_t oled_read_status(void);




#endif /* OLED_H_ */