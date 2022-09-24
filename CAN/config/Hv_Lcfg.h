#ifndef __HV_LCFG_H
#define __HV_LCFG_H

#include "hidef.h"
#include "derivative.h"
#include "Hv.h"

#define HV_MAX_PASSAGE 6U           //��ѹģ�����ͨ������

#define Hv_Buffered_Vol 10U			//��ŵ�������ѹ
#define Hv_Buffered_Temp 5U			//����ȹ������¶�

#define Hv_RES_DC_MIN   (100U)		//ֱ����·��Ե������СֵΪ100ŷķ/V
#define Hv_RES_AC_MIN   (500U)		//������·��Ե������СֵΪ500ŷķ/V

#define HV_BAT_(X)  Hv_VoltageSample[X].BAT  //BAT��ѹ
#define HV_V1_(X)   Hv_VoltageSample[X].V1   //V1��ѹ
#define HV_TEMP_(X) Hv_VoltageSample[X].TEMP //����¶�


extern HV_ThresholdType HV_Threshold;
extern HV_VoltageDataType Hv_VoltageSample[HV_MAX_PASSAGE];
extern Hv_ResistanceType Hv_ResDCCfg;
extern Hv_ResistanceType Hv_ResACCfg;

#endif