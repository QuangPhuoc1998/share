/*
 * ds1307.h
 *
 * Created: 10/29/2021 1:22:57 PM
 *  Author: phuoc
 */ 
#ifndef _DS1307_H_
#define _DS1307_H_

#include "main.h"
#include "bsp_i2c.h"

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}rtc_t;

int DECIMALtoBCD(int DEC);
int BCDtoDECIMAL(int BCD);

void ds1307_set_time(rtc_t *rtc);
void ds1307_get_time(rtc_t *rtc);

void ds1307_set_hour(uint8_t hour);
void ds1307_set_min(uint8_t min);
void ds1307_set_sec(uint8_t sec);
void ds1307_set_date(uint8_t date);
void ds1307_set_mon(uint8_t mon);
void ds1307_set_year(uint8_t mon);
#endif