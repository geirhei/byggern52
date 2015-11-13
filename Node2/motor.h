/*
 * motor.h
 *
 * Created: 13.11.2015 20:09:49
 *  Author: chengbid
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "TWI_Master.h"
#include <avr/io.h>

void MOTOR_init(void);
void MOTOR_speed_set(uint8_t speed);
void MOTOR_dir_set(uint8_t dir);

#endif /* MOTOR_H_ */