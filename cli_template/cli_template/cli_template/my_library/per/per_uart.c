/*
 * per_uart.c
 *
 * Created: 10/29/2021 2:52:59 PM
 *  Author: phuoc
 */ 
#include "per_uart.h"

void per_uart_init(void)
{
	
}
unsigned char per_uart_read_char()
{
	return bsp_uart_read_char();
}
void per_uart_read_string(char *Output, unsigned int length)
{
	bsp_uart_read_string(Output, length);
}
void per_uart_write_char(char ch)
{
	bsp_uart_write_char(ch);
}
void per_uart_send_string(char *str)
{
	bsp_uart_send_string(str);
}
void per_uart_set_function_handle(bsp_uart_function_handle_t pfun)
{
	bsp_uart_set_function_handle(pfun);
}