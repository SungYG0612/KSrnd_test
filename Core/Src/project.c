/*include*/
#include "main.h"

//////////////////////////////////
/*variable*/
extern int flag;
int FND_Buf[4] = {0,6,1,2};
int FND_sel = 0;

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
