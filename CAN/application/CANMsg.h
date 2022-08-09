#ifndef __CANMSG_H
#define __CANMSG_H

#include "CAN.h"

typedef enum _CANMsg_NumType
{
    CANMsg_Num_1 = 0,     
    CANMsg_Num_2 = 1,
    CANMsg_Num_3 = 2
} CANMsg_NumType;

void CANMsg_Send(CANMsg_NumType num);     //����ָ������
void CAN_SendCallBack(void);                   //PIT��ʱ���ķ���
void CAN_RecCallBack(void);             //���ձ����ж�

#endif
