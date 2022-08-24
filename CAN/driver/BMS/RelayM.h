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

typedef enum _RelayM_FaultType     //构建继电器故障类型枚举
{
    RELAYM_NORMAL,                 //正常
    RELAYM_ADHESION,               //粘连
    RELAYM_OPEN_LOOP，             //开路
} RelayM_FaultType;

typedef enum _RelayM_CtrlAttributeType  //构建继电器控制属性枚举（设置状态）
{
    RELAYM_CTRL_STATUS,                 //控制状态
    RELAYM_CTRL_ON_TIME,                //控制闭合时间
    RELAYM_CTRL_OFF_TIME,               //控制断开时间
    RELAYM_CTRL_RES_VAKUE               //控制内阻设置
} RelayM_CtrlAttributeType;

typedef enum _RelayM_ActualAttributeType//构建继电器实际属性枚举（当前状态）
{
    RELAYM_ACTURE_CONTROL,
    RELAYM_ACTURE_STATUS,                 //实际状态
    RELAYM_ACTURE_ON_TIME,                //实际闭合时间
    RELAYM_ACTURE_OFF_TIME,               //实际断开时间
    RELAYM_ACTURE_RES_VAKUE               //实际内阻设置
} RelayM_ActualAttributeType;

extern void RelayM_Init(void);                                           //继电器模块初始化函数
extern void RelayM_InterruptON(void);                                    //开中断
extern void RelayM_InterruptOFF(void);                                   //关中断
extern void RelayM_SetStatus(uint8 channel, uint32 value);               //设置继电器状态
extern uint32 RelayM_GetStatus(uint8 channel);                           //获取继电器状态
extern uint32 RelayM_GetCurStatus(uint8 channel);                        //获取继电器当前状态
extern void RelayM_SetOnTime(uint8 channel, uint32 value);               //设置继电器闭合时间
extern uint32 RelayM_GetOnTime(uint8 channel);                           //获取继电器闭合时间
extern void RelayM_SetOffTime(uint8 channel ,uint32 value);              //设置继电器断开时间
extern uint32 RelayM_GetOffTime(uint8 channel);                          //获取继电器断开时间
extern void RelayM_SetRes(uint8 channel ,uint32 value);                  //设置继电器内阻值
extern uint32 RelayM_GetRes(uint8 channel);                              //获取继电器内阻值
extern RelayM_FaultType RelayM_GetFault(uint8 channel);                  //继电器故障检测
extern void RelayM_Control(uint8 channel, RelayM_CtrlAttributeType attribute, uint32 value);  //获取继电器控制状态(目标通道,属性,值）
extern uint32 RelayM_Acture(uint8 channel, RelayM_ActualAttributeType attribute);             //继电器当前状态获取(通道，属性)

#endif