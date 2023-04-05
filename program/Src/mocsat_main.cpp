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
 * LOCAL VARIABLES
 */
uint8_t buffer[32];
uint8_t loop_count = 0;

/*********************************************************************************
 * LOCAL FUNCTIONS
 */


// do stuff once
void mocsat_main(){

	I2C 	i2c_rpi(hi2c1);
	Serial	uart_rpi(huart1);
	Serial	uart_debug(huart2);

	I2C_TX_BUFFER[0] = 0xAA;
	I2C_TX_BUFFER[1] = 0xBB;
	I2C_TX_BUFFER[2] = 0xCC;
	I2C_TX_BUFFER[3] = 0xDD;

	// HAL_UART_Receive_IT(&huart1, &uart1_rx_byte, 1); 		// receive on huart1 from the pi

	if(HAL_I2C_EnableListen_IT(&hi2c1) != HAL_OK){
		error_handler(i2c_io_error, "failed to enable listen\r\n");
	} else {
		error_handler(i2c_io_error, "success to enable listen\r\n");
	}

	while(1){

		uart_debug.print_string((char*) "Start of Loop: ");
		uart_debug.print_uint8(loop_count);
		uart_debug.print_string((char*) "\r\n");

		if (xfer_complete == 1){
			HAL_Delay(1);
			if(HAL_I2C_EnableListen_IT(&hi2c1) != HAL_OK){
				error_handler(i2c_io_error, "fail to loop listen\r\n");
			} else {
				error_handler(i2c_io_error, "success to loop listen\r\n");
			}
			xfer_complete = 0;
		}
		/****************************************************************************************************/
		/************************************* MAIN BODY ****************************************************/


		// print the results of the rx buffer
		uart_debug.print_string((char*) "RX Buffer: ");
		uart_debug.print_array(I2C_RX_BUFFER);


		/****************************************************************************************************/

		// update the debug screen just so we can see some activity
		uart_debug.print_string((char*) "End of Loop: ");
		uart_debug.print_uint8(loop_count);
		uart_debug.print_string((char*) "\r\n");
		uart_debug.print_string((char*) "\r\n");
		loop_count++;

		// flash the built in LED just so we can see some activity
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
		HAL_Delay(2000);
	}
}
