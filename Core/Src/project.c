/*include*/
#include "main.h"
#include <math.h>
//////////////////////////////////
/*define*/
//////////////////////////////////
/*variable*/
int bADC_Flag = 0;
int bReceive_Flag = 0;
int iRPM_T = 0;
unsigned long int uliADC_Data = 0;
unsigned char ucReceive_Buf[] = {};
unsigned char ucTansmit_CR_Buf[11] = {'<','C','R','/',0,0,0,'.',0,'/','>'};
unsigned char ucTansmit_AR_Buf[10] = {'<','A','R','/',0,0,0,0,'/','>'};
unsigned int uiADC_Buf[16] = {};
unsigned int uiADC_Buf_Sel = 0;

extern ADC_HandleTypeDef hadc;
extern UART_HandleTypeDef huart5;
//////////////////////////////////
void Initialize(void);
void T_Calculation(unsigned long int);
void Number_Convert(unsigned int,int);
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
			uliADC_Data = 0;
			for(int num = 0;num < 16;num ++)
			{
				uliADC_Data += uiADC_Buf[num];
			}
			uliADC_Data /= 4;
			T_Calculation(uliADC_Data);
			bADC_Flag = 0;
		}
		if(bReceive_Flag)
		{
			if(ucReceive_Buf[1] == 'C' && ucReceive_Buf[2] == 'R')
			{
				ucTansmit_CR_Buf[4] = (uliADC_Data/1000)+'0';
				ucTansmit_CR_Buf[5] = ((uliADC_Data%1000)/1000)+'0';
				ucTansmit_CR_Buf[6] = ((uliADC_Data%100)/10)+'0';
				ucTansmit_CR_Buf[8] = (uliADC_Data%10)+'0';
			}
			else if(ucReceive_Buf[1] == 'A' && ucReceive_Buf[2] == 'R')
			{
				ucTansmit_AR_Buf[4] = (iRPM_T/1000)+'0';
				ucTansmit_AR_Buf[5] = ((iRPM_T%1000)/1000)+'0';
				ucTansmit_AR_Buf[6] = ((iRPM_T%100)/10)+'0';
				ucTansmit_AR_Buf[7] = (iRPM_T%10)+'0';
			}
		}
	}
}

//////////////////////////////////
void Initialize(void)
{
	HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, 1);
	HAL_ADCEx_Calibration_Start(&hadc,ADC_SINGLE_ENDED);
	HAL_Delay(500);
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

void Number_Convert(unsigned Number, int Flag)
{

}
