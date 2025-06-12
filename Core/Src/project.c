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
int bSel_Flag = 0;

const unsigned int FND_Number_Table[10] = {0x82007d00,0xdb002400,0x1600e900,0x1a00e500,
		0x4b00b400,0x2a00d500,0x2200dd00,0x9b006400,0x0200fd00,0x0a00f500};
const unsigned int FND_Port_Table[4] = {0x70008000, 0xb0004000, 0xd0002000, 0xe0001000};

int iNumber_Buf = 1234;
unsigned int uiDisplay_Buf[4] = {};
unsigned int uiFND_Port_Buf[4] = {0x70008000, 0xb0004000, 0xd0002000, 0xe0001000};

int iBlink_Port_sel = 0;
unsigned int uiBlink_Port_Data[4] = {0xf0000000,0xb0004000,0xd0002000,0xe0001000};
unsigned int uiPin_value = 0x0000;
char cNumber_sign;
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
			if(uiPin_value == Down_Button)
			{
				iNumber_Buf--;
				Number_convert(iNumber_Buf);
			}
			if(uiPin_value == Set_Button)
			{
				iBlink_Port_sel = 0;
				Blink_convert(iBlink_Port_sel);
				bSet_Flag ^= 1;
			}
			if(uiPin_value == Up_Button)
			{
				iNumber_Buf++;
				Number_convert(iNumber_Buf);
			}
			if(uiPin_value == Sel_Button && bSet_Flag)
			{
				iBlink_Port_sel++;
				iBlink_Port_sel %= 4;
				Blink_convert(iBlink_Port_sel);
			}
			if(uiPin_value == Reset_Button)
			{
				iNumber_Buf=0;
				Number_convert(iNumber_Buf);
			}
			bButton_Flag = 0;
		}
	}
}

//////////////////////////////////
void Initialize(void)
{
	Number_convert(iNumber_Buf);
	for(int sel=0; sel<4; sel++) {uiFND_Port_Buf[sel] = FND_Port_Table[sel];}
}

void Number_convert(int Input_Data)		//숫자 변환 함수
{
	unsigned int uiNumber_state[4] = {};
	if(Input_Data>9999 || Input_Data<-999) {Input_Data = 0;}		//Input_Data가 9999보다 크고 -999보다 작다면 0으로 초기화
	//양수 음수 확인 Code
	if(Input_Data<0)		//iNumber_Buf가 음수일 경우
	{
		Input_Data *= -1;		//음수 X -1로 양수로 변환
		cNumber_sign = '-';
	}
	else {cNumber_sign = '+';}

	if(Input_Data >= 1000)
	{
		uiNumber_state[0] = FND_Number_Table[Input_Data / 1000];
		uiNumber_state[1] = FND_Number_Table[(Input_Data % 1000) / 100];
		uiNumber_state[2] = FND_Number_Table[(Input_Data % 100) / 10];
		uiNumber_state[3] = FND_Number_Table[Input_Data % 10];
	}
	else if(Input_Data >= 100)
	{
		uiNumber_state[0] = 0xff000000;
		uiNumber_state[1] = FND_Number_Table[(Input_Data % 1000) / 100];
		uiNumber_state[2] = FND_Number_Table[(Input_Data % 100) / 10];
		uiNumber_state[3] = FND_Number_Table[Input_Data % 10];
	}
	else if(Input_Data >= 10)
	{
		uiNumber_state[0] = 0xff000000;
		uiNumber_state[1] = 0xff000000;
		uiNumber_state[2] = FND_Number_Table[(Input_Data % 100) / 10];
		uiNumber_state[3] = FND_Number_Table[Input_Data % 10];
	}
	else
	{
		uiNumber_state[0] = 0xff000000;
		uiNumber_state[1] = 0xff000000;
		uiNumber_state[2] = 0xff000000;
		uiNumber_state[3] = FND_Number_Table[Input_Data % 10];
	}

	if(cNumber_sign == '-') {uiDisplay_Buf[0] = 0x7f008000;}
	else {uiDisplay_Buf[0] = uiNumber_state[0];}
	uiDisplay_Buf[1] = uiNumber_state[1];
	uiDisplay_Buf[2] = uiNumber_state[2];
	uiDisplay_Buf[3] = uiNumber_state[3];
}

void Blink_convert(int Input_Data)
{
	for(int sel=0; sel<4; sel++)
	{
		if(sel == Input_Data)
		{
			uiBlink_Port_Data[sel] = 0xf0000000;
		}
		else
		{
			uiBlink_Port_Data[sel] = FND_Port_Table[sel];
		}
	}
}
