#ifndef __CANMSG_H
#define __CANMSG_H

#include "CAN.h"

typedef enum _CANMsg_NumType
{
    CANMsg_Num_1 = 0,     
    CANMsg_Num_2 = 1,
    CANMsg_Num_3 = 2
} CANMsg_NumType;

void CANMsg_Send(CANMsg_NumType num);     //发送指定报文
void CAN_SendCallBack(void);                   //PIT定时报文发送
void CAN_RecCallBack(void);             //接收报文中断

#endif
