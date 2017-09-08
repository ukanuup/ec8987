/*----------------------------------------------------------------------------
 * @file     | OEM_MEMORY.C            | @Chipset | ITE.IT85XX
 * ----------+-----------------------------------------------------------------
 * @function | Memory Definition for extern all code base reference
 * ----------+-----------------------------------------------------------------
 * [Memory Map Description]
 *
 * Chip Internal Ram : 0x00-0xFF For Kernel and Chip Level use
 *
 ***************************************************
 * Chip 8500       : External ram 0x0000-0x07FF
 * Chip Other 85XX : External ram 0x0000-0x0FFF
 ***************************************************
 *
 * [OEM Memory Rang]
 * [External Ram]
 * 0x100-0x1FF   OEM RAM
 * 0x200-0x2FF   OEM RAM
 * 0x300-0x3FF   OEM RAM
 * 0x400-0x4FF   OEM RAM
 * 0x500-0x5FF   OEM RAM
 * 0x600-0x6FF   OEM RAM ITE_Flash_Utility & SPI ROM Read/Write
 * 0x700-0x7FF   OEM RAM RamProgram
 * 0x800-0x8FF   OEM RAM [X] IT8527E
 * 0x900-0x9FF   OEM RAM [X] IT8527E
 * 0xA00-0xAFF   OEM RAM [X] IT8527E
 * 0xB00-0xBFF   OEM RAM [X] IT8527E
 * 0xC00-0xCFF   OEM RAM [X] IT8527E
 * 0xD00-0xDFF   OEM RAM [X] IT8527E
 * 0xE00-0xEFF   OEM RAM [X] IT8527E
 * 0xF00-0xFFF   OEM RAM [X] IT8527E
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_MEMORY_H
#define OEM_MEMORY_H


//-----------------------------------------------------------------------------
/*****************************************************************************/
/* RAM BASE DEFINE ***********************************************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define EC_RAMBase          0x0000
#define OEMRAM1             EC_RAMBase+0x0100   // EC_RAMBase+0x0100
#define OEMRAM2             EC_RAMBase+0x0200   // EC_RAMBase+0x0200
#define OEMRAM3             EC_RAMBase+0x0300   // EC_RAMBase+0x0300
#define OEMRAM4             EC_RAMBase+0x0400   // EC_RAMBase+0x0400
#define OEMRAM5             EC_RAMBase+0x0500   // EC_RAMBase+0x0500
#define OEMRAM8             EC_RAMBase+0x0800   // EC_RAMBase+0x0800
#define OEMRAM9             EC_RAMBase+0x0900   // EC_RAMBase+0x0900
#define OEMRAMA             EC_RAMBase+0x0A00   // EC_RAMBase+0x0A00
#define OEMRAMB             EC_RAMBase+0x0B00   // EC_RAMBase+0x0B00
#define OEMRAMC             EC_RAMBase+0x0C00   // EC_RAMBase+0x0C00
#define OEMRAMD             EC_RAMBase+0x0D00   // EC_RAMBase+0x0D00
#define OEMRAME             EC_RAMBase+0x0E00   // EC_RAMBase+0x0E00
#define OEMRAMF             EC_RAMBase+0x0F00   // EC_RAMBase+0x0F00

//-----------------------------------------------------------------------------
/*****************************************************************************/
extern BBYTE CustomFlag2;
extern bit F_MCU_POWERDOWN;
/* EXTERNAL RAM AREA      (0x0000 ~ 0x00FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
/* Kernel none use resources (need adjustment after update kernel) */
//-----------------------------------------------------------------------------
extern XBYTE    SCIEVT_BUF[];
extern XBYTE    SCIEVT_WIDX;
extern XBYTE    SCIEVT_RIDX;
extern XBYTE    SCIEVT_OUT;
extern XBYTE    SCIEVT_LOSE;
extern XBYTE    SCIEVT_OVT;
extern XBYTE    SCIEVT_DELAY;
extern XBYTE    SCIEVT_LAST;
extern XBYTE    SCIEVT_CNT;
//-----------------------------------------------------------------------------
extern XBYTE    SysPowState;
#define F_PST_BUSY          BIT(7)
extern XBYTE    CtrlPowStep;
extern XWORD    PowSeqDelay;
extern XWORD    PowSeqWait;

