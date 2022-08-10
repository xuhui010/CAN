#include "CAN.h"
#include "CAN_Lcfg.h"

void CAN_Init(CAN_CfgType *CAN_cfg)       //初始化CAN
{
    int delay_time = 100;            //设置系统等待时间
    int time_1 = 0, time_2 = 0, time_3 = 0;

    if (CAN1CTL0_INITRQ == 0)       // 控制寄存器0，查询是否进入初始化状态
    {
        CAN1CTL0_INITRQ = 1;        // 进入初始化状态
    }
    while ((CAN1CTL1_INITAK == 0) && (time_1 < delay_time))     //控制寄存器1，等待进入初始化状态
    {
        time_1++;
    }
    CAN1BTR0_SJW = 0;         //总线计时寄存器，设置同步跳转宽度1Tq时钟周期
    if (CAN_cfg->sp == 1)
    {
        CAN1BTR1_SAMP = 0;     //采样，每位1个样本
    }
    else
    {
        CAN1BTR1_SAMP = 1;    //采样，每位3个样本
    }
    switch (CAN_cfg->bps)     //设置波特率  CANbps=1/TBit 采样率=(1+TSEG1)/(1+TSEG1+TSEG2)
    {
        case CAN_Bps_125k:
        {
            CAN1BTR0_BRP = 0x0E;
            CAN1BTR1 |= 0x1D;
        } break;

        case CAN_Bps_250k:
        {
            CAN1BTR0_BRP = 0x07;
            CAN1BTR1 |= 0x1C;
        } break;

        case CAN_Bps_500k:
        {
            CAN1BTR0_BRP = 0x03;
            CAN1BTR1 |= 0x1C;
        } break;

        default:
        {
        } break;
    }

    CAN1IDMR0 = 0xFF;   // 标识符屏蔽寄存器，写1关闭滤波器
    CAN1IDMR1 = 0xFF;
    CAN1IDMR2 = 0xFF;
    CAN1IDMR3 = 0xFF;
    CAN1IDMR4 = 0xFF;
    CAN1IDMR5 = 0xFF;
    CAN1IDMR6 = 0xFF;
    CAN1IDMR7 = 0xFF;
    CAN1CTL1  = 0xC0;  //CANE位和CLKSRC位写1，使能MSCAN模块并设置时钟源为总线时钟
    CAN1CTL0  = 0x00;  //写0，返回一般模式运行
    while (CAN1CTL1_INITAK && (time_2 < delay_time))     //等待回到一般运行模式
    {
        time_2++;
    }
    while ((CAN1CTL0_SYNCH == 0) && (time_3 < delay_time)) //SYNCH位写1表示MSCAN同步到总线时钟 等待总线时钟同步
    {
        time_3++;
    }
    CAN1RIER_RXFIE = 1;         //MSCAN接收器中断使能寄存器，RXFIE位写1，接收缓冲区已满导致接收方中断请求

}

