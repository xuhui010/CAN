#include "CANMsg.h"

//标准帧ID范围：000-7FF      扩展帧ID范围：00000000-1FFFFFFF
CAN_MsgType CAN_msg1 =
{
    0x6AEU,                                //标准帧 数据帧
    0,
    0,
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', '1'},
    8,
    0,
};

CAN_MsgType CAN_msg2 =
{
    0x1608F168UL,                           //扩展帧 数据帧
    1,
    0,
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', '2'},
    8,
    0,
};

CAN_MsgType CAN_msg3 =
{
    0x7CFU,                               //标准帧 远程帧
    0,
    1,
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', '3'},
    8,
    0,
};

CAN_MsgType CAN_NodeStateCfg =          //配置节点数据结构体
{
	0x123,
	0,
	0,
	{0x01,0x02,0x03,0xA,0xB,0xC,0xD,0xE},
	8,
	0,
};

void CAN_SendCallBack(void)          //PIT定时中断发送，每隔0.5s发送一次
{
	static long send_time = 0;

	send_time++;
	if (send_time == 1)
	{
		if (!CAN_SendMsg(&CAN_msg1))   //发送报文1
        {
        }
	}
	else if (send_time == 2)
	{
		if (!CAN_SendMsg(&CAN_msg2))  //发送报文2
        {
        }
	}
	else if (send_time >= 3)
	{
		if (!CAN_SendMsg(&CAN_msg3))  //发送报文3
        {
        }
		send_time = 0;
	}
	else
	{
	}
}

void CAN_RecevieCallBack(void)      //接收报文中断回调函数
{
	CAN_MsgType get_msg;
	if (CAN_GetMsg(&get_msg))
	{
		if (!CAN_SendMsg(&get_msg)) //将接收到的报文发送回去
		{
		}
	}
}


void CAN_Send_NodeStateCfg(void)                                            //将节点当前状态通过报文发送出去
{
	//extern Node_OutputInfo_Type Node_OutputInfo;
	CAN_NodeStateCfg.data[0] = (uint8)Node_OutputInfo.Current_Node;			//读取当前节点编号赋值到data[0]字段
	CAN_NodeStateCfg.data[1] = (uint8)Node_OutputInfo.JudgeNum;	    		//读取当前预充状态判断函数赋值到data[1]字段
	CAN_NodeStateCfg.data[2] = (uint8)Node_OutputInfo.re;	    			//读取当前预充状态判断函数的返回值赋值到data[2]字段
	CAN_NodeStateCfg.data[3] = (uint8)Node_OutputInfo.ActNum;				//读取当前预充状态的动作响应函数赋值到data[3]字段
 	CAN_NodeStateCfg.data[4] = (uint8)Node_OutputInfo.Next_Node;			//读取下一节点编号赋值到data[4]字段
 	CAN_NodeStateCfg.data[5] = (uint8)Node_OutputInfo.Branch_Num;			//读取当前节点总分支数赋值到data[5]字段
	if (CAN_SendMsg(&CAN_NodeStateCfg) == TRUE)								//将重构的报文通过CAN发出
	{
	}
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED       //中断函数置于非分页区内代码段

void interrupt VectorNumber_Vcan1rx CAN_receive(void)
{
	CAN_RecevieCallBack();	//收到CAN报文触发中断执行接收回调函数
}

void interrupt VectorNumber_Vpit0 PIT0(void)
{
    PITTF_PTF0 = 1;        //写1清除中断标志位
    //CAN_SendCallBack();    //在PIT中断中执行发送回调函数
    //Pre_Node_Poll();
    Hv_Node_Poll();
    CAN_Send_NodeStateCfg();
}

#pragma CODE_SEG DEFAULT