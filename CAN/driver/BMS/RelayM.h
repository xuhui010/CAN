#ifndef __RELAYM_H
#define __RELAYM_H

#include "hidef.h"
#include "derivative.h"

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;

typedef enum _RelayM_Fn_Type       //继电器种类枚举
{
    PreCharged_Relay,              //预充继电器
    TotalPositive_Relay,           //总正继电器
    TotalNegative_Relay,           //总负继电器
    FastCharging_Relay,            //快充继电器
    SlowCharging_Relay,            //慢充继电器
    Heating_Relay,                 //加热继电器
} RelayM_Fn_Type;

typedef struct _RelayM_ControlType   //继电器属性结构体
{
    uint16 control_status;            //继电器控制状态
    uint16 actual_status;             //继电器实际状态
    uint16 on_time;                  //继电器闭合耗时
    uint16 off_time;                 //继电器断开耗时
    uint16 res_value;                //继电器内阻设置
} RelayM_ControlType;

typedef struct _RelayM_StateType      //继电器状态信息配置
{
    RelayM_Fn_Type RelayM_Fn;         //继电器种类
    RelayM_ControlType* cfg;          //继电器属性结构体指针
} RelayM_StateType;

typedef enum _RelayM_FaultType     //构建继电器故障类型枚举
{
    RELAYM_ADHESION,               //粘连
    RELAYM_OPEN_LOOP,              //开路
    RELAYM_NO_FAULT,               //无故障
} RelayM_FaultType;

typedef enum _Std_RetureType         //继电器控制状态
{
    RELAYM_SWITCH,
    RELAYM_ON_TIME,
    RELAYM_OFF_TIME,
    RELAYM_RES_VALUE,
} Std_RetureType;

typedef enum _RelayM_CtlAttributeType      //继电器控制属性选择
{
    RELAYM_CONTROL_SWITCH,                 //控制开关
    RELAYM_CONTROL_ON_TIME,                //控制闭合时间
    RELAYM_CONTROL_OFF_TIME,               //控制断开时间
    RELAYM_CONTROL_RES_VALUE,              //控制内阻
} RelayM_CtlAttributeType;

typedef enum _RelayM_AtuAttributeType      //继电器实际属性选择
{
    RELAYM_ACTURE_SWITCH,                 //实际开关
    RELAYM_ACTURE_ON_TIME,                //实际闭合时间
    RELAYM_ACTURE_OFF_TIME,               //实际断开时间
    RELAYM_ACTURE_RES_VALUE,              //实际内阻
} RelayM_AtuAttributeType;

extern void RelayM_Init(void);                                           //继电器模块初始化函数
extern void RelayM_InterruptON(void);                                    //开中断
extern void RelayM_InterruptOFF(void);                                   //关中断
extern void RelayM_SetStatus(uint8 passage, uint16 data);
extern uint16 RelayM_GetControlStatus(uint8 passage);
extern uint16 RelayM_GetActureStatus(uint8 passage);
extern void RelayM_SetOnTime(uint8 passage, uint16 ontime);
extern uint16 RelayM_GetOnTime(uint16 ontime);
extern void RelayM_SetOffTime(uint8 passage ,uint16 offtime);
extern uint16 RelayM_GetOffTime(uint16 offtime);
extern void RelayM_SetRes(uint8 passage ,uint16 res);
extern uint16 RelayM_GetRes(uint16 res);
extern RelayM_FaultType RelayM_GetFault(uint8 passage);
extern void RelayM_Control(uint8 passage, RelayM_CtlAttributeType ctl, uint16 data);
extern uint16 RelayM_Acture(uint8 passage, RelayM_AtuAttributeType act);

#endif