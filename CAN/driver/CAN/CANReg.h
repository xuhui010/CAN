#ifndef __CANREG_H
#define __CANREG_H

#include "hidef.h"
#include "derivative.h"

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;      //重定义数据类型

#define CAN_BASE_ADR      0x0140UL      //宏定义起始地址
#define CAN_OFFSET_ADR    0x0040UL      //宏定义移位地址

/*宏定义位偏移地址*/
#define CANCTL0_ADR       0x0000UL
#define CANCTL1_ADR       0x0001UL
#define CANBTR0_ADR       0x0002UL
#define CANBTR1_ADR       0x0003UL
#define CANRFLG_ADR       0x0004UL
#define CANRIER_ADR       0x0005UL
#define CANTFLG_ADR       0x0006UL
#define CANTBSEL_ADR      0x000AUL
#define CANIDMR0_ADR      0x0014UL
#define CANIDMR1_ADR      0x0015UL
#define CANIDMR2_ADR      0x0016UL
#define CANIDMR3_ADR      0x0017UL
#define CANIDMR4_ADR      0x001CUL
#define CANIDMR5_ADR      0x001DUL
#define CANIDMR6_ADR      0x001EUL
#define CANIDMR7_ADR      0x001FUL
#define CANRXIDR0_ADR     0x0020UL
#define CANRXIDR1_ADR     0x0021UL
#define CANRXIDR2_ADR     0x0022UL
#define CANRXIDR3_ADR     0x0023UL
#define CANRXDSR0_ADR     0x0024UL
#define CANRXDLR_ADR      0x002CUL
#define CANTXIDR0_ADR     0x0030UL
#define CANTXIDR1_ADR     0x0031UL
#define CANTXIDR2_ADR     0x0032UL
#define CANTXIDR3_ADR     0x0033UL
#define CANTXDSR0_ADR     0x0034UL
#define CANTXDLR_ADR      0x003CUL
#define CANTXTBPR_ADR     0x003DUL

typedef enum _CAN_NumType             //构建CAN通道枚举
{
  CAN0 = 0,
  CAN1 = 1,
  CAN2 = 2,
  CAN3 = 3,
  CAN4 = 5,
} CAN_NumType;

extern CAN_NumType CANNum;


typedef union _CANCTL0_
{
  uint8 Byte;
  struct
  {
    uint8 INITRQ      :1;                                       /* Initialization Mode Request */
    uint8 SLPRQ       :1;                                       /* Sleep Mode Request */
    uint8 WUPE        :1;                                       /* Wake-Up Enable */
    uint8 TIME        :1;                                       /* Timer Enable */
    uint8 SYNCH       :1;                                       /* Synchronized Status */
    uint8 CSWAI       :1;                                       /* CAN Stops in Wait Mode */
    uint8 RXACT       :1;                                       /* Receiver Active Status */
    uint8 RXFRM       :1;                                       /* Received Frame Flag */
  } Bits;
} uCANCTL0, *P_uCANCTL0;

#define CANCTL0(CANNum) (*((volatile P_uCANCTL0)(CANCTL0_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANCTL1_
{
  uint8 Byte;
  struct
  {
    uint8 INITAK      :1;                                       /* Initialization Mode Acknowledge */
    uint8 SLPAK       :1;                                       /* Sleep Mode Acknowledge */
    uint8 WUPM        :1;                                       /* Wake-Up Mode */
    uint8 BORM        :1;                                       /* Bus-Off Recovery Mode */
    uint8 LISTEN      :1;                                       /* Listen Only Mode */
    uint8 LOOPB       :1;                                       /* Loop Back Self Test Mode */
    uint8 CLKSRC      :1;                                       /* MSCAN Clock Source */
    uint8 CANE        :1;                                       /* Received Frame Flag */
  } Bits;
} uCANCTL1, *P_uCANCTL1;

#define CANCTL1(CANNum) (*((volatile P_uCANCTL1)(CANCTL1_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANBTR0_
{
  uint8 Byte;
  struct
  {
    uint8 BRP0        :1;                                       /* Baud Rate Prescaler 0 */
    uint8 BRP1        :1;                                       /* Baud Rate Prescaler 1 */
    uint8 BRP2        :1;                                       /* Baud Rate Prescaler 2 */
    uint8 BRP3        :1;                                       /* Baud Rate Prescaler 3 */
    uint8 BRP4        :1;                                       /* Baud Rate Prescaler 4 */
    uint8 BRP5        :1;                                       /* Baud Rate Prescaler 5 */
    uint8 SJW0        :1;                                       /* Synchronization Jump Width 0 */
    uint8 SJW1        :1;                                       /* Synchronization Jump Width 1 */
  } Bits;
  struct
  {
    uint8 grpBRP  :6;
    uint8 grpSJW  :2;
  } MergedBits;
} uCANBTR0, *P_uCANBTR0;

