/*include*/
#include "main.h"

//////////////////////////////////
/*define*/

//////////////////////////////////
/*variable*/
int bButton_Flag = 0;
int bLong_Button_Flag = 0;
int bSet_Flag = 0;
int bBlink_Flag = 0;
int bSel_Flag = 0;
int bLeading_Zero_Flag = 0;

const unsigned int FND_Number_Table[10] = {0x82007d00,0xdb002400,0x1600e900,0x1a00e500,
		0x4b00b400,0x2a00d500,0x2200dd00,0x9b006400,0x0200fd00,0x0a00f500};
const unsigned int FND_Port_Table[4] = {0x70008000, 0xb0004000, 0xd0002000, 0xe0001000};

int iNumber = 1234;
unsigned int uiDisplay_Data[4] = {};
unsigned int uiBlink_Time = 0;
unsigned int uiButton_Data = 0x0000;
unsigned int uiBlink_Sel = 0;
//////////////////////////////////
void Initialize(void);
void Number_convert(int,int);

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
			switch(uiButton_Data)
			{
			case Up_button:
				if(bSet_Flag)
				{
					switch(uiBlink_Sel)
					{
					case 0:
						if(iNumber>=9000) {iNumber-=9000;}
						else {iNumber+=1000;}
						break;
					case 1:
						if(iNumber%1000>=900) {iNumber-=900;}
						else {iNumber+=100;}
						break;
					case 2:
						if(iNumber%100>=90) {iNumber-=90;}
						else {iNumber+=10;}
						break;
					case 3:
						if(iNumber%10>=9) {iNumber-=9;}
						else {iNumber+=1;}
						break;
					}
				}
				break;
			case Down_button:
				if(bSet_Flag)
				{
					switch(uiBlink_Sel)
					{
					case 0:
						if(iNumber<1000) {iNumber+=9000;}
						else {iNumber-=1000;}
						break;
					case 1:
						if(iNumber%1000<100) {iNumber+=900;}
						else {iNumber-=100;}
						break;
					case 2:
						if(iNumber%100<10) {iNumber+=90;}
						else {iNumber-=10;}
						break;
					case 3:
						if(iNumber%10==0) {iNumber+=9;}
						else {iNumber-=1;}
						break;
					}
				}
				break;
			case Set_button:
				uiBlink_Time = 0;
				bBlink_Flag = 1;
				uiBlink_Sel = 0;
				bSet_Flag ^= 1;
				bLeading_Zero_Flag ^= 1;
				break;
			case Sel_button:
				if(bSet_Flag)
				{
					uiBlink_Time = 0;
					bBlink_Flag = 1;
					uiBlink_Sel ++;
					uiBlink_Sel %= 4;
				}
				break;
			case Reset_button:
				iNumber=0;
				break;
			}
			if(iNumber>9999 || iNumber <0) {iNumber = 0;}
			Number_convert(iNumber,bLeading_Zero_Flag);
			bButton_Flag = 0;
		}
		if(bLong_Button_Flag)
		{
			switch(uiButton_Data)
			{
			case Up_button:
				break;
			case Down_button:
				break;
			case Set_button:
				break;
			case Sel_button:
				break;
			case Reset_button:
				iNumber = 1234;
				Number_convert(iNumber,bLeading_Zero_Flag);
				break;
			}
			bLong_Button_Flag = 0;
		}
	}
}

//////////////////////////////////
void Initialize(void)
{
	bLeading_Zero_Flag = 1;
}

void Number_convert(int number, int Flag)	//숫자 => Digit bit 변환 함수
{
	unsigned int uiData = 0;
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

