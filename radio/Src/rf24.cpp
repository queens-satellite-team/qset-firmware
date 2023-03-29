/** @file	rf24.cpp
 *
 * @author	sean-tedesco
 * @date	2022-03-29
 */

#include <cppmain.h>
#include <rf24.h>
#include <rf24_registers.h>
#include <rf24_hardware.h>
#include "string.h"

/****************************************************************************************************/
RF24::RF24(SPI_HandleTypeDef hspi)
{
	internal_hspi = hspi;
}

/****************************************************************************************************/
void RF24::init(void){

}

/****************************************************************************************************/
void RF24::chip_select_n(void){
	HAL_GPIO_WritePin(NRF24_CSN_PORT, NRF24_CSN_PIN, GPIO_PIN_RESET);
}
/****************************************************************************************************/
void RF24::chip_deselect_n(void){
	HAL_GPIO_WritePin(NRF24_CSN_PORT, NRF24_CSN_PIN, GPIO_PIN_SET);
}
/****************************************************************************************************/
void RF24::chip_enable(void){
	HAL_GPIO_WritePin(NRF24_CE_PORT, NRF24_CE_PIN, GPIO_PIN_SET);
}
/****************************************************************************************************/
void RF24::chip_disable(void){
	HAL_GPIO_WritePin(NRF24_CE_PORT, NRF24_CE_PIN, GPIO_PIN_SET);
}


/****************************************************************************************************/
void RF24::write_reg(uint8_t reg, uint8_t data)
{
	uint8_t buf[2]; // format the SPI payload in buf.
	buf[0] = reg|1<<5; // Shift the register. We are working with binary data.
	buf[1] = data;

	// Pull the CS Pin LOW to select the device
	chip_select_n();

	HAL_SPI_Transmit(&internal_hspi, buf, 2, 1000);

	// Pull the CS HIGH to release the device
	chip_deselect_n();
}

/****************************************************************************************************/
uint8_t RF24::read_reg(uint8_t reg)
{
	uint8_t data=0;

	// Pull the CS Pin LOW to select the device
	chip_select_n();

	HAL_SPI_Transmit(&internal_hspi, &reg, 1, 100);
	HAL_SPI_Receive(&internal_hspi, &data, 1, 100);

	// Pull the CS HIGH to release the device
	chip_deselect_n();

	return data;
}
