#ifndef __RELAYM_H
#define __RELAYM_H

#include "hidef.h"
#include "derivative.h"

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;

typedef enum _RelayM_Kinds_Type    //继电器种类枚举
{
    PreCharged_Relay,              //预充继电器
    TotalPositive_Relay,           //总正继电器
    TotalNegative_Relay,           //总负继电器
    FastCharging_Relay,            //快充继电器
    SlowCharging_Relay,            //慢充继电器
    Heating_Relay,                 //加热继电器
} RelayM_Kinds_Type;

typedef struct _RelayM_ControlType   //继电器属性结构体
{
    uint16 switch_status;            //继电器开关状态
    uint16 on_time;                  //继电器闭合耗时
    uint16 off_time;                 //继电器断开耗时
    uint16 res_value;                //继电器内阻设置
} RelayM_ControlType;

typedef struct _RelayM_StateType      //继电器控制状态信息配置
{
    RelayM_Kinds_Type RelayM_Kinds;   //继电器种类
    RelayM_ControlType* cfg;          //继电器属性结构体指针
} RelayM_StateType;

typedef struct _RelayM_ActureType     //继电器实际状态信息配置
{
    RelayM_Kinds_Type RelayM_Kinds;   //继电器种类
    RelayM_ControlType* act;          //继电器属性结构体指针
} RelayM_ActureType;

typedef enum _RelayM_FaultType     //构建继电器故障类型枚举
{
    RELAYM_ADHESION,               //粘连
    RELAYM_OPEN_LOOP,              //开路
    RELAYM_NO_FAULT,               //无故障
} RelayM_FaultType;

typedef enum _RelayM_Fn_Type      //继电器属性选择
{
    RELAYM_SWITCH,                //开关
    RELAYM_ON_TIME,               //闭合时间
    RELAYM_OFF_TIME,              //断开时间
    RELAYM_RES_VALUE,             //内阻
} RelayM_Fn_Type;

extern void RelayM_Init(void);                                           //继电器模块初始化函数
extern void RelayM_InterruptON(void);                                    //开中断
extern void RelayM_InterruptOFF(void);                                   //关中断
extern void RelayM_SetStatus(uint8 passage, uint16 data);
extern uint16 RelayM_GetControlStatus(uint8 passage);
extern uint16 RelayM_GetActureStatus(uint8 passage);
extern void RelayM_SetOnTime(uint8 passage, uint16 ontime);
extern uint16 RelayM_GetOnTime(uint8 passage);
extern void RelayM_SetOffTime(uint8 passage ,uint16 offtime);
extern uint16 RelayM_GetOffTime(uint8 passage);
extern void RelayM_SetRes(uint8 passage ,uint16 res);
extern uint16 RelayM_GetRes(uint8 passage);
extern RelayM_FaultType RelayM_GetFault(uint8 passage);
extern void RelayM_Control(uint8 passage, RelayM_Fn_Type fn, uint16 data);
extern uint16 RelayM_Acture(uint8 passage, RelayM_Fn_Type fn);

#endif