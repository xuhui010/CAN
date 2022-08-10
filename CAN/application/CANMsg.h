#ifndef __CANMSG_H
#define __CANMSG_H

#include "CAN.h"

typedef enum _CANMsg_NumType          //报文选择
{
    CANMsg_Num_1 = 0,
    CANMsg_Num_2 ,
    CANMsg_Num_3 ,
} CANMsg_NumType;

void CAN_SendCallBack(void);                   //PIT定时报文发送
void CAN_RecCallBack(void);             //接收报文中断

#endif
