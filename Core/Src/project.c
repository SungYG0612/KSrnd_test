/*include*/
#include "main.h"

//////////////////////////////////
/*define*/
//////////////////////////////////
/*variable*/
int bReceive_Flag = 0;
unsigned char ucReceive_Buf[] = {};

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
	}
}

//////////////////////////////////
void Initialize(void)
{
	HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, 1);
	HAL_Delay(500);
}

