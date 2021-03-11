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


#define SPI_CS_PORT		PORTB
#define SPI_CS_DDR		DDRB
#define SPI_CS_PIN		PORTB2

#define F_CPU			1000000

#define CAPTURING_MAX_CLICKS 254


#endif /* CONFIG_H_ */