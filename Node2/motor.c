/*
 * motor.c
 *
 * Created: 13.11.2015 20:09:36
 *  Author: chengbid
 */ 

#include "motor.h"

void MOTOR_init(void)
{
	TWI_Master_Initialise();
	
}

void MOTOR_speed_set(uint8_t speed)
{
	const uint8_t DAC_ADDR = 0b01010000; // Adress of the DAC
	const uint8_t CMD = 0; // Select DAC0 output
	uint8_t msg[3] = {DAC_ADDR, CMD, speed};
	TWI_Start_Transceiver_With_Data(msg, 3); // msg length = 3
}

void MOTOR_dir_set(uint8_t dir)
{
	
}