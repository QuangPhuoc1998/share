/*
 * ftr_sensor_c.c
 *
 * Created: 11/6/2021 11:48:48 PM
 *  Author: phuoc
 */ 

#include "ftr_sensor.h"

#define TIMEOUT_HANDLE_SENSOR 100

uint8_t temperature = 0;

void ftr_sensor_task(void * pv_params);

void ftr_sensor_init(void)
{
	task_add(TASK_REPEATED, TIMEOUT_HANDLE_SENSOR, ftr_sensor_task);
}

uint8_t ftr_sensor_get_temperature(void)
{
	return temperature;
}
void ftr_sensor_task(void * pv_params)
{
	temperature = bsp_adc_read(0) * 0.488f;
}