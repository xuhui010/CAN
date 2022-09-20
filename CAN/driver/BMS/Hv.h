#ifndef __HV_H
#define __HV_H

#include "hidef.h"
#include "derivative.h"

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;      //重定义数据类型

typedef enum _Hv_VoltageType            //高压模块电压类型
{
    HV_VOLTAGE_BAT,                     //BAT电源电压
    HV_VOLTAGE_V1,                      //V1电路电压
} Hv_VoltageType;

typedef enum _Hv_CircuitType            //高压模块电路类型
{
    HV_DC,                              //直流电路
    HV_AC,                              //交流电路
} Hv_CircuitType;

typedef struct _Hv_ResistanceType       //高压模块绝缘电阻
{
    uint32 Rn;
    uint32 Rp;
} Hv_ResistanceType;

typedef struct _HV_VoltageDataType      //高压属性电压和温度类型
{
    uint32 BAT;
    uint32 V1;
    uint32 TEMP;
} HV_VoltageDataType;

typedef enum _Hv_ChargeControlType      //电池充放电和热管理控制
{
    Hv_Charge,                          //充电
    Hv_DisCharge,                       //放电
    Hv_Heating,                         //加热
    Hv_Cooling,                         //散热
} Hv_ChargeControlType;

typedef enum _HV_StateType              //高压模块状态枚举
{
    Whether_Charge,                     //是否需要充电
    Whether_Cooling,                    //是否需要散热
} HV_StateType;

typedef struct _HV_ThresholdType        //阈值结构体
{
    uint32 chargedata;                  //充电阈值
    uint32 dischargedata;               //放电阈值
    uint32 heatingdata;                 //加热阈值
    uint32 coolingdata;                 //散热阈值
} HV_ThresholdType;

typedef enum _HVIL_StateType            //高压互锁故障诊断
{
    HVIL_SHORT_CIRCUIT,                 //短路
    HVIL_CIRCUIT_BREAKER,               //断路
    HVIL_NORMAL,                        //正常
} HVIL_StateType;

extern void Hv_Init(void);
void Hv_InterruptON(void);
void Hv_InterruptOFF(void);
extern uint32 Hv_Get(uint8 passage, Hv_VoltageType Hv_Voltage);     //获取当前电压函数
extern Hv_ChargeControlType Hv_GetControl(uint8 passage, HV_StateType HV_State, HV_ThresholdType *cfg);  //电池充放电控制和热管理函数
extern uint32 Hv_ResistanceGet(uint8 passage, Hv_CircuitType Hv_Circuit);    //获取当前电路绝缘电阻理论最小值
extern Bool Hv_InsulationDetect(uint8 passage, Hv_CircuitType Hv_Circuit, Hv_ResistanceType *res);  //高压模块绝缘检测函数

#endif