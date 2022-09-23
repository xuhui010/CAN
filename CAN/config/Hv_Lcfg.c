#include "Hv.h"
#include "Hv_Lcfg.h"

HV_VoltageDataType Hv_VoltageSample[HV_MAX_PASSAGE] =         //定义结构体变量，用数组存放高压数据示例
{
	{86, 80, -16},
	{88, 86, 0},
	{96, 88, 16},
	{106, 96, 32},
	{108, 98, 48},
	{116, 108, 64}
};

HV_ThresholdType HV_Threshold =						//配置充放电和散热加热的阈值
{
	90,
	110,
	15,
	35,
};

Hv_ResistanceType Hv_ResDCCfg =					 	//直流电路下绝缘电阻数据示例(实际情况中需要实时检测获取 电桥法或交流注入法)
{
	12000,
	18000,
};

Hv_ResistanceType Hv_ResACCfg =					 	//交流电路下绝缘电阻数据示例(实际情况中需要实时检测获取 电桥法或交流注入法)
{
	52000,
	56000,
};