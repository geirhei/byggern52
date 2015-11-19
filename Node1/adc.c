/*
 * adc.c
 *
 * Created: 30.09.2015 12:11:46
 *  Author: geirhei
 */ 

#define F_CPU 4915200

#include "adc.h"

uint8_t ADC_read(DeviceType device){
	volatile char *adc = (char *) 0x1400;
	switch (device) {
		case JOYAXIS1:
			/* Select CH1 */
			adc[0] = 0b00000100;
			break;
		
		case JOYAXIS2:
			/* Select CH2 */
			adc[0] = 0b00000101;
			break;
		
		case LSLIDER:
			/* Select CH3 */
			adc[0] = 0b00000110;
			break;
		
		case RSLIDER:
			/* Select CH4 */
			adc[0] = 0b00000111;
			break;
		
		default:
			break;
	}
	_delay_ms(70);
	return adc[0];
}