
#include "../../../qset/Core/Inc/ant-db-func.h"
#define DPY_DTC_144_GPIO_3V3 GPIO_PIN_0 //Pin PB0
#define DPY_DTC_434_GPIO_3V3 GPIO_PIN_1 //Pin PB1
#define PWR_EN_144_3V3_GPIO GPIO_PIN_2 // Pin PB2
#define PWR_EN_434_3V3_GPIO GPIO_PIN_3 // Pin PB3


//buffer for i2c rx commands
uint8_t I2C_RX_BUFFER[1] = {0x01};

//THIS WILL NEED TO BE REDONE TO PARSE BUFFER
int get_command(uint8_t code){
	return code;
}

//set power enable of antennas - code 0x01
void do_deploy(){
	//write HI signal as enable
	HAL_GPIO_WritePin(GPIOB, PWR_EN_144_3V3_GPIO, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, PWR_EN_434_3V3_GPIO, GPIO_PIN_SET);
}

//return whether the antennas are deployed
int do_detect_144(){
	//read the input pins, logic 0 is not deployed, logic 1 if deployed
	return HAL_GPIO_ReadPin(GPIOB, DPY_DTC_144_GPIO_3V3);

}

int do_detect_434(){
	return HAL_GPIO_ReadPin(GPIOB, DPY_DTC_144_GPIO_3V3);
}

//variables for status of deployment
int deployed, status_144, status_434;

int antenna_db_main(I2C_HandleTypeDef hi2c1, UART_HandleTypeDef huart4){
	while(1){

		//not sure how to read the buffer
		uint8_t code = get_command(I2C_RX_BUFFER[0]);

		switch(code){
			case 1:
				do_deploy();
				break;

			case 2:
				status_144 = do_detect_144();
				status_434 = do_detect_434();
				deployed = status_144 & status_434;

				//do somthing if they are both deployed - set random pin high
				//change this part
				if(deployed){
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
				}else{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
				}
				break;

			default:
				break;
		}



	}
}
