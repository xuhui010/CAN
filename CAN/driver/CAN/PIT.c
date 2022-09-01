#include "PIT.h"
#include "derivative.h"

void PIT_Init(void)
{
	PITCFLMT_PITE = 0U;    //PIT���ƺ�ǿ�Ƽ���΢��ʱ���Ĵ��� ���PITE���������PITģ�鱻�ر���PITTF�Ĵ����еı�־λ�����
	PITCE_PCE0 = 1U;       //PITͨ��ʹ�ܼĴ��� ������Ӧ��PITͨ�� PCE0ͨ��ʹ��
	PITMUX = 0X00U;        //ͨ��0��1��2��3ʹ��΢��ʱ����׼0���� д1������΢��ʱ��1����
	PITMTLD0 = 250U - 1U;
	PITLD0 = 64000U - 1U;	  //T = (PITMTLD+1)*(PITLD+1)/Fbus = 500ms FBUS = 32mhz
	PITINTE_PINTE0 = 1U;   // �ж�ʹ��
	PITCFLMT_PITE = 1U;    //ʹ��PIT
}