extern XBYTE    PowerOnFailed;
extern XBYTE    PowSwFlag;
#define F_PSW_WAIT_UP       BIT(0)
#define F_PSW_SCANCODE      BIT(6)
#define F_PSW_RSMRST        BIT(7)
extern XBYTE    SetAutoBootTimer;
extern XBYTE    AutoBootTimer;
extern XBYTE    PanelOnStep;
extern XBYTE    PanelOnDelay;
extern XBYTE    MutePinDelay;
extern XBYTE    LID_Debounce;
extern XBYTE    LID_OpenDebounce;
extern XWORD    PowSwLockTimer;
extern XWORD    PowSwDownTimer;
extern XWORD    PowSwDebounce;
extern XWORD    wPwrSwTypingDelay;
extern XWORD    wLockPWRBTN;
extern XWORD    wECU_ADDR;
extern XWORD    LID_Resend;
extern XWORD    LID_OpenResend;
//-----------------------------------------------------------------------------
extern XBYTE    SystemFlag1;
#define F_ACPI_MODE         BIT(7)
extern XBYTE    SystemFlag2;
extern XBYTE    HSPI_FPT_timeout;
extern XWORD   	Forece_Shutdown_timer;
extern XBYTE	MISC_EVENT;//						_at_ F2+05;
#define 		EC_RESET_PW			BIT1


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0100 ~ 0x01FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
extern XBYTE    USB_PD_REG_P0[];
//-----------------------------------------------------------------------------
extern XBYTE    DBG1_EJ898A_CMD;
extern XBYTE    DBG1_EJ898A_DATA;
extern XBYTE    DBG1_EJ898A_START;
extern XBYTE    DBG1_EJ898A_STATUS;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0200 ~ 0x02FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
extern XBYTE    USB_PD_REG_P1[];
//-----------------------------------------------------------------------------
extern XBYTE    I2C_EJ898A_EEPROM_VER;
extern XBYTE    I2C_EJ898A_INITIAL;
extern XBYTE    I2C_EJ898A_GET_VER_OK;
extern XBYTE    I2C_EJ898A_NEW_VER;
extern XBYTE    I2C_EJ898A_OFFSET[];
extern XBYTE    I2C_EJ898A_DATA[];

extern XBYTE    I2C_EJ898A_STEP;
extern XBYTE    I2C_EJ898A_RX_DR_SWAP;
extern XBYTE    I2C_EJ898A_LAST_REG_DDH;
extern XBYTE    I2C_EJ898A_PDC_DELAY;
extern XBYTE    I2C_EJ898A_PDC_COUNTER;
extern XBYTE    I2C_EJ898A_RETRY;
extern XBYTE    I2C_EJ898A_ERROR;
extern XBYTE    I2C_EJ898A_DEBUG;

extern XBYTE    I2C_EJ898A_POLLING1;
extern XBYTE    I2C_EJ898A_POLLING2;

extern XBYTE    I2C_EJ898A_RX_PR_SWAP;
extern XBYTE    I2C_EJ898A_PR_SWAP_DELAY;

extern XBYTE    I2C_EJ898A_PD_CONTRACT_HI;
extern XBYTE    I2C_EJ898A_PD_CONTRACT_LO;

extern XBYTE    I2C_EJ898A_RCV_PDO_NUM;
extern XBYTE    I2C_EJ898A_RCV_PDO_DIR;
extern XBYTE    I2C_EJ898A_TPD_SNK_RDO;
extern XBYTE    I2C_EJ898A_PDO_DATA0;
extern XBYTE    I2C_EJ898A_PDO_DATA1;
extern XBYTE    I2C_EJ898A_PDO_DATA2;
extern XBYTE    I2C_EJ898A_PDO_DATA3;
extern XBYTE    I2C_EJ898A_ATTENCTION_INT;
extern XBYTE    I2C_EJ898A_PD_HI_DELAY;
extern XBYTE    I2C_EJ898A_PD_RECHECK_05;
//-----------------------------------------------------------------------------
extern XWORD    wEJ898A_VBUS_Voltage;
extern XWORD    wEJ898A_RDO_Current;
extern XWORD    wEJ898A_PDO_Select_Voltage;
extern XWORD    wEJ898A_PDO_Select_Current;
extern XWORD    wEJ898A_Max_PDO_Voltage;
extern XWORD    wEJ898A_Request_Current;
extern XWORD    wEJ898A_PDO_Sel_V_m10;
extern XWORD    wEJ898A_PDO_Sel_I_m10;
//-----------------------------------------------------------------------------
extern XWORD    wEJ898A_I2C_EJ898A_DELAY;
extern XBYTE    I2C_EJ898A_PR_SWAP_RETRY;

