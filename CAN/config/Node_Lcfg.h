#ifndef __NODE_LCFG_H
#define __NODE_LCFG_H

#include "hidef.h"
#include "derivative.h"
#include "Node.h"

extern const Node_StateJudge_Type Node_Fault_Judge[];
extern const Node_StateJudge_Type Node_PreFinish_Judge[];
extern const Node_StateJudge_Type Node_DischargeFault_Judge[];
extern const Node_StateCfgType Node_StateCfg[];
extern Node_OutputInfo_Type Node_OutputInfo;

#endif