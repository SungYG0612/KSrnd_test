/*include*/
#include "main.h"

//////////////////////////////////
/*variable*/
extern int flag;
const int32_t FND_Number[10] = {0x82007d00,0xdb002400,0x1600e900,0x1a00e500,0x4b00b400,0x2a00d500,0x2200dd00,0x9b006400,0x0200fd00,0x0a00f500};
int FND_Buf[4] = {1,2,3,4};

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
		if(flag)
		{
			flag = 0;
		}
	}
}

//////////////////////////////////
void Initialize(void)
{

}
