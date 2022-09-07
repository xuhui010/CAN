#ifndef __CANMSG_H
#define __CANMSG_H

#include "hidef.h"
#include "derivative.h"
#include "CAN.h"

extern CAN_MsgType CAN_msg1;
extern CAN_MsgType CAN_msg2;
extern CAN_MsgType CAN_msg3;
extern CAN_MsgType CAN_PrechargeMCfg;
extern CAN_MsgType CAN_NodeStateCfg;

void CAN_SendCallBack(void);                //PIT定时报文发送
void CAN_RecevieCallBack(void);             //接收报文中断
void CAN_ReadData_PreCfg(void);				//读取报文数据给Pre配置
void CAN_Send_NodeStateCfg(void);			//
#endif
