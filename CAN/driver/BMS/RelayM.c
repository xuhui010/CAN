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

Bool RelayM_SetStatus(uint8 passage, uint32 data)  				//设置继电器状态
{
	Bool re = FALSE;
	if (passage < RELAYM_MAX_NUM)
	{
		RELAYM_STATUS_(passage) = data;
		RELAYM_CUR_STATUS_(passage) = data;
		re = TRUE;
	}
	else
	{
		re = FALSE;
	}
	return re;
}

uint32 RelayM_GetControlStatus(uint8 passage)					//获取继电器控制状态
{
	uint32 re = 0;
	if (passage < RELAYM_MAX_NUM)
	{
		re = RELAYM_CUR_STATUS_(passage);
	}
	else
	{
		re = 1;
	}
	return re;
}

uint32 RelayM_GetActureStatus(uint8 passage)					//获取继电器实际状态
{
	uint32 re = 0;
	if (passage < RELAYM_MAX_NUM)
	{
		re = RELAYM_STATUS_(passage);
	}
	else
	{
		re = 1;
	}
	return re;
}

Bool RelayM_SetOnTime(uint8 passage, uint32 data)				//设置继电器闭合时间
{
	Bool re = FALSE;
	if (passage < RELAYM_MAX_NUM)
	{
		RELAYM_ON_TIME_(passage) = data;
		RELAYM_CUR_ON_TIME_(passage) = data;
		re = TRUE;
	}
	else
	{
		re = FALSE;
	}
	return re;
}

uint32 RelayM_GetOnTime(uint8 passage)							//获取继电器闭合时间
{
	uint32 re = 0;
	if (passage < RELAYM_MAX_NUM)
	{
		re = RELAYM_ON_TIME_(passage);
	}
	else
	{
		re = 1;
	}
	return re;
}

Bool RelayM_SetOffTime(uint8 passage ,uint32 data) 				//设置继电器断开时间
{
    Bool re = FALSE;
    if (passage < RELAYM_MAX_NUM)
    {
    	RELAYM_OFF_TIME_(passage) = data;
    	RELAYM_CUR_OFF_TIME_(passage) = data;
    	re = TRUE;
    }
    else
    {
    	re = FALSE;
    }
    return re;
}

uint32 RelayM_GetOffTime(uint8 passage)             			//获取继电器断开时间
{
    uint32 re = 0;
    if (passage < RELAYM_MAX_NUM)
    {
    	re = RELAYM_OFF_TIME_(passage);
    }
    else
    {
    	re = 1;
    }
    return re;
}

Bool RelayM_SetRes(uint8 passage ,uint32 data)     				//设置继电器内阻值
{
	Bool re = FALSE;
	if (passage < RELAYM_MAX_NUM)
	{
		RELAYM_RES_VALUE_(passage) = data;
		RELAYM_CUR_RES_VALUE_(passage) = data;
		re = TRUE;
	}
    else
    {
    	re = FALSE;
    }
    return re;
}

uint32 RelayM_GetRes(uint8 passage)                 			//获取继电器内阻值
{
    uint32 re = 0;
    if (passage < RELAYM_MAX_NUM)
    {
    	re = RELAYM_RES_VALUE_(passage);
    }
    else
    {
    	re = 1;
    }
    return re;
}


RelayM_FaultType RelayM_GetFault(uint8 passage)   										//继电器故障检测
{
	RelayM_FaultType re;
	if (passage < RELAYM_MAX_NUM)                               						//数组越界保护
	{
		if (RelayM_CurrentAttribute[passage].actual_status != RELAYM_STATUS_(passage))	//继电器控制状态和实际状态不同，则继电器出现故障，判断故障类型
		{
			if (RelayM_CurrentAttribute[passage].actual_status == 1)
			{
				re = (RelayM_FaultType)RELAYM_ADHESION;             					//继电器粘连
			}
			else if (RelayM_CurrentAttribute[passage].actual_status == 0)
			{
				re = (RelayM_FaultType)RELAYM_OPEN_LOOP;								//继电器开路
			}
			else
			{
			}
		}
		else
		{
			re = (RelayM_FaultType)RELAYM_NO_FAULT;										//继电器无故障
		}
	}
	return re;
}

Bool RelayM_Control(uint8 passage, RelayM_Fn_Type *fn, RelayM_ControlType ctl, uint32 data)	//继电器控制状态获取(目标通道,判断，属性,值）
{
	Bool re = FALSE;
	if (passage < RELAYM_MAX_NUM)                     					//越界保护
	{
		switch (ctl)
		{
			case RELAYM_CTRL_STATUS:
	        {
	            if (fn->status == RELAYM_STATUS)						//判断继电器是否拥有控制属性
	            {
	            	RelayM_SetStatus(passage, data);
	            	re = TRUE;
	            }
	            else
	            {
	            	re = FALSE;
	            }
	        } break;

	        case RELAYM_CTRL_ON_TIME:
	        {
	            if (fn->on_time == RELAYM_ON_TIME)						//判断继电器是否拥有闭合时间属性
	            {
	            	RelayM_SetOnTime(passage, data);
	            	re = TRUE;
	            }
	            else
	            {
	            	re = FALSE;
	            }
	        } break;

	        case RELAYM_CTRL_OFF_TIME:
	        {
	        	if (fn->off_time == RELAYM_OFF_TIME)					//判断继电器是否拥有断开时间属性
	        	{
	        		RelayM_SetOffTime(passage, data);
	        		re = TRUE;
	        	}
	        	else
	        	{
	        		re = FALSE;
	        	}
	        } break;

	        case RELAYM_CTRL_RES_VALUE:
	        {
	        	if (fn->res_value == RELAYM_RES_VALUE)					//判断继电器是否拥有控制阻值属性
	        	{
	        		RelayM_SetRes(passage, data);
	        		re = TRUE;
	        	}
	        	else
	        	{
	        		re = FALSE;
	        	}
	        } break;

	        default:
	        {
	        } break;
		}
	}
	else
	{
		re = FALSE;
	}
	return re;
}

uint32 RelayM_Acture(uint8 passage, RelayM_ActureType attribute)             //继电器实际状态获取(通道，属性)
{
	uint32 re = 0;
	if (passage < RELAYM_MAX_NUM)						//越界保护
	{
		switch (attribute)
		{
			case RELAYM_ACTURE_CONTROL:
			{
				re = RelayM_GetControlStatus(passage);
			} break;

			case RELAYM_ACTURE_STATUS:
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
	}
	else
	{
		re = 1;
	}
	return re;
}