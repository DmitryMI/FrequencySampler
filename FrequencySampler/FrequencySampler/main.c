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

void blink_led2()
{
	DDRB |= (1 << PORTB2);
	
	for(int i = 0; i < 3; i++)
	{
		PORTB |= (1 << PORTB2);
		_delay_ms(200);
		PORTB &= ~(1 << PORTB2);
		_delay_ms(500);
	}
}

void blink_led3()
{
	DDRB |= (1 << PORTB3);
	
	for(int i = 0; i < 3; i++)
	{
		PORTB |= (1 << PORTB3);
		_delay_ms(200);
		PORTB &= ~(1 << PORTB3);
		_delay_ms(500);
	}
}

void start_generation()
{
	cli();
	
	TIMER_COUNTER_STOP;
	
	uint32_t average_time = capture_time_counter / capture_click_counter;
	
	TCNT1 = 0;
	OCR1A = average_time / 2;
	
	TIMER_GENERATOR_INIT;
	TIMER_GENERATOR_START;
	state = GENERATING;
	
	EXT_INT_ENABLE;
	sei();	
}

void start_capturing()
{
	EXT_INT_DISABLE;
	
	PORTB &= ~(1 << PORTB1);
	capture_click_counter = 0;
	capture_time_counter = 0;
	TIMER_GENERATOR_STOP;
	TIMER_COUNTER_INIT;
	TIMER_COUNTER_START;
	state = CAPTURING;
	
	sei();
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = 0;	
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

ISR(INT0_vect)
{
	cli();

	switch(state)
	{
		// Should not occur while in IDLE or in CAPTURING
	case IDLE:
	case CAPTURING:		
		break;
		
	case GENERATING:	
		start_capturing();
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
		/*
		set_sleep_mode(SLEEP_MODE_IDLE);
		sleep_enable();
		sei();
		sleep_cpu();
		sleep_disable();	
		*/
    }
}

