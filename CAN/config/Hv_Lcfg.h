#ifndef __HV_LCFG_H
#define __HV_LCFG_H

#include "hidef.h"
#include "derivative.h"
#include "Hv.h"

#define HV_MAX_PASSAGE 6U           //高压模块最大通道个数

#define Hv_Buffered_Vol 10U			//充放电管理缓冲电压
#define Hv_Buffered_Temp 5U			//电池热管理缓冲温度

#define Hv_RES_DC_MIN   (100U)		//直流电路绝缘电阻最小值为100欧姆/V
#define Hv_RES_AC_MIN   (500U)		//交流电路绝缘电阻最小值为500欧姆/V

#define HV_BAT_(X)  Hv_VoltageSample[X].BAT  //BAT电压
#define HV_V1_(X)   Hv_VoltageSample[X].V1   //V1电压
#define HV_TEMP_(X) Hv_VoltageSample[X].TEMP //电池温度


extern HV_ThresholdType HV_Threshold;
extern HV_VoltageDataType Hv_VoltageSample[HV_MAX_PASSAGE];
extern Hv_ResistanceType Hv_ResDCCfg;
extern Hv_ResistanceType Hv_ResACCfg;

#endif