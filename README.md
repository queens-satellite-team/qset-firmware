# qset-firmware
This repository contains firmware to be used in STM32 controllers for the QSET - Satellite team. 

## Setup in STM32CubeIDE

1. In a terminal, change into the STM32CubeIDE project, for example:
```
cd /Users/seantedesco/STM32CubeIDE/workspace_1.10.1/nucleo-f411re-radio-controller/ 
```

2. Clone the Repository into the repository
```
git clone https://github.com/queens-satellite-team/qset-firmware.git
```

3. Open up STM32CubeIDE and navigate to the desired STM32 project.
a. **If creating a new project, choose C++ as the executable type!**

4. Include paths into the project properties. 
a. Navigate to *Project > Properties > C/C++ General > Paths and Symbols*
b. Select *Include*, *GNU C* and *Add...*
c. Select *Is a workspace path* and *Workspace...* and include the path to the program/Inc, communication/Inc, and any other folder as desired. 
d. Repeat for b. and c. *Include*, *GNU C++*, and *Add...* 
e. Move over to *Source Location* Tab, and select *Add Folder...* and add the paths to the program/Src, communication/Src, and any other folder as desired. 
f. Select *Apply and Close*

5. Modify the main.c folder
a. Include the header file for our main program.
```
/* USER CODE BEGIN Includes */
	#include "cppmain.h"
/* USER CODE END Includes */
```

b. Call our main function
```
/* USER CODE BEGIN 2 */
	cpp_main();
/* USER CODE END 2 */
```

c. Update hardware connections in "cppmain.h" to reflect the actual connections made with hardware. 
- include the _extern_ keyword before the _HandleTypeDef 
- an example, of what the "cppmain.h" should include is given below: 
```
extern I2C_HandleTypeDef hi2c1;		// i2c connection to RPi
extern SPI_HandleTypeDef hspi2;		// spi connection to rf24
extern SPI_HandleTypeDef hspi3;		// spi connection to RPi
extern UART_HandleTypeDef huart1;	// serial connection to RPi
extern UART_HandleTypeDef huart2;	// serial connection to host PC
```

6. Upload the Firmware
a. Build the project.
b. Run the project in a debugging session. 
