/*
 * config_attinyx4.h
 *
 * Created: 11.03.2021 18:18:15
 *  Author: DmitryBigPC
 */ 


#ifndef CONFIG_ATTINYX4_H_
#define CONFIG_ATTINYX4_H_

#include <avr/io.h>

#define TIMER_OVERFLOW_VECTOR TIM1_OVF_vect
 

#define _TIMER_PRESCALER_256	\
TCCR1B |= (1 << CS12);		\
TCCR1B &= ~(1 << CS11);		\
TCCR1B &= ~(1 << CS10);

#define _TIMER_PRESCALER_64		\
TCCR1B &= ~(1 << CS12);		\
TCCR1B |= (1 << CS11);		\
TCCR1B |= (1 << CS10);

#define _TIMER_PRESCALER_8		\
TCCR1B &= ~(1 << CS12);		\
TCCR1B |= (1 << CS11);		\
TCCR1B &= ~(1 << CS10);

#define _TIMER_PRESCALER_1		\
TCCR1B &= ~(1 << CS12);		\
TCCR1B &= ~(1 << CS11);		\
TCCR1B |= (1 << CS10);


#define _TIMER_PRESCALER_0		\
TCCR1B &= ~(1 << CS12);		\
TCCR1B &= ~(1 << CS11);		\
TCCR1B &= ~(1 << CS10);

// Pre-scalers correct

#define _TIMER_INIT_PRESCALER					_TIMER_PRESCALER_64

#define _TIMER_COUNTER_FALLING					TCCR1B &= ~(1 << ICES1);
#define _TIMER_COUNTER_RISING					TCCR1B |= (1 << ICES1);

// Edge detection correct

#define _TIMER_COUNTER_NOISE_CANCELLER_ENABLE	TCCR1B |= (1 << ICNC1);
#define _TIMER_COUNTER_NOISE_CANCELLER_DISABLE	TCCR1B &= ~(1 << ICNC1);

// Noise canceller correct

#define _TIMER_COUNTER_ENABLE_INT				TIMSK1 |= (1 << ICIE1);
#define _TIMER_COUNTER_DISABLE_INT				TIMSK1 &= ~(1 << ICIE1);

// Input capture correct

#define _TIMER_COUNTER_ENABLE_OVF				TIMSK1 |= (1 << TOIE1);
#define _TIMER_COUNTER_DISABLE_OVF				TIMSK1 &= ~(1 << TOIE1);

// Overflow correct

#define _TIMER_CTC								TCCR1B |= (1 << WGM12);
// CTC mode correct

#define _TIMER_NORMAL						\
TCCR1B &= ~(1 << WGM13);					\
TCCR1B &= ~(1 << WGM12);					\
TCCR1A &= ~(1 << WGM11);					\
TCCR1A &= ~(1 << WGM10);

// Normal mode correct

// OC1A Toggling
#define _TIMER_GENERATOR_OC1A_TOGGLE			\
TCCR1A &= ~(1 << COM1A1);						\
TCCR1A |= (1 << COM1A0);

#define _TIMER_GENERATOR_OC1A_DISCONNECT			\
TCCR1A &= ~(1 << COM1A1);						\
TCCR1A &= ~(1 << COM1A0);

#define _TIMER_GENERATOR_OC1B_TOGGLE			\
TCCR1A &= ~(1 << COM1B1);						\
TCCR1A |= (1 << COM1B0);

#define _TIMER_GENERATOR_OC1B_DISCONNECT			\
TCCR1A &= ~(1 << COM1B1);						\
TCCR1A &= ~(1 << COM1B0);

// OC1A Toggling correct

#define _TIMER_GENERATOR_INT_ENABLE			TIMSK1 |= (1 << OCIE1A);
#define _TIMER_GENERATOR_INT_DISABLE		TIMSK1 &= ~(1 << OCIE1A);

// Output Compare A correct

#define TIMER_COUNTER_INIT					\
_TIMER_COUNTER_RISING;						\
_TIMER_COUNTER_NOISE_CANCELLER_ENABLE;		\
_TIMER_NORMAL;

#define TIMER_COUNTER_START					\
TCNT1 = 0;									\
_TIMER_INIT_PRESCALER;						\
_TIMER_COUNTER_ENABLE_INT;					\
_TIMER_COUNTER_ENABLE_OVF;

#define TIMER_COUNTER_STOP					\
_TIMER_PRESCALER_0;							\
_TIMER_COUNTER_DISABLE_INT;					\
_TIMER_COUNTER_DISABLE_OVF

#define TIMER_GENERATOR_INIT				\
_TIMER_CTC;									\
_TIMER_GENERATOR_OC1A_TOGGLE;

#define TIMER_GENERATOR_START				\
TCNT1 = 0;									\
_TIMER_INIT_PRESCALER;						\
_TIMER_GENERATOR_OC1B_TOGGLE

#define TIMER_GENERATOR_STOP				\
_TIMER_PRESCALER_0;							\
_TIMER_GENERATOR_INT_DISABLE;				\
_TIMER_GENERATOR_OC1B_DISCONNECT;

/*
#define EXT_INT_ENABLE						\
MCUCR |= (1 << ISC01);						\
MCUCR &= ~(1 << ISC00);						\
GICR |= (1 << INT0);
*/
#define EXT_INT_ENABLE	\
GIMSK |= (1 << PCIE0);	\
PCMSK0 |= (1 << PCINT7);

#define EXT_INT_DISABLE	\
GIMSK &= ~(1 << PCIE0);	\
PCMSK0 &= ~(1 << PCINT7);

#define EXT_INT_VECTOR PCINT0_vect

#define TIMER_USED_PRESCALER	64

#endif /* CONFIG_ATTINYX4_H_ */