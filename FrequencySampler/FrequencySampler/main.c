/*
 * FrequencySampler.c
 *
 * Created: 20.09.2020 18:45:48
 * Author : DMITRYBIGPC
 */ 

#include <avr/io.h>

#include "config.h"

ISR(TIMER1_OVF_vect)
{
	
}

ISR(TIMER1_CAPT_vect)
{
		
}


int main(void)
{
	TIMER_INIT;
	
	
    while (1) 
    {
    }
}

