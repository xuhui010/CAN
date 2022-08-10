#include <hidef.h>
#include "derivative.h"
#include "CAN.h"
#include "DIO.h"
#include "PLL.h"
#include "PIT.h"
#include "CAN_Lcfg.h"


void main(void)
{
	DisableInterrupts;      //���ж�
	DIO_Init();			    //��ʼ��Dio
	PLL_Init();			    //��ʼ�����໷
	CAN_Init(&CAN_Config);	//��ʼ��CAN
	PIT_Init();			    //��ʼ��PIT�ж�
	EnableInterrupts;	    //���ж�

	for (;;)
	{
	}
}