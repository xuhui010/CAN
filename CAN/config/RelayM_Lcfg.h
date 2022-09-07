#ifndef __RELAYM_LCFG_H
#define __RELAYM_LCFG_H

#include "RelayM.h"

#define RELAYM_MAX_NUM  6                   	//继电器控制最大数量

#define RELAYM_STATUS_(X)			(*(uint32 *)(&(RelayM_AttributeTestData[X].actual_status)))
#define RELAYM_ON_TIME_(X)			(*(uint32 *)(&(RelayM_AttributeTestData[X].on_time)))
#define RELAYM_OFF_TIME_(X)			(*(uint32 *)(&(RelayM_AttributeTestData[X].off_time)))
#define RELAYM_RES_VALUE_(X)		(*(uint32 *)(&(RelayM_AttributeTestData[X].res_value)))

#define RELAYM_CUR_STATUS_(X)   	(*(uint32 *)(&(RelayM_CurrentAttribute[X].actual_status)))
#define RELAYM_CUR_ON_TIME_(X)		(*(uint32 *)(&(RelayM_CurrentAttribute[X].on_time)))
#define RELAYM_CUR_OFF_TIME_(X)		(*(uint32 *)(&(RelayM_CurrentAttribute[X].off_time)))
#define RELAYM_CUR_RES_VALUE_(X)	(*(uint32 *)(&(RelayM_CurrentAttribute[X].res_value)))


extern RelayM_AttributeType RelayM_AttributeTestData[RELAYM_MAX_NUM];	//继电器实际属性数据存放
extern RelayM_AttributeType RelayM_CurrentAttribute[RELAYM_MAX_NUM];	//继电器控制属性数据存放
extern RelayM_Fn_Type RelayM_FnCfg;
#endif