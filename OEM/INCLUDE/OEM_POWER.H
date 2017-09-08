/*-----------------------------------------------------------------------------
 * @file     | OEM_POWER.H
 * ----------+-----------------------------------------------------------------
 * @function | OEM_POWER.C Function prototype include definition
 * ----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_POWER_H
#define OEM_POWER_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
#define _EC_BOOT            0x00
#define _SYSTEM_S0          0x01
#define _SYSTEM_S1          0x02
#define _SYSTEM_S3          0x03
#define _SYSTEM_S4          0x04
#define _SYSTEM_S5          0x05
#define _SYSTEM_G3          0x06

#define _PST_G3_to_S5       0x80
#define _PST_S5_to_S0       0x81
#define _PST_S0_to_S3       0x82
#define _PST_S3_to_S0       0x83
#define _PST_S0_to_S5       0x84
#define _PST_S5_to_G3       0x85


//-----------------------------------------------------------------------------
// System status define
//-----------------------------------------------------------------------------
#define SystemIsS0          SysPowState==_SYSTEM_S0
#define SystemIsS3          SysPowState==_SYSTEM_S3
#define SystemIsS4          SysPowState==_SYSTEM_S4
#define SystemIsS5          SysPowState==_SYSTEM_S5

#define SystemNotS0         SysPowState!=_SYSTEM_S0
#define SystemNotS3         SysPowState!=_SYSTEM_S3
#define SystemNotS4         SysPowState!=_SYSTEM_S4
#define SystemNotS5         SysPowState!=_SYSTEM_S5
/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/
typedef struct PowerSEQ
{
    FUNCT_PTR_B_V func;
    WORD    delay;
    BYTE    checkstatus;
} sPowerSEQ;
//-----------------------------------------------------------------------------
typedef struct InitSleepWakeReg
{
    XBYTE   *reg;
    BYTE    entrysleep;
    BYTE    exitsleep;
} sInitSleepWakeReg;
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void CheckResetSource(void);
extern void SystemWarmBoot(void);
extern void Oem_SysPowSequence(void);
extern void Set_SysPowState(BYTE SetValue);
extern void Oem_TriggerPowerOn(void);
extern void Oem_TriggerPowerOff(BYTE ShutdownCauseCode);
extern void Oem_PowSwToPWRBTN(void);
extern void Oem_SysPowState_S0_S1(void);
extern void Oem_SysPowState_S3(void);
extern void Oem_SysPowState_S4_S5(void);
extern void Oem_SysPowState_G3(void);
extern void PF_AC_PRESENT_HI(void);
extern void PF_AC_PRESENT_LO(void);
extern void PF_VIBRATOR_ON(void);
extern void PF_VIBRATOR_OFF(void);

extern BYTE CheckPowerSaving(void);
extern void InitEnterPowerDown(void);
extern void InitWakeFromPowerDown(void);
extern void EnterPowerSaving(void);

/*-----------------------------------------------------------------------------
 * Sleep/Wake up event setting
 *---------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
#define _SET_EN_WUEMR2  (BIT(6))
#define _SET_EN_WUENR2  (BIT(6) | BIT(0))
#define _SET_WK_WUENR2  0x00

#define _SET_EN_WUEMR7  0x00
#define _SET_EN_WUENR7  0x00
#define _SET_WK_WUENR7  0x00

/*-----------------------------------------------------------------------------
 * Sleep/Wake up Interrupt Controller setting
 *---------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
/* INT0 ~ INT7 */
#define eINT_1      BIT(1)  /* WKO[20]-WU20-WUI0-GPD0-[WUENR2.BIT(0)] */
#define eINT_2      BIT(2)  /* KBC Output Buffer Empty Interrupt */
#define eINT_3      BIT(3)  /* PMC Output Buffer Empty Interrupt */
#define eINT_4      BIT(4)  /* TMKBC Interrupt */
#define eINT_5      BIT(5)  /* WKINTAD (WKINTA or WKINTD) WU10-WU17 */
#define eINT_6      BIT(6)  /* WKO[23]-WU23-WUI3-GPC6-[WUENR2.BIT(3)] */
#define eINT_7      BIT(7)  /* PWM Interrupt */
#define _SET_EN_IER0  (eINT_1)
#define _SET_WK_IER0  0x00
//-----------------------------------------------------------------------------
/* INT8 ~ INT15 */
#define eINT_8      BIT(0)  /* ADC Interrupt */
#define eINT_9      BIT(1)  /* SMBUS0 Interrupt */
#define eINT_10     BIT(2)  /* SMBUS1 Interrupt */
#define eINT_11     BIT(3)  /* KB Matrix Scan Interrupt*/
#define eINT_12     BIT(4)  /* WKO[26]-WU26-SWUC-[WUENR2.BIT(6)] */
#define eINT_13     BIT(5)  /* WKINTC - KSI[0]-KSI[7] */
#define eINT_14     BIT(6)  /* WKO[25]-WU25-PWRSW-GPE4-[WUENR2.BIT(5)] */
#define eINT_15     BIT(7)  /* CIR Interrupt */
#define _SET_EN_IER1  (eINT_14)
#define _SET_WK_IER1  0x00
//-----------------------------------------------------------------------------
/* INT16 ~ INT24 */
#define eINT_16     BIT(0)  /* SMBUS2 Interrupt */
#define eINT_17     BIT(1)  /* WKO[24]-WU24-WUI4-GPD2-[WUENR2.BIT(4)] */
#define eINT_18     BIT(2)  /* PS/2 Interrupt 2 */
#define eINT_19     BIT(3)  /* PS/2 Interrupt 1 */
#define eINT_20     BIT(4)  /* PS/2 Interrupt 0 */
#define eINT_21     BIT(5)  /* WKO[22]-WU22-WUI2-GPC4-[WUENR2.BIT(2)] */
#define eINT_22     BIT(6)  /* SMFI Semaphore Interrupt */
#define eINT_23     BIT(7)  /* SMFI Lock Error Interrupt */
#define _SET_EN_IER2  0x00
#define _SET_WK_IER2  0x00
//-----------------------------------------------------------------------------
/* INT24 ~ INT31 */
#define eINT_24     BIT(0)  /* KBC Input Buffer Full Interrupt */
#define eINT_25     BIT(1)  /* PMC Input Buffer Full Interrupt */
#define eINT_26     BIT(2)
#define eINT_27     BIT(3)
#define eINT_28     BIT(4)  /* GINT from function 1 of GPD5 */
#define eINT_29     BIT(5)  /* EGPC Interrupt */
#define eINT_30     BIT(6)  /* External Timer Interrupt */
#define eINT_31     BIT(7)  /* WKO[21]-WU21-WUI0-GPD1-[WUENR2.BIT(1)] */
#define _SET_EN_IER3  0x00
#define _SET_WK_IER3  0x00
//-----------------------------------------------------------------------------
/* INT32 ~ INT39 */
#define eINT_32     BIT(0)  /* GPINT0 */
#define eINT_33     BIT(1)  /* GPINT1 */
#define eINT_34     BIT(2)  /* GPINT2 */
#define eINT_35     BIT(3)  /* GPINT3 */
#define eINT_36     BIT(4)  /* CIR GPINT */
#define eINT_37     BIT(5)  /* SSPI Interrupt */
#define eINT_38     BIT(6)  /* UART1 Interrupt */
#define eINT_39     BIT(7)  /* UART2 Interrupt */
#define _SET_EN_IER4  0x00
#define _SET_WK_IER4  0x00

