 /** @file	mocsat_main.h
 *
 * @author	sean-tedesco
 * @date	2023-02-03
 */

#ifndef PROGRAM_INC_MOCSAT_MAIN_H_
#define PROGRAM_INC_MOCSAT_MAIN_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include <string.h>
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;		// i2c connection to RPi
extern UART_HandleTypeDef huart1;	// serial connection to RPi
extern UART_HandleTypeDef huart2;	// serial connection to host PC
extern SPI_HandleTypeDef hspi2;		// spi connection not currently used

void mocsat_main(void);

#ifdef __cplusplus
}
#endif

#endif /* PROGRAM_INC_MOCSAT_MAIN_H_ */