extern XBYTE    I2C_EJ898A_DISCOVER_MODE;
extern XWORD    wEJ898A_PDO_Sel_W_m10;
extern XBYTE    I2C_EJ898A_PD_WATT;
extern XBYTE    I2C_EJ898A_FLAG;        //0x2CF
#define F_PD_ADAPTER_IN         BIT(0)
#define F_PD_IS_5V_ADAPTER      BIT(1)
#define F_PD_STOP_CHARGING      BIT(2)
#define F_PD_LEGACY_5V_ADAPTER  BIT(3)

#define F_MRD_IS_SOURCE         BIT(4)
#define F_CABLE_CONNECTED       BIT(5)
#define F_CABLE_DICONNECTED     BIT(6)
#define F_INIT_PD_ADAPTER       BIT(7)
//-----------------------------------------------------------------------------
extern XWORD    DLY_S3_S4;
extern XWORD    USBC_LoopTimer;
extern XWORD    LED_FLASH_CNT;
extern XBYTE    LED_OFF_CNT;
extern XBYTE    S5_STATE_FLG;

extern XBYTE    I2C_EJ898A_REQ_DIR;
extern XBYTE    xEC_EJ898A_FW_VERSION2;
extern XBYTE    P80_DEBUG_CODE;
//-----------------------------------------------------------------------------
extern XBYTE    DBG2_EJ898A_CMD;
extern XBYTE    DBG2_EJ898A_DATA;
extern XBYTE    DBG2_EJ898A_START;
extern XBYTE    DBG2_EJ898A_STATUS;
#define I2C_EJ898_SET_5V				BIT(0)
#define I2C_EJ898A_ChargeNoDealy		BIT(1)
#define I2C_AC_ChargeNoDealy			BIT(7)

