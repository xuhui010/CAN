#include "Node_Lcfg.h"
#include "Pre_Lcfg.h"
#include "PrechargeM.h"


const Node_StateJudge_Type Node_Fault_Judge[] =         //判断故障节点
{
    {Node_1 ,Pre_Cfg_Fault, 1, Node_NoAct, Node_1 },
    {Node_1 ,Pre_Cfg_Fault, 0, PrechargeM_StartPre, Node_2 },
};

const Node_StateJudge_Type Node_PreFinish_Judge[] =    //预充完成判断节点
{
    {Node_2 ,Pre_Cfg_Fault, 1, PrechargeM_StopPre, Node_1 },
    {Node_2 ,PrechargeM_IsFail, 1, PrechargeM_StopPre, Node_1 },
    {Node_2 ,PrechargeM_IsFinish, 0, Node_NoAct, Node_2 },
    {Node_2 ,PrechargeM_IsFinish, 1, PrechargeM_Change, Node_3 },
};

const Node_StateJudge_Type Node_DischargeFault_Judge[] =       //放电故障判断节点
{
    {Node_3, Pre_Cfg_Fault, 1, PrechargeM_StopMaster, Node_1 },
    {Node_3, Pre_Cfg_Fault, 0, Node_NoAct, Node_3 },
};

const Node_StateCfgType Node_StateCfg[] =       //节点状态转换表
{
    {2, Node_Fault_Judge* state},
    {4, Node_PreFinish_Judge* state},
    {2, Node_DischargeFault_Judge* state},
};

Node_OutputInfo_Type Node_OutputInfo;