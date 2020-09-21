/*
 * adc.c
 *
 * Created: 21.09.2020 15:01:36
 *  Author: DMITRYBIGPC
 */ 

#include "adc.h"

void adc_init()
{
	// Enabling ADC
	ADCSRA |= (1 << ADEN);
	
	// Selecting AREF as voltage reference
	ADMUX &= ~((1 << REFS0) | (1 << REFS1));
	
	// Selecting ADC0 channel (PC0)
	ADMUX &= ~(1 << MUX3);
	ADMUX &= ~(1 << MUX2);
	ADMUX &= ~(1 << MUX1);
	ADMUX &= ~(1 << MUX0);
	
	// Set ADC prescaler
	_ADC_PRESCALER_128;
	
}

void adc_set_free_running(int enabled)
{
	if(enabled)
	{
		ADCSRA |= (1 << ADFR);
	}
	else
	{
		ADCSRA &= ~(1 << ADFR);
	}
	
}

void adc_set_left_adjust(int enabled)
{
	if(enabled)
	{
		ADMUX |= (1 << ADLAR);
	}
	else
	{
		ADMUX &= ~(1 << ADLAR);
	}
}

void adc_start_conversion()
{
	ADCSRA |= (1 << ADSC);
}

uint16_t adc_read()
{
	while(!(ADCSRA & ADIF));
	
	uint16_t tmp = ADCW;
	ADCSRA |= (1 << ADIF);
	return tmp;
}

uint8_t adc_read_high()
{
	while(!(ADCSRA & ADIF));
	uint8_t tmp = ADCH;
	ADCSRA |= (1 << ADIF);
	return tmp;
}