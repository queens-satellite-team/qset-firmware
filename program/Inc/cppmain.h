/** @file	cppmain.h
 *
 * @author	sean-tedesco
 * @date	2023-02-03
 */

#ifndef PROGRAM_INC_CPPMAIN_H_
#define PROGRAM_INC_CPPMAIN_H_

#ifdef __cplusplus
 extern "C" {
#endif


#include "main.h"
#include <string.h>
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;		// i2c connection to RPi
extern SPI_HandleTypeDef hspi2;		// spi connection to rf24
extern SPI_HandleTypeDef hspi3;		// spi connection to RPi
extern UART_HandleTypeDef huart1;	// serial connection to RPi
extern UART_HandleTypeDef huart2;	// serial connection to host PC

void cpp_main(void);

#ifdef __cplusplus
}
#endif

#endif /* PROGRAM_INC_CPPMAIN_H_ */
