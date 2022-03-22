/*
 * ftr_cli.c
 *
 * Created: 10/29/2021 3:06:45 PM
 *  Author: phuoc
 */ 
#include "ftr_cli.h"

#define RINGBUFFER_SIZE 16
#define MAX_CLI_BUFFER 64
#define TIMEOUT_HANDLE_CLI 100 // ms

Ring_Buffer_t ftr_ring_buffer;
uint8_t ftr_ring_buffer_rx_data[RINGBUFFER_SIZE] = {0};
uint32_t ftr_ring_buffer_position = 0;

void ftr_cli_task(void * pv_params);
void ftr_cli_handle(uint8_t data);

void ftr_cli_init(void)
{
	Ring_Buffer_Init(&ftr_ring_buffer, ftr_ring_buffer_rx_data, 1, RINGBUFFER_SIZE);
	per_uart_set_function_handle(ftr_cli_handle);
	task_add(TASK_REPEATED, TIMEOUT_HANDLE_CLI, ftr_cli_task);
}

void ftr_cli_handle(uint8_t data)
{
	Ring_Buffer_Put_Char(&ftr_ring_buffer, data);
}
void ftr_cli_add_command(CLI_Command_t *command_def)
{
	CLI_Add_Command(command_def);
}
void ftr_cli_remove_command(CLI_Command_t *command_def)
{
	CLI_Remove_command(command_def);
}
void ftr_cli_task(void * pv_params)
{
	uint8_t * buffer_read_malloc;
	uint8_t * buffer_out_malloc;
	if(Ring_Buffer_Search_Char(&ftr_ring_buffer, 0x0A, &ftr_ring_buffer_position))
	{
		
		buffer_read_malloc = (uint8_t*)malloc(MAX_CLI_BUFFER * sizeof(uint8_t));
		buffer_out_malloc = (uint8_t*)malloc(MAX_CLI_BUFFER * sizeof(uint8_t));
		
		Ring_Buffer_Get(&ftr_ring_buffer, buffer_read_malloc, MAX_CLI_BUFFER);
		CLI_Process_Command((char *)buffer_read_malloc, (char *)buffer_out_malloc, MAX_CLI_BUFFER);
		bsp_uart_send_string((char *)buffer_out_malloc);
		
		memset(buffer_read_malloc, 0, MAX_CLI_BUFFER);
		memset(buffer_out_malloc, 0, MAX_CLI_BUFFER);
		free(buffer_read_malloc);
		free(buffer_out_malloc);	
	}
}