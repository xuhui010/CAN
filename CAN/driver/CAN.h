#ifndef __CAN_H
#define __CAN_H

#include "hidef.h"
#include "derivative.h"

#define CAN_MSG_MAXLEN 8            //宏定义数据位最大为8

typedef enum _CAN_BpsType    //波特率选择
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

typedef struct _CAN_MsgType             //构造CAN通信报文结构
{
    unsigned long id;                   //仲裁帧id
    Bool IDE;                           //0为标准帧 1为扩展帧
    Bool RTR;                            //RTR:0数据帧,1远程帧
    unsigned char data[CAN_MSG_MAXLEN]; //数据位
    unsigned char len;                  //数据长度
    unsigned char prty;                 //设置优先级
} CAN_MsgType;

void CAN_Init(CAN_CfgType *CAN_cfg);     //CAN的初始化函数
Bool CAN1_SendMsg(CAN_MsgType *msg);    //CAN1的发送函数
Bool CAN1_GetMsg(CAN_MsgType *msg);    //CAN1的接收函数
#endif




