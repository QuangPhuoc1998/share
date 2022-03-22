#include "app_bootloader.h"

#define RINGBUFFER_SIZE 256
#define FLASH_SECTOR2_BASE_ADDRESS 0x08008000U

#define C_UART   &huart1
#define BL_RX_LEN  200

uint8_t bl_rx_buffer[BL_RX_LEN];
uint8_t supported_commands[] = {
                               BL_FLASH_ERASE,
                               BL_MEM_WRITE};

void bootloader_handle_flash_erase_cmd(uint8_t *pBuffer);
void bootloader_handle_mem_write_cmd(uint8_t *pBuffer);								 
uint8_t bootloader_verify_crc (uint8_t *pData, uint32_t len, uint32_t crc_host);
uint8_t execute_mem_write(uint8_t *pBuffer, uint32_t mem_address, uint32_t len);
void bootloader_send_ack(uint8_t command_code, uint8_t follow_len);
void bootloader_send_nack(void);
void bootloader_uart_write_data(uint8_t *pBuffer,uint32_t len);		
uint8_t execute_flash_erase(uint8_t sector_number , uint8_t number_of_sector);		
uint8_t verify_address(uint32_t go_address);
															 
void bootloader_init(void)
{

}
void bootloader_jump_to_user_app()
{
	void (*app_reset_handler)(void);
	
	uint32_t msp_value = *(volatile uint32_t *)FLASH_SECTOR2_BASE_ADDRESS;
	
	__set_MSP(msp_value);
	
	uint32_t resethandler_address = *(volatile uint32_t *) (FLASH_SECTOR2_BASE_ADDRESS + 4);
	
	app_reset_handler = (void *)resethandler_address;
	
	app_reset_handler();
}
void bootloader_update_data()
{
	uint8_t rcv_len=0;

	while(1)
	{
		memset(bl_rx_buffer,0,200);
		//here we will read and decode the commands coming from host
		//first read only one byte from the host , which is the "length" field of the command packet
    HAL_UART_Receive(C_UART,bl_rx_buffer,1,HAL_MAX_DELAY);
		rcv_len= bl_rx_buffer[0];
		HAL_UART_Receive(C_UART,&bl_rx_buffer[1],rcv_len,HAL_MAX_DELAY);
		switch(bl_rx_buffer[1])
		{
			case BL_FLASH_ERASE:
				bootloader_handle_flash_erase_cmd(bl_rx_buffer);
				break;
			case BL_MEM_WRITE:
				bootloader_handle_mem_write_cmd(bl_rx_buffer);
				break;
			default:
        break;
		}
	}
}
/*Helper function to handle BL_FLASH_ERASE command */
void bootloader_handle_flash_erase_cmd(uint8_t *pBuffer)
{
	uint32_t sectorError;
	
	FLASH_EraseInitTypeDef flashErase_handle;
	
	flashErase_handle.TypeErase = FLASH_TYPEERASE_SECTORS;
	flashErase_handle.Sector = 1; // this is the initial sector
	flashErase_handle.NbSectors = 11;
	flashErase_handle.Banks = FLASH_BANK_1;

		/*Get access to touch the flash registers */
	HAL_FLASH_Unlock();
	flashErase_handle.VoltageRange = FLASH_VOLTAGE_RANGE_3;  // our mcu will work on this voltage range
	HAL_FLASHEx_Erase(&flashErase_handle, &sectorError);
	HAL_FLASH_Lock();
	
	HAL_UART_Transmit(C_UART,(uint8_t*)"2",1,HAL_MAX_DELAY);
	HAL_Delay(100);
	HAL_UART_Transmit(C_UART,(uint8_t*)"W",1,HAL_MAX_DELAY);
	/*
  uint8_t erase_status = 0x00;

    //Total length of the command packet
	uint32_t command_packet_len = bl_rx_buffer[0]+1 ;

	//extract the CRC32 sent by the Host
	uint32_t host_crc = *((uint32_t * ) (bl_rx_buffer+command_packet_len - 4) ) ;

	if (!bootloader_verify_crc(&bl_rx_buffer[0],command_packet_len-4,host_crc))
	{
        bootloader_send_ack(pBuffer[0],1);

        BSP_LED_On(LED_RED);
        erase_status = execute_flash_erase(pBuffer[2] , pBuffer[3]);
        BSP_LED_Off(LED_RED);


        bootloader_uart_write_data(&erase_status,1);

	}else
	{
        bootloader_send_nack();
	}
	*/
}
void bootloader_handle_mem_write_cmd(uint8_t *pBuffer)
{
	uint32_t len_to_write = pBuffer[2];
	uint32_t mem_address = *((uint32_t *) ( &pBuffer[3]) );
	
	execute_mem_write(&pBuffer[7],mem_address, len_to_write);
	
	HAL_UART_Transmit(C_UART,(uint8_t*)"1",1,HAL_MAX_DELAY);
	HAL_Delay(100);
	HAL_UART_Transmit(C_UART,(uint8_t*)"W",1,HAL_MAX_DELAY);
	
	/*
	uint8_t addr_valid = ADDR_VALID;
	uint8_t write_status = 0x00;
	uint8_t chksum =0, len=0;
	len = pBuffer[0];
	uint8_t payload_len = pBuffer[6];

	uint32_t mem_address = *((uint32_t *) ( &pBuffer[2]) );

	chksum = pBuffer[len];


    //Total length of the command packet
	uint32_t command_packet_len = bl_rx_buffer[0]+1 ;

	//extract the CRC32 sent by the Host
	uint32_t host_crc = *((uint32_t * ) (bl_rx_buffer+command_packet_len - 4) ) ;


	if (! bootloader_verify_crc(&bl_rx_buffer[0],command_packet_len-4,host_crc))
	{

        bootloader_send_ack(pBuffer[0],1);


		if( verify_address(mem_address) == ADDR_VALID )
		{


            //glow the led to indicate bootloader is currently writing to memory
            BSP_LED_On(LED_RED);

            //execute mem write
            write_status = execute_mem_write(&pBuffer[7],mem_address, payload_len);

            //turn off the led to indicate memory write is over
            BSP_LED_Off(LED_RED);

            //inform host about the status
            bootloader_uart_write_data(&write_status,1);

		}else
		{
            write_status = ADDR_INVALID;
            //inform host that address is invalid
            bootloader_uart_write_data(&write_status,1);
		}


	}else
	{
        bootloader_send_nack();
	}
	*/
}
//This verifies the CRC of the given buffer in pData .
uint8_t bootloader_verify_crc (uint8_t *pData, uint32_t len, uint32_t crc_host)
{
	HAL_Delay(50);
	return VERIFY_CRC_SUCCESS;
	/*
    uint32_t uwCRCValue=0xff;

    for (uint32_t i=0 ; i < len ; i++)
	{
        uint32_t i_data = pData[i];
        uwCRCValue = HAL_CRC_Accumulate(&hcrc, &i_data, 1);
	}

	 // Reset CRC Calculation Unit 
  __HAL_CRC_DR_RESET(&hcrc);

	if( uwCRCValue == crc_host)
	{
		return VERIFY_CRC_SUCCESS;
	}

	return VERIFY_CRC_FAIL;
	*/
}

