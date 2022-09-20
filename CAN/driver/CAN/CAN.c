#include "CAN.h"
#include "CAN_Lcfg.h"
#include "CANReg.h"

void CAN_Init(CAN_CfgType *CAN_cfg)                 //��ʼ��CAN
{
    static CAN_NumType CANNum = (CAN_NumType)CAN1;  //ѡ��CANͨ��(CAN0~CAN4)
    int delay_time = 500;                           //����ϵͳ�ȴ�ʱ��
    int time = 0;
    CAN_cfg = &CAN_Config;                          //ָ��ṹ�������ָ�����Ҫ�ȸ�ֵ

    if (CANCTL0(CANNum).Bits.INITRQ == 0)           //���ƼĴ���0����ѯ�Ƿ�����ʼ��״̬
    {
        CANCTL0(CANNum).Bits.INITRQ = 1;            // �����ʼ��״̬
    }
    while ((CANCTL1(CANNum).Bits.INITAK == 0) && (time < delay_time))     //���ƼĴ���1���ȴ������ʼ��״̬
    {
        time++;
    }
    time = 0;
    CANBTR0(CANNum).MergedBits.grpSJW = 0;         //���߼�ʱ�Ĵ���������ͬ����ת���1Tqʱ������
    if (CAN_cfg->sp == 1)
    {
        CANBTR1(CANNum).Bits.SAMP = 0;             //������ÿλ1������
    }
    else
    {
        CANBTR1(CANNum).Bits.SAMP = 1;             //������ÿλ3������
    }
    switch (CAN_cfg->bps)                          //���ò�����  CANbps=1/TBit ������=(1+TSEG1)/(1+TSEG1+TSEG2)
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

    CANIDMR0(CANNum).Byte = 0xFF;   // ��ʶ�����μĴ�����д1�ر��˲���
    CANIDMR1(CANNum).Byte = 0xFF;
    CANIDMR2(CANNum).Byte = 0xFF;
    CANIDMR3(CANNum).Byte = 0xFF;
    CANIDMR4(CANNum).Byte = 0xFF;
    CANIDMR5(CANNum).Byte = 0xFF;
    CANIDMR6(CANNum).Byte = 0xFF;
    CANIDMR7(CANNum).Byte = 0xFF;
    CANCTL1(CANNum).Byte  = 0xC0;  //CANEλ��CLKSRCλд1��ʹ��MSCANģ�鲢����ʱ��ԴΪ����ʱ��
    CANCTL0(CANNum).Byte  = 0x00;  //д0������һ��ģʽ����
    while (CANCTL1(CANNum).Bits.INITAK && (time < delay_time))     //�ȴ��ص�һ������ģʽ
    {
        time++;
    }
    time = 0;
    while ((CANCTL0(CANNum).Bits.SYNCH == 0) && (time < delay_time)) //SYNCHλд1��ʾMSCANͬ��������ʱ�� �ȴ�����ʱ��ͬ��
    {
        time++;
    }
    CANRIER(CANNum).Bits.RXFIE = 1;         //MSCAN�������ж�ʹ�ܼĴ�����RXFIEλд1�����ջ������������½��շ��ж�����

}

