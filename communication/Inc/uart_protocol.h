/** @file	uart_protocol.h
 *
 * @author	sean-tedesco
 * @date	2022-02-03
 */

#ifndef COMMUNICATION_INC_UART_PROTOCOL_H_
#define COMMUNICATION_INC_UART_PROTOCOL_H_


/****************************************************************************************************
 * GLOBAL CONTROLS
 * These are to be used in cppmain to handle communication from UART channels
 */
extern uint8_t uart1_rx_flag;
extern uint8_t uart2_rx_flag;

/****************************************************************************************************
 * SERIAL CLASS
 * This class provides basic methods to transmit strings and numbers to the console
 */
class Serial {
	public: // attributes
		UART_HandleTypeDef internal_huart;

	public: // methods
		Serial(UART_HandleTypeDef huart);
		void print_string(char* string);
		void print_uint8(uint8_t number);
};

#endif /* COMMUNICATION_INC_UART_PROTOCOL_H_ */
