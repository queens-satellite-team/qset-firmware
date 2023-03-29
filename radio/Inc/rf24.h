/** @file	rf24.h
 *
 * @author	sean-tedesco
 * @date	2022-02-11
 */

#ifndef RADIO_INC_RF24_H_
#define RADIO_INC_RF24_H_

/****************************************************************************************************
 * GLOBAL CONTROLS
 * These are to be used in cppmain to handle communication with the radio
 */


/****************************************************************************************************
 * RF24 CLASS
 * This class provides basic methods to transmit strings and numbers to the console
 */
class RF24 {
	public: // attributes
		SPI_HandleTypeDef internal_hspi;
		char ce_port;
		char csn_port;
		uint8_t ce_pin;
		uint8_t csn_pin;

	public: // methods
		RF24(SPI_HandleTypeDef hspi);
		void init(void);
		void change_tx_mode (uint8_t *address, uint8_t channel);
		void change_rx_mode (uint8_t *Address, uint8_t channel);

		uint8_t transmit(uint8_t *data);
		void 	receive (uint8_t *data);
		uint8_t is_data_available (int pipenum);
		void 	read_all (uint8_t *data);

		void 	write_reg(uint8_t reg, uint8_t data);
		uint8_t read_reg(uint8_t reg);


	private: // methods
		void chip_select_n(void);
		void chip_deselect_n(void);
		void chip_enable(void);
		void chip_disable(void);
};

#endif /* RADIO_INC_RF24_H_ */