Bool CAN_SendMsg(CAN_MsgType *msg)   //CAN�ķ��ͺ���
{
    static CAN_NumType CANNum = (CAN_NumType)CAN1;  //ѡ��CANͨ��
    unsigned char send_buf = 0, sp = 0;
    Bool re = FALSE;

    if ((msg->len > CAN_MSG_MAXLEN) || (CANCTL0(CANNum).Bits.SYNCH == 0)) //������ݳ��Ⱥ�����ʱ��
    {
        re = FALSE;
    }
    else
    {
        do
        {
            CANTBSEL(CANNum).Byte = CANTFLG(CANNum).Byte;  //Ϊ�����һ�����÷��ͻ�����,�����ȡ��������־�Ĵ�����ֵ����д�뷢�ͻ�����ѡ��Ĵ���
            send_buf = CANTBSEL(CANNum).Bits.TX0;  //ѡ�񻺳�������ͱ��λ����Ϊ1,�ڵ�1λ
        }
        while (!(send_buf));    //0 ��ر��Ļ�������ȡ���� 1 ������λ��ͣ���ر��Ļ�������ѡ��

        if (msg->IDE)          //IDEΪ1ʱ����չ֡
        {
            CANTXIDR0(CANNum).Byte = (unsigned char)(msg->id >> 21);      //д���ʶ�� id28 ~ id21λ
            CANTXIDR1(CANNum).Byte = (unsigned char)(msg->id >> 13) & 0xE0; //&11100000,��д��id18~id20λ
            CANTXIDR1(CANNum).Byte |= 0x18;                              //00011000��д���Զ������λSRR����չ֡��־λIDE
            CANTXIDR1(CANNum).Byte |= (unsigned char)(msg->id >> 15) & 0x07; //&0111,��д��id15 ~id17λ
            CANTXIDR2(CANNum).Byte = (unsigned char)(msg->id >> 7);          //д��id7 ~ id14λ
            CANTXIDR3(CANNum).Byte = (unsigned char)(msg->id << 1);          //д��id0 ~ id6λ
            if (msg->RTR)            //RTRλΪ1ʱ��Զ��֡
            {
                CANTXIDR3(CANNum).Byte |= 0x01;  //RTRλд1
            }
            else                     //RTRλΪ0ʱ������֡
            {
                CANTXIDR3(CANNum).Byte &= 0xFE;  //RTRλд0
            }

        }
        else                         //IDEΪ0ʱ�Ǳ�׼֡
        {
            CANTXIDR0(CANNum).Byte = (unsigned char)(msg->id >> 3);       //д���ʶ��id3 ~ id10λ
            CANTXIDR1(CANNum).Byte = (unsigned char)(msg->id << 5);       //д���ʶ��id0 ~ id2λ
            CANTXIDR1(CANNum).Byte &= 0xF7;
            if (msg->RTR)            //RTRλΪ1ʱ��Զ��֡
            {
                CANTXIDR1(CANNum).Byte |= 0x10;  //RTRλд1
            }
            else                     //RTRλΪ0ʱ������֡
            {
                CANTXIDR1(CANNum).Byte &= 0xEF;  //RTRλд0
            }
        }

        for (sp = 0; sp < msg->len; sp++)
        {
            *((&CANTXDSR0(CANNum).Byte) + sp) = msg->data[sp];            //���ݶμĴ���,д������
        }

        CANTXDLR(CANNum).MergedBits.grpDLC = msg->len;  //���ݳ��ȼĴ���,д�����ݳ���
        CANTXTBPR(CANNum).Byte = msg->prty; //���ͻ��������ȼĴ���,д�����ȼ�
        CANTFLG(CANNum).Byte = send_buf;  //��TXx��־ ������׼������
        re = TRUE;
    }
    return re;
}

Bool CAN_GetMsg(CAN_MsgType *msg)
{
    static CAN_NumType CANNum = (CAN_NumType)CAN1;  //ѡ��CANͨ��
    unsigned char sp = 0;
    Bool re = FALSE;

    if (!CANRFLG(CANNum).Bits.RXF)   //�����ձ�־
    {
        re = FALSE;
    }
    else
    {
        if (CANRXIDR1(CANNum).Bits.IDE)    //�ж��ǲ�����չ֡
        {
            msg->id = ((unsigned long)(CANRXIDR0(CANNum).Byte & 0xff)) << 21;     //����ʶ��
            msg->id = msg->id | (((unsigned long)(CANRXIDR1(CANNum).Byte & 0xe0)) << 13);
            msg->id = msg->id | (((unsigned long)(CANRXIDR1(CANNum).Byte & 0x07)) << 15);
            msg->id = msg->id | (((unsigned long)(CANRXIDR2(CANNum).Byte & 0xff)) << 7);
            msg->id = msg->id | (((unsigned long)(CANRXIDR3(CANNum).Byte & 0xfe)) >> 1);
            msg->IDE = TRUE;               //IDEΪ1����չ֡
            if (CANRXIDR3(CANNum).Byte & 0x01)         //�ж��ǲ�������֡
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
            msg->id = (unsigned long)(CANRXIDR0(CANNum).Byte <<3 ) |
                      (unsigned long)(CANRXIDR1(CANNum).Byte >>5 ) ;      //����ʶ��

            msg->IDE = FALSE;         //IDEΪ0�Ǳ�׼֡
            if (CANRXIDR1(CANNum).Byte & 0x10)    //�ж��ǲ�������֡
            {
                msg->RTR = TRUE;      //RTRλд1 Զ��֡
            }
            else
            {
                msg->RTR = FALSE;    //RTRλд0  ����֡
            }
        }
        msg->prty = CANTXTBPR(CANNum).Byte;           //��ȡ�������ȼ�
        msg->len = CANRXDLR(CANNum).MergedBits.grpDLC;         // ��ȡ���ݳ���
        for (sp = 0; sp < msg->len; sp++)
        {
            msg->data[sp] = *((&CANRXDSR0(CANNum).Byte) + sp);    // ��ȡ����
        }
        CANRFLG(CANNum).Byte = 0x01;         // ��RXF��־λ(������׼������)
        re = TRUE;
    }
    return re;
}


