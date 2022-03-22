/*
 * bsp_i2c.h
 *
 * Created: 10/29/2021 1:12:07 PM
 *  Author: phuoc
 */ 
#ifndef _I2C_H_
#define _I2C_H_

void bsp_i2c_init();								/* I2C initialize function */
uint8_t  bps_i2c_start(char write_address);			/* I2C start function */
uint8_t  bsp_i2c_repeated_start(char read_address);	/* I2C repeated start function */
void bsp_i2c_stop();								/* I2C stop function */
void bsp_i2c_start_wait(char write_address);		/* I2C start wait function */
uint8_t  bsp_i2c_write(char data);					/* I2C write function */
char bsp_i2c_read_ack();							/* I2C read ack function */
char bsp_i2c_read_nack();

void bsp_i2c_slave_init(uint8_t slave_address);		/* I2C slave initialize function with Slave address */
int8_t bsp_i2c_slave_listen();						/* I2C slave listen function */
int8_t bsp_i2c_slave_transmit(char data);			/* I2C slave transmit function */
char bsp_i2c_slave_receive();

#endif