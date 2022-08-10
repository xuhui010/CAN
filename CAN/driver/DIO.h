#ifndef __DIO_H
#define __DIO_H

#include "hidef.h"
#include "derivative.h"

#define PIN_PC4       PORTC_PC4   //端口数据寄存器
#define PIN_PC4_DDRC  DDRC_DDRC4  //端口数据方向寄存器
#define PIN_PC5       PORTC_PC5
#define PIN_PC5_DDRC  DDRC_DDRC5

void DIO_Init(void);

#endif