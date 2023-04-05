/** @file	i2c_protocol.h
 *
 * @author	sean-tedesco
 * @date	2022-03-29
 */

#ifndef I2C_PROTOCOL_H_
#define I2C_PROTOCOL_H_


/****************************************************************************************************
 * GLOBAL CONTROLS
 * These are to be used in mocsat_main to handle communication on a i2c bus
 */
#define		I2C_BUFFER_SIZE	4
extern __IO uint32_t 		transfer_direction;
extern __IO uint32_t 		xfer_complete;
extern 		uint8_t			I2C_TX_BUFFER[I2C_BUFFER_SIZE];
extern 		uint8_t 		I2C_RX_BUFFER[I2C_BUFFER_SIZE];

/****************************************************************************************************
 * I2C CLASS
 * This class provides basic methods to transmit strings and numbers to another I2C device
 */
class I2C {
	public: // attributes
		I2C_HandleTypeDef internal_hi2c;


	public: // methods
		I2C(I2C_HandleTypeDef hi2c);
		void print_string(char* string);
		void print_uint8(uint8_t number);
};

#endif /* I2C_PROTOCOL_H_ */
