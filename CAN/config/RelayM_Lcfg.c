#include "RelayM.h"
#include "RelayM_cfg.h"
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