/*
 * adc.h
 *
 * Created: 21.09.2020 15:01:30
 *  Author: DMITRYBIGPC
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define _ADC_PRESCALER_128 \
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

void adc_init();

void adc_set_free_running(int enabled);

void adc_start_conversion();

uint16_t adc_read();
uint8_t adc_read_high();
void adc_set_left_adjust(int enabled);


#endif /* ADC_H_ */