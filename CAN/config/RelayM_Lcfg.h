#ifndef __RELAYM_LCFG_H
#define __RELAYM_LCFG_H

#include "RelayM.h"

#define RELAYM_MAX_NUM  6                   	//继电器控制最大数量
#define RELAYM_ON_TIME_SET_SUPPORT   TRUE       //继电器支持设置闭合时间功能
#define RELAYM_OFF_TIME_SET_SUPPORT  TRUE       //继电器支持设置断开时间功能
#define RELAYM_RES_VALUE_SET_SUPPORT TRUE       //继电器支持设置内阻功能


#define RELAYM_STATUS_(X)		(*(uint32 *)(&(RelayM_AttributeTestData.actual_status)))
#define RELAYM_ON_TIME_(X)		(*(uint32 *)(&(RelayM_AttributeTestData.on_time)))
#define RELAYM_OFF_TIME_(X)		(*(uint32 *)(&(RelayM_AttributeTestData.off_time)))
#define RELAYM_RES_VALUE_(X)	(*(uint32 *)(&(RelayM_AttributeTestData.res_value)))

extern RelayM_AttributeType RelayM_AttributeTestData[RELAYM_MAX_NUM];	//继电器当前属性测试数据存放
extern RelayM_AttributeType RelayM_CurrentAttribute[RELAYM_MAX_NUM];	//继电器属性测试数据存放

#endif