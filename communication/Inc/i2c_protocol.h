/** @file	i2c_protocol.h
 *
 * @author	sean-tedesco
 * @date	2022-03-29
 */

#ifndef COMMUNICATION_INC_I2C_PROTOCOL_H_
#define COMMUNICATION_INC_I2C_PROTOCOL_H_

#define max_rx_buffer_size 128

/****************************************************************************************************
 * GLOBAL CONTROLS
 * These are to be used in mocsat_main to handle communication on a i2c bus
 */
extern uint8_t i2c1_rx_buffer[max_rx_buffer_size];
extern uint8_t i2c1_rx_byte;
extern uint8_t i2c1_rx_flag;

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

#endif /* COMMUNICATION_INC_I2C_PROTOCOL_H_ */
