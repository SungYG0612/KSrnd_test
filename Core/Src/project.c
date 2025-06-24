/*include*/
#include "main.h"
#include <math.h>
//////////////////////////////////
/*define*/
//////////////////////////////////
/*variable*/
int bADC_Flag = 0;
int bRx_Flag = 0;
int bTx_Flag = 0;

unsigned long int uliADC_Data[5];
unsigned char ucReceive_Buf[] = {};
unsigned char ucTransmit_Buf[] = {'<',0,0,'/',0,0,0,0,'/','>'};
unsigned int uiADC_Buf[16] = {};
unsigned int uiADC_Buf_Sel = 0;
unsigned int uiADC_DMA_Buf[5] = {};
int iTemp_Value[5];

extern ADC_HandleTypeDef hadc;
extern UART_HandleTypeDef huart5;
extern TIM_HandleTypeDef htim6;
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
			iTemp_Value[0] = T_Calculation(uliADC_Data[0] /= 4);
			T_Calculation(uliADC_Data[1] /= 4);
			T_Calculation(uliADC_Data[2] /= 4);
			T_Calculation(uliADC_Data[3] /= 4);
			bADC_Flag = 0;
		}
		if(bRx_Flag)
		{
			if(ucReceive_Buf[1] == 'C' && ucReceive_Buf[2] == 'R')
			{
				ucTransmit_Buf[1] = 'C';
				ucTransmit_Buf[2] = 'R';
				ucTransmit_Buf[4] = (iRPM_T/1000)+'0';
				ucTransmit_Buf[5] = ((iRPM_T%1000)/100)+'0';
				ucTransmit_Buf[6] = ((iRPM_T%100)/10)+'0';
				ucTransmit_Buf[7] = '.';
				ucTransmit_Buf[8] = (iRPM_T%10)+'0';
				ucTransmit_Buf[9] = '/';
				ucTransmit_Buf[10] = '>';
				USART5->TDR = '<';

			}
			else if(ucReceive_Buf[1] == 'A' && ucReceive_Buf[2] == 'R')
			{
				ucTransmit_Buf[1] = 'A';
				ucTransmit_Buf[2] = 'R';
				ucTransmit_Buf[4] = (uliADC_Data/1000)+'0';
				ucTransmit_Buf[5] = ((uliADC_Data%1000)/1000)+'0';
				ucTransmit_Buf[6] = ((uliADC_Data%100)/10)+'0';
				ucTransmit_Buf[7] = (uliADC_Data%10)+'0';
				ucTransmit_Buf[8] = '/';
				ucTransmit_Buf[9] = '>';
				USART5->TDR = '<';
			}
			bTx_Flag = 0;
			bRx_Flag = 0;
		}
	}
}

//////////////////////////////////
void Initialize(void)
{
	HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, 1);
	HAL_ADCEx_Calibration_Start(&hadc,ADC_SINGLE_ENDED);
	HAL_Delay(500);
	__HAL_UART_ENABLE_IT(&huart5,UART_IT_RXNE);
	__HAL_UART_ENABLE_IT(&huart5,UART_IT_TC);
	GPIOB->BSRR = 0x0800;
	HAL_ADC_Start_DMA(&hadc, uiADC_DMA_Buf, 5);
	HAL_TIM_Base_Start(&htim6);
}

void T_Calculation(unsigned long int Input_Data)
{
	float fValue;
	int iRPM_T;
	// A/D ( 16384 ) :
	// RPM Temp Calculation	( 10 k )
	fValue = (float)Input_Data;
	fValue = ( fValue * 2.2 ) / ( 16384 - 2 * fValue);
	iRPM_T = (int)((1.0/(log(fValue/10.0)/3977.0 + 1.0/(273.15+25.0)) - 273.15)*10);

	if ( iRPM_T < 0 ) iRPM_T = 0;
	if ( iRPM_T > 9999) iRPM_T = 9999;
	return iRPM_T;
}

void Number_Convert(unsigned Number, int Flag)
{

}
