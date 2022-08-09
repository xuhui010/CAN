#include "PLL.h"
#include "derivative.h"

void  PLL_Init(void)       //��ʼ�����໷
{
   CLKSEL_PLLSEL = 0;	    //����ʱ����Դ�ھ���
   PLLCTL_PLLON = 0;        //�ر�PLL
   SYNR = 0x47; 	          //VCOFRQ[1:0]=1;STNDDIV[5:0]=7
   REFDV = 0x41;            //REFFRQ[1:0]=1;REFDIV[5:0]=1
   POSTDIV = 0x00;          //fOSC=8MHz;PLL=64M;BUS=32M
   PLLCTL_PLLON = 1;  //��PLL
   _asm(nop);
   _asm(nop);     //�ȴ�������������
   while(CRGFLG_LOCK == 0)
   {
   }                      //����CRGFLG�Ĵ�����LOCKλ��ȷ��PLL�Ƿ��ȶ�	LOCK==1 �ȶ���==0 ���ȶ�
   CLKSEL_PLLSEL = 1;     //ѡ��PLL��Ϊʱ��Դ
}
