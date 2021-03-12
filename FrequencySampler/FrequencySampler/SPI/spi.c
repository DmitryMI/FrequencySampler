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
			USIDR = out_buffer[i];
			USISR = (1<<USIOIF);
			
			do 
			{
				USICR = (1<<USIWM0)|(1<<USICS1)|(1<<USICLK)|(1<<USITC);
			} while ((USISR & (1<<USIOIF)) == 0);
			
			in_buffer[i] = USIDR;
		}
	}
	
	void spi_init()
	{		
		// Direction for MISO (PA6)
		DDRA &= ~(1 << PA6);
		// pull-up for MISO (PA6)
		PORTA |= (1 << PA6);
		
		// Direction for MOSI (PA5) and SCK (PA4)
		DDRA |= (1 << PA5) | (1 << PA4);
		
		// Direction for user-specified CS
		SPI_CS_DDR |= (1 << SPI_CS_PIN);
		
		USICR = (1<<USIWM0)|(1<<USICS1)|(1<<USICLK);
	}


#endif



