#include "RelayM.h"
#include "RelayM_Lcfg.h"

void RelayM_Init(void)              							//继电器模块初始化函数
{
}

void RelayM_InterruptON(void)       							//开中断
{
}

void RelayM_InterruptOFF(void)									//关中断
{
}

void RelayM_SetStatus(uint8 passage, uint16 data)  				//设置继电器开关状态
{
	RelayM_StateCfg[passage].cfg->control_status = data;
	RelayM_StateCfg[passage].cfg->actual_status = data;
}

uint16 RelayM_GetControlStatus(uint8 passage)					//获取继电器开关控制状态
{
	return RelayM_StateCfg[passage].cfg->control_status;
}

uint16 RelayM_GetActureStatus(uint8 passage)					//获取继电器开关实际状态
{
	return RelayM_StateCfg[passage].cfg->actual_status;
}

void RelayM_SetOnTime(uint8 passage, uint16 ontime)				//设置继电器闭合时间
{
	RelayM_StateCfg[passage].cfg->on_time = ontime;
}

uint16 RelayM_GetOnTime(uint16 ontime)							//获取继电器实际闭合时间
{
	ontime = 50;
	return ontime;
}

void RelayM_SetOffTime(uint8 passage ,uint16 offtime) 			//设置继电器断开时间
{
    RelayM_StateCfg[passage].cfg->off_time = offtime;
}

uint16 RelayM_GetOffTime(uint16 offtime)             			//获取继电器实际断开时间
{
    offtime = 100;
    return offtime;
}

void RelayM_SetRes(uint8 passage ,uint16 res)     				//设置继电器内阻值
{
	RelayM_StateCfg[passage].cfg->res_value = res;
}

uint16 RelayM_GetRes(uint16 res)                 				//获取继电器实际内阻值
{
    res = 200;
    return res;
}


RelayM_FaultType RelayM_GetFault(uint8 passage)   				//继电器故障检测
{
	RelayM_FaultType re;
	uint16 ctlre = RelayM_GetControlStatus(passage);
	uint16 ature = RelayM_GetActureStatus(passage);

	if (ctlre != ature) 										//继电器控制状态和实际状态不同，则继电器出现故障
	{
		if (ctlre == 0 && ature == 1)							//控制继电器开关断开，实际状态闭合，则继电器粘连
		{
			re = RELAYM_ADHESION;
		}
		else if (ctlre == 1 && ature == 0)						//控制继电器开关闭合，实际状态断开，则继电器开路
		{
			re = RELAYM_OPEN_LOOP;								//继电器开路
		}
		else
		{
		}
	}
	else
	{
		re = RELAYM_NO_FAULT;									//继电器无故障
	}
	return re;
}

void RelayM_Control(uint8 passage, RelayM_CtlAttributeType ctl, uint16 data)		//继电器控制(继电器种类，属性,值）
{
	switch (ctl)
	{
		case RELAYM_CONTROL_SWITCH:
		{
			RelayM_SetStatus(passage, data);
		} break;

		case RELAYM_CONTROL_ON_TIME:
		{
			RelayM_SetOnTime(passage, data);
		} break;

		case RELAYM_CONTROL_OFF_TIME:
		{
			RelayM_SetOffTime(passage, data);
		} break;

		case RELAYM_CONTROL_RES_VALUE:
		{
			RelayM_SetRes(passage, data);
		} break;

		default:
		{
		} break;
	}
}

uint16 RelayM_Acture(uint8 passage, RelayM_AtuAttributeType act)    //继电器实际状态获取(通道，属性)
{
	uint16 re = 0;

	switch (act)
	{
		case RELAYM_ACTURE_SWITCH:
		{
			re = RelayM_GetActureStatus(passage);
		} break;

		case RELAYM_ACTURE_ON_TIME:
		{
			re = RelayM_GetOnTime(passage);
		} break;

		case RELAYM_ACTURE_OFF_TIME:
		{
			re = RelayM_GetOffTime(passage);
		} break;

		case RELAYM_ACTURE_RES_VALUE:
		{
			re = RelayM_GetRes(passage);
		} break;

		default:
	    {
	    } break;
	}
	return re;
}