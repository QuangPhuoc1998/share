#ifndef _APP_BOOTLOADER_H_
#define _APP_BOOTLOADER_H_

#include "main.h"
#include "stm32f769i_discovery.h"
#include "bsp_uart.h"
#include "ringbuffer.h"

/* ACK and NACK bytes*/
#define BL_ACK   0XA5
#define BL_NACK  0X7F

/*CRC*/
#define VERIFY_CRC_FAIL    1
#define VERIFY_CRC_SUCCESS 0

#define ADDR_VALID 0x00
#define ADDR_INVALID 0x01

#define INVALID_SECTOR 0x04

#define SRAM1_SIZE            368*1024     // STM32F446RE has 112KB of SRAM1
#define SRAM1_END             (SRAM1_BASE + SRAM1_SIZE)
#define SRAM2_SIZE            16*1024     // STM32F446RE has 16KB of SRAM2
#define SRAM2_END             (SRAM2_BASE + SRAM2_SIZE)
#define FLASH_SIZE             512*1024     // STM32F446RE has 512KB of SRAM2
#define BKPSRAM_SIZE           4*1024     // STM32F446RE has 4KB of SRAM2
#define BKPSRAM_END            (BKPSRAM_BASE + BKPSRAM_SIZE)
//This command is used to mass erase or sector erase of the user flash .
#define BL_FLASH_ERASE          0x56
//This command is used to write data in to different memories of the MCU
#define BL_MEM_WRITE			      0x57

void bootloader_init(void);
void bootloader_jump_to_user_app(void);
void bootloader_update_data(void);

#endif // _APP_BOOTLOADER_H_
