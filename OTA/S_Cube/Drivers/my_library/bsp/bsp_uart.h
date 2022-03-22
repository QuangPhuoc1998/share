#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "bsp.h"
#include "usart.h"
#include "string.h"

typedef void (*bsp_uart_handle_typeder)(uint8_t);

void bsp_uart_init(void);

error_code_t bsp_uart_send(void * pdata);

void bsp_uart_set_function_callback(bsp_uart_handle_typeder pfunc);

#endif
