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


RelayM_FaultType RelayM_GetFault(uint8 channel)   				//继电器故障检测
{
	RelayM_FaultType re = 0;
	if (channel < RELAYM_MAX_NUM)                               //数组越界保护
	{
		if ((RelayM_CurrentAttribute[channel].actual_status) == (RELAYM_STATUS_(channel)))//判断继电器控制状态和当前状态是否一致
		{
			re = (RelayM_FaultType)RELAYM_NORMAL;
		}
		else if ((RelayM_CurrentAttribute[channel].actual_status == 1) && (RELAYM_STATUS_(channel)))
		{
			re = (RelayM_FaultType)RELAYM_ADHESION;
		}
		else if ((RelayM_CurrentAttribute[channel].actual_status == 0) && (RELAYM_STATUS_(channel)))
		{
			re = (RelayM_FaultType)RELAYM_OPEN_LOOP;
		}
		else
		{
		}
	}
	return re;
}

void RelayM_Control(uint8 channel, RelayM_CtrlAttributeType attribute, uint32 value)	//获取继电器控制状态(目标通道,属性,值）
{
	if (channel < RELAYM_MAX_NUM)                     //越界保护
	{
		switch (attribute)
		{
			case RELAYM_CTRL_STATUS:
	        {
	            RelayM_SetStatus(channel, value);
	        } break;

	        case RELAYM_CTRL_ON_TIME:
	        {
	            #if (RELAYM_ON_TIME_SET_SUPPORT == TRUE)
	                RelayM_SetOnTime(channel, value);
	            #endif
	        } break;

	        case RELAYM_CTRL_OFF_TIME:
	        {
	        	#if (RELAYM_OFF_TIME_SET_SUPPORT == TRUE)
	        		RelayM_SetOffTime(channel, value);
	        	#endif
	        } break;

	        case RELAYM_CTRL_RES_VAKUE:
	        {
	        	#if (RELAYM_RES_VALUE_SET_SUPPORT == TRUE)
	        		RelayM_SetRes(channel, value);
	        	#endif
	        } break;

	        default:
	        {
	        } break;
		}
	}
}

uint32 RelayM_Acture(uint8 channel, RelayM_ActualAttributeType attribute)             //继电器当前状态获取(通道，属性)
{
	uint32 re = 0;
	if (channel < RELAYM_MAX_NUM)						//越界保护
	{
		switch (attribute)
		{
			case RELAYM_ACTURE_CONTROL:
			{
				re = RelayM_GetStatus(channel);
			} break;

			case RELAYM_ACTURE_STATUS:
			{
				re = RelayM_GetCurStatus(channel);
			} break;

			case RELAYM_ACTURE_ON_TIME:
			{
				re = RelayM_GetOnTime(channel);
			} break;

			case RELAYM_ACTURE_OFF_TIME:
			{
				re = RelayM_GetOffTime(channel);
			} break;

			case RELAYM_ACTURE_RES_VAKUE:
			{
				re = RelayM_GetRes(channel);
			} break;

			default:
	        {
	        } break;

		}
	}
	return re;
}