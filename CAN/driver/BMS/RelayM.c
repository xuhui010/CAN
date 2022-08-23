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

void RelayM_SetStatus(uint8 channel, uint32 value)  			//设置继电器状态
{
	 RELAYM_STATUS_(channel) = value;
	 RelayM_CurrentAttribute[channel].actual_status = value;
}

uint32 RelayM_GetStatus(uint8 channel)							//获取继电器状态
{
	return RelayM_CurrentAttribute[channel].actual_status;
}

uint32 RelayM_GetCurStatus(uint8 channel)						//获取继电器当前状态
{
	return RELAYM_STATUS_(channel);
}

void RelayM_SetOnTime(uint8 channel, uint32 value)				//设置继电器闭合时间
{
	RELAYM_ON_TIME_(channel) = value;
	RelayM_CurrentAttribute[channel].on_time = value;
}

uint32 RelayM_GetOnTime(uint8 channel)							//获取继电器闭合时间
{
	return RELAYM_ON_TIME_(channel);
}

void RelayM_SetOffTime(uint8 channel ,uint32 value) 			//设置继电器断开时间
{
    RELAYM_OFF_TIME_(channel) = value;
    RelayM_CurrentAttribute[channel].off_time = value;
}

uint32 RelayM_GetOffTime(uint8 channel)             			//获取继电器断开时间
{
    return RELAYM_OFF_TIME_(channel);
}

void RelayM_SetRes(uint8 channel ,uint32 value)     			//设置继电器内阻值
{
    RELAYM_RES_VALUE_(channel) = value;
    RelayM_CurrentAttribute[channel].res_value = value;
}

uint32 RelayM_GetRes(uint8 channel)                 			//获取继电器内阻值
{
    return RELAYM_RES_VALUE_(channel);
}


RelayM_FaultStatusType RelayM_GetFault(uint8 channel)   		//继电器故障检测
{

}

//还未完成