extern XBYTE    I2C_EJ898A_VCONN_SWAP;
extern XBYTE    I2C_EJ898A_DP_AB_DELAY;
extern XBYTE    I2C_EJ898A_DP_STATUS_INT;
extern XBYTE    I2C_EJ898A_ATTENCTION_LOCK;
extern XBYTE    I2C_EJ898A_ATTENCTION_CNT;
extern XBYTE    I2C_EJ898A_ATTENCTION_DLY;
extern XBYTE    I2C_EJ898A_NEED_REBOOT;
extern XBYTE    I2C_EJ898A_CODING_VER;
extern XBYTE    I2C_DD_Resend;
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0300 ~ 0x03FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
extern XBYTE    SMBA_CHN_STS;
extern XBYTE    SMBA_CHN_TIMER;
extern XBYTE    SMBA_DEV_DIR;
extern XBYTE    SMBA_CHN_CTL;
extern XBYTE    SMBA_CHN_CMD;
extern XBYTE    SMBA_BYTE_CNT;
extern XWORD    SMBA_DEV_MEM;
extern XBYTE    SMBA_ERR_STS[];
extern XBYTE    SMBA_DAT_CNT[];
extern XBYTE    SMBB_CHN_STS;
extern XBYTE    SMBB_CHN_TIMER;
extern XBYTE    SMBB_DEV_DIR;
extern XBYTE    SMBB_CHN_CTL;
extern XBYTE    SMBB_CHN_CMD;
extern XBYTE    SMBB_BYTE_CNT;
extern XWORD    SMBB_DEV_MEM;
extern XBYTE    SMBB_ERR_STS[];
extern XBYTE    SMBB_DAT_CNT[];
extern XBYTE    SMBC_CHN_STS;
extern XBYTE    SMBC_CHN_TIMER;
extern XBYTE    SMBC_DEV_DIR;
extern XBYTE    SMBC_CHN_CTL;
extern XBYTE    SMBC_CHN_CMD;
extern XBYTE    SMBC_BYTE_CNT;
extern XWORD    SMBC_DEV_MEM;
extern XBYTE    SMBC_ERR_STS[];
extern XBYTE    SMBC_DAT_CNT[];
extern XBYTE    SMBD_CHN_STS;
extern XBYTE    SMBD_CHN_TIMER;
extern XBYTE    SMBD_DEV_DIR;
extern XBYTE    SMBD_CHN_CTL;
extern XBYTE    SMBD_CHN_CMD;
extern XBYTE    SMBD_BYTE_CNT;
extern XWORD    SMBD_DEV_MEM;
extern XBYTE    SMBD_ERR_STS[];
extern XBYTE    SMBD_DAT_CNT[];
extern XBYTE    SMBA_DEV0_STS;
extern XBYTE    SMBA_DEV0_DIR;
extern XWORD    SMBA_DEV0_DLY;
extern XBYTE    SMBA_DEV1_STS;
extern XBYTE    SMBA_DEV1_DIR;
extern XWORD    SMBA_DEV1_DLY;
extern XBYTE    SMBB_DEV0_STS;
extern XBYTE    SMBB_DEV0_DIR;
extern XWORD    SMBB_DEV0_DLY;
extern XBYTE    SMBB_DEV1_STS;
extern XBYTE    SMBB_DEV1_DIR;
extern XWORD    SMBB_DEV1_DLY;
extern XBYTE    SMBC_DEV0_STS;
extern XBYTE    SMBC_DEV0_DIR;
extern XWORD    SMBC_DEV0_DLY;
extern XBYTE    SMBC_DEV1_STS;
extern XBYTE    SMBC_DEV1_DIR;
extern XWORD    SMBC_DEV1_DLY;
extern XWORD    SMBA_DEV2_DLY;

//-----------------------------------------------------------------------------
extern XBYTE    DebounceGPI1;
extern XBYTE    DebounceGPI2;
extern XBYTE    DebounceGPI3;
extern XBYTE    ViberatorTimer;
extern XBYTE    DebounceGPI4;
extern XBYTE    DebounceGPI5;
extern XBYTE    DebounceGPI6;
extern XBYTE    DebounceGPIFlag;
#define F_Volemup_press     BIT(0)
#define F_Volemdn_press     BIT(1)
#define F_pwrbtn_press      BIT(2)
extern XBYTE   DebounceGPI8;

//-----------------------------------------------------------------------------
// SMBX BIT DEFINE
/* SMBX_CHN_STS */
#define F_SMB_BUSY          BIT(7)
#define F_SMB_CHID1         BIT(3)
#define F_SMB_CHID0         BIT(2)
#define F_SMB_DEVD1         BIT(1)
#define F_SMB_DEVD0         BIT(0)
/* SMBA_CHN_STS */
#define F_DEV_STOP          BIT(7)
#define F_DEV_FAILED        BIT(6)
#define F_DEV_UPDATED       BIT(3)

#define F_DEV_INIT          BIT(1)
#define F_DEV_ON_LINE       BIT(0)
#define F_DEV_MASK_READY    (BIT(7) | BIT(6) | BIT(0))
#define F_DEV_READY         BIT(0)

//-----------------------------------------------------------------------------
extern XWORD    wADC[];
extern XBYTE    xADC[];

extern XBYTE    xEC_T1_CNT;
extern XBYTE    xEC_T2_CNT;

extern XBYTE    xEC_T1_AVG;
extern XBYTE    xEC_T1_HiLimit;
extern XBYTE    xEC_T1_LoLimit;
extern XBYTE    xEC_T1_THR;
extern XBYTE    xEC_T1_EventTimer;
extern XBYTE    xEC_T1_SendEvent;
extern XWORD    wEC_T1_THR_ACC;

extern XBYTE    xEC_T2_AVG;
extern XBYTE    xEC_T2_HiLimit;
extern XBYTE    xEC_T2_LoLimit;
extern XBYTE    xEC_T2_THR;
extern XBYTE    xEC_T2_EventTimer;
extern XBYTE    xEC_T2_SendEvent;
extern XWORD    wEC_T2_THR_ACC;


