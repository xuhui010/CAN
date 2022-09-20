#include "CAN.h"
#include "CAN_Lcfg.h"
#include "CANReg.h"

void CAN_Init(CAN_CfgType *CAN_cfg)                 //初始化CAN
{
    static CAN_NumType CANNum = (CAN_NumType)CAN1;  //选择CAN通道(CAN0~CAN4)
    int delay_time = 500;                           //设置系统等待时间
    int time = 0;
    CAN_cfg = &CAN_Config;                          //指向结构体变量的指针变量要先赋值

    if (CANCTL0(CANNum).Bits.INITRQ == 0)           //控制寄存器0，查询是否进入初始化状态
    {
        CANCTL0(CANNum).Bits.INITRQ = 1;            // 进入初始化状态
    }
    while ((CANCTL1(CANNum).Bits.INITAK == 0) && (time < delay_time))     //控制寄存器1，等待进入初始化状态
    {
        time++;
    }
    time = 0;
    CANBTR0(CANNum).MergedBits.grpSJW = 0;         //总线计时寄存器，设置同步跳转宽度1Tq时钟周期
    if (CAN_cfg->sp == 1)
    {
        CANBTR1(CANNum).Bits.SAMP = 0;             //采样，每位1个样本
    }
    else
    {
        CANBTR1(CANNum).Bits.SAMP = 1;             //采样，每位3个样本
    }
    switch (CAN_cfg->bps)                          //设置波特率  CANbps=1/TBit 采样率=(1+TSEG1)/(1+TSEG1+TSEG2)
    {
        case CAN_Bps_125k:
        {
            CANBTR0(CANNum).MergedBits.grpBRP = 0x0E;
            (CANBTR1(CANNum).Byte) |= 0x1D;
        } break;

        case CAN_Bps_250k:
        {
            CANBTR0(CANNum).MergedBits.grpBRP = 0x07;
            CANBTR1(CANNum).Byte |= 0x1C;
        } break;

        case CAN_Bps_500k:
        {
            CANBTR0(CANNum).MergedBits.grpBRP = 0x03;
            CANBTR1(CANNum).Byte |= 0x1C;
        } break;

        default:
        {
        } break;
    }

    CANIDMR0(CANNum).Byte = 0xFF;   // 标识符屏蔽寄存器，写1关闭滤波器
    CANIDMR1(CANNum).Byte = 0xFF;
    CANIDMR2(CANNum).Byte = 0xFF;
    CANIDMR3(CANNum).Byte = 0xFF;
    CANIDMR4(CANNum).Byte = 0xFF;
    CANIDMR5(CANNum).Byte = 0xFF;
    CANIDMR6(CANNum).Byte = 0xFF;
    CANIDMR7(CANNum).Byte = 0xFF;
    CANCTL1(CANNum).Byte  = 0xC0;  //CANE位和CLKSRC位写1，使能MSCAN模块并设置时钟源为总线时钟
    CANCTL0(CANNum).Byte  = 0x00;  //写0，返回一般模式运行
    while (CANCTL1(CANNum).Bits.INITAK && (time < delay_time))     //等待回到一般运行模式
    {
        time++;
    }
    time = 0;
    while ((CANCTL0(CANNum).Bits.SYNCH == 0) && (time < delay_time)) //SYNCH位写1表示MSCAN同步到总线时钟 等待总线时钟同步
    {
        time++;
    }
    CANRIER(CANNum).Bits.RXFIE = 1;         //MSCAN接收器中断使能寄存器，RXFIE位写1，接收缓冲区已满导致接收方中断请求

}

