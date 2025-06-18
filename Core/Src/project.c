/*include*/
#include "main.h"
#include <math.h>
//////////////////////////////////
/*define*/

//////////////////////////////////
/*variable*/
const unsigned int FND_Number_Table[10] = {0x82007d00,0xdb002400,0x1600e900,0x1a00e500,
		0x4b00b400,0x2a00d500,0x2200dd00,0x9b006400,0x0200fd00,0x0a00f500};

int bADC_Flag = 0;

int iRPM_T = 0;
unsigned int uiDisplay_Data[4] = {};
unsigned int uiADC_Buf[16] = {};
//////////////////////////////////
/*extern variable*/
extern ADC_HandleTypeDef hadc;
//////////////////////////////////
void Initialize(void);
void Number_Convert(unsigned int,int);
void T_Calculation(unsigned long int);

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
			unsigned long int uliADC_Data = 0;
			for(int num = 0;num < 16;num ++)
			{
				uliADC_Data += uiADC_Buf[num];
			}
			uliADC_Data /= 4;
			T_Calculation(uliADC_Data);
			Number_Convert(iRPM_T, 0);
			bADC_Flag = 0;
		}
	}
}

//////////////////////////////////
void Initialize(void)
{
	HAL_ADCEx_Calibration_Start(&hadc,ADC_SINGLE_ENDED);
}
void Number_Convert(unsigned int number, int Flag)	//숫자 => Digit bit 변환 함수
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

void T_Calculation(unsigned long int Input_Data)
{
	float fValue;

	// A/D ( 16384 ) :
	// RPM Temp Calculation	( 10 k )
	fValue = (float)Input_Data;
	fValue = ( fValue * 2.2 ) / ( 16384 - 2 * fValue);
	iRPM_T = (int)((1.0/(log(fValue/10.0)/3977.0 + 1.0/(273.15+25.0)) - 273.15)*10);

	if ( iRPM_T < 0 ) iRPM_T = 0;
}
