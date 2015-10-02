/*
 * oled.h
 *
 * Created: 02.10.2015 12:51:02
 *  Author: chengbid
 */ 

#include <avr/io.h>

#ifndef OLED_H_
#define OLED_H_


void OLED_init(void);
void OLED_write_c(char chr);
void OLED_write_d(char chr);
int8_t OLED_read_status(void);
void OLED_print(char character);
void OLED_home(void);
void OLED_goto_line(uint8_t line);
void OLED_clear_line(uint8_t line);
void OLED_pos(uint8_t row, uint8_t column);
void OLED_reset(void);




#endif /* OLED_H_ */