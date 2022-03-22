/*
 * cli_tempalte.c
 *
 * Created: 10/28/2021 3:25:26 PM
 * Author : phuoc
 */ 
#include "bsp_timer_1.h"
#include "ftr_sensor.h"
#include "app_cli.h"
#include "app_display.h"


int main(void)
{	
	/*--- Board support package init ---*/
	bsp_timer_1_init();
	bsp_timer_1_set_interrupt_handle(timer_handler);
	bsp_uart_init(9600);
	bsp_i2c_init();
	bsp_adc_init();
	sei();
	/*--- User library init ---*/
	CLI_Init();
	Lcd_Init();
	/*--- Peripheral init --*/
	per_uart_init();
	/*--- Feature init ---*/
	ftr_cli_init();
	ftr_sensor_init();
	/*--- App init ---*/
	app_display_init();
	app_cli_init();
	/*--- Start loop ---*/
    while (1) 
    {
		task_loop();
    }
}

