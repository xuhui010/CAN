#ifndef __HV_H
#define __HV_H

#include "hidef.h"
#include "derivative.h"

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;      //重定义数据类型

typedef enum _Hv_AttributeType          //高压模块属性类型
{
    HV_VOLTAGE,                         //电压
    HV_CURRENT,                         //电流
} Hv_AttributeType;

typedef struct _HV_DataType             //高压属性数据类型
{
    uint32 voltage;
    uint32 current;
}Hv_DataType;


extern void Hv_Init(void);
void Hv_InterruptON(void);
void Hv_InterruptOFF(void);
int HV_DetectInterval(uint32 data, Hv_AttributeType Attribute);
extern uint16 Hv_GetAttribute(uint8 passage, Hv_AttributeType Attribute);
extern uint16 Hv_Get(uint8 passage, Hv_AttributeType Attribute);

#endif