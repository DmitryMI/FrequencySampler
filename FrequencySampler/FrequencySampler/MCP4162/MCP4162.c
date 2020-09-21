/*
 * MCP4162.c
 *
 * Created: 21.09.2020 14:09:44
 *  Author: DMITRYBIGPC
 */ 

#include "MCP4162.h"
#include <stdlib.h>

static inline void spi_cs(int enabled)
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

static void spi_write(uint8_t *data, int length)
{
	for(int i = 0; i < length; i++)
	{				
		SPDR = data[i];	 
		while(!(SPSR & (1<<SPIF)));
	}
}

static void spi_read(uint8_t *buffer, int length)
{
	for(int i = 0; i < length; i++)
	{		
		SPDR = 0xFF;	 
		while(!(SPSR & (1<<SPIF)));
		buffer[i] = SPDR;
	}
}

static void spi_rw(uint8_t* out_buffer, uint8_t* in_buffer, int length)
{
	for(int i = 0; i < length; i++)
	{
		SPDR = out_buffer[i];
		while(!(SPSR & (1<<SPIF)));
		in_buffer[i] = SPDR;				
	}
}


mcp4162_ecode_t mcp4162_init()
{
	spi_cs(0);
	return MCP_OK;
}

mcp4162_ecode_t mcp4162_write_wiper(uint8_t val)
{
	uint8_t command = 0b00000000;
	uint8_t data = val;
	
	uint8_t out_buffer[2];	
	out_buffer[0] = command;
	out_buffer[1] = data;
	
	uint8_t in_buffer[2] = {0, 0};
	
	spi_cs(1);
	spi_rw(out_buffer, in_buffer, 2);
	spi_cs(0);
	
	if(in_buffer[0] != 0xFF || in_buffer[1] != 0xFF)
	{
		return MCP_SPI_ERR;		
	}
	return MCP_OK;
}

mcp4162_ecode_t mcp4162_read_wiper(uint8_t *out_val)
{
	uint8_t command = 0b00001100;
	uint8_t data = 0xFF;
	
	uint8_t out_buffer[2];
	out_buffer[0] = command;
	out_buffer[1] = data;
	
	uint8_t in_buffer[2] = {0, 0};
		
	spi_cs(1);
	spi_rw(out_buffer, in_buffer, 2);
	spi_cs(0);
	
	if(!(in_buffer[0] & 0b11111110))
	{
		*out_val = 0;
		return MCP_SPI_ERR;
	}
	
	*out_val = in_buffer[1];
	
	return MCP_OK;
}