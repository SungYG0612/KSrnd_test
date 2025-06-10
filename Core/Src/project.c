/*include*/
#include "main.h"

//////////////////////////////////
/*variable*/
const int32_t FND_Number[10] = {0x82007d00,0xdb002400,0x1600e900,0x1a00e500,
		0x4b00b400,0x2a00d500,0x2200dd00,0x9b006400,0x0200fd00,0x0a00f500};
unsigned int uiFND_Data = 0;
unsigned int FND_Buf[4]={};
//////////////////////////////////
void Initialize(void);

//////////////////////////////////
void project_initialization(void)
{
	Initialize();
}

void project_main(void)
{
	uiFND_Data = 512;
	FND_Buf[0] = FND_Number[uiFND_Data / 1000];
	FND_Buf[1] = FND_Number[(uiFND_Data % 1000) / 100];
	FND_Buf[2] = FND_Number[(uiFND_Data % 100) / 10];
	FND_Buf[3] = FND_Number[uiFND_Data % 10];
	while(1)
	{
	}
}

//////////////////////////////////
void Initialize(void)
{
}
