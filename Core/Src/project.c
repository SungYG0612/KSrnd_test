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

const unsigned int FND_Number_Table[10] = {0x82007d00,0xdb002400,0x1600e900,0x1a00e500,
		0x4b00b400,0x2a00d500,0x2200dd00,0x9b006400,0x0200fd00,0x0a00f500};
const unsigned int FND_Port_Table[4] = {0x70008000, 0xb0004000, 0xd0002000, 0xe0001000};

int iNumber_Data = 1234;
unsigned int uiDisplay_Data[4] = {};
unsigned int uiFND_Port_Buf[4] = {0x70008000, 0xb0004000, 0xd0002000, 0xe0001000};

unsigned int uiPort_sel = 0;
unsigned int uiPin_value = 0x0000;
char cNumber_sign;
//////////////////////////////////
void Initialize(void);
void Number_convert(int);

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
			if(uiPin_value == 0x0400) {iNumber_Data--;}		//1번 버튼 = iNumber_Data 증가
			if(uiPin_value == 0x0800) {bSet_Flag ^= 1;}		//2번 버튼 = Setting 버튼 > LED Blink
			if(uiPin_value == 0x1000) {iNumber_Data++;}		//3번 버튼 = iNumber_Data 감소
			if(uiPin_value == 0x2000) {bSel_Flag = 1;}
			if(uiPin_value == 0x4000) {iNumber_Data=0;}		//5번 버튼 = iNumber_Data 0 초기화
			if(iNumber_Data>9999 || iNumber_Data <0) {iNumber_Data = 0;}
			Number_convert(iNumber_Data);
			bButton_Flag = 0;
		}
		if(bSel_Flag)
		{
			uiPort_sel++;
		}
	}
}

//////////////////////////////////
void Initialize(void)
{

}

void Number_convert(int input_number)		//숫자 변환 함수
{
	unsigned int uiNumber_len = 0;

	if(input_number < 1000)
	{
		if(input_number < 100)
		{
			if(input_number < 10)
			{
				uiNumber_len ++;
			}
			uiNumber_len ++;
		}
		uiNumber_len ++;
	}

	uiDisplay_Data[0] = FND_Number_Table[input_number/1000];
	uiDisplay_Data[1] = FND_Number_Table[(input_number%1000)/100];
	uiDisplay_Data[2] = FND_Number_Table[(input_number%100)/10];
	uiDisplay_Data[3] = FND_Number_Table[input_number%10];
}

