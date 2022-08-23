#ifndef __RELAYM_H
#define __RELAYM_H

#include "hidef.h"
#include "derivative.h"

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;

typedef struct _RelayM_AttributeType //构建继电器属性结构体
{
    uint32 actual_status;            //继电器实际状态
    uint32 on_time;                  //继电器闭合耗时
    uint32 off_time;                 //继电器断开耗时
    uint32 res_value;                //继电器内阻设置
} RelayM_AttributeType;



#endif