/*
 * events.h
 *
 *  Created on: 18 Aug 2021
 *      Author: ihambleton
 */

#define NGSA_EXAMPLE_FLAG_TOGGLE    (OS_FLAGS) (1u <<  0)
#define EVENT_ADC_COMPLETE          (OS_FLAGS) (1u <<  1)

extern OS_FLAG_GRP NGSAFlagGrp;
