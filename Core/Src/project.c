/*include*/
#include "main.h"

//////////////////////////////////
/*define*/

//////////////////////////////////
/*variable*/
int Pin_value = 0;
const int32_t FND_Table[10] = {0x82007d00,0xdb002400,0x1600e900,0x1a00e500,
		0x4b00b400,0x2a00d500,0x2200dd00,0x9b006400,0x0200fd00,0x0a00f500};
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
		Pin_value = GPIOD->IDR;
		Pin_value = (Pin_value & 0x7c) ^ 0x7c;
		if(Pin_value & 0x0400) {GPIOE->BSRR = FND_Table[1];}
		if(Pin_value & 0x0800) {GPIOE->BSRR = FND_Table[2];}
		if(Pin_value & 0x1000) {GPIOE->BSRR = FND_Table[3];}
		if(Pin_value & 0x2000) {GPIOE->BSRR = FND_Table[4];}
		if(Pin_value & 0x4000) {GPIOE->BSRR = FND_Table[5];}
	}
}

//////////////////////////////////
void Initialize(void)
{
	GPIOE->BSRR = FND_Table[0];
}

