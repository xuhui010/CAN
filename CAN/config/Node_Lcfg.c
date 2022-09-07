#include "Node_Lcfg.h"
#include "Pre_Lcfg.h"
#include "PrechargeM.h"



/*通过结构体二维数组，关联起每个节点和下一个将要执行的节点的关系*/
const Node_StateJudge_Type Node_Fault_Judge[] =                                     //判断故障节点
{
    {Node_1 ,Pre_StateData_Fault, Precharged_Fault, Node_NoAct, Node_1 },                 //当前节点Node1 判断是否故障 是 NULL 下一节点Node1
    {Node_1 ,Pre_StateData_Fault, Precharged_Not_Fault, PrechargeM_StartPre, Node_2 }     //当前节点Node1 判断是否故障 否 开始预充 下一节点Node2
};

const Node_StateJudge_Type Node_PreFinish_Judge[] =                                 //预充完成判断节点
{
    {Node_2 ,Pre_StateData_Fault, Precharged_Fault, PrechargeM_StopPre, Node_1 },         //当前节点Node2 判断是否故障 是 断开预充 下一节点Node1
    {Node_2 ,PrechargeM_IsFail, Precharged_Timeout, PrechargeM_StopPre, Node_1 },         //当前节点Node2 判断是否超时 是 预充停止 下一节点Node1
    {Node_2 ,PrechargeM_IsFinish, Precharged_Finish, PrechargeM_Change, Node_3 },          //当前节点Node2 是否预充完成 是 闭合总正并断开预充 下一节点Node3
    {Node_2 ,PrechargeM_IsFinish, Precharged_Not_Finish, Node_NoAct, Node_2 },            //当前节点Node2 是否预充完成 否 NULL 下一节点Node2

};

const Node_StateJudge_Type Node_DischargeFault_Judge[] =                            //放电故障判断节点
{
    {Node_3, Pre_StateData_Fault, Precharged_Fault, PrechargeM_StopMaster, Node_1 },       //当前节点Node3 判断是否故障 是 下电 下一节点Node1
    {Node_3, Pre_StateData_Fault, Precharged_Not_Fault, Node_NoAct, Node_3 }              //当前节点Node3 判断是否故障 否 NULL 下一节点Node3
};

const Node_StateCfg_Type Node_StateCfg[] =                                          //节点状态转换表
{
    {2, Node_Fault_Judge},
    {4, Node_PreFinish_Judge},
    {2, Node_DischargeFault_Judge}
};

Node_OutputInfo_Type Node_OutputInfo;