#ifndef __NODE_H
#define __NODE_H

#include "hidef.h"
#include "derivative.h"
#include "PrechargeM.h"
#include "Hv.h"

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;

typedef enum _Node_Num_Type             //列举节点名称
{
    Node_1,
    Node_2,
    Node_3,
    Node_4 = 0,
    Node_5,
} Node_Num_Type;

typedef enum _Node_StateConditions_Type //列举进入状态条件
{
    Precharged_Fault,                   //预充故障
    Precharged_Not_Fault,               //预充无故障
    Precharged_Not_Timeout = 0,         //预充未超时
    Precharged_Timeout,                 //预充超时
    Precharged_Finish = 0,              //预充完成
    Precharged_Not_Finish,              //预充未完成
    Hv_Voltage_High = 0,                //电压过高
    Hv_Voltage_Low,                     //电压过低
    Hv_Voltage_Normal,                  //电压正常
    Hv_Temp_High = 0,                   //温度过高
    Hv_Temp_Low,                        //温度过低
    Hv_Temp_Normal,                     //温度正常
} Node_StateConditions_Type;

typedef struct _Node_StateJudge_Type    //预充节点状态机结构体
{
    Node_Num_Type Current_Node;         //当前节点
    int (*Branch)(void);                //状态判断函数指针
    Node_StateConditions_Type condition;//进入状态条件
    void (*Response)(void);             //状态响应函数指针
    Node_Num_Type Next_Node;            //下一节点
} Node_StateJudge_Type;

typedef struct _Node_StateCfg_Type      //预充节点信息关联结构体
{
    Node_Num_Type NodeNum;              //节点名称
    Node_StateJudge_Type* act;          //节点状态机选择
    uint8 BranchNum;                    //节点分支数
} Node_StateCfg_Type;

typedef struct _Testtype                //预充函数指针数组存放
{
    void (*PreAct[6])(void);
    int (*PreJudge[3])(void);
} Testtype;

typedef struct _Node_HvState_Type       //高压节点状态机
{
    Node_Num_Type Current_Node;         //当前节点
    uint8 (*Judge)(uint8 passage);      //函数指针 选择相应判断函数
    Node_StateConditions_Type condition;//进入状态条件
    void (*act)(uint8 passage);         //函数指针 选择相应动作函数
    Node_Num_Type Next_Node;            //下一节点
} Node_HvState_Type;

typedef struct _Node_HvStateCfg_Type    //高压节点信息关联结构体
{
    Node_Num_Type NodeNum;              //节点名称
    Node_HvState_Type* cfg;             //节点状态机选择
    uint8 BranchNum;                    //节点分支数
} Node_HvStateCfg_Type;

typedef struct _Hvtype                  //高压函数指针数组存放
{
    void (*HvAct[5])(uint8 passage);
    uint8 (*HvJudge[2])(uint8 passage);
} Hvtype;

typedef struct _Node_OutputInfo_Type    //高压节点流程信息结构体
{
    Node_Num_Type Current_Node;         //当前节点
    int Next_Node;                      //下一节点
    uint8 Branch_Num;                   //当前节点分支数量
    int re;                             //存放当前分支函数的返回值
    uint8 JudgeNum;                     //分支判断函数编号
    uint8 ActNum;                       //动作响应函数编号
} Node_OutputInfo_Type;

extern void Node_Init(void);                            //Node初始化函数
extern void Node_InterruptON(void);
extern void Node_InterruptOFF(void);
extern void Pre_Node_Poll(void);                        //Node节点判断函数
extern void Node_NoAct(void);                           //Node空函数
extern void Hv_Node_Poll(void);

#endif