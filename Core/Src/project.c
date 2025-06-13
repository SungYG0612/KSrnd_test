/*include*/
#include "main.h"

//////////////////////////////////
/*define*/
#define Down_Button 0x0400
#define Set_Button 0x0800
#define Up_Button 0x1000
#define Sel_Button 0x2000
#define Reset_Button 0x4000

//////////////////////////////////
/*variable*/
int bButton_Flag = 0;
int bSet_Flag = 0;
int bBlink_Flag = 0;
int bLong_Key_Flag = 0;

const unsigned int FND_Number_Table[10] = {0x82007d00,0xdb002400,0x1600e900,0x1a00e500,
		0x4b00b400,0x2a00d500,0x2200dd00,0x9b006400,0x0200fd00,0x0a00f500};
const unsigned int FND_Port_Table[4] = {0x70008000, 0xb0004000, 0xd0002000, 0xe0001000};

int iNumber = 0;
int iNumber_list[4] = {};
unsigned int uiBlink_FND = 0;

//////////////////////////////////
void Initialize(void);
void Number_convert(int);
void Blink_convert(int);

//////////////////////////////////
void project_initialization(void)
{
	HAL_Delay(1000);

	Initialize();
}

void project_main(void)
{
	while(1)
	{
		if(bButton_Flag)
		{
			switch(uiPin_value)
			{
			case Up_Button:
				iNumber_list[uiBlink_FND]++;
				break;

			case Down_Button:
				iNumber_list[uiBlink_FND]--;
				break;

			case Set_Button:

				break;

			case Sel_Button:

				break;

			case Reset_Button:

				break;
			}
			bButton_Flag = 0;
		}
	}
}

/////////////////////////////////////////////////
void Initialize(void)
{
	Number_convert(iNumber);
	for(int sel=0; sel<4; sel++) {uiFND_Port_Buf[sel] = FND_Port_Table[sel];}
}

/////////////////////////////////////////////////
void Number_convert(int Input_Data)		//숫자 변환 함수
{

}

///////////////////////////////////////////////////////
/*Blink FND 변경*/