//-----------------------------------------------------------------------------
extern XBYTE    PECI_FLAG;
#define F_PECI_STOP         BIT(7)
#define F_PECI_BUSY         BIT(6)
#define F_PECI_UPDATED      BIT(5)
#define F_PECI_INIT4        BIT(3)
#define F_PECI_INIT3        BIT(2)
#define F_PECI_INIT2        BIT(1)
#define F_PECI_INIT         BIT(0)

extern XBYTE    PECI_CMD;
extern XBYTE    PECI_CompletionCode;
extern XBYTE    PECI_TIMER;
extern XBYTE    PECI_ERRCNT;
extern XBYTE    PECI_ERRSTS;
extern XBYTE    PECI_OVTCT;
extern XBYTE    PECI_CRC8;
extern XBYTE    PECI_CPU_T;

extern XBYTE    PECI_DIR;
extern XWORD    PECI_DELAY;
extern XWORD    PECI_MEMADR;
extern XBYTE    PECI_GetDIB[];
extern XBYTE    PECI_GetTemp[];
extern XBYTE    PECI_RdPkgCfg_Idx16_CC;
extern XBYTE    PECI_RdPkgCfg_Idx16[];
#define Processor_Tj_max        PECI_RdPkgCfg_Idx16[2]
#define Processor_T_control     PECI_RdPkgCfg_Idx16[1]
extern XBYTE    PECI_ReadBuffer[];
extern XBYTE    PECI_WriteBuffer[];

extern XBYTE    PECI_PowerUnit;
extern XBYTE    PECI_EnergyUnit;
extern XBYTE    PECI_TimeUnit;
extern XWORD    PECI_UnitPower;
extern XBYTE    PECI_PowerLimit1;
extern XBYTE    PECI_PowerLimit2;
extern XBYTE    CS_2C_CMD_PULL;


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0400 ~ 0x04FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define MEM_EC_SPACE                0x0400

extern XBYTE    xEC_MainVersion;
extern XBYTE    xEC_SubVersion;
extern XBYTE    xEC_TestVersion;

extern XBYTE    xEC_ThermalChargCMD;
extern XBYTE    xEC_ThermalChargFlag;
extern XBYTE   xEC_SensorT_Error_F;
#define F_Skin_Sensor_error      BIT(0)

extern XBYTE	xEC_RTC_WakeupFlag;
extern XBYTE	xEC_RTC_SupportFlag;
extern XWORD	xEC_RTC_Wakeuptimer;
extern XWORD    xEC_Forece_Shutdown_counter;


extern XWORD    xEC_RTC_test_counter;//+0x49;


extern XBYTE    xEC_PECI_CPU_T;
extern XBYTE    xEC_PLMX_T;
extern XBYTE    xEC_SYS_SKIN_T;
extern XBYTE    xEC_CHARGER_T;
extern XBYTE    xEC_LID_STATUS;
#define F_LID_STA			BIT(0)
#define F_GPI_LID_STA       BIT(7)      //OEPN:1, CLOSED:0


extern XBYTE    xEC_Sensor_F;
#define F_PECI_Sensor       BIT(0)
#define F_CHARG_Sensor      BIT(1)
#define F_SKIN_Sensor       BIT(2)

extern XBYTE    xEC_Sensor_TSHT;
extern XBYTE    xEC_Sensor_TSLT;

extern XBYTE    xEC_ThermalSource;
#define F_PECI_HOT          BIT(0)
#define F_CHARG_HOT         BIT(1)
#define F_SKIN_HOT          BIT(2)
extern XWORD    xEC_Charge_Rate;
extern XWORD    xEC_Charge_InCurrent;
extern XWORD    xEC_Charge_Vlot;
extern XWORD    xEC_Charge_option;

