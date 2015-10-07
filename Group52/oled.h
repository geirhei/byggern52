/*
 * oled.h
 *
 * Created: 02.10.2015 12:51:02
 *  Author: chengbid
 */ 

#include <avr/io.h>

#ifndef OLED_H_
#define OLED_H_

#define SIZEOF_ARRAY( a ) (sizeof( a ) / sizeof( a[ 0 ] ))

struct menu_node {
	char *name;
	struct menu_node *parent;
	struct menu_node *children[8];
	
};

	
typedef struct menu_node menuNode;

void OLED_init(void);
void OLED_write_c(char chr);
void OLED_write_d(char chr);
int8_t OLED_read_status(void);
//void OLED_print(char character);
void OLED_home(void);
void OLED_goto_line(uint8_t line);
void OLED_clear_line(uint8_t line);
void OLED_pos(uint8_t row, uint8_t column);
void OLED_reset(void);
void OLED_print_string(char* str);
void OLED_print_arrow(uint8_t row, uint8_t col);
menuNode *OLED_generate_menu(void);
void OLED_print_menu(menuNode *node);
menuNode *OLED_create_node(char* name);



#endif /* OLED_H_ */