#include "PrechargeM.h"
#include "Pre_Lcfg.h"
#include "Node.h"
#include "RelayM_Lcfg.h"

void PrechargeM_Init(void)          	//初始化函数
{
}

void PrechargeM_StartPre(void)      	//启动预充函数，闭合预充继电器开关
{
    if (RelayM_Control(0, &RelayM_FnCfg, RELAYM_CTRL_STATUS, 1))
    {
    }
}

void PrechargeM_StopPre(void)       	//停止预充函数，断开预充继电器开关
{
	if (RelayM_Control(0, &RelayM_FnCfg, RELAYM_CTRL_STATUS, 0))
	{
	}
}

void PrechargeM_StartMaster(void)   	//闭合总正继电器开关
{
	if (RelayM_Control(1, &RelayM_FnCfg, RELAYM_CTRL_STATUS, 1))
	{
	}
}

void PrechargeM_StopMaster(void)    	//断开总正继电器开关
{
	if (RelayM_Control(1, &RelayM_FnCfg, RELAYM_CTRL_STATUS, 0))
	{
	}
}

void PrechargeM_Change(void)        	//继电器切换函数，闭合总正或断开预充
{
	PrechargeM_StartMaster();			//闭合总正
	PrechargeM_StopPre();				//断开预充
}

int PrechargeM_IsFault(void)        	//故障判断函数
{
	int re = 0;
	PrechargeCfg_Type *cfg;
	cfg = &Precharge_Cfg;

	if (cfg->fault == 1)	     		//判断预充是否出现故障，1表示无故障
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	return re;
}

int PrechargeM_IsFail(void)       		//超时判断函数
{
	int re = 0;
	PrechargeCfg_Type *cfg;
	cfg = &Precharge_Cfg;

	if (cfg->pretime <= PRE_TIMEOUT) 	//判断预充实际时间是否超出阈值(3s)
	{
		re = 0;
	}
	else
	{
		re = 1;
	}
	return re;
}

int PrechargeM_IsFinish(void)           	//预充完成判断函数
{
	int re = 0;
	uint8 passage = 1;
	PrechargeCfg_Type *cfg;
	cfg = &Precharge_Cfg;

	if (passage < HV_MAX_PASSAGE)
	{
		if (Hv_Get(passage, HV_VOLTAGE_V1) * 100 > Hv_Get(passage, HV_VOLTAGE_BAT) * (cfg->percent))//判断V1电压是否大于BAT电压的95%
		{
			re = 0;
		}
		else
		{
			re = 1;
		}
	}
	return re;
}