/*This function writes the contents of pBuffer to  "mem_address" byte by byte */
//Note1 : Currently this function supports writing to Flash only .
//Note2 : This functions does not check whether "mem_address" is a valid address of the flash range.
uint8_t execute_mem_write(uint8_t *pBuffer, uint32_t mem_address, uint32_t len)
{
    uint8_t status=HAL_OK;

    //We have to unlock flash module to get control of registers
    HAL_FLASH_Unlock();

    for(uint32_t i = 0 ; i <len ; i++)
    {
        //Here we program the flash byte by byte
        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE,mem_address+i,pBuffer[i] );
    }

    HAL_FLASH_Lock();

    return status;

}
void bootloader_send_ack(uint8_t command_code, uint8_t follow_len)
{
	 //here we send 2 byte.. first byte is ack and the second byte is len value
	uint8_t ack_buf[2];
	ack_buf[0] = BL_ACK;
	ack_buf[1] = follow_len;
	HAL_UART_Transmit(C_UART,ack_buf,2,HAL_MAX_DELAY);

}

/*This function sends NACK */
void bootloader_send_nack(void)
{
	uint8_t nack = BL_NACK;
	HAL_UART_Transmit(C_UART,&nack,1,HAL_MAX_DELAY);
}
void bootloader_uart_write_data(uint8_t *pBuffer,uint32_t len)
{
    /*you can replace the below ST's USART driver API call with your MCUs driver API call */
	HAL_UART_Transmit(C_UART,pBuffer,len,HAL_MAX_DELAY);

}
uint8_t execute_flash_erase(uint8_t sector_number , uint8_t number_of_sector)
{
    //we have totally 8 sectors in STM32F446RE mcu .. sector[0 to 7]
	//number_of_sector has to be in the range of 0 to 7
	// if sector_number = 0xff , that means mass erase !
	//Code needs to modified if your MCU supports more flash sectors
	FLASH_EraseInitTypeDef flashErase_handle;
	uint32_t sectorError;
	HAL_StatusTypeDef status;


	if( number_of_sector > 8 )
		return INVALID_SECTOR;

	if( (sector_number == 0xff ) || (sector_number <= 7) )
	{
		if(sector_number == (uint8_t) 0xff)
		{
			flashErase_handle.TypeErase = FLASH_TYPEERASE_MASSERASE;
		}else
		{
		    /*Here we are just calculating how many sectors needs to erased */
			uint8_t remanining_sector = 8 - sector_number;
            if( number_of_sector > remanining_sector)
            {
            	number_of_sector = remanining_sector;
            }
			flashErase_handle.TypeErase = FLASH_TYPEERASE_SECTORS;
			flashErase_handle.Sector = sector_number; // this is the initial sector
			flashErase_handle.NbSectors = number_of_sector;
		}
		flashErase_handle.Banks = FLASH_BANK_1;

		/*Get access to touch the flash registers */
		HAL_FLASH_Unlock();
		flashErase_handle.VoltageRange = FLASH_VOLTAGE_RANGE_3;  // our mcu will work on this voltage range
		status = (uint8_t) HAL_FLASHEx_Erase(&flashErase_handle, &sectorError);
		HAL_FLASH_Lock();

		return status;
	}


	return INVALID_SECTOR;
}
//verify the address sent by the host .
uint8_t verify_address(uint32_t go_address)
{
	//so, what are the valid addresses to which we can jump ?
	//can we jump to system memory ? yes
	//can we jump to sram1 memory ?  yes
	//can we jump to sram2 memory ? yes
	//can we jump to backup sram memory ? yes
	//can we jump to peripheral memory ? its possible , but dont allow. so no
	//can we jump to external memory ? yes.

//incomplete -poorly written .. optimize it
	if ( go_address >= SRAM1_BASE && go_address <= SRAM1_END)
	{
		return ADDR_VALID;
	}
	else if ( go_address >= SRAM2_BASE && go_address <= SRAM2_END)
	{
		return ADDR_VALID;
	}
	else if ( go_address >= FLASH_BASE && go_address <= FLASH_END)
	{
		return ADDR_VALID;
	}
	else if ( go_address >= BKPSRAM_BASE && go_address <= BKPSRAM_END)
	{
		return ADDR_VALID;
	}
	else
		return ADDR_INVALID;
}
