/*include*/
#include "main.h"

//////////////////////////////////
/*variable*/
extern int flag;
int FND_sel = 0;
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
	uiFND_Data = 3486;
	FND_Buf[0] = uiFND_Data / 1000;
	FND_Buf[1] = (uiFND_Data % 1000) / 100;
	FND_Buf[2] = (uiFND_Data % 100) / 10;
	FND_Buf[3] = uiFND_Data % 10;
	while(1)
	{
		if(flag)
		{
			FND_sel++;
			FND_sel %= 4;
			flag = 0;
		}
	}
}

//////////////////////////////////
void Initialize(void)
{
}
