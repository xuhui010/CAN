#include "CAN.h"
#include "CAN_Lcfg.h"

void CAN_Init(CAN_CfgType *CAN_cfg)       //��ʼ��CAN
{
    int delay_time = 100;            //����ϵͳ�ȴ�ʱ��
    int time_1 = 0, time_2 = 0, time_3 = 0;

    if (CAN1CTL0_INITRQ == 0)       // ���ƼĴ���0����ѯ�Ƿ�����ʼ��״̬
    {
        CAN1CTL0_INITRQ = 1;        // �����ʼ��״̬
    }
    while ((CAN1CTL1_INITAK == 0) && (time_1 < delay_time))     //���ƼĴ���1���ȴ������ʼ��״̬
    {
        time_1++;
    }
    CAN1BTR0_SJW = 0;         //���߼�ʱ�Ĵ���������ͬ����ת���1Tqʱ������
    if (CAN_cfg->sp == 1)
    {
        CAN1BTR1_SAMP = 0;     //������ÿλ1������
    }
    else
    {
        CAN1BTR1_SAMP = 1;    //������ÿλ3������
    }
    switch (CAN_cfg->bps)     //���ò�����  CANbps=1/TBit ������=(1+TSEG1)/(1+TSEG1+TSEG2)
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

    CAN1IDMR0 = 0xFF;   // ��ʶ�����μĴ�����д1�ر��˲���
    CAN1IDMR1 = 0xFF;
    CAN1IDMR2 = 0xFF;
    CAN1IDMR3 = 0xFF;
    CAN1IDMR4 = 0xFF;
    CAN1IDMR5 = 0xFF;
    CAN1IDMR6 = 0xFF;
    CAN1IDMR7 = 0xFF;
    CAN1CTL1  = 0xC0;  //CANEλ��CLKSRCλд1��ʹ��MSCANģ�鲢����ʱ��ԴΪ����ʱ��
    CAN1CTL0  = 0x00;  //д0������һ��ģʽ����
    while (CAN1CTL1_INITAK && (time_2 < delay_time))     //�ȴ��ص�һ������ģʽ
    {
        time_2++;
    }
    while ((CAN1CTL0_SYNCH == 0) && (time_3 < delay_time)) //SYNCHλд1��ʾMSCANͬ��������ʱ�� �ȴ�����ʱ��ͬ��
    {
        time_3++;
    }
    CAN1RIER_RXFIE = 1;         //MSCAN�������ж�ʹ�ܼĴ�����RXFIEλд1�����ջ������������½��շ��ж�����

}

