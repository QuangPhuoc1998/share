/*
 * app_display.c
 *
 * Created: 10/29/2021 3:21:33 PM
 *  Author: phuoc
 */ 

#include "app_display.h"

#define TIMEOUT_APP_DISPLAY 1000 // ms

rtc_t my_rtc;

void app_display_task(void * pv_param);
void app_display_lcd(rtc_t *rtc);

void app_display_init(void)
{
	task_add(TASK_REPEATED, TIMEOUT_APP_DISPLAY, app_display_task);
}

void app_display_task(void * pv_param)
{
	ds1307_get_time(&my_rtc);
	app_display_lcd(&my_rtc);
}
void app_display_lcd(rtc_t *rtc)
{
	Lcd_Set_Cursor(1,4);
	Lcd_Write_Char(rtc->hour/10+48);
	Lcd_Write_Char(rtc->hour%10+48);
	Lcd_Write_Char(':');
	Lcd_Write_Char(rtc->min/10+48);
	Lcd_Write_Char(rtc->min%10+48);
	Lcd_Write_Char(':');
	Lcd_Write_Char(rtc->sec/10+48);
	Lcd_Write_Char(rtc->sec%10+48);
		
	Lcd_Set_Cursor(2,3);
	Lcd_Write_Char(rtc->date/10+48);
	Lcd_Write_Char(rtc->date%10+48);
	Lcd_Write_Char(':');
	Lcd_Write_Char(rtc->month/10+48);
	Lcd_Write_Char(rtc->month%10+48);
	Lcd_Write_Char(':');
	Lcd_Write_String("20");
	Lcd_Write_Char(rtc->year/10+48);
	Lcd_Write_Char(rtc->year%10+48);
		
	Lcd_Set_Cursor(1,0);
	Lcd_Write_Char(' ');
}
