#include <hidef.h>
#include "derivative.h"
#include "CAN.h"
#include "DIO.h"
#include "PLL.h"
#include "PIT.h"
#include "CAN_Lcfg.h"


void main(void)
{
	DisableInterrupts;      //关中断
	DIO_Init();			    //初始化Dio
	PLL_Init();			    //初始化锁相环
	CAN_Init(&CAN_Config);	//初始化CAN
	PIT_Init();			    //初始化PIT中断
	EnableInterrupts;	    //开中断

	for (;;)
	{
	}
}