#include "Hv.h"
#include "Hv_Lcfg.h"
#include "Pre_Lcfg.h"

void Hv_Init(void)              //高压管理模块初始化函数
{
}

void Hv_InterruptON(void)       //中断开
{
}

void Hv_InterruptOFF(void)      //中断关
{
}

int HV_DetectInterval(uint32 data, Hv_AttributeType Attribute)    //检测高压模块属性数据是否在预设区间内
{
	int re = 0;
	uint32 maxdata = 0;
	uint32 mindata = 0;

	if (Attribute == HV_VOLTAGE)              //设定电压数据区间
	{
		maxdata = HV_VOLTAGE_MAX;
		mindata = HV_VOLTAGE_MIN;
	}
	else if (Attribute == HV_CURRENT)         //设定电流数据区间
	{
		maxdata = HV_CURRENTMAX;
		mindata = HV_CURRENTMIN;
	}
	else if (Attribute == HV_TEMP)            //设定温度数据区间
	{
		maxdata = HV_TEMPMAX;
		mindata = HV_TEMPMIN;
	}
	else
	{
	}

	if ((data > mindata) && (data < maxdata))  //判断参数是否在所设的区间内
	{
		re = 0;
	}
	else
	{
		re = 1;
	}
	return re;
}

Hv_AttributeType Hv_BatteryStatus(uint8 channel)  //返回电池的充电或放电状态
{
	Hv_AttributeType re;
	//channel = ?;

	if (HV_CURRENT_(channel) > 0)
	{
		re = HV_DISCHARGE;          //电流大于0为放电状态
	}
	else
	{
		re = HV_CHARGE;             //电流小于等于0为充电状态
	}
	return re;
}

uint16 Hv_GetAttribute(uint8 channel, Hv_AttributeType Attribute) //获取高压模块相应属性数据
{
	uint16 re = 0;
	//channel = ?;

	switch (Attribute)
	{
		case HV_VOLTAGE:
		{
			re = HV_VOLTAGE_(channel);         //获取电压数据
		} break;

		case HV_CURRENT_:
		{
			re = HV_CURRENT_(channel);         //获取电流数据
		} break;

		case HV_TEMP:
		{
			re = HV_TEMP_(channel);            //获取温度数据
		} break;

		default:
		{
		} break;
	}
	return re;
}

uint16 Hv_Get(uint8 channel, Hv_AttributeType Attribute)  //获取正确的电压、电流或温度函数
{
	uint16 re = 0;
	uint8 channel = 0；

	for (channel = 0; channel < 6; channel++)
	{
		re = Hv_GetAttribute(channel, Attribute);
		if (HV_DetectInterval(re, Attribute) == 0)       //返回值是0则表示数据在预设区间内
		{
			break;                                       //在预设区间内则提前跳出循环
		}
	}
	return re;
}