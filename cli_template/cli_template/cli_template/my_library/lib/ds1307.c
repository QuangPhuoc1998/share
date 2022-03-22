/*
 * ds1307.c
 *
 * Created: 10/29/2021 1:22:47 PM
 *  Author: phuoc
 */ 

#include "ds1307.h"

rtc_t static_value;

int DECIMALtoBCD(int DEC)
{
	int L, H;
	L=DEC%10; //make digit low
	H=DEC/10<<4; //make digit high
	return (H+L);
}

int BCDtoDECIMAL(int BCD)
{
	int L, H;
	L=BCD & 0x0F; //ones
	H=(BCD>>4) * 10;//tens
	return (H+L);
}

void ds1307_set_time(rtc_t *rtc)
{
	rtc->hour = DECIMALtoBCD(rtc->hour);
	rtc->min = DECIMALtoBCD(rtc->min);
	rtc->date = DECIMALtoBCD(rtc->date);
	rtc->month = DECIMALtoBCD(rtc->month);
	rtc->year = DECIMALtoBCD(rtc->year);
	/*--------*/
	bps_i2c_start(0xD0);     // connect to DS1307 by sending its ID on I2c Bus
	bsp_i2c_write(0x00); // Request sec RAM address at 00H
	
	bsp_i2c_write(rtc->sec);                    // Write sec from RAM address 00H
	bsp_i2c_write(rtc->min);                    // Write min from RAM address 01H
	bsp_i2c_write(rtc->hour);                    // Write hour from RAM address 02H
	bsp_i2c_write(rtc->weekDay);                // Write weekDay on RAM address 03H
	bsp_i2c_write(rtc->date);                    // Write date on RAM address 04H
	bsp_i2c_write(rtc->month);                    // Write month on RAM address 05H
	bsp_i2c_write(rtc->year);                    // Write year on RAM address 06h
	
	bsp_i2c_stop();                              // Stop I2C communication after Setting the Date
}

void ds1307_get_time(rtc_t *rtc)
{
	bps_i2c_start(0xD0);
	bsp_i2c_write(0x00);
	bsp_i2c_repeated_start(0xD1);
	rtc->sec = bsp_i2c_read_ack();
	rtc->min = bsp_i2c_read_ack();
	rtc->hour= bsp_i2c_read_ack();
	rtc->weekDay = bsp_i2c_read_ack();
	rtc->date = bsp_i2c_read_ack();
	rtc->month =bsp_i2c_read_ack();
	rtc->year = bsp_i2c_read_nack();
	bsp_i2c_stop();
	
	rtc->sec = BCDtoDECIMAL(rtc->sec);
	rtc->min = BCDtoDECIMAL(rtc->min);
	rtc->hour = BCDtoDECIMAL(rtc->hour);
	rtc->weekDay = BCDtoDECIMAL(rtc->weekDay);
	rtc->date = BCDtoDECIMAL(rtc->date);
	rtc->month = BCDtoDECIMAL(rtc->month);
	rtc->year = BCDtoDECIMAL(rtc->year);
}

void ds1307_set_hour(uint8_t hour)
{
	
}
void ds1307_set_min(uint8_t min)
{
	
}
void ds1307_set_sec(uint8_t sec)
{
	
}
void ds1307_set_date(uint8_t date)
{
	
}
void ds1307_set_mon(uint8_t mon)
{
	
}
void ds1307_set_year(uint8_t mon)
{
	
}