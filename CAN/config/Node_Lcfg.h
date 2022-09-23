#ifndef __NODE_LCFG_H
#define __NODE_LCFG_H

#include "Node.h"
#include "hidef.h"
#include "derivative.h"

extern const Node_StateJudge_Type Node_Fault_Judge[];
extern const Node_StateJudge_Type Node_PreFinish_Judge[];
extern const Node_StateJudge_Type Node_DischargeFault_Judge[];
extern const Node_StateCfg_Type Node_StateCfg[];
extern Node_OutputInfo_Type Node_OutputInfo;
extern Testtype a;

#endif