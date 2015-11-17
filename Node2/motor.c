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
	DDRF |= (1 << PF3)|(1 << PF4)|(1 << PF5)|(1 << PF6)|(1 << PF7); // Setting pins to output
	DDRK = 0;
	PORTF &= ~(1 << PF6); // reset
	_delay_us(20);
	PORTF |= (1 << PF6);
	MOTOR_enable(1);  // Enable motor
	MOTOR_speed_set(0); // Initialize motor speed to 0
	MOTOR_dir_set(0); // Set direction bit
}

/* Sets motor speed and direction according to data from input CAN message */
void MOTOR_write(can_message_t msg)
{
	uint8_t dir = msg.data[1];
	uint8_t joy_pos = msg.data[2];
	uint8_t speed = 0;
	
	if (dir == LEFT) {
		speed = 127 - joy_pos;
		MOTOR_dir_set(0);
	} else if (dir == RIGHT) {
		speed = joy_pos - 127;
		MOTOR_dir_set(1);
	}
	
	if (speed > 110) {
		speed = 110;
	}
	
	MOTOR_speed_set(speed);
}

/* Sets or clears motor enable bit */
void MOTOR_enable(uint8_t val)
{
	if (val == 1) {
		PORTF |= (1 << PF4);
	} else {
		PORTF &= ~(1 << PF4);
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
		PORTF |= (1 << PF3);
	} else {
		PORTF &= ~(1 << PF3);
	}
}

/* Reads MJ2 register and returns the the bits in reverse order. This function
	currently does not work as intended.
 */
int16_t MOTOR_pos_read(void)
{
	PORTF &= ~(1 << PF7); // ~OE low
	_delay_us(20);
	PORTF &= ~(1 << PF5); // SEL low to get high byte
	uint8_t msb = PINK;
	PORTF |= (1 << PF5); // SEL high to get low byte
	_delay_us(20);
	uint8_t lsb = PINK;
	
	PORTF |= (1 << PF7); // ~OE HIGH

	uint8_t msb_inv = byte_invert(msb);
	uint8_t lsb_inv = byte_invert(lsb);

	int16_t pos = (msb_inv << 8) | lsb_inv;
	return pos;
}

/* Helper function for inverting a byte */
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