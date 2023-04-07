/** @file	utility.cpp
 *
 * @author	sean-tedesco
 * @date	2022-04-06
 */

/*********************************************************************************
 * INCLUDES
 */
#include "mocsat_main.h"
#include "utility.h"
#include "uart_protocol.h"

/**********************************************************************************/
void error_handler(qset_error_t error_code, const char* error_message){

	Serial printer(huart2);

	switch(error_code){
		case 0:	//i2c_io_error
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_11);	// yellow led
			printer.print_string((char*)error_message);
			break;
		case 1:	//uart_io_error
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_12);	// red led
			printer.print_string((char*)error_message);
			break;
	}
}
