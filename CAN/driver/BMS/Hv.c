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

Bool HV_DetectInterval(uint32 data, Hv_AttributeType Attribute)    //检测高压模块属性数据是否在预设区间内
{
	Bool re = TRUE;
	uint32 maxdata = 0;
	uint32 mindata = 0;

	if (Attribute == HV_VOLTAGE)              //设定电压数据区间
	{
		maxdata = HV_VOLTAGE_MAX;
		mindata = HV_VOLTAGE_MIN;
	}
	else
	{
	}

	if ((data > mindata) && (data < maxdata))  //判断参数是否在所设的区间内
	{
		re = TRUE;
	}
	else
	{
		re = FALSE;
	}
	return re;
}

uint16 Hv_GetAttribute(uint8 channel, Hv_AttributeType Attribute) //获取高压模块相应属性数据
{
	uint16 re = 0;

	if (Attribute == HV_VOLTAGE)
	{
		re = HV_VOLTAGE_(channel);         //获取电压数据
	}
	else
	{
	}
	return re;
}

uint16 Hv_Get(uint8 channel, Hv_AttributeType Attribute)  //获取正确的电压函数
{
	uint16 re = 0;
	channel = 0;

	for (channel = 0; channel < HV_MAX_CHANNEL; channel++)
	{
		re = Hv_GetAttribute(channel, Attribute);
		if (HV_DetectInterval(re, Attribute) == 0)       //返回值是0则表示数据在预设区间内
		{
			break;                                       //在预设区间内则提前跳出循环
		}
	}
	return re;
}