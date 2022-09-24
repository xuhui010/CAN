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

	if (Hv_Voltage == HV_VOLTAGE_BAT)					//获取当前BAT电源电压
	{
		re = HV_BAT_(passage);
	}
	else if (Hv_Voltage == HV_VOLTAGE_V1)				//获取当前V1电路电压
	{
		re = HV_V1_(passage);
	}
	return re;
}

/*uint8 Hv_VoltageJudge(uint8 passage, HV_ThresholdType *cfg)	  //判断电压函数
{
	uint8 re = 0;

	if (HV_V1_(passage) > cfg->dischargedata)			//V1单体电压过高，大于放电电压阈值
	{
		re = 0;											//电压过高返回0
	}
	else if (HV_V1_(passage) < cfg->chargedata)			//V1单体电压过低，小于充电电压阈值
	{
		re = 1;			    							//电压过低返回1
	}
	return re;
}

uint8 Hv_TempJudge(uint8 passage, HV_ThresholdType *cfg)	//判断温度函数
{
	uint8 re = 0;

	if (HV_TEMP_(passage) > cfg->coolingdata)			//电池温度过高，大于散热阈值
	{
		re = 0;                  						//温度过高返回0
	}
	else if (HV_TEMP_(passage) < cfg->heatingdata)		//电池温度过低，小于加热阈值
	{
		re = 1;                  						//温度过低返回1
	}
	return re;
}

void Hv_Discharge(uint8 passage)						//控制电池放电函数
{
	HV_ThresholdType *cfg;
	cfg = &HV_Threshold;

	do
	{
		HV_V1_(passage)--;
	}
	while (!((HV_V1_(passage) + Hv_Buffered_Vol) < cfg->dischargedata));
}

void Hv_Charge(uint8 passage)							//控制电池充电函数
{
	HV_ThresholdType *cfg;
	cfg = &HV_Threshold;

	do
	{
		HV_V1_(passage)++;
	}
	while (!(HV_V1_(passage) > (cfg->chargedata + Hv_Buffered_Vol)));
}

void Hv_Cooling(uint8 passage)							//控制电池散热函数
{
	HV_ThresholdType *cfg;
	cfg = &HV_Threshold;

	do
	{
		RelayM_Control(5, RELAYM_SWITCH, 0)    			//断开加热继电器开关
		HV_TEMP_(passage)--;
	}
	while (!((HV_TEMP_(passage) + Hv_Buffered_Temp) < cfg->coolingdata));
}

void Hv_Heating(uint8 passage)							//控制电池加热函数
{
	HV_ThresholdType *cfg;
	cfg = &HV_Threshold;

	do
	{
		RelayM_Control(5, RELAYM_SWITCH, 1)   //闭合加热继电器开关
		HV_TEMP_(passage)++;
	}
	while (!(HV_TEMP_(passage) > (cfg->coolingdata + Hv_Buffered_Temp)));
}*/

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