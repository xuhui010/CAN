#include "CANMsg.h"
#include "CAN.h"
#include "Pre_Lcfg.h"
#include "Node_Lcfg.h"
#include "Node.h"
#include "RelayM_Lcfg.h"

//��׼֡ID��Χ��000-7FF      ��չ֡ID��Χ��00000000-1FFFFFFF
CAN_MsgType CAN_msg1 =
{
    0x6AEU,                                //��׼֡ ����֡
    0,
    0,
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', '1'},
    8,
    0,
};

CAN_MsgType CAN_msg2 =
{
    0x1608F168UL,                           //��չ֡ ����֡
    1,
    0,
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', '2'},
    8,
    0,
};

CAN_MsgType CAN_msg3 =
{
    0x7CFU,                               //��׼֡ Զ��֡
    0,
    1,
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', '3'},
    8,
    0,
};

CAN_MsgType CAN_NodeStateCfg =          //���ýڵ����ݽṹ��
{
	0x123,
	0,
	0,
	{0x01,0x02,0x03,0xFF,0xFF,0xFF,0xFF,0xFF},
	8,
	0,
};

CAN_MsgType CAN_PrechargeMCfg =          //����Ԥ�����ݽṹ��
{
	0x68FU,
	0,
	0,
	{0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	8,
	0,
};

void CAN_SendCallBack(void)          //PIT��ʱ�жϷ��ͣ�ÿ��0.5s����һ��
{
	static long send_time = 0;

	send_time++;
	if (send_time == 1)
	{
		if (!CAN_SendMsg(&CAN_msg1))   //���ͱ���1
        {
        }
	}
	else if (send_time == 2)
	{
		if (!CAN_SendMsg(&CAN_msg2))  //���ͱ���2
        {
        }
	}
	else if (send_time >= 3)
	{
		if (!CAN_SendMsg(&CAN_msg3))  //���ͱ���3
        {
        }
		send_time = 0;
	}
	else
	{
	}
}

void CAN_RecevieCallBack(void)      //���ձ����жϻص�����
{
	CAN_MsgType get_msg;
	if (CAN_GetMsg(&get_msg))
	{
		if (!CAN_SendMsg(&get_msg)) //�����յ��ı��ķ��ͻ�ȥ
		{
		}
	}
}

void CAN_ReadData_PreCfg(void)		//��ȡ�������ݸ�Pre����
{
	if (CAN_GetMsg(&CAN_PrechargeMCfg) == TRUE)
	{
		Pre_StateData_Write(PRE_STATE_FAULT, CAN_PrechargeMCfg.data[0]);	//data[0]�ֶθ�ֵ��Fault
		Pre_StateData_Write(PRE_STATE_TIME, CAN_PrechargeMCfg.data[1]);		//data[0]�ֶθ�ֵ��TIME
		Pre_StateData_Write(PRE_STATE_VOLTAGE, CAN_PrechargeMCfg.data[2]);	//data[0]�ֶθ�ֵ��VOLTAGE
		if (CAN_SendMsg(&CAN_PrechargeMCfg) == TRUE)						//�����յ����ݷ��ͻ�ȥ
		{
		}
	}

}

void CAN_Send_NodeStateCfg(void)                                               			//���ڵ㵱ǰ״̬ͨ�����ķ��ͳ�ȥ
{
	CAN_NodeStateCfg.data[0] = (unsigned char)NodeInfRead(Current_Node_State);		//��ȡ��ǰ�ڵ�״̬��ֵ��data[0]�ֶ�
	CAN_NodeStateCfg.data[1] = (unsigned char)NodeInfRead(Next_Node_State);	    	//��ȡ��һ�ڵ�״̬��ֵ��data[1]�ֶ�
	CAN_NodeStateCfg.data[2] = (unsigned char)NodeInfRead(Node_Branch_Num);	    	//��ȡ��ǰ�ڵ��֧����ֵ��data[2]�ֶ�
	if (CAN_SendMsg(&CAN_NodeStateCfg) == TRUE)										//���ع��ı���ͨ��CAN����
	{
	}
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED       //�жϺ������ڷǷ�ҳ���ڴ����

void interrupt VectorNumber_Vcan1rx CAN_receive(void)
{
	CAN_RecevieCallBack();	//�յ�CAN���Ĵ����ж�ִ�н��ջص�����
	CAN_ReadData_PreCfg();
}

void interrupt VectorNumber_Vpit0 PIT0(void)
{
    PITTF_PTF0 = 1;        //д1����жϱ�־λ
    //CAN_SendCallBack();    //��PIT�ж���ִ�з��ͻص�����
    Node_Poll();
    CAN_Send_NodeStateCfg();
}
#pragma CODE_SEG DEFAULT