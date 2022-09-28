#ifndef __NODE_LCFG_H
#define __NODE_LCFG_H

#include "Node.h"
#include "hidef.h"
#include "derivative.h"

extern Node_StateJudge_Type Node_Fault_Judge[];
extern Node_StateJudge_Type Node_PreFinish_Judge[];
extern Node_StateJudge_Type Node_DischargeFault_Judge[];
extern Node_HvState_Type Node_Voltage_Judge[];
extern Node_HvState_Type Node_Temp_Judge[];
extern Node_StateCfg_Type Node_StateCfg[3];
extern Node_HvStateCfg_Type Node_HvStateCfg[];
extern Node_OutputInfo_Type Node_OutputInfo;
extern Testtype a;
extern Hvtype b;
#endif