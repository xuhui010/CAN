#ifndef __CANMSG_H
#define __CANMSG_H

#include "hidef.h"
#include "derivative.h"
#include "CAN.h"
#include "Pre_Lcfg.h"
#include "Node_Lcfg.h"
#include "Node.h"
#include "RelayM_Lcfg.h"

extern CAN_MsgType CAN_msg1;
extern CAN_MsgType CAN_msg2;
extern CAN_MsgType CAN_msg3;
extern CAN_MsgType CAN_NodeStateCfg;
extern Node_OutputInfo_Type Node_OutputInfo;

void CAN_SendCallBack(void);                //PIT定时报文发送
void CAN_RecevieCallBack(void);             //接收报文中断
void CAN_Send_NodeStateCfg(void);			//发送节点当前状态

#endif
