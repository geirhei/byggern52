/*
 * adc.h
 *
 * Created: 30.09.2015 12:11:28
 *  Author: geirhei
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <util/delay.h>

typedef enum {
	JOYAXIS1 = 1,
	JOYAXIS2 = 2,
	LSLIDER = 3,
	RSLIDER = 4
} DeviceType;
	
uint8_t ADC_read(DeviceType device);


#endif /* ADC_H_ */