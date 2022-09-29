#include "Node.h"
#include "Node_Lcfg.h"

void Node_Init(void)
{
}

void Node_InterruptON(void)
{
}

void Node_InterruptOFF(void)
{
}

void Node_NoAct(void)                    						//Node空函数
{
}

void Pre_Node_Poll(void)                    					//预充节点判断函数
{
	static Node_Num_Type Node_Name = Node_1;    				//节点选择
	uint8 i = 0, branch = 0;         			  			  	//定义节点状态分支变量

	Node_InterruptOFF();             			  			 	//关中断
	branch = Node_StateCfg[Node_Name].BranchNum;        		//获取当前节点分支数量
	Node_OutputInfo.Current_Node = Node_Name;      				//输出当前节点号
	Node_OutputInfo.Branch_Num = branch;          				//输出当前节点分支数量
	for (i = 0; i < branch; i++)                  				//寻找分支对应的响应函数
	{
		if (i < branch)                           			  	//数组越界保护
		{
			if (Node_StateCfg[Node_Name].act[i].Branch()		//判断状态分支与进入状态条件是否相同
				== Node_StateCfg[Node_Name].act[i].condition)
			{
				uint8 x = 0, y = 0;
  				Testtype *test;
  				test = &a;

				for (x = 0; x < 3; x++)
				{
					if (test->PreJudge[x] == Node_StateCfg[Node_Name].act[i].Branch)    	//根据函数名匹配正确的数组下标
					{
						Node_OutputInfo.JudgeNum = x;
						break;
					}
				}
				Node_OutputInfo.re = test->PreJudge[x]();
				Node_StateCfg[Node_Name].act[i].Response();		  							//选择状态响应函数
				for (y = 0; y < 6; y++)
				{
					if (test->PreAct[y] == Node_StateCfg[Node_Name].act[i].Response)	   //根据函数名匹配正确的数组下标
					{
						Node_OutputInfo.ActNum = y;
						break;
					}
				}
				Node_Name = Node_StateCfg[Node_Name].act[i].Next_Node;		//获取下一节点号
				Node_OutputInfo.Next_Node = Node_Name;           			//输出下一节点号
				Node_InterruptON();
				break;
			}
		}
	}
}

void Hv_Node_Poll(void)                    					  	//高压节点判断函数
{
	static Node_Num_Type Node_Name = Node_4;    				//节点选择
	uint8 i = 0, branch = 0;         			  			  	//定义节点状态分支变量
	uint8 passage = 1;											//选择HV高压模块通道

	Node_InterruptOFF();             			  			  	//关中断
	branch = Node_HvStateCfg[Node_Name].BranchNum;        		//获取当前节点分支数量
	Node_OutputInfo.Current_Node = Node_Name;      			 	//输出当前节点号
	Node_OutputInfo.Branch_Num = branch;          			  	//输出当前节点分支数量
	for (i = 0; i < branch; i++)                  			  	//寻找分支对应的响应函数
	{
		if (i < branch)                           			  	//数组越界保护
		{
			if (Node_HvStateCfg[Node_Name].cfg[i].Judge(passage)						//判断状态分支与进入状态条件是否相同
				== Node_HvStateCfg[Node_Name].cfg[i].condition)
			{
				uint8 x = 0, y = 0;
  				Hvtype  *test;
  				test = &b;

				for (x = 0; x < 2; x++)
				{
					if (test->HvJudge[x] == Node_HvStateCfg[Node_Name].cfg[i].Judge)    //根据函数名匹配正确的数组下标
					{
						Node_OutputInfo.JudgeNum = x;
						break;
					}
				}
				Node_OutputInfo.re = test->HvJudge[x](passage);
				Node_HvStateCfg[Node_Name].cfg[i].act(passage);		  					//选择状态响应函数
				for (y = 0; y < 5; y++)
				{
					if (test->HvAct[y] == Node_HvStateCfg[Node_Name].cfg[i].act)	    //根据函数名匹配正确的数组下标
					{
						Node_OutputInfo.ActNum = y;
						break;
					}
				}
				Node_Name = Node_HvStateCfg[Node_Name].cfg[i].Next_Node;		//获取下一节点号
				Node_OutputInfo.Next_Node = Node_Name;           				//输出下一节点号
				Node_InterruptON();
				break;
			}
		}
	}
}

/*int (*PreJudge[3])(void) =
{
	PrechargeM_IsFault,
	PrechargeM_IsFail,
	PrechargeM_IsFinish,
};

void (*PreAct[6])(void) =
{
	Node_NoAct,
	PrechargeM_StartPre,
	PrechargeM_StopPre,
	PrechargeM_StartMaster,
	PrechargeM_StopMaster,
	PrechargeM_Change,
};

void Test()
{
  Testtype *test;
  test = &a;

  if(test->PreJudge[0]())
  {
  };
}*/