#include "ftr_cli.h"

#define RINGBUFFER_SIZE 16
#define MAX_CLI_BUFFER 128
#define TIMEOUT_HANDLE_CLI 100 // ms

Ring_Buffer_t ftr_ring_buffer;
uint8_t ftr_ring_buffer_rx_data[RINGBUFFER_SIZE] = {0};
uint8_t ftr_ring_buffer_get_data[RINGBUFFER_SIZE] = {0};
uint32_t ftr_ring_buffer_position = 0;
char ftr_cli_buffer_receiver[MAX_CLI_BUFFER] = {0};

void ftr_cli_task(void * pv_params);
void ftr_cli_handle(uint8_t data);

void ftr_cli_init(void)
{
	Ring_Buffer_Init(&ftr_ring_buffer, ftr_ring_buffer_rx_data, 1, RINGBUFFER_SIZE);
	per_uart_set_function_callback(ftr_cli_handle);
	CLI_Init();
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
	if(Ring_Buffer_Search(&ftr_ring_buffer, "\n", &ftr_ring_buffer_position) == 1)
	{
		Ring_Buffer_Get(&ftr_ring_buffer, ftr_ring_buffer_get_data, Ring_Buffer_Get_Count(&ftr_ring_buffer));
		CLI_Process_Command((char *)ftr_ring_buffer_get_data, ftr_cli_buffer_receiver, MAX_CLI_BUFFER);
		per_uart_send(ftr_cli_buffer_receiver);
		memset(ftr_cli_buffer_receiver, 0, MAX_CLI_BUFFER);
		memset(ftr_ring_buffer_get_data, 0, RINGBUFFER_SIZE);
	}
}
