/** @file	mocsat_main.cpp
 *
 * @author	sean-tedesco
 * @date	2022-02-03
 */

/*********************************************************************************
 * INCLUDES
 */
#include <mocsat_main.h>
#include <utility.h>
#include <uart_protocol.h>
#include <i2c_protocol.h>
#include <rf24.h>
#include <rf24_registers.h>

/*********************************************************************************
 * DEFINES
 */
#define	TXBUFFERSIZE	(COUNTOF(tx_buffer))
#define	RXBUFFERSIZE	TXBUFFERSIZE

/*********************************************************************************
 * LOCAL VARIABLES
 */
uint8_t buffer[32];
uint8_t loop_count = 0;

__IO uint32_t transfer_direction = 0;
__IO uint32_t xfer_complete = 0;
uint8_t tx_buffer[4];
uint8_t rx_buffer[4];

/*********************************************************************************
 * LOCAL FUNCTIONS
 */


extern void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
	transfer_direction = TransferDirection;
	if (transfer_direction != 0){
		// start transmission process
		if (HAL_I2C_Slave_Seq_Transmit_IT(hi2c, (uint8_t *)tx_buffer, TXBUFFERSIZE, I2C_FIRST_AND_LAST_FRAME) != HAL_OK){
			error_handler(i2c_io_error, "seq tx bad\r\n");
		} else {
			error_handler(i2c_io_error, "seq tx good\r\n");
		}
	} else {
		// start reception process
		if (HAL_I2C_Slave_Seq_Receive_IT(hi2c, (uint8_t *)rx_buffer, RXBUFFERSIZE, I2C_FIRST_AND_LAST_FRAME) != HAL_OK){
			error_handler(i2c_io_error, "seq rx bad\r\n");
		} else {
			error_handler(i2c_io_error, "seq rx good\r\n");
		}
	}
}

extern void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
	error_handler(i2c_io_error, "reached listen callback\r\n");

}

extern void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
	if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF){
		error_handler(i2c_io_error, "error callback bad\r\n");
	}
}

extern void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	error_handler(i2c_io_error, "tx callback\r\n");
	xfer_complete = 1;
	tx_buffer[0]++;
	tx_buffer[1]++;
	tx_buffer[2]++;
	tx_buffer[3]++;
}

extern void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	error_handler(i2c_io_error, "rx callback\r\n");
	xfer_complete = 1;
}

// do stuff once
void mocsat_main(){

	I2C 	i2c_rpi(hi2c1);
	Serial	uart_rpi(huart1);
	Serial	uart_debug(huart2);


	for (uint8_t i=0; i<RXBUFFERSIZE; i++){
		rx_buffer[i] = 0x00;
	}
	tx_buffer[0] = 0xAA;
	tx_buffer[1] = 0xBB;
	tx_buffer[2] = 0xCC;
	tx_buffer[3] = 0xDD;

	// HAL_UART_Receive_IT(&huart1, &uart1_rx_byte, 1); 		// receive on huart1 from the pi

	if(HAL_I2C_EnableListen_IT(&hi2c1) != HAL_OK){
		error_handler(i2c_io_error, "failed to enable listen\r\n");
	} else {
		error_handler(i2c_io_error, "success to enable listen\r\n");
	}

	while(1){

		if (xfer_complete == 1){
			HAL_Delay(1);
			if(HAL_I2C_EnableListen_IT(&hi2c1) != HAL_OK){
				error_handler(i2c_io_error, "fail to loop listen\r\n");
			} else {
				error_handler(i2c_io_error, "success to loop listen\r\n");
			}
			xfer_complete = 0;
		}

		// print the results of the rx buffer
		uart_debug.print_string((char*) "RX Buffer: ");
		for (uint8_t i=0; i<RXBUFFERSIZE; i++){
			uart_debug.print_uint8(rx_buffer[i]);
			uart_debug.print_string((char*) ", ");
		}
		uart_debug.print_string((char*) "\r\n");

		// update the debug screen just so we can see some activity
		uart_debug.print_string((char*) "Loop: ");
		uart_debug.print_uint8(loop_count);
		uart_debug.print_string((char*) "\r\n");
		loop_count++;

		// flash the built in LED just so we can see some activity
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
		HAL_Delay(2000);
	}
}
