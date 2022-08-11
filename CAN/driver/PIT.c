#include "PIT.h"
#include "derivative.h"

void PIT_Init(void)
{
	PITCFLMT_PITE = 0;    //PIT���ƺ�ǿ�Ƽ���΢��ʱ���Ĵ��� ���PITE���������PITģ�鱻�ر���PITTF�Ĵ����еı�־λ�����
	PITCE_PCE0 = 1;       //PITͨ��ʹ�ܼĴ��� ������Ӧ��PITͨ�� PCE0ͨ��ʹ��
	PITMUX = 0X00;        //ͨ��0��1��2��3ʹ��΢��ʱ����׼0���� д1������΢��ʱ��1����
	PITMTLD0 = 250 - 1;
	PITLD0 = 64000 - 1;	  //T = (PITMTLD+1)*(PITLD+1)/Fbus = 500ms FBUS = 32mhz
	PITINTE_PINTE0 = 1;   // �ж�ʹ��
	PITCFLMT_PITE = 1;    //ʹ��PIT
}