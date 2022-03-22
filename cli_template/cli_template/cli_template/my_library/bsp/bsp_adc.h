/*
 * bsp_adc.h
 *
 * Created: 11/6/2021 11:45:34 PM
 *  Author: phuoc
 */ 

#ifndef _BSP_ADC_H_
#define _BSP_ADC_H_

#include "main.h"

void bsp_adc_init(void);
uint16_t bsp_adc_read(uint8_t channel);

#endif
