#include "PLL.h"
#include "derivative.h"

void  PLL_Init(void)       //初始化锁相环
{
   CLKSEL_PLLSEL = 0;	    //总线时钟来源于晶振
   PLLCTL_PLLON = 0;        //关闭PLL
   SYNR = 0x47; 	          //VCOFRQ[1:0]=1;STNDDIV[5:0]=7
   REFDV = 0x41;            //REFFRQ[1:0]=1;REFDIV[5:0]=1
   POSTDIV = 0x00;          //fOSC=8MHz;PLL=64M;BUS=32M
   PLLCTL_PLLON = 1;  //打开PLL
   _asm(nop);
   _asm(nop);     //等待两个机器周期
   while(CRGFLG_LOCK == 0)
   {
   }                      //根据CRGFLG寄存器的LOCK位，确定PLL是否稳定	LOCK==1 稳定，==0 不稳定
   CLKSEL_PLLSEL = 1;     //选择PLL作为时钟源
}