Bool CAN1_SendMsg(CAN_MsgType *msg)   //CAN1的发送函数
{
    unsigned char send_buf = 0, sp = 0;
    Bool re = FALSE;

    if ((msg->len > CAN_MSG_MAXLEN) || (CAN1CTL0_SYNCH == 0)) //检查数据长度和总线时钟
    {
        re = FALSE;
    }
    else
    {
        do
        {
            CAN1TBSEL = CAN1TFLG;  //为获得下一个可用发送缓冲区,必须读取发送器标志寄存器的值，并写入发送缓冲器选择寄存器
            send_buf = CAN1TBSEL;  //选择缓冲器，最低编号位设置为1,在第1位
        }
        while (!(send_buf));    //0 相关报文缓冲器被取消， 1 如果编号位最低，相关报文缓冲器被选中

        if (msg->IDE)          //IDE为1时是扩展帧
        {
            CAN1TXIDR0 = (unsigned char)(msg->id >> 21);      //写入标识符 id28 ~ id21位
            CAN1TXIDR1 = (unsigned char)(msg->id >> 13) & 0xE0; //&11100000,先写入id18~id20位
            CAN1TXIDR1 |= 0x18;                              //00011000，写替代远程请求位SRR和扩展帧标志位IDE
            CAN1TXIDR1 |= (unsigned char)(msg->id >> 15) & 0x07; //&0111,再写入id15 ~id17位
            CAN1TXIDR2 = (unsigned char)(msg->id >> 7);          //写入id7 ~ id14位
            CAN1TXIDR3 = (unsigned char)(msg->id << 1);          //写入id0 ~ id6位
            if (msg->RTR)            //RTR位为1时是远程帧
            {
                CAN1TXIDR3 |= 0x01;  //RTR位写1
            }
            else                     //RTR位为0时是数据帧
            {
                CAN1TXIDR3 &= 0xFE;  //RTR位写0
            }

        }
        else                         //IDE为0时是标准帧
        {
            CAN1TXIDR0 = (unsigned char)(msg->id >> 3);       //写入标识符id3 ~ id10位
            CAN1TXIDR1 = (unsigned char)(msg->id << 5);       //写入标识符id0 ~ id2位
            CAN1TXIDR1 &= 0xF7;
            if (msg->RTR)            //RTR位为1时是远程帧
            {
                CAN1TXIDR1 |= 0x10;  //RTR位写1
            }
            else                     //RTR位为0时是数据帧
            {
                CAN1TXIDR1 &= 0xEF;  //RTR位写0
            }
        }

        for (sp = 0; sp < msg->len; sp++)
        {
            *((&CAN1TXDSR0) + sp) = msg->data[sp];            //数据段寄存器,写入数据
        }

        CAN1TXDLR_DLC = msg->len;  //数据长度寄存器,写入数据长度
        CAN1TXTBPR = msg->prty; //发送缓冲器优先寄存器,写入优先级
        CAN1TFLG = send_buf;  //清TXx标志 缓冲器准备发送
        re = TRUE;
    }
    return re;
}

Bool CAN1_GetMsg(CAN_MsgType *msg)
{
    unsigned char sp = 0;
    Bool re = FALSE;

    if (!CAN1RFLG_RXF)   //检测接收标志
    {
        re = FALSE;
    }
    else
    {
        if (CAN1RXIDR1_IDE)    //判断是不是扩展帧
        {
            msg->id = ((unsigned long)(CAN1RXIDR0 & 0xff)) << 21;     //读标识符
            msg->id = msg->id | (((unsigned long)(CAN1RXIDR1 & 0xe0)) << 13);
            msg->id = msg->id | (((unsigned long)(CAN1RXIDR1 & 0x07)) << 15);
            msg->id = msg->id | (((unsigned long)(CAN1RXIDR2 & 0xff)) << 7);
            msg->id = msg->id | (((unsigned long)(CAN1RXIDR3 & 0xfe)) >> 1);
            msg->IDE = TRUE;               //IDE为1是扩展帧
            if (CAN1RXIDR3 & 0x01)         //判断是不是数据帧
            {
                msg->RTR = TRUE;           //RTR位写1 远程帧
            }
            else
            {
                msg->RTR = FALSE;          //RTR位写0 数据帧
            }

        }
        else
        {
            msg->id = (unsigned long)(CAN1RXIDR0 <<3 ) |
                      (unsigned long)(CAN1RXIDR1 >>5 ) ;      //读标识符

            msg->IDE = FALSE;         //IDE为0是标准帧
            if (CAN1RXIDR1 & 0x10)    //判断是不是数据帧
            {
                msg->RTR = TRUE;      //RTR位写1 远程帧
            }
            else
            {
                msg->RTR = FALSE;    //RTR位写0  数据帧
            }
        }
        msg->prty = CAN1TXTBPR;           //读取数据优先级
        msg->len = CAN1RXDLR_DLC;         // 读取数据长度
        for (sp = 0; sp < msg->len; sp++)
        {
            msg->data[sp] = *((&CAN1RXDSR0) + sp);    // 读取数据
        }
        CAN1RFLG = 0x01;         // 清RXF标志位(缓冲器准备接收)
        re = TRUE;
    }
    return re;
}


