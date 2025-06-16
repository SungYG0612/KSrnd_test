/*include*/
#include "main.h"

//////////////////////////////////
/*define*/

//////////////////////////////////
/*variable*/
int bButton_Flag = 0;
int bSet_Flag = 0;
int bBlink_Flag = 0;
int bSel_Flag = 0;
int bLeading_Zero_Flag = 0;

const unsigned int FND_Number_Table[10] = {0x82007d00,0xdb002400,0x1600e900,0x1a00e500,
		0x4b00b400,0x2a00d500,0x2200dd00,0x9b006400,0x0200fd00,0x0a00f500};
const unsigned int FND_Port_Table[4] = {0x70008000, 0xb0004000, 0xd0002000, 0xe0001000};

int iNumber = 1234;
unsigned int uiDisplay_Data[4] = {};
unsigned int uiTime = 0;
unsigned int uiPin_value = 0x0000;
char cNumber_sign;
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
			if(uiPin_value == Down_button && bSet_Flag) {iNumber--;}		//1번 버튼 = iNumber 증가
			if(uiPin_value == Set_button) //2번 버튼 = Setting 버튼 > LED Blink
			{
				bBlink_Flag = 1;
				bSet_Flag ^= 1;
				bLeading_Zero_Flag ^= 1;
			}
			if(uiPin_value == Up_button && bSet_Flag) {iNumber++;}		//3번 버튼 = iNumber 감소
			if(uiPin_value == Sel_button && bSet_Flag) {bSel_Flag = 1;}
			if(uiPin_value == Reset_button) {iNumber=0;}		//5번 버튼 = iNumber 0 초기화
			if(iNumber>9999 || iNumber <0) {iNumber = 0;}
			Number_convert(iNumber,bLeading_Zero_Flag);
			bButton_Flag = 0;
		}
	}
}

//////////////////////////////////
void Initialize(void)
{

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

