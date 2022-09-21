#include "RelayM_Lcfg.h"

RelayM_ControlType RelayM_Control0 =
{
	0,
	0,
	0,
	0,
	0,
};

RelayM_ControlType RelayM_Control1 =
{
	0,
	0,
	0,
	0,
	0,
};

RelayM_ControlType RelayM_Control2 =
{
	0,
	0,
	0,
	0,
	0,
};

RelayM_ControlType RelayM_Control3 =
{
	0,
	0,
	0,
	0,
	0,
};

RelayM_ControlType RelayM_Control4 =
{
	0,
	0,
	0,
	0,
	0,
};

RelayM_ControlType RelayM_Control5 =
{
	0,
	0,
	0,
	0,
	0,
};

RelayM_StateType RelayM_StateCfg[RELAYM_MAX_NUM] =
{
    {PreCharged_Relay, &RelayM_Control0},
    {TotalPositive_Relay, &RelayM_Control1},
    {TotalNegative_Relay, &RelayM_Control2},
    {FastCharging_Relay, &RelayM_Control3},
    {SlowCharging_Relay, &RelayM_Control4},
    {Heating_Relay, &RelayM_Control5,}
};
