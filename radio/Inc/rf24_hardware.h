/** @file	rf24_hardware.h
 *
 * @author	sean-tedesco
 * @date	2022-03-29
 */

#ifndef RADIO_INC_RF24_HARDWARE_H_
#define RADIO_INC_RF24_HARDWARE_H_

// Define the Chip-Enable GPIO address
#define NRF24_CE_PORT   GPIOB
#define NRF24_CE_PIN    GPIO_PIN_7

// Define the Chip-Select GPIO address.
#define NRF24_CSN_PORT   GPIOB
#define NRF24_CSN_PIN    GPIO_PIN_6


#endif /* RADIO_INC_RF24_HARDWARE_H_ */
