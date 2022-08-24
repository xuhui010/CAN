#ifndef __HV_LCFG_H
#define __HV_LCFG_H

#include "hidef.h"
#include "derivative.h"
#include "Hv.h"

#define HV_MAX_CHANNEL 6           //高压模块最大通道个数

#define HV_VOLTAGE_MIN  (12U)		//高压模块数据预设范围
#define HV_CURRENT_MIN  (12U)
#define HV_TEMP_MIN     (12U)
#define HV_VOLTAGE_MAX  (100U)
#define HV_CURRENT_MAX  (100U)
#define HV_TEMP_MAX     (100U)

#define HV_VOLTAGE_(X)  (*(uint16 *)(&(Hv_DataSample[X].voltage)))
#define HV_CURRENT_(X)  (*(uint16 *)(&(Hv_DataSample[X].current)))
#define HV_TEMP_(X)     (*(uint16 *)(&(Hv_DataSample[X].temp)))

extern Hv_DataType Hv_DataSample[HV_MAX_CHANNEL];

#endif