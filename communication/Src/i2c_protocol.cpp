/** @file	i2c_protocol.cpp
 *
 * @author	sean-tedesco
 * @date	2022-03-29
 */

/*********************************************************************************
 * INCLUDES
 */
#include <mocsat_main.h>
#include <i2c_protocol.h>
#include "string.h"

/*********************************************************************************
 * LOCAL VARIABLES
 */
__IO uint32_t transfer_direction = 0;
__IO uint32_t xfer_complete = 0;
uint8_t I2C_TX_BUFFER[I2C_BUFFER_SIZE] = {0};
uint8_t I2C_RX_BUFFER[I2C_BUFFER_SIZE] = {0};

/*********************************************************************************
 * HAL I2C FUNCTIONS
 */
extern void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
	transfer_direction = TransferDirection;
	if (transfer_direction != 0){
		// start transmission process
		if (HAL_I2C_Slave_Seq_Transmit_IT(hi2c, (uint8_t *)I2C_TX_BUFFER, I2C_BUFFER_SIZE, I2C_FIRST_AND_LAST_FRAME) != HAL_OK){
		} else {
		}
	} else {
		// start reception process
		if (HAL_I2C_Slave_Seq_Receive_IT(hi2c, (uint8_t *)I2C_RX_BUFFER, I2C_BUFFER_SIZE, I2C_FIRST_AND_LAST_FRAME) != HAL_OK){
		} else {
		}
	}
}

extern void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{

}

extern void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
	if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF){
	}
}

extern void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	xfer_complete = 1;
	I2C_TX_BUFFER[0]++;
	I2C_TX_BUFFER[1]++;
	I2C_TX_BUFFER[2]++;
	I2C_TX_BUFFER[3]++;
}

extern void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	xfer_complete = 1;
}

/****************************************************************************************************
 * I2C CLASS
 */
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
