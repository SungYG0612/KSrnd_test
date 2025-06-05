#include "function.h"

void toggle()
{
	if(time_value >= 500)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		time_value = 0;
	}
	time_value += 1;
}
