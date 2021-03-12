/*
 * FrequencySampler.c
 *
 * Created: 20.09.2020 18:45:48
 * Author : DMITRYBIGPC
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "config.h"
#include "common_types.h"
#include "MCP4162/MCP4162.h"
#include "ADC/adc.h"
#include "SPI/spi.h"
#include "frequency_division_modes.h"

state_t state = IDLE;

capt_t capture_click_counter = 0;
uint32_t capture_time_counter = 0;

/*
		Время зажержки = (0.01146*(сопротивление потенциометра + сопротивлене резистора, который стоит на входе пина))+29.70
		T = (0.01146*(Rp + Rr))+29.70
		Rp = (T - b) / a - Rr
		K = Rmax / ((T - b) / a - Rr) * 256
		T = Timer / (F_CPU / TIMER_USED_PRESCALER)
	*/

#if USE_FLOAT_CALCULATIONS == 1
	uint8_t get_resistance(uint16_t timer1_time, int freq_div_mode)
	{
		const real_t a = 0.01146;
		const real_t b = 29.70;
		real_t delay_time = (real_t)timer1_time / (F_CPU / TIMER_USED_PRESCALER);	
		delay_time *= frequency_modes[freq_div_mode].numerator;
		delay_time /= frequency_modes[freq_div_mode].denominator;
		real_t resistance = (((real_t)delay_time * 1000 - b) / a - RESISTOR_VALUE);
		if (resistance < 0)
		{
			return 0;
		}
		if (resistance >= RHEOSTAT_MAX_VALUE)
		{
			return 0xFF;
		}
		uint8_t rheostat_coefficient = resistance / RHEOSTAT_MAX_VALUE * 255;
		return rheostat_coefficient;
	
	}
#else
	uint8_t get_resistance(uint16_t timer1_time, int freq_div_mode)
	{
		const real_t a = (real_t)0.01146;
		const uint16_t invA = (uint16_t)(1.0f / a); //~87
		const real_t b = (real_t)29.70;
		const uint16_t bDivA = (uint16_t)(b / a);

		if (timer1_time < 476)
		{
			return 0;
		}
		if (timer1_time > 6359)
		{
			return 0xFF;
		}

		uint32_t timeSecInvA = (uint32_t)1000UL * timer1_time * invA;
		timeSecInvA *= frequency_modes[freq_div_mode].numerator;
		timeSecInvA /= frequency_modes[freq_div_mode].denominator;
		uint32_t freqDivResult = timeSecInvA / (F_CPU / TIMER_USED_PRESCALER);
		uint16_t resistance = (uint16_t)(freqDivResult - bDivA - RESISTOR_VALUE);
		//uint16_t resistance = (uint16_t)(1000 * timer1_time * invA / (F_CPU / TIMER_USED_PRESCALER) - bDivA - RESISTOR_VALUE);

		if (resistance >= RHEOSTAT_MAX_VALUE)
		{
			return 0xFF;
		}

		int resistanceUpper = 255 * resistance;

		uint8_t rheostat_coefficient = (uint8_t)(resistanceUpper / RHEOSTAT_MAX_VALUE);
		return rheostat_coefficient;
	}
#endif

void start_generation()
{
	cli();
	
	TIMER_COUNTER_STOP;
	
	uint32_t average_time = capture_time_counter / capture_click_counter;
	
	uint16_t period = (uint16_t)average_time;
	
	// TODO Get Frequency Division Mode
	uint8_t mcp4162_data = get_resistance(period, 0);
		
	spi_init(); // Since LED is attached to MOSI, it is better to reinit SPI
	
	mcp4162_write_wiper(mcp4162_data);
	
	TCNT1 = 0;
	OCR1A = period / 2;
	
	TIMER_GENERATOR_INIT;
	TIMER_GENERATOR_START;	
	
	state = GENERATING;
	
	EXT_INT_ENABLE;
	sei();	
}


void start_capturing()
{
	EXT_INT_DISABLE;	
	
	// Force LED to be on
	LED_PORT |= (1 << LED_PIN);
	
	capture_click_counter = 0;
	capture_time_counter = 0;
	TIMER_GENERATOR_STOP;
	TIMER_COUNTER_INIT;
	TIMER_COUNTER_START;
	state = CAPTURING;
	
	sei();
}

void send_adc_value()
{
	//uint16_t adc_value = adc_read();				// This is left-adjusted value
	uint8_t potentiometer_value = adc_read_high();	// Shift it to use only Most Significant Bits
	mcp4162_write_wiper(potentiometer_value);
}

ISR(TIMER_OVERFLOW_VECTOR)
{
	TCNT1 = 0;	
	switch(state)
	{
		// Should not occur while in IDLE or GENERATING mode
	case IDLE:
		send_adc_value();
		break;
	case GENERATING:
		break;
		// If we were in CAPTURING mode, we must start GENERATING
	case CAPTURING:		
		start_generation();		
		break;
	}
}

// Button press detection by Timer1 Capture Mode
ISR(TIMER1_CAPT_vect)
{	
	TCNT1 = 0;

	switch(state)
	{
		
	// If state is IDLE or GENERATING we need to enter CAPTURING mode
	// and wait for next TIMER1_CAPT interrupt with capture value ignored
	case IDLE:	
	case GENERATING:		
		start_capturing();
		break;
	case CAPTURING:
		
		if(capture_click_counter > CAPTURING_MAX_CLICKS)
		{
			start_generation();	
		}
		else
		{
			capture_click_counter++;
			capture_time_counter += ICR1;
		}
		break;
	default:
		break;
	}
}

// Button press detection by Pin Change Interrupt
ISR(EXT_INT_VECTOR)
{
	switch(state)
	{
	// Should not occur while in CAPTURING
	case CAPTURING:		
		break;
		
	case IDLE:
	case GENERATING:	
		start_capturing();
		break;
	}
}


int main(void)
{
	state = IDLE;
	
	spi_init();	
	
	mcp4162_init();
	adc_init();
	adc_set_free_running(1);
	adc_set_left_adjust(1);
	adc_start_conversion();
	
	TIMER_COUNTER_INIT;
	TIMER_COUNTER_START;
	
	_TIMER_PRESCALER_8;
		
    while (1) 
    {		
		set_sleep_mode(SLEEP_MODE_IDLE);
		sleep_enable();
		sei();
		sleep_cpu();
		sleep_disable();			
    }
}

