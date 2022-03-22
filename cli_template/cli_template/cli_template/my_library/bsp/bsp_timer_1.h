/*
 * bsp_timer_1.h
 *
 * Created: 10/29/2021 1:51:36 PM
 *  Author: phuoc
 */ 

#ifndef _TIMER_1_H_
#define _TIMER_1_H_

#include "main.h"

typedef void (*bsp_timer_handle_t)(void*);

void bsp_timer_1_init(void);

void bsp_timer_1_set_interrupt_handle(bsp_timer_handle_t pfun);

#endif


