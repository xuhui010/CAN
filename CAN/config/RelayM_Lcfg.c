#include "RelayM_Lcfg.h"

RelayM_AttributeType RelayM_AttributeTestData[RELAYM_MAX_NUM] = 	//继电器实际状态数据存放数组
{
	{PreCharged_Relay, 1, 0, 0, 0},		//预充继电器设置
	{TotalPositive_Relay, 1, 0, 0, 0},	//总正继电器设置
	{TotalNegative_Relay, 1, 0, 0, 0},	//总负继电器设置
	{FastCharging_Relay, 1, 0, 0, 0},	//快充继电器设置
	{SlowCharging_Relay, 1, 0, 0, 0},	//慢充继电器设置
	{Heating_Relay, 1, 0, 0, 0}			//加热继电器设置
};

RelayM_AttributeType RelayM_CurrentAttribute[RELAYM_MAX_NUM] = 		//继电器控制状态数据存放数组
{
	{PreCharged_Relay, 1, 0, 0, 0},
	{TotalPositive_Relay, 1, 0, 0, 0},
	{TotalNegative_Relay, 1, 0, 0, 0},
	{FastCharging_Relay, 1, 0, 0, 0},
	{SlowCharging_Relay, 1, 0, 0, 0},
	{Heating_Relay, 1, 0, 0, 0}
};

RelayM_Fn_Type RelayM_FnCfg =
{
	RELAYM_STATUS,
	RELAYM_ON_TIME,
	RELAYM_OFF_TIME,
	RELAYM_RES_VALUE,
};
