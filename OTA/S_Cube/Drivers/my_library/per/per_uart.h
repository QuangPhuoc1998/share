#ifndef _PER_UART_H_
#define _PER_UART_H_

#include "bsp_uart.h"

void per_uart_init(void);

error_code_t per_uart_send(void * pdata);

void per_uart_set_function_callback(bsp_uart_handle_typeder pfunc);

#endif 
