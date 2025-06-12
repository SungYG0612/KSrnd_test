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

int iNumber_Buf = 0;
unsigned int uiDisplay_Number_Buf[4] = {};
unsigned int uiFND_Port_Buf[4] = {0x70008000, 0xb0004000, 0xd0002000, 0xe0001000};

int iBlink_Port_sel = 0;
unsigned int uiBlink_State_Sel = 0;
unsigned int uiBlink_Time = 0;
unsigned int uiBlink_Port_Data[4] = {0xf0000000,0xb0004000,0xd0002000,0xe0001000};
unsigned int uiPin_value = 0x0000;
char cNumber_sign;
unsigned int uiLong_Key_Data = 0;
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
				iNumber_Buf++;
				Number_convert(iNumber_Buf);
				break;

			case Down_Button:
				iNumber_Buf--;
				Number_convert(iNumber_Buf);
				break;

			case Set_Button:
				iBlink_Port_sel = 0;	//blink 하는 FND 선택 초기화
				Blink_convert(iBlink_Port_sel);
				uiBlink_State_Sel = 0;	//blink 상태 초기화(ON or OFF)
				uiBlink_Time = 0;	//blink flag 만드는 시간 초기화
				bSet_Flag ^= 1;	//Set Flag 토글
				if(bSet_Flag) {uiBlink_State_Sel = 1;}
				bBlink_Flag = 1;
				break;

			case Sel_Button:
				if(bSet_Flag)
				{
					iBlink_Port_sel++;
					iBlink_Port_sel %= 4;
					Blink_convert(iBlink_Port_sel);
					uiBlink_State_Sel = 1;
					uiBlink_Time = 0;
					bBlink_Flag = 1;
				}
				break;

			case Reset_Button:
				iNumber_Buf=0;
				Number_convert(iNumber_Buf);
				break;
			}
			bButton_Flag = 0;
		}

		if(bLong_Key_Flag)
		{
			switch(uiLong_Key_Data)
			{
			case 1:
				iNumber_Buf = 1234;
				Number_convert(iNumber_Buf);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			}
			uiLong_Key_Data = 0;
			bLong_Key_Flag = 0;
		}
		/*Blink 토글*/
		if(bBlink_Flag)
		{
			switch(uiBlink_State_Sel)
			{
			case 0:
				uiFND_Port_Buf[0]=FND_Port_Table[0];
				uiFND_Port_Buf[1]=FND_Port_Table[1];
				uiFND_Port_Buf[2]=FND_Port_Table[2];
				uiFND_Port_Buf[3]=FND_Port_Table[3];
				uiBlink_State_Sel = 1;
				break;
			case 1:
				uiFND_Port_Buf[0]=uiBlink_Port_Data[0];
				uiFND_Port_Buf[1]=uiBlink_Port_Data[1];
				uiFND_Port_Buf[2]=uiBlink_Port_Data[2];
				uiFND_Port_Buf[3]=uiBlink_Port_Data[3];
				uiBlink_State_Sel = 0;
				break;
			}
			bBlink_Flag = 0;
		}
	}
}

/////////////////////////////////////////////////
void Initialize(void)
{
	Number_convert(iNumber_Buf);
	for(int sel=0; sel<4; sel++) {uiFND_Port_Buf[sel] = FND_Port_Table[sel];}
}

/////////////////////////////////////////////////
void Number_convert(int Input_Data)		//숫자 변환 함수
{
	unsigned int uiNumber_Data[4] = {};
	unsigned int uiNumber_len = 0;
	if(Input_Data>9999 || Input_Data<-999) {Input_Data = 0;}		//Input_Data가 9999보다 크고 -999보다 작다면 0으로 초기화
	//양수 음수 확인 Code
	if(Input_Data<0)		//iNumber_Buf가 음수일 경우
	{
		Input_Data *= -1;		//음수 X -1로 양수로 변환
		cNumber_sign = '-';
	}
	else {cNumber_sign = '+';}

	if(Input_Data >= 1000){uiNumber_len=0;}
	else if(Input_Data >= 100){uiNumber_len=1;}
	else if(Input_Data >= 10){uiNumber_len=2;}
	else{uiNumber_len=3;}

	for(int sel=0; sel<4; sel++)
	{
		if(sel<uiNumber_len)
		{
			uiNumber_Data[sel] = 0xff000000;
		}
		else
		{
			switch(sel)
			{
			case 0:
				uiNumber_Data[0] = FND_Number_Table[Input_Data / 1000];
				break;
			case 1:
				uiNumber_Data[1] = FND_Number_Table[(Input_Data % 1000) / 100];
				break;
			case 2:
				uiNumber_Data[2] = FND_Number_Table[(Input_Data % 100) / 10];
				break;
			case 3:
				uiNumber_Data[3] = FND_Number_Table[Input_Data % 10];
				break;
			}
		}
	}

	if(cNumber_sign == '-') {uiDisplay_Number_Buf[0] = 0x7f008000;}
	else {uiDisplay_Number_Buf[0] = uiNumber_Data[0];}
	uiDisplay_Number_Buf[1] = uiNumber_Data[1];
	uiDisplay_Number_Buf[2] = uiNumber_Data[2];
	uiDisplay_Number_Buf[3] = uiNumber_Data[3];
}

///////////////////////////////////////////////////////
/*Blink FND 변경*/
void Blink_convert(int Input_Sel_Data)
{
	for(int sel=0; sel<4; sel++)
	{
		if(sel==Input_Sel_Data)
		{
			uiBlink_Port_Data[sel] = 0xf0000000;
		}
		else
		{
			uiBlink_Port_Data[sel] = FND_Port_Table[sel];
		}
	}
}
