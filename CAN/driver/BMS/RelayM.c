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
	RelayM_StateCfg[passage].cfg->switch_status = data;
}

uint16 RelayM_GetControlStatus(uint8 passage)					//获取继电器开关控制状态
{
	return RelayM_StateCfg[passage].cfg->switch_status;
}

uint16 RelayM_GetActureStatus(uint8 passage)					//获取继电器开关实际状态
{
	return RelayM_ActureCfg[passage].act->switch_status;
}

void RelayM_SetOnTime(uint8 passage, uint16 ontime)				//设置继电器闭合时间
{
	RelayM_StateCfg[passage].cfg->on_time = ontime;
}

uint16 RelayM_GetOnTime(uint8 passage)							//获取继电器实际闭合时间
{
	return RelayM_ActureCfg[passage].act->on_time;
}

void RelayM_SetOffTime(uint8 passage ,uint16 offtime) 			//设置继电器断开时间
{
    RelayM_StateCfg[passage].cfg->off_time = offtime;
}

uint16 RelayM_GetOffTime(uint8 passage)             			//获取继电器实际断开时间
{
    return RelayM_ActureCfg[passage].act->off_time;
}

void RelayM_SetRes(uint8 passage ,uint16 res)     				//设置继电器内阻值
{
	RelayM_StateCfg[passage].cfg->res_value = res;
}

uint16 RelayM_GetRes(uint8 passage)                 				//获取继电器实际内阻值
{
    return RelayM_ActureCfg[passage].act->res_value;
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

void RelayM_Control(uint8 passage, RelayM_Fn_Type fn, uint16 data)		//继电器控制(继电器种类，属性,值）
{
	switch (fn)
	{
		case RELAYM_SWITCH:							      				//控制开关状态
		{
			RelayM_SetStatus(passage, data);
		} break;

		case RELAYM_ON_TIME:											//控制闭合时间
		{
			RelayM_SetOnTime(passage, data);
		} break;

		case RELAYM_OFF_TIME:											//控制断开时间
		{
			RelayM_SetOffTime(passage, data);
		} break;

		case RELAYM_RES_VALUE:											//控制内阻大小
		{
			RelayM_SetRes(passage, data);
		} break;

		default:
		{
		} break;
	}
}

uint16 RelayM_Acture(uint8 passage, RelayM_Fn_Type fn)    //继电器实际状态获取(通道，属性)
{
	uint16 re = 0;

	switch (fn)
	{
		case RELAYM_SWITCH:							      //获取开关实际状态
		{
			re = RelayM_GetActureStatus(passage);
		} break;

		case RELAYM_ON_TIME:							  //获取闭合实际时间
		{
			re = RelayM_GetOnTime(passage);
		} break;

		case RELAYM_OFF_TIME:							  //获取断开实际时间
		{
			re = RelayM_GetOffTime(passage);
		} break;

		case RELAYM_RES_VALUE:							  //获取内阻实际大小
		{
			re = RelayM_GetRes(passage);
		} break;

		default:
	    {
	    } break;
	}
	return re;
}