/** @file	uart_protocol.cpp
 *
 * @author	sean-tedesco
 * @date	2022-02-03
 */

#include <cppmain.h>
#include <uart_protocol.h>
#include "string.h"

/****************************************************************************************************/
uint16_t uart1_rxidx = 0;
uint8_t uart1_rx_flag = 0;
uint8_t uart1_rx_buffer[max_rx_buffer_size] = {0};
uint8_t uart1_rx_byte = 0;

uint16_t uart2_rxidx = 0;
uint8_t uart2_rx_flag = 0;
uint8_t uart2_rx_buffer[max_rx_buffer_size] = {0};
uint8_t uart2_rx_byte = 0;

/****************************************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1){
		if (uart1_rx_byte == '>' || uart1_rxidx >= max_rx_buffer_size) {
			uart1_rx_buffer[uart1_rxidx] = uart1_rx_byte;
			uart1_rx_flag = 1;
			uart1_rxidx = 0;
		} else {
			uart1_rx_buffer[uart1_rxidx] = uart1_rx_byte;
			uart1_rxidx++;

		}
	HAL_UART_Receive_IT(&huart1, &uart1_rx_byte, 1);
	}
	if(huart->Instance == USART2){
		if (uart2_rx_byte == '>' || uart2_rxidx >= max_rx_buffer_size) {
			uart2_rx_buffer[uart2_rxidx] = uart2_rx_byte;
			uart2_rx_flag = 1;
			uart2_rxidx = 0;
		} else {
			uart2_rx_buffer[uart2_rxidx] = uart2_rx_byte;
			uart2_rxidx++;

		}
	HAL_UART_Receive_IT(&huart2, &uart2_rx_byte, 1);
	}

}

/****************************************************************************************************/
Serial::Serial(UART_HandleTypeDef huart)
{
	internal_huart = huart;
}

/****************************************************************************************************/
void Serial::print_string( char* string)
{
	uint8_t buf[strlen(string)];
	strcpy((char*)buf, string);
	HAL_UART_Transmit(&internal_huart, buf, strlen((char*)buf), HAL_MAX_DELAY);
}

/****************************************************************************************************/
void Serial::print_uint8(uint8_t number)
{
	uint8_t buf[4];
	sprintf((char*)buf, "%d", number);
	HAL_UART_Transmit(&internal_huart, buf, strlen((char*)buf), HAL_MAX_DELAY);
}

/****************************************************************************************************/
