#include "RelayM_Pbcfg.h"
#include "RelayM_cfg.h"
#include "RelayM_Lcfg.h"

RelayM_StateType RelayM_StateCfg[RELAYM_MAX_NUM] =
{
    {PreCharged_Relay, &RelayM_ControlNum[0]},
    {TotalPositive_Relay, &RelayM_ControlNum[1]},
    {TotalNegative_Relay, &RelayM_ControlNum[2]},
    {FastCharging_Relay, &RelayM_ControlNum[3]},
    {SlowCharging_Relay, &RelayM_ControlNum[4]},
    {Heating_Relay, &RelayM_ControlNum[5]}
};

RelayM_ActureType RelayM_ActureCfg[RELAYM_MAX_NUM] =
{
    {PreCharged_Relay, &RelayM_ActureNum[0]},
    {TotalPositive_Relay, &RelayM_ActureNum[1]},
    {TotalNegative_Relay, &RelayM_ActureNum[2]},
    {FastCharging_Relay, &RelayM_ActureNum[3]},
    {SlowCharging_Relay, &RelayM_ActureNum[4]},
    {Heating_Relay, &RelayM_ActureNum[5]}
};