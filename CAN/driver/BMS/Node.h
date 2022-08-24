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

typedef enum _Node_Information_Type     //列举节点信息
{
    Current_Node_State,                 //当前节点状态
    Next_Node_State,                    //下一节点状态
    Node_Branch_Num,                    //节点分支数量
} Node_Information_Type;

typedef struct _Node_StateJudge_Type    //节点状态判断结构体
{
    Node_Num_Type Current_Node;         //当前节点
    int (*Branch)(void);                //状态分支 选择相应函数作为结构体成员
    int condition;                      //进入状态条件
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
    Node_Num_Type Current_Node;
    int Next_Node;
    int Branch_Num;
} Node_OutputInfo_Type;


extern void Node_Init(void);                   //Node初始化函数
extern void Node_Act(void);                    //Node空函数
extern void Node_InterruptON(void);
extern void Node_InterruptOFF(void);
extern void Node_Poll(void);                   //Node节点判断函数
extern int Node_StateRead(Node_Information_Type state);//节点状态信息读取函数

#endif