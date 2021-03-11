/*
 * spi.h
 *
 * Created: 11.03.2021 19:08:58
 *  Author: DmitryBigPC
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

#include "../config.h"

inline void spi_cs(int enabled)
{
	if(enabled)
	{
		SPI_CS_PORT &= ~(1 << SPI_CS_PIN);	// CS is low-level driven
	}
	else
	{
		SPI_CS_PORT |= (1 << SPI_CS_PIN);
	}
}

void spi_init();
void spi_rw(uint8_t* out_buffer, uint8_t* in_buffer, int length);


#endif /* SPI_H_ */