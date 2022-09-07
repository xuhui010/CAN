#ifndef __HV_LCFG_H
#define __HV_LCFG_H

#include "hidef.h"
#include "derivative.h"
#include "Hv.h"

#define HV_MAX_PASSAGE 6           //高压模块最大通道个数

#define HV_VOLTAGE_MIN  (12U)		//高压模块数据预设范围
#define HV_VOLTAGE_MAX  (100U)


#define HV_VOLTAGE_(X)  (*(uint16 *)(&(Hv_DataSample[X].voltage)))

extern Hv_DataType Hv_DataSample[HV_MAX_PASSAGE];

#endif