#include "Hv.h"
#include "Hv_Lcfg.h"
#include "Pre_Lcfg.h"
#include "RelayM_Lcfg.h"

void Hv_Init(void)              //高压管理模块初始化函数
{
}

void Hv_InterruptON(void)       //中断开
{
}

void Hv_InterruptOFF(void)      //中断关
{
}

uint32 Hv_Get(uint8 passage, Hv_VoltageType Hv_Voltage)     //获取当前电压函数
{
	uint32 re = 0;

	if (passage < HV_MAX_PASSAGE)							//越界保护
	{
		if (Hv_Voltage == HV_VOLTAGE_BAT)					//获取当前BAT电源电压
		{
			re = HV_BAT_(passage);
		}
		else if (Hv_Voltage == HV_VOLTAGE_V1)				//获取当前V1电路电压
		{
			re = HV_V1_(passage);
		}
	}
	return re;
}

Hv_ChargeControlType Hv_GetControl(uint8 passage, HV_StateType HV_State, HV_ThresholdType *cfg)	//电池充放电控制和热管理函数
{
	Hv_ChargeControlType Hv_ChargeControl;

	if (passage < HV_MAX_PASSAGE)
	{
		if (HV_State == Whether_Charge)							//电池充放电管理
		{
			if (HV_V1_(passage) > cfg->dischargedata)			//V1单体电压过高，大于放电电压阈值
			{
				do
				{
					HV_V1_(passage)--;
				}
				while (!((HV_V1_(passage) + Hv_Buffered_Vol) < cfg->dischargedata));
				Hv_ChargeControl = Hv_DisCharge;				//控制电池放电
			}
			else if (HV_V1_(passage) < cfg->chargedata)			//V1单体电压过低，小于充电电压阈值
			{
				do
				{
					HV_V1_(passage)++;
				}
				while (!(HV_V1_(passage) > (cfg->chargedata + Hv_Buffered_Vol)));
				Hv_ChargeControl = Hv_Charge;			    	//控制电池充电
			}
		}

		else if (HV_State == Whether_Cooling)					//电池热管理
		{
			if (HV_TEMP_(passage) > cfg->coolingdata)			//电池温度过高，大于散热阈值
			{
				do
				{
					if (RelayM_Control(5, &RelayM_FnCfg, RELAYM_CTRL_STATUS, 0))    //断开加热继电器开关
					{
						HV_TEMP_(passage)--;
					}
				}
				while (!((HV_TEMP_(passage) + Hv_Buffered_Temp) < cfg->coolingdata));
				Hv_ChargeControl = Hv_Cooling;                  //控制电池散热
			}
			else if (HV_TEMP_(passage) < cfg->heatingdata)		//电池温度过低，小于加热阈值
			{
				do
				{
					if (RelayM_Control(5, &RelayM_FnCfg, RELAYM_CTRL_STATUS, 1))    //闭合加热继电器开关
					{
						HV_TEMP_(passage)++;
					}
				}
				while (!(HV_TEMP_(passage) > (cfg->coolingdata + Hv_Buffered_Temp)));
				Hv_ChargeControl = Hv_Heating;                  //控制电池加热
			}
		}
	}
	return Hv_ChargeControl;
}

uint32 Hv_ResistanceGet(uint8 passage, Hv_CircuitType Hv_Circuit)	//获取当前电路绝缘电阻理论上最小值
{
	uint32 re = 0;

	if (passage < HV_MAX_PASSAGE)
	{
		if (Hv_Circuit == HV_DC)										//直流电路
		{
			re = Hv_Get(passage, HV_VOLTAGE_V1) * Hv_RES_DC_MIN;
		}
		else if (Hv_Circuit == HV_AC)									//交流电路
		{
			re = Hv_Get(passage, HV_VOLTAGE_V1) * Hv_RES_AC_MIN;
		}
	}
	return re;
}

Bool Hv_InsulationDetect(uint8 passage, Hv_CircuitType Hv_Circuit, Hv_ResistanceType *res)  //高压模块绝缘检测函数
{
	Bool re = FALSE;
	uint32 data = Hv_ResistanceGet(passage, Hv_Circuit);

	if (passage < HV_MAX_PASSAGE)
	{
		if (Hv_Circuit == HV_DC)         			//直流电路
		{
			res = &Hv_ResDCCfg;						//初始化结构体指针变量
			if ((res->Rn > data) && (res->Rp > data))
			{
				re = TRUE;
			}
			else
			{
				re = FALSE;
			}
		}
		else if (Hv_Circuit == HV_AC)				//交流电路
		{
			res = &Hv_ResACCfg;
			if ((res->Rn > data) && (res->Rp > data))
			{
				re = TRUE;
			}
			else
			{
				re = FALSE;
			}
		}
	}
	return re;
}