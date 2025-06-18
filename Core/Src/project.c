/*include*/
#include "main.h"

//////////////////////////////////
/*define*/
//////////////////////////////////
/*variable*/
uint8_t received = '\0';
HAL_StatusTypeDef rcvStat;

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
	while(1)
	{
		rcvStat = HAL_UART_Receive(&huart5, &received, 1, 10);
		if(rcvStat == HAL_OK)
		{
			HAL_UART_Transmit(&huart5, &received, 1, 1000); //읽어드린 값 터미널로 출력
		}
	}
}

//////////////////////////////////
void Initialize(void)
{
	HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, 1);
	HAL_Delay(500);
}

