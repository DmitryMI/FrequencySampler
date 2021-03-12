/*
 * common_types.h
 *
 * Created: 20.09.2020 20:01:02
 *  Author: DMITRYBIGPC
 */ 

#ifndef COMMON_TYPES_H_
#define COMMON_TYPES_H_

typedef double real_t;

typedef enum state_t 
{
	IDLE,			// In this state MCU retransmits potentiometer value. MCU starts with this state.
	CAPTURING,		// In this state MCU starts capturing the frequency via Timer1 Input Capture mode
	GENERATING		// In this state MCU sends a wave with captured frequency via Timer1 CTC mode
} state_t;

typedef uint8_t capt_t;

typedef struct
{
	uint8_t numerator;
	uint8_t denominator;
} frequency_divider_t;


#endif /* COMMON_TYPES_H_ */