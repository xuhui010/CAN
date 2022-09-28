#ifndef __HV_LCFG_H
#define __HV_LCFG_H

#include "hidef.h"
#include "derivative.h"
#include "Hv.h"
#include "Hv_Cfg.h"

#define HV_BAT_(X)  Hv_VoltageSample[X].BAT  //BAT��ѹ
#define HV_V1_(X)   Hv_VoltageSample[X].V1   //V1��ѹ
#define HV_TEMP_(X) Hv_VoltageSample[X].TEMP //����¶�

extern HV_VoltageDataType Hv_VoltageSample[HV_MAX_PASSAGE];
extern HV_ThresholdType HV_Threshold;
extern Hv_ResistanceType Hv_ResDCCfg;
extern Hv_ResistanceType Hv_ResACCfg;

#endif