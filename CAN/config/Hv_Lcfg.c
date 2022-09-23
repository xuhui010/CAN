#include "Hv.h"
#include "Hv_Lcfg.h"

HV_VoltageDataType Hv_VoltageSample[HV_MAX_PASSAGE] =         //����ṹ��������������Ÿ�ѹ����ʾ��
{
	{86, 80, -16},
	{88, 86, 0},
	{96, 88, 16},
	{106, 96, 32},
	{108, 98, 48},
	{116, 108, 64}
};

HV_ThresholdType HV_Threshold =						//���ó�ŵ��ɢ�ȼ��ȵ���ֵ
{
	90,
	110,
	15,
	35,
};

Hv_ResistanceType Hv_ResDCCfg =					 	//ֱ����·�¾�Ե��������ʾ��(ʵ���������Ҫʵʱ����ȡ ���ŷ�����ע�뷨)
{
	12000,
	18000,
};

Hv_ResistanceType Hv_ResACCfg =					 	//������·�¾�Ե��������ʾ��(ʵ���������Ҫʵʱ����ȡ ���ŷ�����ע�뷨)
{
	52000,
	56000,
};