//-----------------------------------------------------------------------------
/* INT40 ~ INT47 */
#define _SET_EN_IER5  0x00
#define _SET_WK_IER5  0x00

//-----------------------------------------------------------------------------
/* INT48 ~ INT55 */
#define eINT_48     BIT(0)  /* WKO[60]-WU60-WUI16-GPH0-[WUENR6.BIT(0)] */
#define eINT_49     BIT(1)  /* WKO[61]-WU61-WUI17-GPH1-[WUENR6.BIT(1)] */
#define eINT_50     BIT(2)  /* WKO[62]-WU62-WUI18-GPH2-[WUENR6.BIT(2)] */
#define eINT_51     BIT(3)  /* WKO[63]-WU63-WUI19-GPH3-[WUENR6.BIT(3)] */
#define eINT_52     BIT(4)  /* WKO[64]-WU64-WUI20-GPF4-[WUENR6.BIT(4)] */
#define eINT_53     BIT(5)  /* WKO[65]-WU65-WUI21-GPF5-[WUENR6.BIT(5)] */
#define eINT_54     BIT(6)  /* WKO[66]-WU66-WUI22-GPF6-[WUENR6.BIT(6)] */
#define eINT_55     BIT(7)  /* WKO[67]-WU67-WUI23-GPF7-[WUENR6.BIT(7)] */
#define _SET_EN_IER6  eINT_49
#define _SET_WK_IER6  0x00

