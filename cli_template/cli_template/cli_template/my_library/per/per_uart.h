/*
 * per_uart.h
 *
 * Created: 10/29/2021 2:53:08 PM
 *  Author: phuoc
 */ 

#include "bsp_uart.h"

void			per_uart_init(void);
unsigned char	per_uart_read_char();
void			per_uart_read_string(char *Output, unsigned int length);
void			per_uart_write_char(char ch);
void			per_uart_send_string(char *str);
void			per_uart_set_function_handle(bsp_uart_function_handle_t pfun);
