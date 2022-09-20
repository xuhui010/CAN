#ifndef __NODE_H
#define __NODE_H

#include "hidef.h"
#include "derivative.h"

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;

typedef enum _Node_Num_Type             //列举节点名称
{
    Node_1,
    Node_2,
    Node_3,
} Node_Num_Type;

typedef enum _Node_StateConditions_Type //列举进入状态条件
{
    Precharged_Fault,                   //预充故障
    Precharged_Not_Fault,               //预充无故障
    Precharged_Timeout = 1,             //预充超时
    Precharged_Not_Timeout,             //预充未超时
    Precharged_Finish = 0,              //预充完成
    Precharged_Not_Finish,              //预充未完成
} Node_StateConditions_Type;

typedef struct _Node_StateJudge_Type    //节点状态判断结构体
{
    Node_Num_Type Current_Node;         //当前节点
    int (*Branch)(void);                //状态分支 选择相应函数作为结构体成员
    Node_StateConditions_Type condition;//进入状态条件
    void (*Response)(void);             //状态响应 选择相应函数作为结构体成员
    Node_Num_Type Next_Node;            //下一节点
} Node_StateJudge_Type;

typedef struct _Node_StateCfg_Type      //节点状态信息配置
{
    uint8 BranchNum;                    //定义节点分支数量
    const Node_StateJudge_Type* state;  //节点状态判断结构体指针 只读，无法通过指针state去修改所指内容
} Node_StateCfg_Type;

typedef struct _Node_State_Type         //节点状态信息(枚举和结构体嵌套)
{
    Node_Num_Type NodeNum;              //节点成员选择
    const Node_StateCfg_Type* state;    //节点状态信息配置结构体指针 只读，无法通过指针state去修改所指内容
} Node_State_Type;

typedef struct _Node_OutputInfo_Type    //输出节点信息结构体
{
    Node_Num_Type Current_Node;         //当前节点
    int Next_Node;                      //下一节点
    int Branch_Num;                     //当前节点分支数量
} Node_OutputInfo_Type;


extern void Node_Init(void);                            //Node初始化函数
extern void Node_InterruptON(void);
extern void Node_InterruptOFF(void);
extern void Node_Poll(void);                            //Node节点判断函数
extern void Node_NoAct(void);                           //Node空函数

#endif