//-----------------------------------------------------------------------------
/* INT56 ~ INT63 */
#define eINT_56     BIT(0)  /* RTC Alarm 1 */
#define eINT_57     BIT(1)  /* RTC Alarm 2 */
#define eINT_58     BIT(2)  /* External Timer 2 Interrupt */
#define eINT_59     BIT(3)  /* Deferred SPI Instruction Interrupt */
#define eINT_60     BIT(4)  /* TMRINTA0 */
#define eINT_61     BIT(5)  /* TMRINTA1 */
#define eINT_62     BIT(6)  /* TMRINTB0 */
#define eINT_63     BIT(7)  /* TMRINTB1 */
#define _SET_EN_IER7  eINT_58
#define _SET_WK_IER7  0x00

//-----------------------------------------------------------------------------
/* INT64 ~ INT71 */
#define eINT_64     BIT(0)  /* PMC2EX Output Buffer Empty Intr. */
#define eINT_65     BIT(1)  /* PMC2EX Input Buffer Full Intr. */
#define eINT_66     BIT(2)  /* PMC3 Output Buffer Empty Intr. */
#define eINT_67     BIT(3)  /* PMC3 Input Buffer Full Intr. */
#define eINT_68     BIT(4)  /* PMC4 Output Buffer Empty Intr. */
#define eINT_69     BIT(5)  /* PMC4 Input Buffer Full Intr. */
#define eINT_70     BIT(6)
#define eINT_71     BIT(7)  /* I2BRAM Interrupt */
#define _SET_EN_IER8  0x00
#define _SET_WK_IER8  0x00

//-----------------------------------------------------------------------------
/* INT72 ~ INT79 */
#define eINT_72     BIT(0)  /* WKO[70]-WU70-WUI24-GPE0-[WUENR7.BIT(0)] */
#define eINT_73     BIT(1)  /* WKO[71]-WU71-WUI25-GPE1-[WUENR7.BIT(1)] */
#define eINT_74     BIT(2)  /* WKO[72]-WU72-WUI26-GPE2-[WUENR7.BIT(2)] */
#define eINT_75     BIT(3)  /* WKO[73]-WU73-WUI27-GPE3-[WUENR7.BIT(3)] */
#define eINT_76     BIT(4)  /* WKO[74]-WU74-WUI28-GPI4-[WUENR7.BIT(4)] */
#define eINT_77     BIT(5)  /* WKO[75]-WU75-WUI29-GPI5-[WUENR7.BIT(5)] */
#define eINT_78     BIT(6)  /* WKO[76]-WU76-WUI30-GPI6-[WUENR7.BIT(6)] */
#define eINT_79     BIT(7)  /* WKO[77]-WU77-WUI31-GPI7-[WUENR7.BIT(7)] */
#define _SET_EN_IER9  0x00
#define _SET_WK_IER9  0x00

//-----------------------------------------------------------------------------
/* INT80 ~ INT87 */
#define eINT_80     BIT(0)
#define eINT_81     BIT(1)  /* SMBus Clock Held Intr. */
#define eINT_82     BIT(2)  /* CEC Interrupt */
#define eINT_83     BIT(3)  /* H2RAM LPC Trigger */
#define eINT_84     BIT(4)
#define eINT_85     BIT(5)  /* WKO[88]-WU88-WUI29-GPI5-[WUENR7.BIT(5)] */
#define eINT_86     BIT(6)  /* WKO[89]-WU89-WUI30-GPI6-[WUENR7.BIT(6)] */
#define eINT_87     BIT(7)  /* WKO[90]-WU90-WUI31-GPI7-[WUENR7.BIT(7)] */
#define _SET_EN_IER10 0x00
#define _SET_WK_IER10 0x00

