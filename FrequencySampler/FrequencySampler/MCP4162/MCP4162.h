/*
 * MCP4162.h
 *
 * Created: 21.09.2020 14:08:21
 *  Author: DMITRYBIGPC
 */ 


#ifndef MCP4162_H_
#define MCP4162_H_

#include <avr/io.h>

typedef enum mcp4162_ecode_t
{
	MCP_OK,
	MCP_SPI_ERR,
	MCP_NOT_IMPLEMENTED
} mcp4162_ecode_t;

mcp4162_ecode_t mcp4162_init();
mcp4162_ecode_t mcp4162_write_wiper(uint8_t val);
mcp4162_ecode_t mcp4162_read_wiper(uint8_t *out_val);


#endif /* MCP4162_H_ */