extern XBYTE    xEC_PowerState;
extern XBYTE    xEC_Bt1ModelCode;
extern XBYTE    xEC_Bt1SerialNumberL;
extern XBYTE    xEC_Bt1SerialNumberH;
extern XBYTE    xEC_Bt1DesignCapacityL;
extern XBYTE    xEC_Bt1DesignCapacityH;
extern XBYTE    xEC_Bt1DesignVoltageL;
extern XBYTE    xEC_Bt1DesignVoltageH;
extern XBYTE    xEC_Bt1FullChrgCapacityL;
extern XBYTE    xEC_Bt1FullChrgCapacityH;
extern XBYTE    xEC_Bt1TripPointL;
extern XBYTE    xEC_Bt1TripPointH;
extern XBYTE    xEC_Bt1State;
#define F_ACPI_DISCHRGE     BIT(0)
#define F_ACPI_CHARGING     BIT(1)
#define F_ACPI_CRITICAL     BIT(2)
extern XBYTE    xEC_Bt1PresentRateL;
extern XBYTE    xEC_Bt1PresentRateH;
extern XBYTE    xEC_Bt1RemainCapacityL;
extern XBYTE    xEC_Bt1RemainCapacityH;
extern XBYTE    xEC_Bt1PresentVoltageL;
extern XBYTE    xEC_Bt1PresentVoltageH;
extern XBYTE    xEC_BtRSOC;//                    _at_ MEM_EC_SPACE+0x93;

extern XBYTE	xEC_RTC_lastwakeup_counter_H;//	_at_ MEM_EC_SPACE+0xBD;
extern XBYTE	xEC_RTC_lastwakeup_counter_L;//	_at_ MEM_EC_SPACE+0xBE;
extern XBYTE    xEC_EJ898A_FW_VERSION;


extern XBYTE    xEC_USB_TC_MB_MGI0;
extern XBYTE    xEC_USB_TC_MB_MGI1;
extern XBYTE    xEC_USB_TC_MB_MGI2;
extern XBYTE    xEC_USB_TC_MB_MGI3;
extern XBYTE    xEC_USB_TC_MB_MGI4;
extern XBYTE    xEC_USB_TC_MB_MGI5;
extern XBYTE    xEC_USB_TC_MB_MGI6;
extern XBYTE    xEC_USB_TC_MB_MGI7;
extern XBYTE    xEC_USB_TC_MB_MGI8;
extern XBYTE    xEC_USB_TC_MB_MGI9;
extern XBYTE    xEC_USB_TC_MB_MGIA;
extern XBYTE    xEC_USB_TC_MB_MGIB;
extern XBYTE    xEC_USB_TC_MB_MGIC;
extern XBYTE    xEC_USB_TC_MB_MGID;
extern XBYTE    xEC_USB_TC_MB_MGIE;
extern XBYTE    xEC_USB_TC_MB_MGIF;

extern XBYTE   xEC_USB_TC_MB_MGO0;
extern XBYTE   xEC_USB_TC_MB_MGO1;
extern XBYTE   xEC_USB_TC_MB_MGO2;
extern XBYTE   xEC_USB_TC_MB_MGO3;
extern XBYTE   xEC_USB_TC_MB_MGO4;
extern XBYTE   xEC_USB_TC_MB_MGO5;
extern XBYTE   xEC_USB_TC_MB_MGO6;
extern XBYTE   xEC_USB_TC_MB_MGO7;
extern XBYTE   xEC_USB_TC_MB_MGO8;
extern XBYTE   xEC_USB_TC_MB_MGO9;
extern XBYTE   xEC_USB_TC_MB_MGOA;
extern XBYTE   xEC_USB_TC_MB_MGOB;
extern XBYTE   xEC_USB_TC_MB_MGOC;
extern XBYTE   xEC_USB_TC_MB_MGOD;
extern XBYTE   xEC_USB_TC_MB_MGOE;
extern XBYTE   xEC_USB_TC_MB_MGOF;

extern XBYTE   xEC_USB_TC_UCSI_DATA_VER1;
extern XBYTE   xEC_USB_TC_UCSI_DATA_VER2;
extern XBYTE   xEC_USB_TC_UCSI_DATA_RSV1;
extern XBYTE   xEC_USB_TC_UCSI_DATA_RSV2;

extern XBYTE   xEC_USB_TC_CCI0;
extern XBYTE   xEC_USB_TC_CCI1;
extern XBYTE   xEC_USB_TC_CCI2;
extern XBYTE   xEC_USB_TC_CCI3;

