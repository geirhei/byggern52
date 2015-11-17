/*
 * oled.c
 *
 * Created: 02.10.2015 12:50:51
 *  Author: chengbid
 */ 

#include "oled.h"
#include "font.h"

	
void OLED_init(void)
{
	OLED_write_c(0xae); // display off
	OLED_write_c(0xa1); //segment remap
	OLED_write_c(0xda); //common pads hardware: alternative
	OLED_write_c(0x12);
	OLED_write_c(0xc8); //common output scan direction:com63~com0
	OLED_write_c(0xa8); //multiplex ration mode:63
	OLED_write_c(0x3f);
	OLED_write_c(0xd5); //display divide ratio/osc. freq. mode
	OLED_write_c(0x80);
	OLED_write_c(0x81); //contrast control
	OLED_write_c(0x50);
	OLED_write_c(0xd9); //set pre-charge period
	OLED_write_c(0x21);
	OLED_write_c(0x20); //Set Memory Addressing Mode
	OLED_write_c(0x00); //Horizontal mode
	OLED_write_c(0xdb); //VCOM deselect level mode
	OLED_write_c(0x30);
	OLED_write_c(0xad); //master configuration
	OLED_write_c(0x00);
	OLED_write_c(0xa4); //out follows RAM content
	OLED_write_c(0xa6); //set normal display
	OLED_write_c(0xaf); // display on
	
	for (int i = 0; i < 512; i++)
	{
		OLED_write_d(0xFF);
	}
	
	OLED_reset();
}


void OLED_update(menuNode *menu, position_t joypos)
{
	uint8_t currentRow = 1;
	uint8_t lastRow = 0;
	Direction joydir = NEUTRAL;
	uint8_t buttonPressed = 0;
	
	joydir = JOYSTICK_get_direction(joypos);
	lastRow = currentRow;
	if (joydir == UP) {
		if (currentRow == 1) {
			currentRow = 7;
			} else {
			currentRow -= 1;
		}
		
		} else if (joydir == DOWN) {
		if (currentRow == 7) {
			currentRow = 1;
			} else {
			currentRow += 1;
		}
	}
	
	OLED_move_arrow(currentRow, 20, lastRow, 20);
	buttonPressed = JOYSTICK_read_button();
	
	if (buttonPressed) {
		menu = menu->children[currentRow];
	}
	
	OLED_print_menu(menu);
}

void OLED_write_c(char chr)
{
	volatile char *oled = (char *) 0x1000;
	oled[0] = chr;
}

void OLED_write_d(char chr)
{
	volatile char *oled = (char *) 0x1200;
	oled[0] = chr;
}

int8_t OLED_read_status(void)
{
	volatile char *oled = (char *) 0x1000;
	return oled[0];
}

void OLED_home(void)
{
	OLED_pos(0,0);
}

void OLED_goto_line(uint8_t line)
{
	/* Set page address */
	OLED_write_c(0x22);
	OLED_write_c(line);
	OLED_write_c(0x07);
}

void OLED_clear_line(uint8_t line)
{
	OLED_goto_line(line);

	/* Set column start and end address */
	OLED_write_c(0x21);
	OLED_write_c(0x00);
	OLED_write_c(0x7F);

	/* Write zeros to line */
	for (int i = 0; i < 128; i++) {
		OLED_write_d(0x00);
	}
}

void OLED_pos(uint8_t row, uint8_t column)
{
	/* Set page address */
	OLED_write_c(0x22);
	OLED_write_c(row);
	OLED_write_c(0x07);

	/* Set column start and end address */
	OLED_write_c(0x21);
	OLED_write_c(column);
	OLED_write_c(0x7F);
}

void OLED_reset(void)
{
	for (uint8_t i = 0; i < 8; i++) {
		OLED_clear_line(i);
	}
	OLED_pos(0,0);
}

void OLED_print_string(char* str)
{
	uint8_t c;
	uint8_t font_width = 4;
	uint8_t i = 0;
	while (str[i] != '\0') {
		for (uint8_t j = 0; j < font_width; j++) {
			c = pgm_read_byte_near(font[str[i]-32] + j);
			OLED_write_d(c);
		}
		i++;
	}
}

void OLED_print_arrow(uint8_t row, uint8_t col)
{
	OLED_pos(row, col);
	OLED_write_d(0b00011000);
	OLED_write_d(0b00011000);
	OLED_write_d(0b01111110);
	OLED_write_d(0b00111100);
	OLED_write_d(0b00011000);
}

void OLED_move_arrow(uint8_t newRow, uint8_t newCol, uint8_t currentRow, uint8_t currentCol)
{
	OLED_pos(currentRow, currentCol);
	OLED_write_d(0b00000000);
	OLED_write_d(0b00000000);
	OLED_write_d(0b00000000);
	OLED_write_d(0b00000000);
	OLED_write_d(0b00000000);
	
	OLED_print_arrow(newRow, newCol);
}

menuNode *OLED_create_node(char* name, menuNode* parent)
{
	menuNode* ret = (menuNode*) malloc(sizeof(menuNode));
	ret->name = name;
	ret->parent = NULL;
	return ret;
}

menuNode *OLED_generate_menu(void)
{	
	menuNode *mainmenu = OLED_create_node("MAIN MENU", NULL);
	menuNode *highscores = OLED_create_node("Highscores", mainmenu);
	menuNode *playgame = OLED_create_node("Start new game", mainmenu);
	menuNode *debugging = OLED_create_node("Debugging", mainmenu);
	menuNode *calibrate = OLED_create_node("Calibrate", mainmenu);
	menuNode *difficulty = OLED_create_node("Difficulty", mainmenu);

	/*
	highscores->parent = mainmenu;
	playgame->parent = mainmenu;
	calibrate->parent = mainmenu;
	difficulty->parent = mainmenu;
	debugging->parent = mainmenu;
	*/
	
	mainmenu->children[1] = playgame;
	mainmenu->children[2] = highscores;
	mainmenu->children[3] = difficulty;
	mainmenu->children[4] = calibrate;
	mainmenu->children[5] = debugging;
	
	return mainmenu;
}

void OLED_print_menu(menuNode *node)
{
	OLED_pos(0,50);
	OLED_print_string(node->name);
	OLED_pos(1,50);
	OLED_print_string(node->children[1]->name);
	OLED_pos(2,50);
	OLED_print_string(node->children[2]->name);
	OLED_pos(3,50);
	OLED_print_string(node->children[3]->name);
	OLED_pos(4,50);
	OLED_print_string(node->children[4]->name);
	OLED_pos(5,50);
	OLED_print_string(node->children[5]->name);
}