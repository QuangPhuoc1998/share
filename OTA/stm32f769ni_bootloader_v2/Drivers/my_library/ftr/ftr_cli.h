#ifndef _FTR_CLI_H_
#define _FTR_CLI_H_

#include "per_uart.h"
#include "cli.h"
#include "ringbuffer.h"
#include "sys_task.h"

void ftr_cli_init(void);

void ftr_cli_add_command(CLI_Command_t *command_def);

void ftr_cli_remove_command(CLI_Command_t *command_def);

#endif
