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

state_t state = IDLE;

capt_t capture_click_counter = 0;
uint32_t capture_time_counter = 0;

void start_generation()
{
	TIMER_COUNTER_STOP;
	
	uint32_t average_time = capture_time_counter / capture_click_counter;
	
	TCNT1 = 0;
	OCR1A = average_time;
	
	TIMER_GENERATOR_INIT;
	TIMER_GENERATOR_START;
	state = GENERATING;
}

void start_capturing()
{
	capture_click_counter = 0;
	capture_time_counter = 0;
	TIMER_GENERATOR_STOP;
	TIMER_COUNTER_INIT;
	TIMER_COUNTER_START;
	state = CAPTURING;
}

ISR(TIMER1_OVF_vect)
{
	switch(state)
	{
		// Should not occur while in IDLE or GENERATING mode
	case IDLE:
	case GENERATING:
		break;
		// If we were in CAPTURING mode, we must start GENERATING
	case CAPTURING:
		start_generation();
		break;
	}
}

ISR(TIMER1_CAPT_vect)
{	
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

ISR(TIMER1_COMPA_vect)
{
	// TODO: Send SPI data	
}


int main(void)
{
	state = IDLE;
	
	DDRB |= (1 << PORTB1);	
	
	TIMER_COUNTER_INIT;
	TIMER_COUNTER_START;
	sei();
	
    while (1) 
    {
		/*set_sleep_mode(SLEEP_MODE_IDLE);
		sleep_enable();
		sei();
		sleep_cpu();
		sleep_disable();*/
    }
}

