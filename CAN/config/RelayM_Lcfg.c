#include "RelayM_Lcfg.h"

/*RelayM_ControlType RelayM_Control0 =
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
};*/

RelayM_ControlType RelayM_ControlNum[RELAYM_MAX_NUM] =
{
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
};

RelayM_ControlType RelayM_ActureNum[RELAYM_MAX_NUM] =
{
	{1,20,50,100},
	{1,25,55,120},
	{1,30,60,140},
	{1,35,65,160},
	{1,40,70,180},
	{1,45,75,200}
};

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