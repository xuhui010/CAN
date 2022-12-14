#include "Node_Lcfg.h"
#include "Pre_Lcfg.h"
#include "PrechargeM.h"
#include "Node.h"


/*通过结构体二维数组，关联起每个节点和下一个将要执行的节点的关系*/
Node_StateJudge_Type Node_Fault_Judge[] =                                     //判断故障节点
{
    {Node_1 ,PrechargeM_IsFault, Precharged_Fault, Node_NoAct, Node_1 },                 //当前节点Node1 判断是否故障 是 NULL 下一节点Node1
    {Node_1 ,PrechargeM_IsFault, Precharged_Not_Fault, PrechargeM_StartPre, Node_2 }     //当前节点Node1 判断是否故障 否 开始预充 下一节点Node2
};

Node_StateJudge_Type Node_PreFinish_Judge[] =                                 //预充完成判断节点
{
    {Node_2 ,PrechargeM_IsFault, Precharged_Fault, PrechargeM_StopPre, Node_1 },         //当前节点Node2 判断是否故障 是 断开预充 下一节点Node1
    {Node_2 ,PrechargeM_IsFail, Precharged_Timeout, PrechargeM_StopPre, Node_1 },         //当前节点Node2 判断是否超时 是 预充停止 下一节点Node1
    {Node_2 ,PrechargeM_IsFinish, Precharged_Finish, PrechargeM_Change, Node_3 },          //当前节点Node2 是否预充完成 是 闭合总正并断开预充 下一节点Node3
    {Node_2 ,PrechargeM_IsFinish, Precharged_Not_Finish, Node_NoAct, Node_2 },            //当前节点Node2 是否预充完成 否 NULL 下一节点Node2

};

Node_StateJudge_Type Node_DischargeFault_Judge[] =                            //放电故障判断节点
{
    {Node_3, PrechargeM_IsFault, Precharged_Fault, PrechargeM_StopMaster, Node_1 },       //当前节点Node3 判断是否故障 是 下电 下一节点Node1
    {Node_3, PrechargeM_IsFault, Precharged_Not_Fault, Node_NoAct, Node_3 }              //当前节点Node3 判断是否故障 否 NULL 下一节点Node3
};

Node_HvState_Type Node_Voltage_Judge[] =
{
    {Node_4, Hv_VoltageJudge, Hv_Voltage_High, Hv_Discharge, Node_5},
    {Node_4, Hv_VoltageJudge, Hv_Voltage_Low, Hv_Charge, Node_5},
    {Node_4, Hv_VoltageJudge, Hv_Voltage_Normal, Hv_NoAct, Node_5}
};

Node_HvState_Type Node_Temp_Judge[] =
{
    {Node_5, Hv_TempJudge, Hv_Temp_High, Hv_Cooling, Node_4},
    {Node_5, Hv_TempJudge, Hv_Temp_Low, Hv_Heating, Node_4},
    {Node_5, Hv_TempJudge, Hv_Temp_Normal, Hv_NoAct, Node_4}
};

Node_StateCfg_Type Node_StateCfg[] =
{
    {Node_1, Node_Fault_Judge, 2},
    {Node_2, Node_PreFinish_Judge, 4},
    {Node_3, Node_DischargeFault_Judge, 2}
};

Node_HvStateCfg_Type Node_HvStateCfg[] =
{
    {Node_4, Node_Voltage_Judge, 3},
    {Node_5, Node_Temp_Judge, 3}
};

Node_OutputInfo_Type Node_OutputInfo;

Testtype a =
{
    {
        Node_NoAct,
        PrechargeM_StartPre,
        PrechargeM_StopPre,
        PrechargeM_StartMaster,
        PrechargeM_StopMaster,
        PrechargeM_Change
    },
    {
        PrechargeM_IsFault,
        PrechargeM_IsFail,
        PrechargeM_IsFinish
    },
};

Hvtype b =
{
    {
        Hv_Discharge,
        Hv_Charge,
        Hv_Cooling,
        Hv_Heating,
        Hv_NoAct
    },
    {
        Hv_VoltageJudge,
        Hv_TempJudge
    },
};