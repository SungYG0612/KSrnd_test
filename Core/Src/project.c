/*include*/
#include "main.h"

//////////////////////////////////
/*define*/


//////////////////////////////////
/*variable*/
const unsigned int FND_Number_Table[10] = {0x82007d00,0xdb002400,0x1600e900,0x1a00e500,0x4b00b400,0x2a00d500,
		0x2200dd00,0x9b006400,0x0200fd00,0x0a00f500};
const unsigned int FND_Port_Table[4] = {0x70008000, 0xb0004000, 0xd0002000, 0xe0001000};

int bButton_Flag = 0;
int bSet_Flag = 0;
int bSel_Flag = 0;
int iNumber_Buf = 0;
int bBlink_Flag = 0;
int bNo_Blink_Flag = 0;
int bLong_Key_Flag = 0;

unsigned int uiPin_value = 0;
unsigned int iNumber_list[4] = {};
unsigned int uiBlink_FND = 0;
unsigned int uiNumber_Display_Buf[4] = {};
unsigned int uiFND_Port_Buf[4] = {};
unsigned int uiBlink_Port_Data = 0;
unsigned int uiLong_Key_Data = 0;

//////////////////////////////////
void Initialize(void);
void Number_convert(void);

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
				if(bSet_Flag)
				{
					iNumber_list[uiBlink_FND]++;
				}
				break;

			case Down_Button:
				if(bSet_Flag)
				{
					iNumber_list[uiBlink_FND]--;
				}
				break;

			case Set_Button:
				bSet_Flag = 1;
				break;

			case Sel_Button:
				bSel_Flag = 1;
				break;

			case Reset_Button:
				iNumber_list[0] = 0;
				iNumber_list[1] = 0;
				iNumber_list[2] = 0;
				iNumber_list[3] = 0;
				bSet_Flag = 0;
				break;
			}
			Number_convert();
			bButton_Flag = 0;
		}

		if(bNo_Blink_Flag)
		{
			uiFND_Port_Buf[0] = uiBlink_Port_Data[0];
			uiFND_Port_Buf[1] = uiBlink_Port_Data[1];
			uiFND_Port_Buf[2] = uiBlink_Port_Data[2];
			uiFND_Port_Buf[3] = uiBlink_Port_Data[3];
			bNo_Blink_Flag = 0;
		}

		if(bBlink_Flag)
		{
			switch(uiBlink_Sel)
			{
			case 0:
				uiFND_Port_Buf[0] = uiBlink_Port_Data[0];
				uiFND_Port_Buf[1] = uiBlink_Port_Data[1];
				uiFND_Port_Buf[2] = uiBlink_Port_Data[2];
				uiFND_Port_Buf[3] = uiBlink_Port_Data[3];
				uiBlink_Sel = 1;
				break;
			case 1:
				uiFND_Port_Buf[0] = FND_Port_Table[0];
				uiFND_Port_Buf[1] = FND_Port_Table[1];
				uiFND_Port_Buf[2] = FND_Port_Table[2];
				uiFND_Port_Buf[3] = FND_Port_Table[3];
				uiBlink_Sel = 0;
				break;
			}
			bBlink_Flag = 0;
		}
	}
}

/////////////////////////////////////////////////
void Initialize(void)
{
	Number_convert();
}

/////////////////////////////////////////////////
void Number_convert()		//숫자 변환 함수
{
	unsigned int uiNumber_len = 0;

	if(iNumber_list[uiBlink_FND]>9) {iNumber_list[uiBlink_FND] = 0;}
	if(iNumber_list[uiBlink_FND]<0) {iNumber_list[uiBlink_FND] = 9;}
	/*자릿수 체크*/
	if(iNumber_list[0] == 0)
	{
		if(iNumber_list[1] == 0)
		{
			if(iNumber_list[2] == 0)
			{
				uiNumber_len ++;
			}
			uiNumber_len ++;
		}
		uiNumber_len ++;
	}
	/*Leading Zero*/
	for(int sel=0; sel<4; sel++)
	{
		if(bSet_Flag)
		{
			uiFND_Port_Buf[sel] = FND_Port_Table[sel];
		}
		else
		{
			switch(sel<uiNumber_len)
			{
				case False:
					uiFND_Port_Buf[sel] = FND_Port_Table[sel];
					break;
				case True:
					uiFND_Port_Buf[sel] = 0xff000000;
					break;
			}
		}
		uiNumber_Display_Buf[sel] = FND_Number_Table[iNumber_list[sel]];
	}
}

///////////////////////////////////////////////////////
/*Blink FND 변경*/

