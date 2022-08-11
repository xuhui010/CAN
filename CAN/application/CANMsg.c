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

void CAN_SendCallBack(void)          //PIT定时中断发送，每隔0.5s发送一次
{
	static long now_send_time = 0;
	static long last_send_time = 0;
	long time;

	now_send_time++;
	time = now_send_time - last_send_time;

	if (time == 1)
	{
		if (!CAN1_SendMsg(&CAN_msg1))   //发送报文1
        {
        }
	}
	else if (time == 2)
	{
		if (!CAN1_SendMsg(&CAN_msg2))  //发送报文2
        {
        }
	}
	else if (time >= 3)
	{
		if (!CAN1_SendMsg(&CAN_msg3))  //发送报文3
        {
        }
		last_send_time = now_send_time;
	}
	else
	{
	}
	PITTF_PTF0 = 1;        //写1清除中断标志位
}

void CAN_RecevieCallBack(void)      //接收报文中断回调函数
{
	CAN_MsgType get_msg;
	if (CAN1_GetMsg(&get_msg))
	{
		if (!CAN1_SendMsg(&get_msg)) //将接收到的报文发送回去
		{
		}
	}
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED       //中断函数置于非分页区内代码段

void interrupt VectorNumber_Vcan1rx CAN_receive(void)
{
	CAN_RecevieCallBack();	//收到CAN报文触发中断执行接收回调函数
}

void interrupt VectorNumber_Vpit0 PIT0(void)
{
    CAN_SendCallBack();    //在PIT中断中执行发送回调函数
}
#pragma CODE_SEG DEFAULT