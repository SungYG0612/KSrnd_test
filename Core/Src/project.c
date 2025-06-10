/*include*/
#include "main.h"

//////////////////////////////////
/*variable*/
extern int flag;
extern int FND_sel;
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
