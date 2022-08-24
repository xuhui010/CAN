#include "PrechargeM.h"
#include "Pre_Lcfg.h"
#include "Hv.h"

void PrechargeM_Init(void)          //初始化函数
{
}

void PrechargeM_StartPre(void)      //启动预充函数，闭合预充开关
{
    if (RelayM_Control(0, RELAYM_CTRL_STATUS, 1))
    {
    }
}

void PrechargeM_StopPre(void)       //停止预充函数，断开预充开关
{
	if (RelayM_Control(0, RELAYM_CTRL_STATUS, 0))
	{
	}
}

void PrechargeM_StartMsater(void)   //启动总正函数，闭合总正开关
{
	if (RelayM_Control(1, RELAYM_CTRL_STATUS, 1))
	{
	}
}

void PrechargeM_StopMsater(void)    //停止总正函数，断开总正开关
{
	if (RelayM_Control(1, RELAYM_CTRL_STATUS, 0))
	{
	}
}

void PrechargeM_Change(void)        //继电器切换函数，闭合总正或断开预充
{
	PrechargeM_StartMsater();		//闭合总正
	PrechargeM_StopPre();			//断开预充
}

int PrechargeM_IsFail()             //超时判断函数，判断自启动预充至此刻的时间是否超过3秒
{
	int re = 0;
	if (Pre_StateData_Time() > Pre_TimeOut.Critical_Time)	//判断从启动预充至此刻的时间是否超过3秒
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	return re;
}

int PrechargeM_IsFinish()           //预充完成判断函数，判断V1电压是否大于BAT电压的95%
{
	int re = 0;
	if (Hv_Get(Pre_StateData.voltage, HV_VOLTAGE) * 100 >=
		Hv_Get(0, HV_VOLTAGE) * (Pre_BAT_Voltage.percent))//判断V1电压是否大于BAT电压的95%
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	return re;
}