Bool CAN1_SendMsg(CAN_MsgType *msg)   //CAN1�ķ��ͺ���
{
    unsigned char send_buf = 0, sp = 0;
    Bool re = FALSE;

    if ((msg->len > CAN_MSG_MAXLEN) || (CAN1CTL0_SYNCH == 0)) //������ݳ��Ⱥ�����ʱ��
    {
        re = FALSE;
    }
    else
    {
        do
        {
            CAN1TBSEL = CAN1TFLG;  //Ϊ�����һ�����÷��ͻ�����,�����ȡ��������־�Ĵ�����ֵ����д�뷢�ͻ�����ѡ��Ĵ���
            send_buf = CAN1TBSEL;  //ѡ�񻺳�������ͱ��λ����Ϊ1,�ڵ�1λ
        }
        while (!(send_buf));    //0 ��ر��Ļ�������ȡ���� 1 ������λ��ͣ���ر��Ļ�������ѡ��

        if (msg->IDE)          //IDEΪ1ʱ����չ֡
        {
            CAN1TXIDR0 = (unsigned char)(msg->id >> 21);      //д���ʶ�� id28 ~ id21λ
            CAN1TXIDR1 = (unsigned char)(msg->id >> 13) & 0xE0; //&11100000,��д��id18~id20λ
            CAN1TXIDR1 |= 0x18;                              //00011000��д���Զ������λSRR����չ֡��־λIDE
            CAN1TXIDR1 |= (unsigned char)(msg->id >> 15) & 0x07; //&0111,��д��id15 ~id17λ
            CAN1TXIDR2 = (unsigned char)(msg->id >> 7);          //д��id7 ~ id14λ
            CAN1TXIDR3 = (unsigned char)(msg->id << 1);          //д��id0 ~ id6λ
            if (msg->RTR)            //RTRλΪ1ʱ��Զ��֡
            {
                CAN1TXIDR3 |= 0x01;  //RTRλд1
            }
            else                     //RTRλΪ0ʱ������֡
            {
                CAN1TXIDR3 &= 0xFE;  //RTRλд0
            }

        }
        else                         //IDEΪ0ʱ�Ǳ�׼֡
        {
            CAN1TXIDR0 = (unsigned char)(msg->id >> 3);       //д���ʶ��id3 ~ id10λ
            CAN1TXIDR1 = (unsigned char)(msg->id << 5);       //д���ʶ��id0 ~ id2λ
            CAN1TXIDR1 &= 0xF7;
            if (msg->RTR)            //RTRλΪ1ʱ��Զ��֡
            {
                CAN1TXIDR1 |= 0x10;  //RTRλд1
            }
            else                     //RTRλΪ0ʱ������֡
            {
                CAN1TXIDR1 &= 0xEF;  //RTRλд0
            }
        }

        for (sp = 0; sp < msg->len; sp++)
        {
            *((&CAN1TXDSR0) + sp) = msg->data[sp];            //���ݶμĴ���,д������
        }

        CAN1TXDLR_DLC = msg->len;  //���ݳ��ȼĴ���,д�����ݳ���
        CAN1TXTBPR = msg->prty; //���ͻ��������ȼĴ���,д�����ȼ�
        CAN1TFLG = send_buf;  //��TXx��־ ������׼������
        re = TRUE;
    }
    return re;
}

Bool CAN1_GetMsg(CAN_MsgType *msg)
{
    unsigned char sp = 0;
    Bool re = FALSE;

    if (!CAN1RFLG_RXF)   //�����ձ�־
    {
        re = FALSE;
    }
    else
    {
        if (CAN1RXIDR1_IDE)    //�ж��ǲ�����չ֡
        {
            msg->id = ((unsigned long)(CAN1RXIDR0 & 0xff)) << 21;     //����ʶ��
            msg->id = msg->id | (((unsigned long)(CAN1RXIDR1 & 0xe0)) << 13);
            msg->id = msg->id | (((unsigned long)(CAN1RXIDR1 & 0x07)) << 15);
            msg->id = msg->id | (((unsigned long)(CAN1RXIDR2 & 0xff)) << 7);
            msg->id = msg->id | (((unsigned long)(CAN1RXIDR3 & 0xfe)) >> 1);
            msg->IDE = TRUE;               //IDEΪ1����չ֡
            if (CAN1RXIDR3 & 0x01)         //�ж��ǲ�������֡
            {
                msg->RTR = TRUE;           //RTRλд1 Զ��֡
            }
            else
            {
                msg->RTR = FALSE;          //RTRλд0 ����֡
            }

        }
        else
        {
            msg->id = (unsigned long)(CAN1RXIDR0 <<3 ) |
                      (unsigned long)(CAN1RXIDR1 >>5 ) ;      //����ʶ��

            msg->IDE = FALSE;         //IDEΪ0�Ǳ�׼֡
            if (CAN1RXIDR1 & 0x10)    //�ж��ǲ�������֡
            {
                msg->RTR = TRUE;      //RTRλд1 Զ��֡
            }
            else
            {
                msg->RTR = FALSE;    //RTRλд0  ����֡
            }
        }
        msg->prty = CAN1TXTBPR;           //��ȡ�������ȼ�
        msg->len = CAN1RXDLR_DLC;         // ��ȡ���ݳ���
        for (sp = 0; sp < msg->len; sp++)
        {
            msg->data[sp] = *((&CAN1RXDSR0) + sp);    // ��ȡ����
        }
        CAN1RFLG = 0x01;         // ��RXF��־λ(������׼������)
        re = TRUE;
    }
    return re;
}


