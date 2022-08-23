#include "PIT.h"
#include "derivative.h"

void PIT_Init(void)
{
	PITCFLMT_PITE = 0U;    //PIT控制和强制加载微定时器寄存器 如果PITE被清除，则PIT模块被关闭且PITTF寄存器中的标志位被清除
	PITCE_PCE0 = 1U;       //PIT通道使能寄存器 启用相应的PIT通道 PCE0通道使能
	PITMUX = 0X00U;        //通道0、1、2、3使用微定时器基准0计数 写1代表以微定时器1计数
	PITMTLD0 = 250U - 1U;
	PITLD0 = 64000U - 1U;	  //T = (PITMTLD+1)*(PITLD+1)/Fbus = 500ms FBUS = 32mhz
	PITINTE_PINTE0 = 1U;   // 中断使能
	PITCFLMT_PITE = 1U;    //使能PIT
}