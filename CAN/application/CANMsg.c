#include "CANMsg.h"
#include "CAN.h"
#include "Pre_Lcfg.h"
#include "Node_Lcfg.h"
#include "Node.h"
#include "RelayM_Lcfg.h"

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
	{0x01,0x02,0x03,0xFF,0xFF,0xFF,0xFF,0xFF},
	8,
	0,
};

CAN_MsgType CAN_PrechargeMCfg =          //配置预充数据结构体
{
	0x68FU,
	0,
	0,
	{0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
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

void CAN_ReadData_PreCfg(void)		//读取报文数据给Pre配置
{
	if (CAN_GetMsg(&CAN_PrechargeMCfg) == TRUE)
	{
		Pre_StateData_Write(PRE_STATE_FAULT, CAN_PrechargeMCfg.data[0]);	//data[0]字段赋值给Fault
		Pre_StateData_Write(PRE_STATE_TIME, CAN_PrechargeMCfg.data[1]);		//data[0]字段赋值给TIME
		Pre_StateData_Write(PRE_STATE_VOLTAGE, CAN_PrechargeMCfg.data[2]);	//data[0]字段赋值给VOLTAGE
		if (CAN_SendMsg(&CAN_PrechargeMCfg) == TRUE)						//将接收的数据发送回去
		{
		}
	}

}

void CAN_Send_NodeStateCfg(void)                                               			//将节点当前状态通过报文发送出去
{
	CAN_NodeStateCfg.data[0] = (unsigned char)NodeInfRead(Current_Node_State);		//读取当前节点状态赋值到data[0]字段
	CAN_NodeStateCfg.data[1] = (unsigned char)NodeInfRead(Next_Node_State);	    	//读取下一节点状态赋值到data[1]字段
	CAN_NodeStateCfg.data[2] = (unsigned char)NodeInfRead(Node_Branch_Num);	    	//读取当前节点分支数赋值到data[2]字段
	if (CAN_SendMsg(&CAN_NodeStateCfg) == TRUE)										//将重构的报文通过CAN发出
	{
	}
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED       //中断函数置于非分页区内代码段

void interrupt VectorNumber_Vcan1rx CAN_receive(void)
{
	CAN_RecevieCallBack();	//收到CAN报文触发中断执行接收回调函数
	CAN_ReadData_PreCfg();
}

void interrupt VectorNumber_Vpit0 PIT0(void)
{
    PITTF_PTF0 = 1;        //写1清除中断标志位
    //CAN_SendCallBack();    //在PIT中断中执行发送回调函数
    Node_Poll();
    CAN_Send_NodeStateCfg();
}
#pragma CODE_SEG DEFAULT