//-----------------------------------------------------------------------------
/* INT88 ~ INT95 */
#define eINT_88     BIT(0)  /* WKO[80]-WU80-WUI32-GPA3-[WUENR8.BIT(0)] */
#define eINT_89     BIT(1)  /* WKO[81]-WU81-WUI33-GPA4-[WUENR8.BIT(1)] */
#define eINT_90     BIT(2)  /* WKO[82]-WU82-WUI34-GPA5-[WUENR8.BIT(2)] */
#define eINT_91     BIT(3)  /* WKO[83]-WU83-WUI35-GPA6-[WUENR8.BIT(3)] */
#define eINT_92     BIT(4)  /* WKO[84]-WU84-WUI36-GPB2-[WUENR8.BIT(4)] */
#define eINT_93     BIT(5)  /* WKO[85]-WU85-WUI37-GPC0-[WUENR8.BIT(5)] */
#define eINT_94     BIT(6)  /* WKO[86]-WU86-WUI38-GPC7-[WUENR8.BIT(6)] */
#define eINT_95     BIT(7)  /* WKO[87]-WU87-WUI39-GPD7-[WUENR8.BIT(7)] */
#define _SET_EN_IER11 0x00
#define _SET_WK_IER11 0x00

//-----------------------------------------------------------------------------
/* INT96 ~ INT103 */
#define eINT_96     BIT(0)  /* WKO[91]-WU91-WUI43-GPA0-[WUENR9.BIT(3)] */
#define eINT_97     BIT(1)  /* WKO[92]-WU92-WUI44-GPA1-[WUENR9.BIT(4)] */
#define eINT_98     BIT(2)  /* WKO[93]-WU93-WUI45-GPA2-[WUENR9.BIT(5)] */
#define eINT_99     BIT(3)  /* WKO[94]-WU94-WUI46-GPB4-[WUENR9.BIT(6)] */
#define eINT_100    BIT(4)  /* WKO[95]-WU95-WUI47-GPC2-[WUENR9.BIT(7)] */
#define eINT_101    BIT(5)  /* WKO[96]-WU96-WUI48-GPF0-[WUENR10.BIT(0)] */
#define eINT_102    BIT(6)  /* WKO[97]-WU97-WUI49-GPF1-[WUENR10.BIT(1)] */
#define eINT_103    BIT(7)  /* WKO[98]-WU98-WUI50-GPF2-[WUENR10.BIT(2)] */
#define _SET_EN_IER12 eINT_103
#define _SET_WK_IER12 0x00

//-----------------------------------------------------------------------------
/* INT104 ~ INT111 */
#define eINT_104    BIT(0)  /* WKO[99]-WU99-WUI51-GPF3-[WUENR10.BIT(3)] */
#define eINT_105    BIT(1)  /* WKO[100]-WU100-WUI52-GPA7-[WUENR10.BIT(4)] */
#define eINT_106    BIT(2)  /* WKO[101]-WU101-WUI53-GPB0-[WUENR10.BIT(5)] */
#define eINT_107    BIT(3)  /* WKO[102]-WU102-WUI54-GPB1-[WUENR10.BIT(6)] */
#define eINT_108    BIT(4)  /* WKO[103]-WU103-WUI55-GPB3-[WUENR10.BIT(7)] */
#define eINT_109    BIT(5)  /* WKO[104]-WU104-WUI56-GPB5-[WUENR11.BIT(0)] */
#define eINT_110    BIT(6)  /* WKO[105]-WU105-WUI57-GPB6-[WUENR11.BIT(1)] */
#define eINT_111    BIT(7)  /* WKO[106]-WU106-WUI58-GPB7-[WUENR11.BIT(2)] */
#define _SET_EN_IER13 0x00
#define _SET_WK_IER13 0x00

