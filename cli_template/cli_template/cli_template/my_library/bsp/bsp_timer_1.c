/*
 * bsp_timer_1.c
 *
 * Created: 10/29/2021 1:51:22 PM
 *  Author: phuoc
 */ 

#include "bsp_timer_1.h"

#define DEFAULT_TIMER_VALUE 49536

bsp_timer_handle_t bsp_timer_interrupt_callback;

void bsp_timer_1_init(void)
{
	TCNT1 = DEFAULT_TIMER_VALUE;
	TCCR1A = 0x00;
	TCCR1B |= (1<<CS10);
	TIMSK1 |= (1<<TOIE1);
}

void bsp_timer_1_set_interrupt_handle(bsp_timer_handle_t pfun)
{
	bsp_timer_interrupt_callback = pfun;
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = DEFAULT_TIMER_VALUE;
	bsp_timer_interrupt_callback(0);
}