/** @file	i2c_protocol.cpp
 *
 * @author	sean-tedesco
 * @date	2022-03-29
 */

#include <mocsat_main.h>
#include <i2c_protocol.h>
#include "string.h"

/****************************************************************************************************/
uint16_t i2c1_rxidx = 0;
uint8_t i2c1_rx_flag = 0;
uint8_t i2c1_rx_buffer[max_rx_buffer_size] = {0};
uint8_t i2c1_rx_byte = 0;

/****************************************************************************************************/
void HAL_I2C_RxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c->Instance == I2C1){
		if (i2c1_rx_byte == '>' || i2c1_rxidx >= max_rx_buffer_size) {
			i2c1_rx_buffer[i2c1_rxidx] = i2c1_rx_byte;
			i2c1_rx_flag = 1;
			i2c1_rxidx = 0;
		} else {
			i2c1_rx_buffer[i2c1_rxidx] = i2c1_rx_byte;
			i2c1_rxidx++;

		}
	HAL_I2C_Slave_Receive_IT(&hi2c1, &i2c1_rx_byte, 1);
	}
}

/****************************************************************************************************/
I2C::I2C(I2C_HandleTypeDef hi2c)
{
	internal_hi2c = hi2c;
}

/****************************************************************************************************/
void I2C::print_string(char* string)
{
	uint8_t buf[strlen(string)];
	strcpy((char*)buf, string);
	HAL_I2C_Slave_Transmit(&internal_hi2c, buf, strlen((char*)buf), HAL_MAX_DELAY);
}

/****************************************************************************************************/
void I2C::print_uint8(uint8_t number)
{
	uint8_t buf[4];
	sprintf((char*)buf, "%d", number);
	HAL_I2C_Slave_Transmit(&internal_hi2c, buf, strlen((char*)buf), HAL_MAX_DELAY);
}

/****************************************************************************************************/
