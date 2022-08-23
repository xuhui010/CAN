#include "Node.h"
#include "Node_Lcfg.h"

void Node_Init(void)                  							 //Node初始化函数
{
}

void Node_Act(void)                    							 //Node空函数
{
}

void Node_InterruptON(void)
{
}

void Node_InterruptOFF(void)
{
}

void Node_Poll(void)                    						//Node节点判断函数
{
	static Node_Num_Type NodeInit = (Node_Num_Type)Node_1;    	//节点选择初始化
	static Node_State_Type Node_State;
	uint8 i = 0, branch = 0;         							//定义节点状态分支变量

	Node_InterruptOFF();             							//关中断
	Node_State.NodeNum = NodeInit;   							//获取当前节点号
	Node_State.state = &(Node_StateCfg[NodeInit]);				//获取当前节点状态
	branch = Node_State.state->BranchNum;         				//获取当前节点分支数量
	Node_OutputInfo.Current_Node = NodeInit;      				//输出当前节点号
	Node_OutputInfo.Branch_Num = branch           				//输出当前节点分支数量
	Node_InterruptON();                           				//开中断
	for (i = 0; i < branch; i++)                  				//寻找分支对应的响应函数
	{
		if (i < branch)                           				//数组越界保护
		{
			if (Node_State.state->state[i].Branch()				//判断状态分支与进入状态条件是否相同
				== Node_State.state->state[i].condition)
			{
				Node_State.state->state[i].Response();			//选择状态响应函数
				Node_InterruptOFF();
				NodeInit = Node_State.state->state[i].Next_Node;//获取下一节点号
				Node_OutputInfo.Next_Node = NodeInit; 			//输出下一节点号
				Node_InterruptON();
				break;                                			//退出for循环
			}
		}
	}
}

int Node_StateRead(Node_Information_Type state)                 //节点状态信息读取函数
{
    Node_Poll();
    int re;
    if (state == Current_Node_State)
    {
        rebuf = Node_OutputInfo.Current_Node;
    }
    else if (state == Next_Node_State)
    {
        rebuf = Node_OutputInfo.Next_Node;
    }
    else if (state == Node_Branch_Num)
    {
        rebuf = Node_OutputInfo.Branch_Num;
    }
    else
    {
    }
    return re;
}