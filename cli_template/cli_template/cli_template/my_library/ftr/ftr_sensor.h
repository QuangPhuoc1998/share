/*
 * ftr_sensor.h
 *
 * Created: 11/6/2021 11:49:04 PM
 *  Author: phuoc
 */ 

#ifndef _FTR_SENSOR_H_
#define _FTR_SENSOR_H_

#include "bsp_adc.h"
#include "sys_task.h"
#include "sys_timer.h"


void ftr_sensor_init(void);

uint8_t ftr_sensor_get_temperature(void);

#endif
