#include "DIO.h"

void DIO_Init(void)  //直接配置PORT口和PORT位，仅输入参数（端口配置）
{
    PIN_PC4 = 1;
    PIN_PC4_DDRC = 1;
    PIN_PC5 = 0;
    PIN_PC5_DDRC = 1;
}
