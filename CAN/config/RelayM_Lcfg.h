#ifndef __RELAYM_LCFG_H
#define __RELAYM_LCFG_H

#include "RelayM.h"

#define RELAYM_MAX_NUM  6                   //继电器控制最大数量



#define RELAYM_STATUS_(X)		(*(uint32 *)(&(RelayM_AttributeTestData.actual_status)))
#define RELAYM_ON_TIME_(X)		(*(uint32 *)(&(RelayM_AttributeTestData.on_time)))
#define RELAYM_OFF_TIME_(X)		(*(uint32 *)(&(RelayM_AttributeTestData.off_time)))
#define RELAYM_RES_VALUE_(X)	(*(uint32 *)(&(RelayM_AttributeTestData.res_value)))

#endif