#ifndef __PRECHARGEM_H
#define __PRECHARGEM_H

#include "hidef.h"
#include "derivative.h"
#include "Hv.h"
#include "Node.h"
#include "Hv_Lcfg.h"

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;

typedef struct _PrechargeCfgType			//构建预充配置结构体
{
	uint32 percent;							//BAT电压百分比
	uint32 pretime;							//预充实际时间
	uint32 fault;							//预充有无故障
} PrechargeCfg_Type;

extern void delay(uint8 count);				//延时函数
extern void PrechargeM_Init(void);          //初始化函数
extern void PrechargeM_StartPre(void);      //启动预充函数，闭合预充开关
extern void PrechargeM_StopPre(void);       //停止预充函数，断开预充开关
extern void PrechargeM_StartMaster(void);   //闭合总正函数
extern void PrechargeM_StopMaster(void);    //断开总正函数
extern void PrechargeM_Change(void);        //继电器切换函数，闭合总正或断开总正*/
extern int PrechargeM_IsFail(void);       			//超时判断函数
extern int PrechargeM_IsFinish(void);	//预充完成判断函数
extern int PrechargeM_IsFault(void);      			//故障判断函数

#endif