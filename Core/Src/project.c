/*include*/
#include "main.h"

//////////////////////////////////
/*variable*/
int flag = 0;
const int32_t FND_Table[10] = {0x82007d00,0xdb002400,0x1600e900,0x1a00e500,
		0x4b00b400,0x2a00d500,0x2200dd00,0x9b006400,0x0200fd00,0x0a00f500};
unsigned int uiFND_Data = 0;
unsigned int FND_Buf[4]={};
//////////////////////////////////
void Initialize(void);
void Number_Transform(unsigned int);
//////////////////////////////////
void project_initialization(void)
{
	Initialize();
}

void project_main(void)
{

	while(1)
	{
		if(flag)
		{
			uiFND_Data ++;
			uiFND_Data %= 10000;
			Number_Transform(uiFND_Data);
			flag = 0;
		}
	}
}

//////////////////////////////////
void Initialize(void)
{
}

void Number_Transform(unsigned int input)
{
	FND_Buf[0] = FND_Table[input / 1000];
	FND_Buf[1] = FND_Table[(input % 1000) / 100];
	FND_Buf[2] = FND_Table[(input % 100) / 10];
	FND_Buf[3] = FND_Table[input % 10];
}
