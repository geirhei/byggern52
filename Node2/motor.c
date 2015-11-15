/*
 * motor.c
 *
 * Created: 13.11.2015 20:09:36
 *  Author: chengbid
 */ 

#include "motor.h"

uint8_t byte_invert(uint8_t data);

void MOTOR_init(void)
{
	TWI_Master_Initialise();
	DDRF |= (1 << PINF3)|(1 << PINF4)|(1 << PINF5)|(1 << PINF6)|(1 << PINF7); // Setting pins to output
	MOTOR_enable(1);  // Enable motor
	MOTOR_speed_set(0); // Initialize motor speed to 0
	//MOTOR_dir_set(0); // Set direction bit
	//DDRK |= 1; // Set MJ2 as input
	
}

void MOTOR_write(can_message_t msg)
{
	uint8_t dir = msg.data[1];
	uint8_t joy_pos = msg.data[2];
	uint8_t val = 0;
	
	if (dir == LEFT) {
		val = 127 - joy_pos;
		MOTOR_dir_set(0);
		//printf("LEFT ENTERED, val: %d\n", val);
	} else if (dir == RIGHT) {
		val = joy_pos - 127;
		MOTOR_dir_set(1);
		//printf("RIGHT ENTERED, val: %d\n", val);
	}
	
	uint8_t speed = val;
	
	
	MOTOR_speed_set(speed);
	
}

void MOTOR_enable(uint8_t val)
{
	if (val == 1) {
		PORTF |= (1 << PINF4);
	} else {
		PORTF &= ~(1 << PINF4);
	}
}

/* Sets speed value converted to analog 0-5V */
void MOTOR_speed_set(uint8_t speed)
{
	uint8_t msg[3] = {DAC_ADDR, CMD, speed};
	TWI_Start_Transceiver_With_Data(msg, 3); // msg length = 3
}

/* Sets/clears direction bit DIR */
void MOTOR_dir_set(uint8_t dir)
{
	if (dir == 1) {
		PORTF |= (1 << PINF3);
	} else {
		PORTF &= ~(1 << PINF3);
	}
}

/* Reads MJ2 register and returns the the bits in reverse order */
int16_t MOTOR_pos_read(void)
{
	PORTF &= ~(1 << PINF7); // ~OE low
	PORTF &= ~(1 << PINF5); // SEL low to get high byte
	_delay_us(20);
	int16_t msb = PINK;
	PORTF |= (1 << PINF5); // SEL high to get low byte
	_delay_us(20);
	int16_t lsb = PINK;
	PORTF |= (1 << PINF6); // Toggle ~RST
	//PORTF &= ~(1 << PINF6);
	PORTF |= (1 << PINF7); // ~OE HIGH
	
	//printf("msb: %d", msb);
	//printf("       lsb: %d\n", lsb);
	
	int16_t msb_inv = (byte_invert(msb) << 8);
	int16_t lsb_inv = byte_invert(lsb);
	int16_t pos = msb_inv | lsb_inv;
	return pos;
}

uint8_t byte_invert(uint8_t data)
{
	uint8_t res = 0;
	uint8_t i;
	for (uint8_t i = 0; i < 8; i++) {
		if ((data & (1 << i)))
			res |= 1 << (7 - i);
	}
	return res;
}