 /** @file	utility.h
 *
 * @author	sean-tedesco
 * @date	2023-04-01
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#define COUNTOF(__BUFFER__)	(sizeof(__BUFFER__) / sizeof (*(__BUFFER__)))

enum qset_error_t {
	i2c_io_error,
	uart_io_error
};

void error_handler(qset_error_t error_code, const char* error_message);

#endif /* UTILITY_H_ */
