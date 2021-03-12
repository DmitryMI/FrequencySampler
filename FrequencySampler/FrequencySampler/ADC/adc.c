/*
 * adc.c
 *
 * Created: 21.09.2020 15:01:36
 *  Author: DMITRYBIGPC
 */ 

#include "adc.h"

#define _ADC_PRESCALER_128 \
ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

void adc_init()
{
	// Enabling ADC
	ADCSRA |= (1 << ADEN);
	
	
#if defined (__AVR_ATmega8__)
	// Selecting AREF as voltage reference	
	ADMUX &= ~((1 << REFS0) | (1 << REFS1));
	
	// Selecting ADC0 channel (PC0)
	ADMUX &= ~(1 << MUX3);
	ADMUX &= ~(1 << MUX2);
	ADMUX &= ~(1 << MUX1);
	ADMUX &= ~(1 << MUX0);
	
#elif defined (__AVR_ATtiny44__)
	// Selecting AREF as voltage reference	
	// AREF == PORTA0
	ADMUX &= ~(1 << REFS1);
	ADMUX &= (1 << REFS0);
	
	// Selecting ADC1 channel (PA1). MUX[5:0] = 000001
	ADMUX &= ~(1 << MUX5);
	ADMUX &= ~(1 << MUX4);
	ADMUX &= ~(1 << MUX3);
	ADMUX &= ~(1 << MUX2);
	ADMUX &= ~(1 << MUX1);
	ADMUX |= (1 << MUX0);
#else
	#pragma message("ADC: Device not supported!")
#endif	
	
	// Set ADC prescaler
	_ADC_PRESCALER_128;
	
}

#if defined (__AVR_ATmega8__)

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
	
#elif defined (__AVR_ATtiny44__)
	void adc_set_free_running(int enabled)
	{
		if(enabled)
		{
			ADCSRB &= ~((1 << ADTS0) | (1 << ADTS1) | (1 << ADTS2));
			ADCSRA |= (1 << ADATE);
		}
		else
		{
			ADCSRA &= ~(1 << ADATE);
		}		
	}
	
	void adc_set_left_adjust(int enabled)
	{
		if(enabled)
		{
			ADCSRB  |= (1 << ADLAR);
		}
		else
		{
			ADCSRB  &= ~(1 << ADLAR);
		}
	}

#endif

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