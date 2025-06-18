/*include*/
#include "main.h"

//////////////////////////////////
/*define*/
//////////////////////////////////
/*variable*/
uint8_t rx_data=0;

extern UART_HandleTypeDef huart5;
//////////////////////////////////
void Initialize(void);

//////////////////////////////////
void project_initialization(void)
{
	Initialize();
}

void project_main(void)
{
	HAL_UART_Transmit(&huart5, &rx_data, 1, 10);
	while(1)
	{
	}
}

//////////////////////////////////
void Initialize(void)
{
	HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, 1);
	HAL_Delay(500);
}

