#include "CANMsg.h"
#include "CAN.h"

//��׼֡ID��Χ��000-7FF      ��չ֡ID��Χ��00000000-1FFFFFFF
static CAN_MsgType CAN_msg1 =
{
    0x6AE,                                //��׼֡ ����֡
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

void CAN_SendCallBack(void)          // ���ͻص����� PIT��ʱ�жϷ��ͣ�ÿ��0.5s����һ��
{
	static long send_time = 0;
	send_time++;

	if (send_time == 1)
	{
		if (!CAN1_SendMsg(&CAN_msg1))   //���ͱ���1
        {
        }
	}
	else if (send_time == 2)
	{
		if (!CAN1_SendMsg(&CAN_msg2))  //���ͱ���2
        {
        }
	}
	else if (send_time >= 3)
	{
		if (!CAN1_SendMsg(&CAN_msg3))  //���ͱ���3
        {
        }
		send_time = 0;
	}
	else
	{
	}
	PITTF_PTF0 = 1;        //д1����жϱ�־λ
}

void CAN_RecCallBack(void)      //���ձ����ж�
{
	CAN_MsgType get_msg;
	if (CAN1_GetMsg(&get_msg))
	{
		if (!CAN1_SendMsg(&get_msg))
		{
		}
	}
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED       //�жϺ������ڷǷ�ҳ���ڴ����

void interrupt VectorNumber_Vcan1rx CAN_receive(void)
{
	CAN_RecCallBack();	//�յ�CAN���Ĵ����ж�
}

#pragma CODE_SEG DEFAULT