Bool CAN_SendMsg(CAN_MsgType *msg)   //CAN的发送函数
{
    static CAN_NumType CANNum = (CAN_NumType)CAN1;  //选择CAN通道
    unsigned char send_buf = 0, sp = 0;
    Bool re = FALSE;

    if ((msg->len > CAN_MSG_MAXLEN) || (CANCTL0(CANNum).Bits.SYNCH == 0)) //检查数据长度和总线时钟
    {
        re = FALSE;
    }
    else
    {
        do
        {
            CANTBSEL(CANNum).Byte = CANTFLG(CANNum).Byte;  //为获得下一个可用发送缓冲区,必须读取发送器标志寄存器的值，并写入发送缓冲器选择寄存器
            send_buf = CANTBSEL(CANNum).Bits.TX0;  //选择缓冲器，最低编号位设置为1,在第1位
        }
        while (!(send_buf));    //0 相关报文缓冲器被取消， 1 如果编号位最低，相关报文缓冲器被选中

        if (msg->IDE)          //IDE为1时是扩展帧
        {
            CANTXIDR0(CANNum).Byte = (unsigned char)(msg->id >> 21);      //写入标识符 id28 ~ id21位
            CANTXIDR1(CANNum).Byte = (unsigned char)(msg->id >> 13) & 0xE0; //&11100000,先写入id18~id20位
            CANTXIDR1(CANNum).Byte |= 0x18;                              //00011000，写替代远程请求位SRR和扩展帧标志位IDE
            CANTXIDR1(CANNum).Byte |= (unsigned char)(msg->id >> 15) & 0x07; //&0111,再写入id15 ~id17位
            CANTXIDR2(CANNum).Byte = (unsigned char)(msg->id >> 7);          //写入id7 ~ id14位
            CANTXIDR3(CANNum).Byte = (unsigned char)(msg->id << 1);          //写入id0 ~ id6位
            if (msg->RTR)            //RTR位为1时是远程帧
            {
                CANTXIDR3(CANNum).Byte |= 0x01;  //RTR位写1
            }
            else                     //RTR位为0时是数据帧
            {
                CANTXIDR3(CANNum).Byte &= 0xFE;  //RTR位写0
            }

        }
        else                         //IDE为0时是标准帧
        {
            CANTXIDR0(CANNum).Byte = (unsigned char)(msg->id >> 3);       //写入标识符id3 ~ id10位
            CANTXIDR1(CANNum).Byte = (unsigned char)(msg->id << 5);       //写入标识符id0 ~ id2位
            CANTXIDR1(CANNum).Byte &= 0xF7;
            if (msg->RTR)            //RTR位为1时是远程帧
            {
                CANTXIDR1(CANNum).Byte |= 0x10;  //RTR位写1
            }
            else                     //RTR位为0时是数据帧
            {
                CANTXIDR1(CANNum).Byte &= 0xEF;  //RTR位写0
            }
        }

        for (sp = 0; sp < msg->len; sp++)
        {
            *((&CANTXDSR0(CANNum).Byte) + sp) = msg->data[sp];            //数据段寄存器,写入数据
        }

        CANTXDLR(CANNum).MergedBits.grpDLC = msg->len;  //数据长度寄存器,写入数据长度
        CANTXTBPR(CANNum).Byte = msg->prty; //发送缓冲器优先寄存器,写入优先级
        CANTFLG(CANNum).Byte = send_buf;  //清TXx标志 缓冲器准备发送
        re = TRUE;
    }
    return re;
}

Bool CAN_GetMsg(CAN_MsgType *msg)
{
    static CAN_NumType CANNum = (CAN_NumType)CAN1;  //选择CAN通道
    unsigned char sp = 0;
    Bool re = FALSE;

    if (!CANRFLG(CANNum).Bits.RXF)   //检测接收标志
    {
        re = FALSE;
    }
    else
    {
        if (CANRXIDR1(CANNum).Bits.IDE)    //判断是不是扩展帧
        {
            msg->id = ((unsigned long)(CANRXIDR0(CANNum).Byte & 0xff)) << 21;     //读标识符
            msg->id = msg->id | (((unsigned long)(CANRXIDR1(CANNum).Byte & 0xe0)) << 13);
            msg->id = msg->id | (((unsigned long)(CANRXIDR1(CANNum).Byte & 0x07)) << 15);
            msg->id = msg->id | (((unsigned long)(CANRXIDR2(CANNum).Byte & 0xff)) << 7);
            msg->id = msg->id | (((unsigned long)(CANRXIDR3(CANNum).Byte & 0xfe)) >> 1);
            msg->IDE = TRUE;               //IDE为1是扩展帧
            if (CANRXIDR3(CANNum).Byte & 0x01)         //判断是不是数据帧
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
            msg->id = (unsigned long)(CANRXIDR0(CANNum).Byte <<3 ) |
                      (unsigned long)(CANRXIDR1(CANNum).Byte >>5 ) ;      //读标识符

            msg->IDE = FALSE;         //IDE为0是标准帧
            if (CANRXIDR1(CANNum).Byte & 0x10)    //判断是不是数据帧
            {
                msg->RTR = TRUE;      //RTR位写1 远程帧
            }
            else
            {
                msg->RTR = FALSE;    //RTR位写0  数据帧
            }
        }
        msg->prty = CANTXTBPR(CANNum).Byte;           //读取数据优先级
        msg->len = CANRXDLR(CANNum).MergedBits.grpDLC;         // 读取数据长度
        for (sp = 0; sp < msg->len; sp++)
        {
            msg->data[sp] = *((&CANRXDSR0(CANNum).Byte) + sp);    // 读取数据
        }
        CANRFLG(CANNum).Byte = 0x01;         // 清RXF标志位(缓冲器准备接收)
        re = TRUE;
    }
    return re;
}


