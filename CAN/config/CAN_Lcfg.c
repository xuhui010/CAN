#include "derivative.h"
#include "CAN_Lcfg.h"

CAN_CfgType CAN_Config =		//CAN硬件配置
{
	CAN_Bps_125k,
	1,
};

#pragma CODE_SEG __NEAR_SEG NON_BANKED       //中断函数置于非分页区内代码段

void interrupt VectorNumber_Vcan1rx CAN_receive(void)
{
	CAN_RecCallBack();	//收到CAN报文触发中断
}

#pragma CODE_SEG DEFAULT
