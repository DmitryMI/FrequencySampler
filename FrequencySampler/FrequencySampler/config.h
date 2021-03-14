/*
 * config.h
 *
 * Created: 11.03.2021 18:40:11
 *  Author: DmitryBigPC
 */ 
#ifndef CONFIG_H_
#define CONFIG_H_

#if defined (__AVR_ATmega8__)
	#include "Config/config_atmega8.h"
#elif defined (__AVR_ATtiny44__)
	#include "Config/config_attinyx4.h"
#else
	#pragma message("Device not supported!")
#endif

#include "common_types.h"

/*
#define SPI_CS_PORT		PORTB
#define SPI_CS_DDR		DDRB
#define SPI_CS_PIN		PORTB2
*/
#define SPI_CS_PORT		PORTA
#define SPI_CS_DDR		DDRA
#define SPI_CS_PIN		PA3

#define F_CPU			1000000

#define CAPTURING_MAX_CLICKS 254

#define RESISTOR_VALUE			2700
#define RHEOSTAT_MAX_VALUE		50000

#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED_PIN PB2


#define MODE1_PORT	PORTA
#define MODE2_PORT	PORTB
#define MODE3_PORT	PORTB
#define MODE4_PORT	PORTB

#define MODE1_READ	PINA
#define MODE2_READ	PINB
#define MODE3_READ	PINB
#define MODE4_READ	PINB

#define MODE1_DDR	DDRA
#define MODE2_DDR	DDRB
#define MODE3_DDR	DDRB
#define MODE4_DDR	DDRB

#define MODE1_PIN	PA2
#define MODE2_PIN	PB0
#define MODE3_PIN	PB1
#define MODE4_PIN	PB2

#define BUTTON_PORT	PORTA
#define BUTTON_READ	PINA
#define BUTTON_PIN	PA7
#define BUTTON_DDR	DDRA

#define USE_FLOAT_CALCULATIONS 1

#endif /* CONFIG_H_ */