extern XBYTE   xEC_USB_TC_CTL0;
extern XBYTE   xEC_USB_TC_CTL1;
extern XBYTE   xEC_USB_TC_CTL2;
extern XBYTE   xEC_USB_TC_CTL3;
extern XBYTE   xEC_USB_TC_CTL4;
extern XBYTE   xEC_USB_TC_CTL5;
extern XBYTE   xEC_USB_TC_CTL6;
extern XBYTE   xEC_USB_TC_CTL7;

extern XBYTE   xEC_USB_PD_STS_DD;
#define F_PD_DD_3     BIT(3)
#define F_PD_DD_6     BIT(6)
extern XBYTE   xEC_USB_PD_STS_4;
#define F_PD_4_3    BIT(3)
extern XBYTE   xEC_USB_PD_STS_5;
#define F_PD_5_4    BIT(4)
#define F_PD_5_6    BIT(6)
extern XBYTE   xEC_USB_PD_STS_10;
#define F_PD_10_5   BIT(5)
#define F_PD_10_6   BIT(6)
extern XBYTE   xEC_USB_PD_STS_11;
#define F_PD_11_0   BIT(0)
extern XBYTE   xEC_USB_PD_STS_E;
#define F_PD_E_3    BIT(3)

extern XBYTE    xEC_ShutdownCode;
extern XBYTE   xEC_EJ898A_NEED_REBOOT;
extern XBYTE   xEC_EJ898A_ERROR;

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0500 ~ 0x05FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define BAT1_MemBase                0x0500
extern XWORD    BAT1_ManufacturerAccess;
extern XWORD    BAT1_BatteryMode;
extern XWORD    BAT1_Temperature;
extern XWORD    BAT1_Voltage;
extern XWORD    BAT1_Current;
extern XWORD    BAT1_AverageCurrent;
extern XWORD    BAT1_MaxError;
extern XBYTE    BAT1_RelativeStateOfChg;
extern XBYTE    BAT1_RelativeStateOfChgL;
extern XWORD    BAT1_AbsoluteOfCharge;
extern XWORD    BAT1_RemainingCapacity;
extern XWORD    BAT1_FullChargeCapacity;
extern XWORD    BAT1_ChargingCurrent;
extern XWORD    BAT1_ChargingVoltage;
extern XWORD    BAT1_BatteryStatus1;
extern XWORD    BAT1_CycleCount;
extern XWORD    BAT1_DesignCapacity;
extern XWORD    BAT1_DesignVoltage;
extern XWORD    BAT1_SpecificationInfo;
extern XWORD    BAT1_ManufactureDate;
extern XWORD    BAT1_SerialNumber;
extern XBYTE    BAT1_ManufacturerName[];
extern XBYTE    BAT1_DeviceName[];
extern XBYTE    BAT1_DeviceChemistry[];
extern XBYTE    BAT1_ManufacturerData[];
extern XBYTE    BAT1_PACKAGE;
extern XWORD    BAT1_BatteryStatus2;
extern XWORD    BAT1_BatteryStatus;
extern XBYTE    BAT1_LockPowerOnRSOC;
extern XBYTE    BAT1_NoOCPTimer;
extern XBYTE    BAT1_LastRSOC;
//extern XWORD    BAT1_LastBTP;
extern XWORD    BAT1_LastFCC;
extern XBYTE    BAT1_Low_ShutdownCount;//       _at_ BAT1_MemBase+0x63;

extern XBYTE    BAT1_Counter1;
extern XBYTE    BAT1_ChargePauseTimer;
extern XBYTE    BAT1_THROT_DIR;
extern XWORD    BAT1_THROT_DNT;
extern XWORD    BAT1_THROT_UPT;

extern XBYTE    SkinTripFlag;
extern XBYTE    xEC_Sensor_TSHT_New;
extern XBYTE    xEC_Sensor_TSLT_New;
extern XBYTE    xEC_Sensor_TSHT_Send;
extern XBYTE    xEC_Sensor_TSLT_Send;

