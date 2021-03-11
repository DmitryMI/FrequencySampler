/*
 * spi.c
 *
 * Created: 11.03.2021 19:09:11
 *  Author: DmitryBigPC
 */ 

#include "spi.h"

#if defined (__AVR_ATmega8__)

	void spi_rw(uint8_t* out_buffer, uint8_t* in_buffer, int length)
	{
		for(int i = 0; i < length; i++)
		{
			SPDR = out_buffer[i];
			while(!(SPSR & (1<<SPIF)));
			in_buffer[i] = SPDR;
		}
	}
	
	void spi_init()
	{
		DDRB |= ((1<<PB3)|(1<<PB5));		\
		SPI_CS_DDR |= (1 << SPI_CS_PIN);
		SPCR = ((1<<SPE)|(1<<MSTR));				
	}

#elif defined (__AVR_ATtiny44__)

	void spi_rw(uint8_t* out_buffer, uint8_t* in_buffer, int length)
	{
		for(int i = 0; i < length; i++)
		{
			SPDR = out_buffer[i];
			while(!(SPSR & (1<<SPIF)));
			in_buffer[i] = SPDR;
		}
	}
	
	void spi_init()
	{
		DDRB |= ((1<<PORTB3)|(1<<PORTB5));		\
		SPI_CS_DDR |= (1 << SPI_CS_PIN);
		SPCR = ((1<<SPE)|(1<<MSTR));
	}


#endif



