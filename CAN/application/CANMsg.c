#include "CANMsg.h"
#include "CAN.h"

//标准帧ID范围：000-7FF      扩展帧ID范围：00000000-1FFFFFFF
static CAN_MsgType CAN_msg1 =
{
    0x6AE,                                //标准帧 数据帧
    0,
    0,
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', '1'},
    8,
    0,
};

static CAN_MsgType CAN_msg2 =
{
    0x1608F168,                           //扩展帧 数据帧
    1,
    0,
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', '2'},
    8,
    0,
};

static CAN_MsgType CAN_msg3 =
{
    0x7CF,                               //标准帧 远程帧
    0,
    1,
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', '3'},
    8,
    0,
};

void CAN_SendCallBack(void)          // 发送回调函数 PIT定时中断发送，每隔0.5s发送一次
{
	static long send_time = 0;
	send_time++;

	if (send_time == 1)
	{
		if (!CAN1_SendMsg(&CAN_msg1))   //发送报文1
        {
        }
	}
	else if (send_time == 2)
	{
		if (!CAN1_SendMsg(&CAN_msg2))  //发送报文2
        {
        }
	}
	else if (send_time >= 3)
	{
		if (!CAN1_SendMsg(&CAN_msg3))  //发送报文3
        {
        }
		send_time = 0;
	}
	else
	{
	}
	PITTF_PTF0 = 1;        //写1清除中断标志位
}

void CAN_RecCallBack(void)      //接收报文中断
{
	CAN_MsgType get_msg;
	if (CAN1_GetMsg(&get_msg))
	{
		if (!CAN1_SendMsg(&get_msg))
		{
		}
	}
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED       //中断函数置于非分页区内代码段

void interrupt VectorNumber_Vcan1rx CAN_receive(void)
{
	CAN_RecCallBack();	//收到CAN报文触发中断
}

#pragma CODE_SEG DEFAULT