#define CANBTR0(CANNum) (*((volatile P_uCANBTR0)(CANBTR0_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANBTR1_
{
  uint8 Byte;
  struct
  {
    uint8 TSEG10      :1;                                       /* Time Segment 10 */
    uint8 TSEG11      :1;                                       /* Time Segment 11 */
    uint8 TSEG12      :1;                                       /* Time Segment 12 */
    uint8 TSEG13      :1;                                       /* Time Segment 13 */
    uint8 TSEG20      :1;                                       /* Time Segment 20 */
    uint8 TSEG21      :1;                                       /* Time Segment 21 */
    uint8 TSEG22      :1;                                       /* Time Segment 22 */
    uint8 SAMP        :1;                                       /* Sampling */
  } Bits;
  struct
  {
    uint8 grpTSEG_10 :4;
    uint8 grpTSEG_20 :3;
    uint8         :1;
  } MergedBits;
} uCANBTR1, *P_uCANBTR1;

#define CANBTR1(CANNum) (*((volatile P_uCANBTR1)(CANBTR1_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANRFLG_
{
  uint8 Byte;
  struct
  {
    uint8 RXF         :1;                                       /* Receive Buffer Full */
    uint8 OVRIF       :1;                                       /* Overrun Interrupt Flag */
    uint8 TSTAT0      :1;                                       /* Transmitter Status Bit 0 */
    uint8 TSTAT1      :1;                                       /* Transmitter Status Bit 1 */
    uint8 RSTAT0      :1;                                       /* Receiver Status Bit 0 */
    uint8 RSTAT1      :1;                                       /* Receiver Status Bit 1 */
    uint8 CSCIF       :1;                                       /* CAN Status Change Interrupt Flag */
    uint8 WUPIF       :1;                                       /* Wake-up Interrupt Flag */
  } Bits;
  struct {
    uint8         :1;
    uint8         :1;
    uint8 grpTSTAT :2;
    uint8 grpRSTAT :2;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} uCANRFLG, *P_uCANRFLG;

#define CANRFLG(CANNum) (*((volatile P_uCANRFLG)(CANRFLG_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANRIER_
{
  uint8 Byte;
  struct
  {
    uint8 RXFIE       :1;                                       /* Receiver Full Interrupt Enable */
    uint8 OVRIE       :1;                                       /* Overrun Interrupt Enable */
    uint8 TSTATE0     :1;                                       /* Transmitter Status Change Enable 0 */
    uint8 TSTATE1     :1;                                       /* Transmitter Status Change Enable 1 */
    uint8 RSTATE0     :1;                                       /* Receiver Status Change Enable 0 */
    uint8 RSTATE1     :1;                                      /* Receiver Status Change Enable 1 */
    uint8 CSCIE       :1;                                       /* CAN Status Change Interrupt Enable */
    uint8 WUPIE       :1;                                       /* Wake-up Interrupt Enable */
  } Bits;
  struct
  {
    uint8         :1;
    uint8         :1;
    uint8 grpTSTATE :2;
    uint8 grpRSTATE :2;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} uCANRIER, *P_uCANRIER;

#define CANRIER(CANNum) (*((volatile P_uCANRIER)(CANRIER_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANTFLG_
{
  uint8 Byte;
  struct
  {
    uint8 TXE0        :1;                                       /* Transmitter Buffer Empty 0 */
    uint8 TXE1        :1;                                       /* Transmitter Buffer Empty 1 */
    uint8 TXE2        :1;                                       /* Transmitter Buffer Empty 2 */
    uint8             :1;
    uint8             :1;
    uint8             :1;
    uint8             :1;
    uint8             :1;
  } Bits;
  struct
  {
    uint8 grpTXE  :3;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} uCANTFLG, *P_uCANTFLG;

#define CANTFLG(CANNum) (*((volatile P_uCANTFLG)(CANTFLG_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANTBSEL_
{
  uint8 Byte;
  struct
  {
    uint8 TX0         :1;                                       /* Transmit Buffer Select 0 */
    uint8 TX1         :1;                                       /* Transmit Buffer Select 1 */
    uint8 TX2         :1;                                       /* Transmit Buffer Select 2 */
    uint8             :1;
    uint8             :1;
    uint8             :1;
    uint8             :1;
    uint8             :1;
  } Bits;
  struct
  {
    uint8 grpTX   :3;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} uCANTBSEL, *P_uCANTBSEL;

#define CANTBSEL(CANNum) (*((volatile P_uCANTBSEL)(CANTBSEL_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANIDMR0_
{
  uint8 Byte;
  struct
  {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} uCANIDMR0, *P_uCANIDMR0;

#define CANIDMR0(CANNum) (*((volatile P_uCANIDMR0)(CANIDMR0_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANIDMR1_
{
  uint8 Byte;
  struct
  {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} uCANIDMR1, *P_uCANIDMR1;

#define CANIDMR1(CANNum) (*((volatile P_uCANIDMR1)(CANIDMR1_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANIDMR2_
{
  uint8 Byte;
  struct
  {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} uCANIDMR2, *P_uCANIDMR2;

#define CANIDMR2(CANNum) (*((volatile P_uCANIDMR2)(CANIDMR2_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANIDMR3_
{
  uint8 Byte;
  struct
  {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} uCANIDMR3, *P_uCANIDMR3;

#define CANIDMR3(CANNum) (*((volatile P_uCANIDMR3)(CANIDMR3_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANIDMR4_
{
  uint8 Byte;
  struct
  {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} uCANIDMR4, *P_uCANIDMR4;

#define CANIDMR4(CANNum) (*((volatile P_uCANIDMR4)(CANIDMR4_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANIDMR5_
{
  uint8 Byte;
  struct
  {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} uCANIDMR5, *P_uCANIDMR5;

#define CANIDMR5(CANNum) (*((volatile P_uCANIDMR5)(CANIDMR5_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANIDMR6_
{
  uint8 Byte;
  struct
  {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} uCANIDMR6, *P_uCANIDMR6;

#define CANIDMR6(CANNum) (*((volatile P_uCANIDMR6)(CANIDMR6_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANIDMR7_
{
  uint8 Byte;
  struct
  {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} uCANIDMR7, *P_uCANIDMR7;

#define CANIDMR7(CANNum) (*((volatile P_uCANIDMR7)(CANIDMR7_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANRXIDR0_
{
  uint8 Byte;
  struct
  {
    uint8 ID21        :1;                                       /* Extended format identifier Bit 21 */
    uint8 ID22        :1;                                       /* Extended format identifier Bit 22 */
    uint8 ID23        :1;                                       /* Extended format identifier Bit 23 */
    uint8 ID24        :1;                                       /* Extended format identifier Bit 24 */
    uint8 ID25        :1;                                       /* Extended format identifier Bit 25 */
    uint8 ID26        :1;                                       /* Extended format identifier Bit 26 */
    uint8 ID27        :1;                                       /* Extended format identifier Bit 27 */
    uint8 ID28        :1;                                       /* Extended format identifier Bit 28 */
  } Bits;
} uCANRXIDR0, *P_uCANRXIDR0;

#define CANRXIDR0(CANNum) (*((volatile P_uCANRXIDR0)(CANRXIDR0_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANRXIDR1_
{
  uint8 Byte;
  struct
  {
    uint8 ID15        :1;                                       /* Extended format identifier Bit 15 */
    uint8 ID16        :1;                                       /* Extended format identifier Bit 16 */
    uint8 ID17        :1;                                       /* Extended format identifier Bit 17 */
    uint8 IDE         :1;                                       /* ID Extended */
    uint8 SRR         :1;                                       /* Substitute Remote Request */
    uint8 ID18        :1;                                       /* Extended format identifier Bit 18 */
    uint8 ID19        :1;                                       /* Extended format identifier Bit 19 */
    uint8 ID20        :1;                                       /* Extended format identifier Bit 20 */
  } Bits;
  struct
  {
    uint8 grpID_15 :3;
    uint8          :1;
    uint8          :1;
    uint8 grpID_18 :3;
  } MergedBits;
} uCANRXIDR1, *P_uCANRXIDR1;

#define CANRXIDR1(CANNum) (*((volatile P_uCANRXIDR1)(CANRXIDR1_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANRXIDR2_
{
  uint8 Byte;
  struct
  {
    uint8 ID7         :1;                                       /* Extended format identifier Bit 7 */
    uint8 ID8         :1;                                       /* Extended format identifier Bit 8 */
    uint8 ID9         :1;                                       /* Extended format identifier Bit 9 */
    uint8 ID10        :1;                                       /* Extended format identifier Bit 10 */
    uint8 ID11        :1;                                       /* Extended format identifier Bit 11 */
    uint8 ID12        :1;                                       /* Extended format identifier Bit 12 */
    uint8 ID13        :1;                                       /* Extended format identifier Bit 13 */
    uint8 ID14        :1;                                       /* Extended format identifier Bit 14 */
  } Bits;
} uCANRXIDR2, *P_uCANRXIDR2;

#define CANRXIDR2(CANNum) (*((volatile P_uCANRXIDR2)(CANRXIDR2_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANRXIDR3_
{
  uint8 Byte;
  struct
  {
    uint8 RTR         :1;                                       /* Remote Transmission Request */
    uint8 ID0         :1;                                       /* Extended format identifier Bit 0 */
    uint8 ID1         :1;                                       /* Extended format identifier Bit 1 */
    uint8 ID2         :1;                                       /* Extended format identifier Bit 2 */
    uint8 ID3         :1;                                       /* Extended format identifier Bit 3 */
    uint8 ID4         :1;                                       /* Extended format identifier Bit 4 */
    uint8 ID5         :1;                                       /* Extended format identifier Bit 5 */
    uint8 ID6         :1;                                       /* Extended format identifier Bit 6 */
  } Bits;
  struct
  {
    uint8         :1;
    uint8 grpID   :7;
  } MergedBits;
} uCANRXIDR3, *P_uCANRXIDR3;

#define CANRXIDR3(CANNum) (*((volatile P_uCANRXIDR3)(CANRXIDR3_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANRXDSR0_
{
  uint8 Byte;
  struct
  {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} uCANRXDSR0, *P_uCANRXDSR0;

#define CANRXDSR0(CANNum) (*((volatile P_uCANRXDSR0)(CANRXDSR0_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANRXDLR_
{
  uint8 Byte;
  struct
  {
    uint8 DLC0        :1;                                       /* Data Length Code Bit 0 */
    uint8 DLC1        :1;                                       /* Data Length Code Bit 1 */
    uint8 DLC2        :1;                                       /* Data Length Code Bit 2 */
    uint8 DLC3        :1;                                       /* Data Length Code Bit 3 */
    uint8             :1;
    uint8             :1;
    uint8             :1;
    uint8             :1;
  } Bits;
  struct
  {
    uint8 grpDLC  :4;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} uCANRXDLR, *P_uCANRXDLR;

#define CANRXDLR(CANNum) (*((volatile P_uCANRXDLR)(CANRXDLR_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANTXIDR0_
{
  uint8 Byte;
  struct
  {
    uint8 ID21        :1;                                       /* Extended format identifier Bit 21 */
    uint8 ID22        :1;                                       /* Extended format identifier Bit 22 */
    uint8 ID23        :1;                                       /* Extended format identifier Bit 23 */
    uint8 ID24        :1;                                       /* Extended format identifier Bit 24 */
    uint8 ID25        :1;                                       /* Extended format identifier Bit 25 */
    uint8 ID26        :1;                                       /* Extended format identifier Bit 26 */
    uint8 ID27        :1;                                       /* Extended format identifier Bit 27 */
    uint8 ID28        :1;                                       /* Extended format identifier Bit 28 */
  } Bits;
} uCANTXIDR0, *P_uCANTXIDR0;

#define CANTXIDR0(CANNum) (*((volatile P_uCANTXIDR0)(CANTXIDR0_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANTXIDR1_
{
  uint8 Byte;
  struct
  {
    uint8 ID15        :1;                                       /* Extended format identifier Bit 15 */
    uint8 ID16        :1;                                       /* Extended format identifier Bit 16 */
    uint8 ID17        :1;                                       /* Extended format identifier Bit 17 */
    uint8 IDE         :1;                                       /* ID Extended */
    uint8 SRR         :1;                                       /* Substitute Remote Request */
    uint8 ID18        :1;                                       /* Extended format identifier Bit 18 */
    uint8 ID19        :1;                                       /* Extended format identifier Bit 19 */
    uint8 ID20        :1;                                       /* Extended format identifier Bit 20 */
  } Bits;
  struct
  {
    uint8 grpID_15 :3;
    uint8         :1;
    uint8         :1;
    uint8 grpID_18 :3;
  } MergedBits;
} uCANTXIDR1, *P_uCANTXIDR1;

#define CANTXIDR1(CANNum) (*((volatile P_uCANTXIDR1)(CANTXIDR1_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANTXIDR2_
{
  uint8 Byte;
  struct
  {
    uint8 ID7         :1;                                       /* Extended format identifier Bit 7 */
    uint8 ID8         :1;                                       /* Extended format identifier Bit 8 */
    uint8 ID9         :1;                                       /* Extended format identifier Bit 9 */
    uint8 ID10        :1;                                       /* Extended format identifier Bit 10 */
    uint8 ID11        :1;                                       /* Extended format identifier Bit 11 */
    uint8 ID12        :1;                                       /* Extended format identifier Bit 12 */
    uint8 ID13        :1;                                       /* Extended format identifier Bit 13 */
    uint8 ID14        :1;                                       /* Extended format identifier Bit 14 */
  } Bits;
} uCANTXIDR2, *P_uCANTXIDR2;

#define CANTXIDR2(CANNum) (*((volatile P_uCANTXIDR2)(CANTXIDR2_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANTXIDR3_
{
  uint8 Byte;
  struct
  {
    uint8 RTR         :1;                                       /* Remote Transmission Request */
    uint8 ID0         :1;                                       /* Extended format identifier Bit 0 */
    uint8 ID1         :1;                                       /* Extended format identifier Bit 1 */
    uint8 ID2         :1;                                       /* Extended format identifier Bit 2 */
    uint8 ID3         :1;                                       /* Extended format identifier Bit 3 */
    uint8 ID4         :1;                                       /* Extended format identifier Bit 4 */
    uint8 ID5         :1;                                       /* Extended format identifier Bit 5 */
    uint8 ID6         :1;                                       /* Extended format identifier Bit 6 */
  } Bits;
  struct
  {
    uint8         :1;
    uint8 grpID   :7;
  } MergedBits;
} uCANTXIDR3, *P_uCANTXIDR3;

#define CANTXIDR3(CANNum) (*((volatile P_uCANTXIDR3)(CANTXIDR3_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANTXDSR0_
{
  uint8 Byte;
  struct
  {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} uCANTXDSR0, *P_uCANTXDSR0;

#define CANTXDSR0(CANNum) (*((volatile P_uCANTXDSR0)(CANTXDSR0_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANTXDLR_
{
  uint8 Byte;
  struct
  {
    uint8 DLC0        :1;                                       /* Data Length Code Bit 0 */
    uint8 DLC1        :1;                                       /* Data Length Code Bit 1 */
    uint8 DLC2        :1;                                       /* Data Length Code Bit 2 */
    uint8 DLC3        :1;                                       /* Data Length Code Bit 3 */
    uint8             :1;
    uint8             :1;
    uint8             :1;
    uint8             :1;
  } Bits;
  struct
  {
    uint8 grpDLC  :4;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} uCANTXDLR, *P_uCANTXDLR;

#define CANTXDLR(CANNum) (*((volatile P_uCANTXDLR)(CANTXDLR_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

typedef union _CANTXTBPR_
{
  uint8 Byte;
  struct
  {
    uint8 PRIO0       :1;                                       /* Transmit Buffer Priority Bit 0 */
    uint8 PRIO1       :1;                                       /* Transmit Buffer Priority Bit 1 */
    uint8 PRIO2       :1;                                       /* Transmit Buffer Priority Bit 2 */
    uint8 PRIO3       :1;                                       /* Transmit Buffer Priority Bit 3 */
    uint8 PRIO4       :1;                                       /* Transmit Buffer Priority Bit 4 */
    uint8 PRIO5       :1;                                       /* Transmit Buffer Priority Bit 5 */
    uint8 PRIO6       :1;                                       /* Transmit Buffer Priority Bit 6 */
    uint8 PRIO7       :1;                                       /* Transmit Buffer Priority Bit 7 */
  } Bits;
} uCANTXTBPR, *P_uCANTXTBPR;

#define CANTXTBPR(CANNum) (*((volatile P_uCANTXTBPR)(CANTXTBPR_ADR + CAN_BASE_ADR + CANNum * CAN_OFFSET_ADR)))

#endif