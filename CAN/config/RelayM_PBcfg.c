#include "RelayM_Pbcfg.h"

RelayM_StateType RelayM_StateCfg[RELAYM_MAX_NUM] =
{
    {PreCharged_Relay, &RelayM_Control0},
    {TotalPositive_Relay, &RelayM_Control1},
    {TotalNegative_Relay, &RelayM_Control2},
    {FastCharging_Relay, &RelayM_Control3},
    {SlowCharging_Relay, &RelayM_Control4},
    {Heating_Relay, &RelayM_Control5,}
};