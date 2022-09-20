#ifndef __RELAYM_H
#define __RELAYM_H

#include "hidef.h"
#include "derivative.h"

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;

typedef enum _RelayM_NameType   //继电器种类枚举
{
    PreCharged_Relay,           //预充继电器
    TotalPositive_Relay,        //总正继电器
    TotalNegative_Relay,        //总负继电器
    FastCharging_Relay,         //快充继电器
    SlowCharging_Relay,         //慢充继电器
    Heating_Relay,              //加热继电器
} RelayM_NameType;

typedef struct _RelayM_AttributeType //构建继电器属性结构体
{
    RelayM_NameType RelayM_Name;     //继电器类型选择
    uint32 actual_status;            //继电器实际状态
    uint32 on_time;                  //继电器闭合耗时
    uint32 off_time;                 //继电器断开耗时
    uint32 res_value;                //继电器内阻设置
} RelayM_AttributeType;

typedef enum _Std_RetureType
{
    RELAYM_STATUS,
    RELAYM_NOT_STATUS,
    RELAYM_ON_TIME,
    RELAYM_NOT_ON_TIME,
    RELAYM_OFF_TIME,
    RELAYM_NOT_OFF_TIME,
    RELAYM_RES_VALUE,
    RELAYM_NOT_RES_VALUE,
} Std_RetureType;

typedef enum _Std_SwitchType         //继电器开关状态返回值
{
    RELAYM_SWITCH_ON,
    RELAYM_SWITCH_OFF,
} Std_SwitchType;

typedef struct _RelayM_Fn_Type
{
    Std_RetureType status;      //是否拥有控制属性
    Std_RetureType on_time;     //是否拥有闭合时间属性
    Std_RetureType off_time;    //是否拥有断开时间属性
    Std_RetureType res_value;   //是否拥有控制阻值属性
} RelayM_Fn_Type;

typedef enum _RelayM_FaultType     //构建继电器故障类型枚举
{
    RELAYM_ADHESION,               //粘连
    RELAYM_OPEN_LOOP,              //开路
    RELAYM_NO_FAULT,               //无故障
} RelayM_FaultType;

typedef enum _RelayM_ControlType        //继电器控制属性枚举（设置状态）
{
    RELAYM_CTRL_STATUS,                 //控制状态
    RELAYM_CTRL_ON_TIME,                //控制闭合时间
    RELAYM_CTRL_OFF_TIME,               //控制断开时间
    RELAYM_CTRL_RES_VALUE               //控制内阻设置
} RelayM_ControlType;

typedef enum _RelayM_ActureType         //继电器实际属性枚举（当前状态）
{
    RELAYM_ACTURE_CONTROL,
    RELAYM_ACTURE_STATUS,                 //实际状态
    RELAYM_ACTURE_ON_TIME,                //实际闭合时间
    RELAYM_ACTURE_OFF_TIME,               //实际断开时间
    RELAYM_ACTURE_RES_VALUE               //实际内阻设置
} RelayM_ActureType;

extern void RelayM_Init(void);                                           //继电器模块初始化函数
extern void RelayM_InterruptON(void);                                    //开中断
extern void RelayM_InterruptOFF(void);                                   //关中断
extern Bool RelayM_SetStatus(uint8 passage, uint32 data);                //设置继电器状态
extern uint32 RelayM_GetControlStatus(uint8 passage);                    //获取继电器控制状态
extern uint32 RelayM_GetActureStatus(uint8 passage);                     //获取继电器实际状态
extern Bool RelayM_SetOnTime(uint8 passage, uint32 data);                //设置继电器闭合时间
extern uint32 RelayM_GetOnTime(uint8 passage);                           //获取继电器闭合时间
extern Bool RelayM_SetOffTime(uint8 passage ,uint32 data);               //设置继电器断开时间
extern uint32 RelayM_GetOffTime(uint8 passage);                          //获取继电器断开时间
extern Bool RelayM_SetRes(uint8 passage ,uint32 data);                   //设置继电器内阻值
extern uint32 RelayM_GetRes(uint8 passage);                              //获取继电器内阻值
extern RelayM_FaultType RelayM_GetFault(uint8 passage);                  //继电器故障检测
extern Std_SwitchType RelayM_Control(uint8 passage, RelayM_Fn_Type *fn, RelayM_ControlType ctl, uint32 data);  //继电器控制状态获取(目标通道,判断，属性,值）
extern uint32 RelayM_Acture(uint8 passage, RelayM_ActureType attribute);                             //继电器实际状态获取(通道，属性)

#endif