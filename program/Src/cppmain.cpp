/** @file	cppmain.cpp
 *
 * @author	sean-tedesco
 * @date	2022-02-03
 */

/*********************************************************************************
 * INCLUDES
 */
#include <cppmain.h>
#include <uart_protocol.h>
#include <i2c_protocol.h>
#include <rf24.h>
#include <rf24_registers.h>

/*********************************************************************************
 * LOCAL VARIABLES
 */
uint8_t rx_data[32];
uint8_t tx_data[32];

/*********************************************************************************
 * LOCAL FUNCTIONS
 */


// do stuff once
void cpp_main(){

	I2C 	transmitter(hi2c2);
	RF24	radio(hspi2);

	uint8_t desired_reg = (uint8_t) CONFIG;
	uint8_t config_data = (uint8_t) 0x0A;

	radio.write_reg(desired_reg, config_data);
	radio.read_reg(desired_reg);


	while(1){
		transmitter.print_string("sending to obc: ");
		transmitter.print_uint8(10);
		transmitter.print_string("\r\n");

		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
		HAL_Delay(200);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
		HAL_Delay(1000);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
		HAL_Delay(200);
	}
}
