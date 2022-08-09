#include "DIO.h"

void DIO_Init(void)
{
    PIN_PC4 = 1;
    PIN_PC4_DDRC = 1;
    PIN_PC5 = 0;
    PIN_PC5_DDRC = 1;
}

/*对DIO驱动标准化，
在配置文件中可以直接配置PORT口和PORT位
仅输入参数（端口配置）即可*/