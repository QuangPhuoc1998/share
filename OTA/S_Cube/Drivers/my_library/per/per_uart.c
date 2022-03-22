#include "per_uart.h"

void per_uart_init(void)
{
	
}

error_code_t per_uart_send(void * pdata)
{
	return bsp_uart_send(pdata);
}

void per_uart_set_function_callback(bsp_uart_handle_typeder pfunc)
{
	bsp_uart_set_function_callback(pfunc);
}
