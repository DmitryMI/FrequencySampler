/*
 * config.h
 *
 * Created: 20.09.2020 18:47:16
 *  Author: DMITRYBIGPC
 */ 

/*
Maximum Frequency is 4 Hz
Minimum Frequency is 0.0625 Hz
F_CPU = 1 000 000 Hz
Timer prescaler = 256
*/


#ifndef CONFIG_H_
#define CONFIG_H_

#include <avr/io.h>

#define _TIMER_PRESCALER_256	\
	TCCR1B |= (1 << CS12);		\
	TCCR1B &= ~(1 << CS11);		\
	TCCR1B &= ~(1 << CS10);
	
#define _TIMER_PRESCALER_64		\
	TCCR1B &= ~(1 << CS12);		\
	TCCR1B |= (1 << CS11);		\
	TCCR1B |= (1 << CS10);
	
#define _TIMER_PRESCALER_0		\
	TCCR1B &= ~(1 << CS12);		\
	TCCR1B &= ~(1 << CS11);		\
	TCCR1B &= ~(1 << CS10);

#define _TIMER_INIT_PRESCALER					_TIMER_PRESCALER_64			

#define _TIMER_COUNTER_FALLING					TCCR1B &= ~(1 << ICES1);
#define _TIMER_COUNTER_RISING					TCCR1B |= (1 << ICES1);

#define _TIMER_COUNTER_NOISE_CANCELLER_ENABLE	TCCR1B |= (1 << ICNC1);
#define _TIMER_COUNTER_NOISE_CANCELLER_DISABLE	TCCR1B &= ~(1 << ICNC1);

#define _TIMER_COUNTER_ENABLE_INT				TIMSK |= (1 << TICIE1);
#define _TIMER_COUNTER_DISABLE_INT				TIMSK &= ~(1 << TICIE1);

#define _TIMER_COUNTER_ENABLE_OVF				TIMSK |= (1 << TOIE1);
#define _TIMER_COUNTER_DISABLE_OVF				TIMSK &= ~(1 << TOIE1);

#define _TIMER_CTC					TCCR1B |= (1 << WGM12);
#define _TIMER_NORMAL						\
	TCCR1B &= ~(1 << WGM13);				\
	TCCR1B &= ~(1 << WGM12);				\
	TCCR1A &= ~(1 << WGM11);				\
	TCCR1A &= ~(1 << WGM10);

#define _TIMER_GENERATOR_PIN_TOGGLE			\
	TCCR1A &= ~(1 << COM1A1);				\
	TCCR1A |= (1 << COM1A0);
	
#define _TIMER_GENERATOR_INT_ENABLE				TIMSK |= (1 << OCIE1A);
#define _TIMER_GENERATOR_INT_DISABLE			TIMSK &= ~(1 << OCIE1A);

#define TIMER_COUNTER_INIT					\
	_TIMER_COUNTER_RISING;					\
	_TIMER_COUNTER_NOISE_CANCELLER_ENABLE;	\
	_TIMER_NORMAL;
	
#define TIMER_COUNTER_START					\
	TCNT1 = 0;								\
	_TIMER_INIT_PRESCALER;					\
	_TIMER_COUNTER_ENABLE_INT;				\
	_TIMER_COUNTER_ENABLE_OVF;				

#define TIMER_COUNTER_STOP					\
	_TIMER_PRESCALER_0;						\
	_TIMER_COUNTER_DISABLE_INT;				\
	_TIMER_COUNTER_DISABLE_OVF

#define TIMER_GENERATOR_INIT				\
	_TIMER_CTC;					\
	_TIMER_GENERATOR_PIN_TOGGLE;
	
#define TIMER_GENERATOR_START				\
	TCNT1 = 0;								\
	_TIMER_INIT_PRESCALER;					\
	_TIMER_GENERATOR_INT_ENABLE;
	
#define TIMER_GENERATOR_STOP				\
	_TIMER_PRESCALER_0;						\
	_TIMER_GENERATOR_INT_DISABLE;
	
#define EXT_INT_ENABLE						\
	MCUCR |= (1 << ISC01);					\
	MCUCR &= ~(1 << ISC00);					\
	GICR |= (1 << INT0);
	
#define EXT_INT_DISABLE		GICR &= ~(1 << INT0);

#define CAPTURING_MAX_CLICKS 254
typedef uint8_t capt_t;
	



#endif /* CONFIG_H_ */