//-----------------------------------------------------------------------------
/* INT112 ~ INT119 */
#define eINT_112    BIT(0)  /* WKO[107]-WU107-WUI59-GPC1-[WUENR11.BIT(3)] */
#define eINT_113    BIT(1)  /* WKO[108]-WU108-WUI60-GPC3-[WUENR11.BIT(4)] */
#define eINT_114    BIT(2)  /* WKO[109]-WU109-WUI61-GPC5-[WUENR11.BIT(5)] */
#define eINT_115    BIT(3)  /* WKO[110]-WU110-WUI62-GPD3-[WUENR11.BIT(6)] */
#define eINT_116    BIT(4)  /* WKO[111]-WU111-WUI63-GPD4-[WUENR11.BIT(7)] */
#define eINT_117    BIT(5)  /* WKO[112]-WU112-WUI64-GPD5-[WUENR12.BIT(0)] */
#define eINT_118    BIT(6)  /* WKO[113]-WU113-WUI65-GPD6-[WUENR12.BIT(1)] */
#define eINT_119    BIT(7)  /* WKO[114]-WU114-WUI66-GPE4-[WUENR12.BIT(2)] */
#define _SET_EN_IER14 eINT_119
#define _SET_WK_IER14 0x00

//-----------------------------------------------------------------------------
/* INT120 ~ INT127 */
#define eINT_120    BIT(0)  /* WKO[115]-WU115-WUI67-GPG0-[WUENR12.BIT(3)] */
#define eINT_121    BIT(1)  /* WKO[116]-WU116-WUI68-GPG1-[WUENR12.BIT(4)] */
#define eINT_122    BIT(2)  /* WKO[117]-WU117-WUI69-GPG2-[WUENR12.BIT(5)] */
#define eINT_123    BIT(3)  /* WKO[118]-WU118-WUI70-GPG6-[WUENR12.BIT(6)] */
#define eINT_124    BIT(4)  /* WKO[119]-WU119-WUI71-GPI0-[WUENR12.BIT(7)] */
#define eINT_125    BIT(5)  /* WKO[120]-WU120-WUI72-GPI1-[WUENR13.BIT(0)] */
#define eINT_126    BIT(6)  /* WKO[121]-WU121-WUI73-GPI2-[WUENR13.BIT(1)] */
#define eINT_127    BIT(7)  /* WKO[122]-WU122-WUI74-GPI3-[WUENR13.BIT(2)] */
#define _SET_EN_IER15 eINT_121
#define _SET_WK_IER15 0x00

//-----------------------------------------------------------------------------
/* INT128 ~ INT135 */
#define eINT_128    BIT(0)  /* WKO[128]-WU128-WUI80-GPJ0-[WUENR14.BIT(0)] */
#define eINT_129    BIT(1)  /* WKO[129]-WU129-WUI81-GPJ1-[WUENR14.BIT(1)] */
#define eINT_130    BIT(2)  /* WKO[130]-WU130-WUI82-GPJ2-[WUENR14.BIT(2)] */
#define eINT_131    BIT(3)  /* WKO[131]-WU131-WUI83-GPJ3-[WUENR14.BIT(3)] */
#define eINT_132    BIT(4)  /* WKO[132]-WU132-WUI84-GPJ4-[WUENR14.BIT(4)] */
#define eINT_133    BIT(5)  /* WKO[133]-WU133-WUI85-GPJ5-[WUENR14.BIT(5)] */
#define eINT_134    BIT(6)  /* WKO[134]-WU134-WUI86-GPJ6-[WUENR14.BIT(6)] */
#define eINT_135    BIT(7)
#define _SET_EN_IER16 0x00
#define _SET_WK_IER16 0x00

//-----------------------------------------------------------------------------
/* INT136 ~ INT143 */
#define eINT_136    BIT(0)
#define eINT_137    BIT(1)
#define eINT_138    BIT(2)
#define eINT_139    BIT(3)
#define eINT_140    BIT(4)
#define eINT_141    BIT(5)
#define eINT_142    BIT(6)
#define eINT_143    BIT(7)
#define _SET_EN_IER17 0x00
#define _SET_WK_IER17 0x00

//-----------------------------------------------------------------------------
/* INT144 ~ INT151 */
#define eINT_144    BIT(0)
#define eINT_145    BIT(1)
#define eINT_146    BIT(2)
#define eINT_147    BIT(3)
#define eINT_148    BIT(4)
#define eINT_149    BIT(5)  /* PMC5 Output Buffer Empty Intr. */
#define eINT_150    BIT(6)  /* PMC5 Input Buffer Full Intr. */
#define eINT_151    BIT(7)  /* Voltage Comparator Interrupt */
#define _SET_EN_IER18 0x00
#define _SET_WK_IER18 0x00

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#endif  //OEM_POWER_H
/*-----------------------------------------------------------------------------
 * End of OEM_POWER.H */