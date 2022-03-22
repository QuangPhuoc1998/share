/*
 * ftr_cli.h
 *
 * Created: 10/29/2021 3:06:55 PM
 *  Author: phuoc
 */ 
#ifndef _FTR_CLI_H_
#define _FTR_CLI_H_

#include "per_uart.h"
#include "cli.h"
#include "ringbuffer.h"
#include "sys_task.h"
#include "stdlib.h"

void ftr_cli_init(void);

void ftr_cli_add_command(CLI_Command_t *command_def);

void ftr_cli_remove_command(CLI_Command_t *command_def);

#endif
