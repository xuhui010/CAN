#ifndef __CANMSG_H
#define __CANMSG_H

#include "CAN.h"

void CAN_SendCallBack(void);                //PIT定时报文发送
void CAN_RecevieCallBack(void);             //接收报文中断
#endif
