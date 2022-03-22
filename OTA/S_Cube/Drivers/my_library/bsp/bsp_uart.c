#include "bsp_uart.h"

uint8_t rx_data = 0;

bsp_uart_handle_typeder bsp_uart_callback;

void bsp_uart_init(void)
{
	HAL_UART_Receive_IT(&huart1, &rx_data, 1);
}

error_code_t bsp_uart_send(void * pdata)
{
	uint8_t * ptr = (uint8_t * )pdata;
	if( ptr == NULL)
	{
		return UART_INVALID_INPUT;
	}
	else;
	
	if (HAL_UART_Transmit(&huart1,ptr,strlen((char *)ptr),100))
		return ERROR_TX;
	else
		return NO_ERROR;
}

void bsp_uart_set_function_callback(bsp_uart_handle_typeder pfunc)
{
	bsp_uart_callback = pfunc;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		(*bsp_uart_callback)(rx_data);
		HAL_UART_Receive_IT(&huart1, &rx_data, 1);
  }
}
