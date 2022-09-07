#include "Pre_Lcfg.h"

Pre_TimeOutType Pre_TimeOut =
{
	3,
};

Pre_StateDataType Pre_StateData;

Pre_BAT_VoltageType Pre_BAT_Voltage =
{
	95,
};

void Pre_StateData_Write(Pre_StateType state, uint8 data) //将报文相关数据存入预充状态数据结构体中
{
	switch (state)
	{
		case PRE_STATE_FAULT:
		{
			Pre_StateData.fault = data;      //存储故障数据
		} break;

		case PRE_STATE_TIME:
		{
			Pre_StateData.time = data;       //存储时间数据
		} break;

		case PRE_STATE_VOLTAGE:
		{
			Pre_StateData.voltage = data;    //存储电压数据
		} break;

		default:
		{

		} break;
	}
}

int Pre_StateData_Fault(void)             //预充故障函数初始化
{
	return Pre_StateData.fault;             //返回故障参数值
}

int Pre_StateData_Time(void)              //预充时间函数初始化
{
	return Pre_StateData.time;              //返回时间参数值
}

uint16 Pre_StateData_Voltage(uint8 channel)    //预充电压函数初始化
{
	uint16 re = 0;
	if (channel == 0)
	{
		re = Hv_Get(Pre_StateData.voltage, HV_VOLTAGE);  //获取存储电压
	}
	else
	{
		re = Hv_Get(channel, HV_VOLTAGE);
	}
	return re;
}
