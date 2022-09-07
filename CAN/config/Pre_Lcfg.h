#ifndef __PRE_LCFG_H
#define __PRE_LCFG_H

#include "hidef.h"
#include "derivative.h"
#include "Hv.h"

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;

typedef struct _Pre_TimeOutType     //构建预充超时结构体
{
	uint32 Critical_Time;           //定义超时临界时间
} Pre_TimeOutType;

typedef enum _Pre_StateType         //构建预充状态枚举
{
	PRE_STATE_FAULT,                //预充故障判断
	PRE_STATE_TIME,                 //预充时间判断
	PRE_STATE_VOLTAGE,              //预充电压配置
} Pre_StateType;

typedef struct _Pre_StateDataType   //构建预充状态数据结构体
{
	uint8 fault;                    //故障
	uint8 time;                     //时间
	uint8 voltage;                  //电压
} Pre_StateDataType;

typedef struct _Pre_BAT_VoltageType  //构建BAT电压百分比结构体
{
    int percent;
} Pre_BAT_VoltageType;

extern Pre_TimeOutType Pre_TimeOut;
extern Pre_StateDataType Pre_StateData;
extern Pre_BAT_VoltageType Pre_BAT_Voltage;
extern void Pre_StateData_Write(Pre_StateType state, uint8 data);	//将报文相关数据存入预充状态数据结构体中
extern int Pre_StateData_Fault(void);	//预充故障函数初始化
extern int Pre_StateData_Time(void);	//预充时间函数初始化
extern uint16 Pre_StateData_Voltage(uint8 channel);	//预充电压函数初始化

#endif