//-----------------------------------------------------------------------------
extern XBYTE    xEC_PowerSource;
extern XBYTE    PowerSource;
#define _BATT_CLR_MASK      F_BAT1_DISCHRGE+F_BAT1_CHARGING+F_BAT1_CRITICAL+\
                            F_BAT1_LOW+F_BAT1_DETECTED+F_BAT1_PRESENT
#define F_BAT1_DISCHRGE     BIT(7)
#define F_BAT1_CHARGING     BIT(6)
#define F_BAT1_CRITICAL     BIT(5)
#define F_BAT1_LOW          BIT(4)
#define F_BAT1_DETECTED     BIT(2)
#define F_BAT1_PRESENT      BIT(1)
#define F_AC_ON_LINE        BIT(0)

extern XBYTE    Debounce_ACin;
extern XBYTE    Debounce_Bt1In;
extern XBYTE    Debounce_Bt2In;
extern XBYTE    SendBatEventTimer;
extern XBYTE    SendACiEventTimer;
extern XBYTE    PowPgmScan;
extern XBYTE    SMBA_FloatingTimer;
extern XBYTE    BatteryDetectStep;
extern XBYTE    BatteryDetectRetry;
extern XWORD    wBatteryDetectTmr;

extern XBYTE    EventTestTimer;
extern XBYTE    EventTestNumber;
//-----------------------------------------------------------------------------

extern XBYTE    xEC_CPUT_HiLimit;
extern XBYTE    xEC_CPUT_LoLimit;
extern XBYTE    xEC_CPUT_EventTimer;
extern XBYTE    xEC_CPUT_SendEvent;

extern XWORD    wPowerSavingDelay;
extern XBYTE    PowerSavingCount;

extern XWORD    BAT1_ChargingCurrentLast;
extern XWORD    USBC_ChargingCurrentLast;
extern XWORD    USBC_InputCurrent;
extern XWORD    USBC_ChargingCurrent;
extern XWORD    USBC_ChargingVoltage;
//-----------------------------------------------------------------------------
extern XWORD    CHGR_ChargerOption;
extern XWORD    CHGR_InputCurrent;
extern XWORD    CHGR_ChargingCurrent;
extern XWORD    CHGR_ChargingVoltage;
extern XWORD    CHGR_ManufacturerID;
extern XWORD    CHGR_DeviceID;
extern XWORD    CHGR_ChargerREG3E;
extern XBYTE    WakeUpChargeTimer;

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0600 ~ 0x06FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * For ITE_Flash_Utility & SPI ROM Read/Write
 * using 0x0600-0x06FF
 *---------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0700 ~ 0x07FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * RamProgram using 0x0700-0x07FF
 *---------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0800 ~ 0x08FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
extern XBYTE    SPIBuffer[];

/* [X] IT8527E */
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0900 ~ 0x09FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
extern XBYTE   P80_RAM_9[];

/* [X] IT8527E */
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0A00 ~ 0x0AFF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
extern XBYTE   EJ898A_DEBUG_A[];
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0B00 ~ 0x0BFF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
extern XBYTE   EJ898A_DEBUG_B[];
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0C00 ~ 0x0CFF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
extern XBYTE   EJ898A_RAM_C[];
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0D00 ~ 0x0DFF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
extern XBYTE   EJ898A_RAM_D[];
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0E00 ~ 0x0EFF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
/* [X] IT8527E */
#define DebugRamAddr                0xE00   /* IT858XE */
//#define DebugRamAddr              0x600   /* IT8527E */
#define DebugRamRange               0xFF
extern XBYTE    DebugIndex;
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0F00 ~ 0x0FFF) **********************************/
/*****************************************************************************/
extern XBYTE   P80_RAM_F[];

//-----------------------------------------------------------------------------
/* [X] IT8527E */
//-----------------------------------------------------------------------------
#define DebugRamAddrP80                0xF00   /* IT858XE */
#define DebugRamAddrh25				   0xE00

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* BRAM                   (0x2200 ~ 0x22FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------



/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Clear_Memory_Range(WORD nAddr, WORD nSize);


//-----------------------------------------------------------------------------
#endif  //OEM_MEMORY_H
/*-----------------------------------------------------------------------------
 * End of OEM_MEMORY.H */
