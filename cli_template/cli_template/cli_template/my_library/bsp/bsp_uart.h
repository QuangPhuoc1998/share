#ifndef _UART_H_
#define _UART_H_

#include "main.h"

typedef void (*bsp_uart_function_handle_t)(uint8_t);

void			bsp_uart_init(long USART_BAUDRATE);
unsigned char	bsp_uart_read_char();
void			bsp_uart_read_string(char *Output, unsigned int length);
void			bsp_uart_write_char(char ch);
void			bsp_uart_send_string(char *str);
void			bsp_uart_set_function_handle(bsp_uart_function_handle_t pfun);
#endif