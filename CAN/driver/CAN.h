#ifndef __CAN_H
#define __CAN_H

#include "hidef.h"
#include "derivative.h"

#define CAN_MSG_MAXLEN 8            //�궨������λ���Ϊ8

typedef enum _CAN_BpsType    //������ѡ��
{
    CAN_Bps_125k = 0,
    CAN_Bps_250k ,
    CAN_Bps_500k ,
}CAN_BpsType;

typedef struct _CAN_CfgType
{
    CAN_BpsType bps;
    unsigned char sp;
} CAN_CfgType;

typedef struct _CAN_MsgType             //����CANͨ�ű��Ľṹ
{
    unsigned long id;                   //�ٲ�֡id
    Bool IDE;                           //0Ϊ��׼֡ 1Ϊ��չ֡
    Bool RTR;                            //RTR:0����֡,1Զ��֡
    unsigned char data[CAN_MSG_MAXLEN]; //����λ
    unsigned char len;                  //���ݳ���
    unsigned char prty;                 //�������ȼ�
} CAN_MsgType;

void CAN_Init(CAN_CfgType *CAN_cfg);     //CAN�ĳ�ʼ������
Bool CAN1_SendMsg(CAN_MsgType *msg);    //CAN1�ķ��ͺ���
Bool CAN1_GetMsg(CAN_MsgType *msg);    //CAN1�Ľ��պ���
#endif




