/*
 * motor.h
 *
 * Created: 13.11.2015 20:09:49
 *  Author: chengbid
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#define DAC_ADDR 0b01010000 // Adress of the DAC
#define CMD 0 // Select DAC0 output

#include "TWI_Master.h"
#include "can.h"
#include <avr/io.h>
#include <util/delay.h>

enum uint8_t{
	NEUTRAL = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
};

void MOTOR_init(void);
void MOTOR_speed_set(uint8_t speed);
void MOTOR_dir_set(uint8_t dir);
int16_t MOTOR_pos_read(void);

#endif /* MOTOR_H_ */