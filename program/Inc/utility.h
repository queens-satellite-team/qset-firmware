 /** @file	utility.h
 *
 * @author	sean-tedesco
 * @date	2023-04-01
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include "mocsat_main.h"
#include "uart_protocol.h"

#define COUNTOF(__BUFFER__)	(sizeof(__BUFFER__) / sizeof (*(__BUFFER__)))

enum qset_error_t {
	i2c_io_error,
	uart_io_error
};

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

#endif /* UTILITY_H_ */
