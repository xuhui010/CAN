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

void CAN_SendCallBack(void);                //PIT��ʱ���ķ���
void CAN_RecevieCallBack(void);             //���ձ����ж�
void CAN_ReadData_PreCfg(void);				//��ȡ�������ݸ�Pre����
void CAN_Send_NodeStateCfg(void);			//
#endif
