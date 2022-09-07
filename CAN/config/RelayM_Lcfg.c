#include "RelayM_Lcfg.h"

RelayM_AttributeType RelayM_AttributeTestData[RELAYM_MAX_NUM] = 	//继电器实际状态数据存放数组
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
};

RelayM_AttributeType RelayM_CurrentAttribute[RELAYM_MAX_NUM] = 		//继电器控制状态数据存放数组
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
};

RelayM_Fn_Type RelayM_FnCfg =
{
	RELAYM_STATUS,
	RELAYM_ON_TIME,
	RELAYM_OFF_TIME,
	RELAYM_RES_VALUE,
};