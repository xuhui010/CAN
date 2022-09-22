#ifndef __HV_H
#define __HV_H

#include "hidef.h"
#include "derivative.h"
#include "Node.h"

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

typedef struct _HV_ThresholdType        //阈值结构体
{
    uint32 chargedata;                  //充电阈值
    uint32 dischargedata;               //放电阈值
    uint32 heatingdata;                 //加热阈值
    uint32 coolingdata;                 //散热阈值
} HV_ThresholdType;

typedef struct _Node_HvState_Type       //高压节点状态机
{
    Node_Num_Type Current_Node;         //当前节点
    uint8 (*Judge)(uint8 passage, HV_ThresholdType *cfg); //函数指针 选择相应判断函数
    Node_StateConditions_Type condition;//进入状态条件
    void (*act)(uint8 passage);         //函数指针 选择相应动作函数
    Node_Num_Type Next_Node;            //下一节点
} Node_HvState_Type;

typedef enum _HVIL_StateType            //高压互锁故障诊断
{
    HVIL_SHORT_CIRCUIT,                 //短路
    HVIL_CIRCUIT_BREAKER,               //断路
    HVIL_NORMAL,                        //正常
} HVIL_StateType;

extern void Hv_Init(void);
void Hv_InterruptON(void);
void Hv_InterruptOFF(void);
extern uint32 Hv_Get(uint8 passage, Hv_VoltageType Hv_Voltage);         //获取当前电压函数
extern uint8 Hv_VoltageJudge(uint8 passage, HV_ThresholdType *cfg);     //判断电压函数
extern uint8 Hv_TempJudge(uint8 passage, HV_ThresholdType *cfg);        //判断温度函数
extern void Hv_Discharge(uint8 passage);                                //控制电池放电函数
extern void Hv_Charge(uint8 passage);                                   //控制电池充电函数
extern void Hv_Cooling(uint8 passage);                                  //控制电池散热函数
extern void Hv_Heating(uint8 passage);                                  //控制电池加热函数
extern uint32 Hv_ResistanceGet(uint8 passage, Hv_CircuitType Hv_Circuit);    //获取当前电路绝缘电阻理论最小值
extern Bool Hv_InsulationDetect(uint8 passage, Hv_CircuitType Hv_Circuit, Hv_ResistanceType *res);  //高压模块绝缘检测函数

#endif