/**
 * @file adc.h
 * @brief This is IR sensor library file
 * @author Team B4  S2018 ISU
 * @date 4/25/2018
 * */

#ifndef ADC_H_
#define ADC_H_

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>

void ADC_init(void);
unsigned ADC_read(char channel);

#endif
