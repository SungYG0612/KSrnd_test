/*include*/
#include "main.h"

//////////////////////////////////
/*define*/

//////////////////////////////////
/*variable*/
const unsigned int FND_Number_Table[10] = {0x82007d00,0xdb002400,0x1600e900,0x1a00e500,
		0x4b00b400,0x2a00d500,0x2200dd00,0x9b006400,0x0200fd00,0x0a00f500};

int bADC_Flag = 0;

unsigned int uiDisplay_Data[4] = {};
unsigned int uiADC_Buf[16] = {};
//////////////////////////////////
void Initialize(void);
void Number_Convert(int,int);

//////////////////////////////////
void project_initialization(void)
{
	Initialize();
}

void project_main(void)
{
	while(1)
	{
		if(bADC_Flag)
		{
			unsigned int uiADC_Data = 0;
			for(int num = 0;num < 16;num ++)
			{
				uiADC_Data += uiADC_Buf[num];
			}
			uiADC_Data /= 4;
			Number_Convert(uiADC_Data, 0);
			bADC_Flag = 0;
		}
	}
}

//////////////////////////////////
void Initialize(void)
{
	Number_Convert(0,0);
}
void Number_Convert(int number, int Flag)	//숫자 => Digit bit 변환 함수
{
	unsigned int uiData = 0;
	if(number>9999) {number=9999;}

	uiData = number/1000;
	if(uiData==0 && Flag) {uiDisplay_Data[0] = 0xff000000;}
	else
	{
		uiDisplay_Data[0] = FND_Number_Table[uiData];
		Flag = 0;
	}
	uiData = (number%1000)/100;
	if(uiData==0 && Flag) {uiDisplay_Data[1] = 0xff000000;}
	else
	{
		uiDisplay_Data[1] = FND_Number_Table[uiData];
		Flag = 0;
	}
	uiData = (number%100)/10;
	if(uiData==0 && Flag) {uiDisplay_Data[2] = 0xff000000;}
	else
	{
		uiDisplay_Data[2] = FND_Number_Table[uiData];
		Flag = 0;
	}
	uiDisplay_Data[3] = FND_Number_Table[number%10];
}
