/*
 * frequency_division_modes.h
 *
 * Created: 12.03.2021 15:21:25
 *  Author: DmitryBigPC
 */ 


#ifndef FREQUENCY_DIVISION_MODES_H_
#define FREQUENCY_DIVISION_MODES_H_

#include "common_types.h"

const frequency_divider_t frequency_modes[] = {
	{1, 1},
	{1, 2},
	{1, 3},
	{1, 4},
	{1, 6},
	{3, 4},
};

#define FREQUENCY_MODES_NUMBER = sizeof(frequency_modes) / sizeof(frequency_divider_t);


#endif /* FREQUENCY_DIVISION_MODES_H_ */