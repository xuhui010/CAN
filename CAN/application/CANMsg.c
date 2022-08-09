#include "CANMsg.h"
#include "CAN.h"

//��׼֡ID��Χ��000-7FF      ��չ֡ID��Χ��00000000-1FFFFFFF
static CAN_MsgType CAN_msg1 =
{
    0x6AE,                               //��׼֡ ����֡
    0,
    0,
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', '1'},
    8,
    0,
};

static CAN_MsgType CAN_msg2 =
{
    0x1608F168,                           //��չ֡ ����֡
    1,
    0,
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', '2'},
    8,
    0,
};

static CAN_MsgType CAN_msg3 =
{
    0x7CF,                               //��׼֡ Զ��֡
    0,
    1,
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', '3'},
    8,
    0,
};

void CANMsg_Send(CANMsg_NumType num)           //����ָ������
{
    if (num == CANMsg_Num_1)
    {
        if (!CAN1_SendMsg(&CAN_msg1))
        {
        }
    }
    else if (num == CANMsg_Num_2)
    {
        if (!CAN1_SendMsg(&CAN_msg2))
        {
        }
    }
    else if (num == CANMsg_Num_3)
    {
        if (!CAN1_SendMsg(&CAN_msg3))
        {
        }
    }
    else
    {
    }
}


void CAN_SendCallBack(void)          // ���ͻص����� PIT��ʱ�жϷ��ͣ�ÿ��500ms����һ��
{
	static long send_time = 0;
	send_time++;

	if(send_time == 1)
	{
		CANMsg_Send(CANMsg_Num_1);  //���ͱ���1
	}
	else if (send_time == 2)
	{
		CANMsg_Send(CANMsg_Num_2);  //���ͱ���2
	}
	else if (send_time == 3)
	{
		CANMsg_Send(CANMsg_Num_3);  //���ͱ���3
		send_time = 0;
	}
	else
	{
	}
	PITTF_PTF0 = 1;        //д1����жϱ�־λ
}

void CAN_RecCallBack(void)      //���ձ����ж�
{
	CAN_MsgType msg_get;

	if (CAN1_GetMsg(&msg_get))
	{
		if (!CAN1_SendMsg(&msg_get))
		{

		}
	}
}