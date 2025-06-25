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

unsigned int uiADC_Data[5];
unsigned char ucReceive_Buf[] = {};
unsigned char ucTransmit_Buf[] = {'<',0,0,'/',0,0,0,0,'/','>'};
unsigned int uiADC_Buf[16] = {};
unsigned int uiADC_Buf_Sel = 0;
unsigned int uiADC_DMA_Data[5] = {};
unsigned int uiIN10_Data[16];
unsigned int uiIN11_Data[16];
unsigned int uiIN12_Data[16];
unsigned int uiIN13_Data[16];
unsigned int uiIN14_Data[16];
int iTemp_Value[5];

extern ADC_HandleTypeDef hadc;
extern UART_HandleTypeDef huart5;
extern TIM_HandleTypeDef htim6;
//////////////////////////////////
void Initialize(void);
int T_Calculation(unsigned int);
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
			unsigned long int uliADC_Data_Buf[5];
			for(int num=0; num<16; num++)
			{
				uliADC_Data_Buf[0] += uiIN10_Data[num];
				uliADC_Data_Buf[1] += uiIN11_Data[num];
				uliADC_Data_Buf[2] += uiIN12_Data[num];
				uliADC_Data_Buf[3] += uiIN13_Data[num];
				uliADC_Data_Buf[4] += uiIN14_Data[num];
			}
			uiADC_Data[0] = uliADC_Data_Buf[0] / 4;
			uiADC_Data[1] = uliADC_Data_Buf[1] / 4;
			uiADC_Data[2] = uliADC_Data_Buf[2] / 4;
			uiADC_Data[3] = uliADC_Data_Buf[3] / 4;
			uiADC_Data[4] = uliADC_Data_Buf[4] / 4;

			iTemp_Value[0] = T_Calculation(uiADC_Data[0]);
			iTemp_Value[1] = T_Calculation(uiADC_Data[1]);
			iTemp_Value[2] = T_Calculation(uiADC_Data[2]);
			iTemp_Value[3] = T_Calculation(uiADC_Data[3]);
			iTemp_Value[4] = T_Calculation(uiADC_Data[4]);
			bADC_Flag = 0;
		}
		if(bRx_Flag)
		{
			if(ucReceive_Buf[1] == 'C' && ucReceive_Buf[2] == 'R')
			{
				ucTransmit_Buf[1] = 'C';
				ucTransmit_Buf[2] = 'R';
				ucTransmit_Buf[4] = '(';
				ucTransmit_Buf[5] = (iTemp_Value[0]/1000)+'0';
				ucTransmit_Buf[6] = ((iTemp_Value[0]%1000)/100)+'0';
				ucTransmit_Buf[7] = ((iTemp_Value[0]%100)/10)+'0';
				ucTransmit_Buf[8] = '.';
				ucTransmit_Buf[9] = (iTemp_Value[0]%10)+'0';
				ucTransmit_Buf[10] = ')';
				ucTransmit_Buf[11] = '(';
				ucTransmit_Buf[12] = (iTemp_Value[1]/1000)+'0';
				ucTransmit_Buf[13] = ((iTemp_Value[1]%1000)/100)+'0';
				ucTransmit_Buf[14] = ((iTemp_Value[1]%100)/10)+'0';
				ucTransmit_Buf[15] = '.';
				ucTransmit_Buf[16] = (iTemp_Value[1]%10)+'0';
				ucTransmit_Buf[17] = ')';
				ucTransmit_Buf[18] = '(';
				ucTransmit_Buf[19] = (iTemp_Value[2]/1000)+'0';
				ucTransmit_Buf[20] = ((iTemp_Value[2]%1000)/100)+'0';
				ucTransmit_Buf[21] = ((iTemp_Value[2]%100)/10)+'0';
				ucTransmit_Buf[22] = '.';
				ucTransmit_Buf[23] = (iTemp_Value[2]%10)+'0';
				ucTransmit_Buf[24] = ')';
				ucTransmit_Buf[25] = '(';
				ucTransmit_Buf[26] = (iTemp_Value[3]/1000)+'0';
				ucTransmit_Buf[27] = ((iTemp_Value[3]%1000)/100)+'0';
				ucTransmit_Buf[28] = ((iTemp_Value[3]%100)/10)+'0';
				ucTransmit_Buf[29] = '.';
				ucTransmit_Buf[30] = (iTemp_Value[3]%10)+'0';
				ucTransmit_Buf[31] = ')';
				ucTransmit_Buf[32] = '(';
				ucTransmit_Buf[33] = (iTemp_Value[4]/1000)+'0';
				ucTransmit_Buf[34] = ((iTemp_Value[4]%1000)/100)+'0';
				ucTransmit_Buf[35] = ((iTemp_Value[4]%100)/10)+'0';
				ucTransmit_Buf[36] = '.';
				ucTransmit_Buf[37] = (iTemp_Value[4]%10)+'0';
				ucTransmit_Buf[38] = ')';
				ucTransmit_Buf[39] = '/';
				ucTransmit_Buf[40] = '>';
				USART5->TDR = '<';

			}
			else if(ucReceive_Buf[1] == 'A' && ucReceive_Buf[2] == 'R')
			{
				ucTransmit_Buf[1] = 'A';
				ucTransmit_Buf[2] = 'R';
				ucTransmit_Buf[4] = '(';
				ucTransmit_Buf[5] = (uiADC_Data[0]/1000)+'0';
				ucTransmit_Buf[6] = ((uiADC_Data[0]%1000)/100)+'0';
				ucTransmit_Buf[7] = ((uiADC_Data[0]%100)/10)+'0';
				ucTransmit_Buf[8] = (uiADC_Data[0]%10)+'0';
				ucTransmit_Buf[9] = ')';
				ucTransmit_Buf[10] = '(';
				ucTransmit_Buf[11] = (uiADC_Data[1]/1000)+'0';
				ucTransmit_Buf[12] = ((uiADC_Data[1]%1000)/100)+'0';
				ucTransmit_Buf[13] = ((uiADC_Data[1]%100)/10)+'0';
				ucTransmit_Buf[14] = (uiADC_Data[1]%10)+'0';
				ucTransmit_Buf[15] = ')';
				ucTransmit_Buf[16] = '(';
				ucTransmit_Buf[17] = (uiADC_Data[2]/1000)+'0';
				ucTransmit_Buf[18] = ((uiADC_Data[2]%1000)/100)+'0';
				ucTransmit_Buf[19] = ((uiADC_Data[2]%100)/10)+'0';
				ucTransmit_Buf[20] = (uiADC_Data[2]%10)+'0';
				ucTransmit_Buf[21] = ')';
				ucTransmit_Buf[22] = '(';
				ucTransmit_Buf[23] = (uiADC_Data[3]/1000)+'0';
				ucTransmit_Buf[24] = ((uiADC_Data[3]%1000)/100)+'0';
				ucTransmit_Buf[25] = ((uiADC_Data[3]%100)/10)+'0';
				ucTransmit_Buf[26] = (uiADC_Data[3]%10)+'0';
				ucTransmit_Buf[27] = ')';
				ucTransmit_Buf[28] = '(';
				ucTransmit_Buf[29] = (uiADC_Data[4]/1000)+'0';
				ucTransmit_Buf[30] = ((uiADC_Data[4]%1000)/100)+'0';
				ucTransmit_Buf[31] = ((uiADC_Data[4]%100)/10)+'0';
				ucTransmit_Buf[32] = (uiADC_Data[4]%10)+'0';
				ucTransmit_Buf[33] = ')';
				ucTransmit_Buf[34] = '/';
				ucTransmit_Buf[35] = '>';
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
	HAL_ADC_Start_DMA(&hadc, uiADC_DMA_Data, 5);
	HAL_TIM_Base_Start(&htim6);
}

int T_Calculation(unsigned int Input_Data)
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
