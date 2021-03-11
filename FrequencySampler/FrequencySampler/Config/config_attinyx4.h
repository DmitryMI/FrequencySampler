/*
 * config_attinyx4.h
 *
 * Created: 11.03.2021 18:18:15
 *  Author: DmitryBigPC
 */ 


#ifndef CONFIG_ATTINYX4_H_
#define CONFIG_ATTINYX4_H_

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
#define _TIMER_GENERATOR_PIN_TOGGLE			\
TCCR1A &= ~(1 << COM1A1);					\
TCCR1A |= (1 << COM1A0);

// OC1A Toggling correct

#define _TIMER_GENERATOR_INT_ENABLE			TIMSK1 |= (1 << OCIE1A);
#define _TIMER_GENERATOR_INT_DISABLE		TIMSK1 &= ~(1 << OCIE1A);

// Output Compare A correct

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
_TIMER_CTC;								\
_TIMER_GENERATOR_PIN_TOGGLE;

#define TIMER_GENERATOR_START				\
TCNT1 = 0;								\
_TIMER_INIT_PRESCALER;					\

#define TIMER_GENERATOR_STOP				\
_TIMER_PRESCALER_0;						\
_TIMER_GENERATOR_INT_DISABLE;

/*
#define EXT_INT_ENABLE						\
MCUCR |= (1 << ISC01);						\
MCUCR &= ~(1 << ISC00);						\
GICR |= (1 << INT0);
*/
#define EXT_INT_ENABLE	\
GIMSK |= (1 << PCIE0);


#define EXT_INT_DISABLE	\
GIMSK &= ~(1 << PCIE0);

/*
SPITransfer:
	out    USIDR,r16
	ldi    r16,(1<<USIOIF)
	out    USISR,r16
	ldi    r17, (1<<USIWM0)|(1<<USICS1)|(1<<USICLK)|(1<<USITC)
	
SPITransfer_loop:
	out    USICR,r17
	in     r16, USISR
	sbrs   r16, USIOIF			// Skip if Bit in Register is Se
	rjmp   SPITransfer_loop
	in     r16,USIDR
	ret
*/

#define SPI_INIT											\
DDRA |= (1 << PORTA5) | (1 << PORTA4);						\
DDRA &= !(1 << PORTA6);										\
USIDR |= (1 << USIOIF);										\

#define SPI_DATA_REG	\
USIDR

#define SPI_CHECK_FLAG	\
USISR & (1 << USIOIF)

#define SPI_RW(b)		\
	SPI_INIT			\
	SPI_DATA_REG = b;	\
	do					\
	{					\
		USICR |= (1<<USIWM0)|(1<<USICS1)|(1<<USICLK)|(1<<USITC);	\	
	}while(!SPI_CHECK_FLAG)
	

#define RESISTOR_VALUE			2700
#define RHEOSTAT_MAX_VALUE		50000

#define TIMER_USED_PRESCALER	64

#endif /* CONFIG_ATTINYX4_H_ */