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

void CAN_SendCallBack(void)          //PIT��ʱ�жϷ��ͣ�ÿ��0.5s����һ��
{
	static long now_send_time = 0;
	static long last_send_time = 0;
	long time;

	now_send_time++;
	time = now_send_time - last_send_time;

	if (time == 1)
	{
		if (!CAN1_SendMsg(&CAN_msg1))   //���ͱ���1
        {
        }
	}
	else if (time == 2)
	{
		if (!CAN1_SendMsg(&CAN_msg2))  //���ͱ���2
        {
        }
	}
	else if (time >= 3)
	{
		if (!CAN1_SendMsg(&CAN_msg3))  //���ͱ���3
        {
        }
		last_send_time = now_send_time;
	}
	else
	{
	}
	PITTF_PTF0 = 1;        //д1����жϱ�־λ
}

void CAN_RecevieCallBack(void)      //���ձ����жϻص�����
{
	CAN_MsgType get_msg;
	if (CAN1_GetMsg(&get_msg))
	{
		if (!CAN1_SendMsg(&get_msg)) //�����յ��ı��ķ��ͻ�ȥ
		{
		}
	}
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED       //�жϺ������ڷǷ�ҳ���ڴ����

void interrupt VectorNumber_Vcan1rx CAN_receive(void)
{
	CAN_RecevieCallBack();	//�յ�CAN���Ĵ����ж�ִ�н��ջص�����
}

void interrupt VectorNumber_Vpit0 PIT0(void)
{
    CAN_SendCallBack();    //��PIT�ж���ִ�з��ͻص�����
}
#pragma CODE_SEG DEFAULT