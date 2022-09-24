#ifndef __RELAYM_LCFG_H
#define __RELAYM_LCFG_H

#include "RelayM.h"

#define RELAYM_MAX_NUM  6                   	//继电器控制最大数量
#define RELAYM_RES_SUPPORT TRUE
#define RELAYM_ONTIME_SUPPORT TRUE
#define RELAYM_OFFTIME_SUPPORT TRUE

extern RelayM_ControlType RelayM_ControlNum[RELAYM_MAX_NUM];
extern RelayM_ControlType RelayM_ActureNum[RELAYM_MAX_NUM];
extern RelayM_StateType RelayM_StateCfg[RELAYM_MAX_NUM];
extern RelayM_ActureType RelayM_ActureCfg[RELAYM_MAX_NUM];
/*extern RelayM_ControlType RelayM_Control0;
extern RelayM_ControlType RelayM_Control1;
extern RelayM_ControlType RelayM_Control2;
extern RelayM_ControlType RelayM_Control3;
extern RelayM_ControlType RelayM_Control4;
extern RelayM_ControlType RelayM_Control5;*/

#endif