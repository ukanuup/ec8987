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
 * @note     | Copyright(c)2010-2014, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

volatile unsigned char bdata CustomFlag2 _at_ 0x2F;
sbit F_MCU_POWERDOWN                = CustomFlag2^0;

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0000 ~ 0x00FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
/* Kernel none use resources (need adjustment after update kernel) */
//-----------------------------------------------------------------------------
#define MEM_SCI_RAM                 0x00A0
XBYTE   SCIEVT_BUF[8]               _at_ MEM_SCI_RAM+0x00;
XBYTE   SCIEVT_WIDX                 _at_ MEM_SCI_RAM+0x08;
XBYTE   SCIEVT_RIDX                 _at_ MEM_SCI_RAM+0x09;
XBYTE   SCIEVT_OUT                  _at_ MEM_SCI_RAM+0x0A;
XBYTE   SCIEVT_LOSE                 _at_ MEM_SCI_RAM+0x0B;
XBYTE   SCIEVT_OVT                  _at_ MEM_SCI_RAM+0x0C;
XBYTE   SCIEVT_DELAY                _at_ MEM_SCI_RAM+0x0D;
XBYTE   SCIEVT_LAST                 _at_ MEM_SCI_RAM+0x0E;
XBYTE   SCIEVT_CNT                  _at_ MEM_SCI_RAM+0x0F;
//-----------------------------------------------------------------------------
#define MEM_PWRCTRL                 0x00B0
XBYTE   SysPowState                 _at_ MEM_PWRCTRL+0x00;
XBYTE   CtrlPowStep                 _at_ MEM_PWRCTRL+0x01;
XWORD   PowSeqDelay                 _at_ MEM_PWRCTRL+0x02;
XWORD   PowSeqWait                  _at_ MEM_PWRCTRL+0x04;

XBYTE   PowerOnFailed               _at_ MEM_PWRCTRL+0x07;
XBYTE   PowSwFlag                   _at_ MEM_PWRCTRL+0x08;
XBYTE   SetAutoBootTimer            _at_ MEM_PWRCTRL+0x09;
XBYTE   AutoBootTimer               _at_ MEM_PWRCTRL+0x0A;
XBYTE   PanelOnStep                 _at_ MEM_PWRCTRL+0x0B;
XBYTE   PanelOnDelay                _at_ MEM_PWRCTRL+0x0C;
XBYTE   MutePinDelay                _at_ MEM_PWRCTRL+0x0D;
XBYTE   LID_Debounce                _at_ MEM_PWRCTRL+0x0E;
XBYTE   LID_OpenDebounce            _at_ MEM_PWRCTRL+0x0F;
XWORD   PowSwLockTimer              _at_ MEM_PWRCTRL+0x10;
XWORD   PowSwDownTimer              _at_ MEM_PWRCTRL+0x12;
XWORD   PowSwDebounce               _at_ MEM_PWRCTRL+0x14;
XWORD   wPwrSwTypingDelay           _at_ MEM_PWRCTRL+0x16;
XWORD   wLockPWRBTN                 _at_ MEM_PWRCTRL+0x18;
XWORD   wECU_ADDR                   _at_ MEM_PWRCTRL+0x1A;
XWORD   LID_Resend                  _at_ MEM_PWRCTRL+0x1C;
XWORD   LID_OpenResend              _at_ MEM_PWRCTRL+0x1E;
//-----------------------------------------------------------------------------
#define MEM_SYSCTRL                 0x00F2
XBYTE   SystemFlag1                 _at_ MEM_SYSCTRL+0x00;
XBYTE   SystemFlag2                 _at_ MEM_SYSCTRL+0x01;
XBYTE   HSPI_FPT_timeout            _at_ MEM_SYSCTRL+0x02;
XWORD   Forece_Shutdown_timer       _at_ MEM_SYSCTRL+0x03;
XBYTE	MISC_EVENT					_at_ MEM_SYSCTRL+0x05;


//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0100 ~ 0x01FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
XBYTE   USB_PD_REG_P0[0xF0]         _at_ 0x100;
//-----------------------------------------------------------------------------
#define USBA_MemBase                0x01F0
XBYTE   DBG1_EJ898A_CMD             _at_ USBA_MemBase+0x00;
XBYTE   DBG1_EJ898A_DATA            _at_ USBA_MemBase+0x01;
XBYTE   DBG1_EJ898A_START           _at_ USBA_MemBase+0x02;
XBYTE   DBG1_EJ898A_STATUS          _at_ USBA_MemBase+0x03;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0200 ~ 0x02FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
XBYTE   USB_PD_REG_P1[0x8D]         _at_ 0x200;
//-----------------------------------------------------------------------------
#define USBC_MemBase                0x0290
XBYTE   I2C_EJ898A_EEPROM_VER       _at_ USBC_MemBase+0x00;
XBYTE   I2C_EJ898A_INITIAL          _at_ USBC_MemBase+0x01;
XBYTE   I2C_EJ898A_GET_VER_OK       _at_ USBC_MemBase+0x02;
XBYTE   I2C_EJ898A_NEW_VER          _at_ USBC_MemBase+0x03;
XBYTE   I2C_EJ898A_OFFSET[2]        _at_ USBC_MemBase+0x04;
XBYTE   I2C_EJ898A_DATA[2]          _at_ USBC_MemBase+0x06;
XBYTE   I2C_EJ898A_STEP             _at_ USBC_MemBase+0x08;
XBYTE   I2C_EJ898A_RX_DR_SWAP       _at_ USBC_MemBase+0x09;
XBYTE   I2C_EJ898A_LAST_REG_DDH     _at_ USBC_MemBase+0x0A;
XBYTE   I2C_EJ898A_PDC_DELAY        _at_ USBC_MemBase+0x0B;
XBYTE   I2C_EJ898A_PDC_COUNTER      _at_ USBC_MemBase+0x0C;
XBYTE   I2C_EJ898A_RETRY            _at_ USBC_MemBase+0x0D;
XBYTE   I2C_EJ898A_ERROR            _at_ USBC_MemBase+0x0E;
XBYTE   I2C_EJ898A_DEBUG            _at_ USBC_MemBase+0x0F;
XBYTE   I2C_EJ898A_POLLING1         _at_ USBC_MemBase+0x10;
XBYTE   I2C_EJ898A_POLLING2         _at_ USBC_MemBase+0x11;

XBYTE   I2C_EJ898A_RX_PR_SWAP       _at_ USBC_MemBase+0x12;
XBYTE   I2C_EJ898A_PR_SWAP_DELAY    _at_ USBC_MemBase+0x13;
XBYTE   I2C_EJ898A_PD_CONTRACT_HI   _at_ USBC_MemBase+0x14;
XBYTE   I2C_EJ898A_PD_CONTRACT_LO   _at_ USBC_MemBase+0x15;

XBYTE   I2C_EJ898A_RCV_PDO_NUM      _at_ USBC_MemBase+0x16;
XBYTE   I2C_EJ898A_RCV_PDO_DIR      _at_ USBC_MemBase+0x17;
XBYTE   I2C_EJ898A_TPD_SNK_RDO      _at_ USBC_MemBase+0x18;
XBYTE   I2C_EJ898A_PDO_DATA0        _at_ USBC_MemBase+0x19;
XBYTE   I2C_EJ898A_PDO_DATA1        _at_ USBC_MemBase+0x1A;
XBYTE   I2C_EJ898A_PDO_DATA2        _at_ USBC_MemBase+0x1B;
XBYTE   I2C_EJ898A_PDO_DATA3        _at_ USBC_MemBase+0x1C;
XBYTE   I2C_EJ898A_ATTENCTION_INT   _at_ USBC_MemBase+0x1D;
XBYTE   I2C_EJ898A_PD_HI_DELAY      _at_ USBC_MemBase+0x1E;
XBYTE   I2C_EJ898A_PD_RECHECK_05    _at_ USBC_MemBase+0x1F;
//-----------------------------------------------------------------------------
XWORD   wEJ898A_VBUS_Voltage        _at_ USBC_MemBase+0x20;
XWORD   wEJ898A_RDO_Current         _at_ USBC_MemBase+0x22;
XWORD   wEJ898A_PDO_Select_Voltage  _at_ USBC_MemBase+0x24;
XWORD   wEJ898A_PDO_Select_Current  _at_ USBC_MemBase+0x26;
XWORD   wEJ898A_Max_PDO_Voltage     _at_ USBC_MemBase+0x28;
XWORD   wEJ898A_Request_Current     _at_ USBC_MemBase+0x2A;
XWORD   wEJ898A_PDO_Sel_V_m10       _at_ USBC_MemBase+0x2C;
XWORD   wEJ898A_PDO_Sel_I_m10       _at_ USBC_MemBase+0x2E;
//-----------------------------------------------------------------------------
XWORD   wEJ898A_I2C_EJ898A_DELAY    _at_ USBC_MemBase+0x30;
XBYTE   I2C_EJ898A_PR_SWAP_RETRY    _at_ USBC_MemBase+0x32;

XBYTE   I2C_EJ898A_DISCOVER_MODE    _at_ USBC_MemBase+0x3B;
XWORD   wEJ898A_PDO_Sel_W_m10       _at_ USBC_MemBase+0x3C; //[02CC]
XBYTE   I2C_EJ898A_PD_WATT          _at_ USBC_MemBase+0x3E;
XBYTE   I2C_EJ898A_FLAG             _at_ USBC_MemBase+0x3F;
//-----------------------------------------------------------------------------
#define MIXA_MemBase                0x02E0
XWORD   DLY_S3_S4                   _at_ MIXA_MemBase+0x00;
XWORD   USBC_LoopTimer              _at_ MIXA_MemBase+0x02;
XWORD   LED_FLASH_CNT               _at_ MIXA_MemBase+0x04;
XBYTE   LED_OFF_CNT                 _at_ MIXA_MemBase+0x06;
XBYTE   S5_STATE_FLG                _at_ MIXA_MemBase+0x07;

XBYTE   I2C_EJ898A_REQ_DIR          _at_ MIXA_MemBase+0x0D;
XBYTE   xEC_EJ898A_FW_VERSION2      _at_ MIXA_MemBase+0x0E;
XBYTE   P80_DEBUG_CODE              _at_ MIXA_MemBase+0x0F;
//-----------------------------------------------------------------------------
#define USBD_MemBase                0x02F0
XBYTE   DBG2_EJ898A_CMD             _at_ USBD_MemBase+0x00;
XBYTE   DBG2_EJ898A_DATA            _at_ USBD_MemBase+0x01;
XBYTE   DBG2_EJ898A_START           _at_ USBD_MemBase+0x02;
XBYTE   DBG2_EJ898A_STATUS          _at_ USBD_MemBase+0x03;

XBYTE   I2C_EJ898A_VCONN_SWAP       _at_ USBD_MemBase+0x08;
XBYTE   I2C_EJ898A_DP_AB_DELAY      _at_ USBD_MemBase+0x09;
XBYTE   I2C_EJ898A_DP_STATUS_INT    _at_ USBD_MemBase+0x0A;
XBYTE   I2C_EJ898A_ATTENCTION_LOCK  _at_ USBD_MemBase+0x0B;
XBYTE   I2C_EJ898A_ATTENCTION_CNT   _at_ USBD_MemBase+0x0C;
XBYTE   I2C_EJ898A_ATTENCTION_DLY   _at_ USBD_MemBase+0x0D;
XBYTE   I2C_EJ898A_NEED_REBOOT      _at_ USBD_MemBase+0x0E;
XBYTE   I2C_DD_Resend               _at_ USBD_MemBase+0x0F;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0300 ~ 0x03FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define SMBX_MemBase                0x0300
//-----------------------------------------------------------------------------
XBYTE   SMBA_CHN_STS                _at_ SMBX_MemBase+0x00;
XBYTE   SMBA_CHN_TIMER              _at_ SMBX_MemBase+0x01;
XBYTE   SMBA_DEV_DIR                _at_ SMBX_MemBase+0x02;
XBYTE   SMBA_CHN_CTL                _at_ SMBX_MemBase+0x03;
XBYTE   SMBA_CHN_CMD                _at_ SMBX_MemBase+0x04;
XBYTE   SMBA_BYTE_CNT               _at_ SMBX_MemBase+0x05;
XWORD   SMBA_DEV_MEM                _at_ SMBX_MemBase+0x06;
XBYTE   SMBA_ERR_STS[4]             _at_ SMBX_MemBase+0x08;
XBYTE   SMBA_DAT_CNT[4]             _at_ SMBX_MemBase+0x0C;
XBYTE   SMBB_CHN_STS                _at_ SMBX_MemBase+0x10;
XBYTE   SMBB_CHN_TIMER              _at_ SMBX_MemBase+0x11;
XBYTE   SMBB_DEV_DIR                _at_ SMBX_MemBase+0x12;
XBYTE   SMBB_CHN_CTL                _at_ SMBX_MemBase+0x13;
XBYTE   SMBB_CHN_CMD                _at_ SMBX_MemBase+0x14;
XBYTE   SMBB_BYTE_CNT               _at_ SMBX_MemBase+0x15;
XWORD   SMBB_DEV_MEM                _at_ SMBX_MemBase+0x16;
XBYTE   SMBB_ERR_STS[4]             _at_ SMBX_MemBase+0x18;
XBYTE   SMBB_DAT_CNT[4]             _at_ SMBX_MemBase+0x1C;
XBYTE   SMBC_CHN_STS                _at_ SMBX_MemBase+0x20;
XBYTE   SMBC_CHN_TIMER              _at_ SMBX_MemBase+0x21;
XBYTE   SMBC_DEV_DIR                _at_ SMBX_MemBase+0x22;
XBYTE   SMBC_CHN_CTL                _at_ SMBX_MemBase+0x23;
XBYTE   SMBC_CHN_CMD                _at_ SMBX_MemBase+0x24;
XBYTE   SMBC_BYTE_CNT               _at_ SMBX_MemBase+0x25;
XWORD   SMBC_DEV_MEM                _at_ SMBX_MemBase+0x26;
XBYTE   SMBC_ERR_STS[4]             _at_ SMBX_MemBase+0x28;
XBYTE   SMBC_DAT_CNT[4]             _at_ SMBX_MemBase+0x2C;
XBYTE   SMBD_CHN_STS                _at_ SMBX_MemBase+0x30;
XBYTE   SMBD_CHN_TIMER              _at_ SMBX_MemBase+0x31;
XBYTE   SMBD_DEV_DIR                _at_ SMBX_MemBase+0x32;
XBYTE   SMBD_CHN_CTL                _at_ SMBX_MemBase+0x33;
XBYTE   SMBD_CHN_CMD                _at_ SMBX_MemBase+0x34;
XBYTE   SMBD_BYTE_CNT               _at_ SMBX_MemBase+0x35;
XWORD   SMBD_DEV_MEM                _at_ SMBX_MemBase+0x36;
XBYTE   SMBD_ERR_STS[4]             _at_ SMBX_MemBase+0x38;
XBYTE   SMBD_DAT_CNT[4]             _at_ SMBX_MemBase+0x3C;


//-----------------------------------------------------------------------------
#define GPID_MemBase                0x0340
XBYTE   DebounceGPI1                _at_ GPID_MemBase+0x00;
XBYTE   DebounceGPI2                _at_ GPID_MemBase+0x01;
XBYTE   DebounceGPI3                _at_ GPID_MemBase+0x02;
XBYTE   ViberatorTimer              _at_ GPID_MemBase+0x03;
XBYTE   DebounceGPI4                _at_ GPID_MemBase+0x04;
XBYTE   DebounceGPI5                _at_ GPID_MemBase+0x05;
XBYTE   DebounceGPI6                _at_ GPID_MemBase+0x06;
XBYTE   DebounceGPIFlag             _at_ GPID_MemBase+0x07;
XBYTE   DebounceGPI8                _at_ GPID_MemBase+0x08;

//-----------------------------------------------------------------------------
#define SMBV_MemBase                0x0360
XBYTE   SMBA_DEV0_STS               _at_ SMBV_MemBase+0x00;
XBYTE   SMBA_DEV0_DIR               _at_ SMBV_MemBase+0x01;
XWORD   SMBA_DEV0_DLY               _at_ SMBV_MemBase+0x02;
XBYTE   SMBA_DEV1_STS               _at_ SMBV_MemBase+0x04;
XBYTE   SMBA_DEV1_DIR               _at_ SMBV_MemBase+0x05;
XWORD   SMBA_DEV1_DLY               _at_ SMBV_MemBase+0x06;
XBYTE   SMBB_DEV0_STS               _at_ SMBV_MemBase+0x08;
XBYTE   SMBB_DEV0_DIR               _at_ SMBV_MemBase+0x09;
XWORD   SMBB_DEV0_DLY               _at_ SMBV_MemBase+0x0A;
XBYTE   SMBB_DEV1_STS               _at_ SMBV_MemBase+0x0C;
XBYTE   SMBB_DEV1_DIR               _at_ SMBV_MemBase+0x0D;
XWORD   SMBB_DEV1_DLY               _at_ SMBV_MemBase+0x0E;
XBYTE   SMBC_DEV0_STS               _at_ SMBV_MemBase+0x10;
XBYTE   SMBC_DEV0_DIR               _at_ SMBV_MemBase+0x11;
XWORD   SMBC_DEV0_DLY               _at_ SMBV_MemBase+0x12;
XBYTE   SMBC_DEV1_STS               _at_ SMBV_MemBase+0x14;
XBYTE   SMBC_DEV1_DIR               _at_ SMBV_MemBase+0x15;
XWORD   SMBC_DEV1_DLY               _at_ SMBV_MemBase+0x16;
XWORD   SMBA_DEV2_DLY               _at_ SMBV_MemBase+0x18;
//-----------------------------------------------------------------------------
#define ADCC_MemBase                0x0380
XWORD   wADC[8]                     _at_ ADCC_MemBase + 0x00;
XBYTE   xADC[8]                     _at_ ADCC_MemBase + 0x10;

XBYTE   xEC_T1_CNT                  _at_ ADCC_MemBase + 0x18;
XBYTE   xEC_T2_CNT                  _at_ ADCC_MemBase + 0x19;

XBYTE   xEC_T1_AVG                  _at_ ADCC_MemBase + 0x20;
XBYTE   xEC_T1_HiLimit              _at_ ADCC_MemBase + 0x21;
XBYTE   xEC_T1_LoLimit              _at_ ADCC_MemBase + 0x22;
XBYTE   xEC_T1_THR                  _at_ ADCC_MemBase + 0x23;
XBYTE   xEC_T1_EventTimer           _at_ ADCC_MemBase + 0x24;
XBYTE   xEC_T1_SendEvent            _at_ ADCC_MemBase + 0x25;
XWORD   wEC_T1_THR_ACC              _at_ ADCC_MemBase + 0x26;

XBYTE   xEC_T2_AVG                  _at_ ADCC_MemBase + 0x28;
XBYTE   xEC_T2_HiLimit              _at_ ADCC_MemBase + 0x29;
XBYTE   xEC_T2_LoLimit              _at_ ADCC_MemBase + 0x2A;
XBYTE   xEC_T2_THR                  _at_ ADCC_MemBase + 0x2B;
XBYTE   xEC_T2_EventTimer           _at_ ADCC_MemBase + 0x2C;
XBYTE   xEC_T2_SendEvent            _at_ ADCC_MemBase + 0x2D;
XWORD   wEC_T2_THR_ACC              _at_ ADCC_MemBase + 0x2E;

//-----------------------------------------------------------------------------
#define PECI_MemBase                0x03B0
XBYTE   PECI_FLAG                   _at_ PECI_MemBase + 0x00;
XBYTE   PECI_CMD                    _at_ PECI_MemBase + 0x01;
XBYTE   PECI_CompletionCode         _at_ PECI_MemBase + 0x02;
XBYTE   PECI_TIMER                  _at_ PECI_MemBase + 0x03;
XBYTE   PECI_ERRCNT                 _at_ PECI_MemBase + 0x04;
XBYTE   PECI_ERRSTS                 _at_ PECI_MemBase + 0x05;
XBYTE   PECI_OVTCT                  _at_ PECI_MemBase + 0x06;
XBYTE   PECI_CRC8                   _at_ PECI_MemBase + 0x07;
XBYTE   PECI_CPU_T                  _at_ PECI_MemBase + 0x08;

XBYTE   PECI_DIR                    _at_ PECI_MemBase + 0x0B;
XWORD   PECI_DELAY                  _at_ PECI_MemBase + 0x0C;
XWORD   PECI_MEMADR                 _at_ PECI_MemBase + 0x0E;
XBYTE   PECI_GetDIB[8]              _at_ PECI_MemBase + 0x10;
XBYTE   PECI_GetTemp[2]             _at_ PECI_MemBase + 0x18;
XBYTE   PECI_RdPkgCfg_Idx16_CC      _at_ PECI_MemBase + 0x1A;
XBYTE   PECI_RdPkgCfg_Idx16[5]      _at_ PECI_MemBase + 0x1B;
XBYTE   PECI_ReadBuffer[16]         _at_ PECI_MemBase + 0x20;
XBYTE   PECI_WriteBuffer[16]        _at_ PECI_MemBase + 0x30;

XBYTE   PECI_PowerUnit              _at_ PECI_MemBase + 0x40;
XBYTE   PECI_EnergyUnit             _at_ PECI_MemBase + 0x41;
XBYTE   PECI_TimeUnit               _at_ PECI_MemBase + 0x42;
XWORD   PECI_UnitPower              _at_ PECI_MemBase + 0x43;
XBYTE   PECI_PowerLimit1            _at_ PECI_MemBase + 0x45;
XBYTE   PECI_PowerLimit2            _at_ PECI_MemBase + 0x46;
XBYTE   CS_2C_CMD_PULL              _at_ PECI_MemBase + 0x47;


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0400 ~ 0x04FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define MEM_EC_SPACE                0x0400
XBYTE   xEC_MainVersion             _at_ MEM_EC_SPACE+0x00;
XBYTE   xEC_SubVersion              _at_ MEM_EC_SPACE+0x01;
XBYTE   xEC_TestVersion             _at_ MEM_EC_SPACE+0x02;
XBYTE   I2C_EJ898A_CODING_VER       _at_ MEM_EC_SPACE+0x03;



XBYTE   xEC_ThermalChargCMD         _at_ MEM_EC_SPACE+0x20;
XBYTE   xEC_ThermalChargFlag        _at_ MEM_EC_SPACE+0x21;

XBYTE   xEC_SensorT_Error_F          _at_ MEM_EC_SPACE+0x30;


XBYTE	xEC_RTC_WakeupFlag			 _at_ MEM_EC_SPACE+0x42;
XBYTE	xEC_RTC_SupportFlag			 _at_ MEM_EC_SPACE+0x43;
XWORD	xEC_RTC_Wakeuptimer			 _at_ MEM_EC_SPACE+0x44;
XWORD   xEC_Forece_Shutdown_counter  _at_ MEM_EC_SPACE+0x47;
XWORD   xEC_RTC_test_counter		_at_ MEM_EC_SPACE+0x49;



XWORD   xEC_Charge_Rate             _at_ MEM_EC_SPACE+0x50;
XWORD   xEC_Charge_InCurrent        _at_ MEM_EC_SPACE+0x52;
XWORD   xEC_Charge_Vlot             _at_ MEM_EC_SPACE+0x54;
XWORD   xEC_Charge_option           _at_ MEM_EC_SPACE+0x56;

XBYTE   xEC_SYS_SKIN_T              _at_ MEM_EC_SPACE+0x62;
XBYTE   xEC_Sensor_F                _at_ MEM_EC_SPACE+0x63;
XBYTE   xEC_Sensor_TSHT             _at_ MEM_EC_SPACE+0x64;
XBYTE   xEC_Sensor_TSLT             _at_ MEM_EC_SPACE+0x65;
XBYTE   xEC_ThermalSource           _at_ MEM_EC_SPACE+0x66;


XBYTE   xEC_PECI_CPU_T              _at_ MEM_EC_SPACE+0x70;
XBYTE   xEC_PLMX_T                  _at_ MEM_EC_SPACE+0x71;
XBYTE   xEC_CHARGER_T               _at_ MEM_EC_SPACE+0x72;
XBYTE   xEC_LID_STATUS              _at_ MEM_EC_SPACE+0x7F;


XBYTE   xEC_PowerState              _at_ MEM_EC_SPACE+0x80;
XBYTE   xEC_Bt1ModelCode            _at_ MEM_EC_SPACE+0x81;
XBYTE   xEC_Bt1SerialNumberL        _at_ MEM_EC_SPACE+0x82;
XBYTE   xEC_Bt1SerialNumberH        _at_ MEM_EC_SPACE+0x83;
XBYTE   xEC_Bt1DesignCapacityL      _at_ MEM_EC_SPACE+0x84;
XBYTE   xEC_Bt1DesignCapacityH      _at_ MEM_EC_SPACE+0x85;
XBYTE   xEC_Bt1DesignVoltageL       _at_ MEM_EC_SPACE+0x86;
XBYTE   xEC_Bt1DesignVoltageH       _at_ MEM_EC_SPACE+0x87;
XBYTE   xEC_Bt1FullChrgCapacityL    _at_ MEM_EC_SPACE+0x88;
XBYTE   xEC_Bt1FullChrgCapacityH    _at_ MEM_EC_SPACE+0x89;
XBYTE   xEC_Bt1TripPointL           _at_ MEM_EC_SPACE+0x8A;
XBYTE   xEC_Bt1TripPointH           _at_ MEM_EC_SPACE+0x8B;
XBYTE   xEC_Bt1State                _at_ MEM_EC_SPACE+0x8C;
XBYTE   xEC_Bt1PresentRateL         _at_ MEM_EC_SPACE+0x8D;
XBYTE   xEC_Bt1PresentRateH         _at_ MEM_EC_SPACE+0x8E;
XBYTE   xEC_Bt1RemainCapacityL      _at_ MEM_EC_SPACE+0x8F;
XBYTE   xEC_Bt1RemainCapacityH      _at_ MEM_EC_SPACE+0x90;
XBYTE   xEC_Bt1PresentVoltageL      _at_ MEM_EC_SPACE+0x91;
XBYTE   xEC_Bt1PresentVoltageH      _at_ MEM_EC_SPACE+0x92;
XBYTE   xEC_BtRSOC                  _at_ MEM_EC_SPACE+0x93;



XBYTE	xEC_RTC_lastwakeup_counter_H	_at_ MEM_EC_SPACE+0xBD;
XBYTE	xEC_RTC_lastwakeup_counter_L	_at_ MEM_EC_SPACE+0xBE;

XBYTE   xEC_EJ898A_FW_VERSION       _at_ MEM_EC_SPACE+0xBF;

//-----------------------------------------------------------------------------
//-------------- USB TYPE C  (x04C0 ~ 0x4EF) ----------------------------------
//-----------------------------------------------------------------------------

XBYTE   xEC_USB_TC_MB_MGI0          _at_ MEM_EC_SPACE+0xC0;
XBYTE   xEC_USB_TC_MB_MGI1          _at_ MEM_EC_SPACE+0xC1;
XBYTE   xEC_USB_TC_MB_MGI2          _at_ MEM_EC_SPACE+0xC2;
XBYTE   xEC_USB_TC_MB_MGI3          _at_ MEM_EC_SPACE+0xC3;
XBYTE   xEC_USB_TC_MB_MGI4          _at_ MEM_EC_SPACE+0xC4;
XBYTE   xEC_USB_TC_MB_MGI5          _at_ MEM_EC_SPACE+0xC5;
XBYTE   xEC_USB_TC_MB_MGI6          _at_ MEM_EC_SPACE+0xC6;
XBYTE   xEC_USB_TC_MB_MGI7          _at_ MEM_EC_SPACE+0xC7;
XBYTE   xEC_USB_TC_MB_MGI8          _at_ MEM_EC_SPACE+0xC8;
XBYTE   xEC_USB_TC_MB_MGI9          _at_ MEM_EC_SPACE+0xC9;
XBYTE   xEC_USB_TC_MB_MGIA          _at_ MEM_EC_SPACE+0xCA;
XBYTE   xEC_USB_TC_MB_MGIB          _at_ MEM_EC_SPACE+0xCB;
XBYTE   xEC_USB_TC_MB_MGIC          _at_ MEM_EC_SPACE+0xCC;
XBYTE   xEC_USB_TC_MB_MGID          _at_ MEM_EC_SPACE+0xCD;
XBYTE   xEC_USB_TC_MB_MGIE          _at_ MEM_EC_SPACE+0xCE;
XBYTE   xEC_USB_TC_MB_MGIF          _at_ MEM_EC_SPACE+0xCF;

XBYTE   xEC_USB_TC_MB_MGO0          _at_ MEM_EC_SPACE+0xD0;
XBYTE   xEC_USB_TC_MB_MGO1          _at_ MEM_EC_SPACE+0xD1;
XBYTE   xEC_USB_TC_MB_MGO2          _at_ MEM_EC_SPACE+0xD2;
XBYTE   xEC_USB_TC_MB_MGO3          _at_ MEM_EC_SPACE+0xD3;
XBYTE   xEC_USB_TC_MB_MGO4          _at_ MEM_EC_SPACE+0xD4;
XBYTE   xEC_USB_TC_MB_MGO5          _at_ MEM_EC_SPACE+0xD5;
XBYTE   xEC_USB_TC_MB_MGO6          _at_ MEM_EC_SPACE+0xD6;
XBYTE   xEC_USB_TC_MB_MGO7          _at_ MEM_EC_SPACE+0xD7;
XBYTE   xEC_USB_TC_MB_MGO8          _at_ MEM_EC_SPACE+0xD8;
XBYTE   xEC_USB_TC_MB_MGO9          _at_ MEM_EC_SPACE+0xD9;
XBYTE   xEC_USB_TC_MB_MGOA          _at_ MEM_EC_SPACE+0xDA;
XBYTE   xEC_USB_TC_MB_MGOB          _at_ MEM_EC_SPACE+0xDB;
XBYTE   xEC_USB_TC_MB_MGOC          _at_ MEM_EC_SPACE+0xDC;
XBYTE   xEC_USB_TC_MB_MGOD          _at_ MEM_EC_SPACE+0xDD;
XBYTE   xEC_USB_TC_MB_MGOE          _at_ MEM_EC_SPACE+0xDE;
XBYTE   xEC_USB_TC_MB_MGOF          _at_ MEM_EC_SPACE+0xDF;

XBYTE   xEC_USB_TC_UCSI_DATA_VER1   _at_ MEM_EC_SPACE+0xE0;
XBYTE   xEC_USB_TC_UCSI_DATA_VER2   _at_ MEM_EC_SPACE+0xE1;
XBYTE   xEC_USB_TC_UCSI_DATA_RSV1   _at_ MEM_EC_SPACE+0xE2;
XBYTE   xEC_USB_TC_UCSI_DATA_RSV2   _at_ MEM_EC_SPACE+0xE3;

XBYTE   xEC_USB_TC_CCI0             _at_ MEM_EC_SPACE+0xE4;
XBYTE   xEC_USB_TC_CCI1             _at_ MEM_EC_SPACE+0xE5;
XBYTE   xEC_USB_TC_CCI2             _at_ MEM_EC_SPACE+0xE6;
XBYTE   xEC_USB_TC_CCI3             _at_ MEM_EC_SPACE+0xE7;

XBYTE   xEC_USB_TC_CTL0             _at_ MEM_EC_SPACE+0xE8;
XBYTE   xEC_USB_TC_CTL1             _at_ MEM_EC_SPACE+0xE9;
XBYTE   xEC_USB_TC_CTL2             _at_ MEM_EC_SPACE+0xEA;
XBYTE   xEC_USB_TC_CTL3             _at_ MEM_EC_SPACE+0xEB;
XBYTE   xEC_USB_TC_CTL4             _at_ MEM_EC_SPACE+0xEC;
XBYTE   xEC_USB_TC_CTL5             _at_ MEM_EC_SPACE+0xED;
XBYTE   xEC_USB_TC_CTL6             _at_ MEM_EC_SPACE+0xEE;
XBYTE   xEC_USB_TC_CTL7             _at_ MEM_EC_SPACE+0xEF;

XBYTE   xEC_USB_PD_STS_DD           _at_ MEM_EC_SPACE+0xF0;
XBYTE   xEC_USB_PD_STS_4            _at_ MEM_EC_SPACE+0xF1;
XBYTE   xEC_USB_PD_STS_5            _at_ MEM_EC_SPACE+0xF2;
XBYTE   xEC_USB_PD_STS_E            _at_ MEM_EC_SPACE+0xF3;
XBYTE   xEC_USB_PD_STS_10           _at_ MEM_EC_SPACE+0xF4;
XBYTE   xEC_USB_PD_STS_11           _at_ MEM_EC_SPACE+0xF5;
XBYTE   xEC_ShutdownCode            _at_ MEM_EC_SPACE+0xFD;
XBYTE   xEC_EJ898A_NEED_REBOOT      _at_ MEM_EC_SPACE+0xFE;
XBYTE   xEC_EJ898A_ERROR            _at_ MEM_EC_SPACE+0xFF;
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0500 ~ 0x05FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define BAT1_MemBase                0x0500
XWORD   BAT1_ManufacturerAccess     _at_ BAT1_MemBase+0x00;
XWORD   BAT1_BatteryMode            _at_ BAT1_MemBase+0x02;
XWORD   BAT1_Temperature            _at_ BAT1_MemBase+0x04;
XWORD   BAT1_Voltage                _at_ BAT1_MemBase+0x06;
XWORD   BAT1_Current                _at_ BAT1_MemBase+0x08;
XWORD   BAT1_AverageCurrent         _at_ BAT1_MemBase+0x0A;
XWORD   BAT1_MaxError               _at_ BAT1_MemBase+0x0C;
XBYTE   BAT1_RelativeStateOfChg     _at_ BAT1_MemBase+0x0E;
XBYTE   BAT1_RelativeStateOfChgL    _at_ BAT1_MemBase+0x0F;
XWORD   BAT1_AbsoluteOfCharge       _at_ BAT1_MemBase+0x10;
XWORD   BAT1_RemainingCapacity      _at_ BAT1_MemBase+0x12;
XWORD   BAT1_FullChargeCapacity     _at_ BAT1_MemBase+0x14;
XWORD   BAT1_ChargingCurrent        _at_ BAT1_MemBase+0x16;
XWORD   BAT1_ChargingVoltage        _at_ BAT1_MemBase+0x18;
XWORD   BAT1_BatteryStatus1         _at_ BAT1_MemBase+0x1A;
XWORD   BAT1_CycleCount             _at_ BAT1_MemBase+0x1C;
XWORD   BAT1_DesignCapacity         _at_ BAT1_MemBase+0x1E;
XWORD   BAT1_DesignVoltage          _at_ BAT1_MemBase+0x20;
XWORD   BAT1_SpecificationInfo      _at_ BAT1_MemBase+0x22;
XWORD   BAT1_ManufactureDate        _at_ BAT1_MemBase+0x24;
XWORD   BAT1_SerialNumber           _at_ BAT1_MemBase+0x26;
XBYTE   BAT1_ManufacturerName[14]   _at_ BAT1_MemBase+0x28;
XBYTE   BAT1_DeviceName[14]         _at_ BAT1_MemBase+0x37;
XBYTE   BAT1_DeviceChemistry[6]     _at_ BAT1_MemBase+0x45;
XBYTE   BAT1_ManufacturerData[14]   _at_ BAT1_MemBase+0x4B;
XBYTE   BAT1_PACKAGE                _at_ BAT1_MemBase+0x59;
XWORD   BAT1_BatteryStatus2         _at_ BAT1_MemBase+0x5A;
XWORD   BAT1_BatteryStatus          _at_ BAT1_MemBase+0x5C;
XBYTE   BAT1_LockPowerOnRSOC        _at_ BAT1_MemBase+0x5E;
XBYTE   BAT1_NoOCPTimer             _at_ BAT1_MemBase+0x5F;
XBYTE   BAT1_LastRSOC               _at_ BAT1_MemBase+0x60;
//XWORD   BAT1_LastBTP                _at_ BAT1_MemBase+0x61;
XWORD   BAT1_LastFCC                _at_ BAT1_MemBase+0x61;

XBYTE   BAT1_Low_ShutdownCount      _at_ BAT1_MemBase+0x63;

XBYTE   BAT1_Counter1               _at_ BAT1_MemBase+0x69;
XBYTE   BAT1_ChargePauseTimer       _at_ BAT1_MemBase+0x6A;
XBYTE   BAT1_THROT_DIR              _at_ BAT1_MemBase+0x6B;
XWORD   BAT1_THROT_DNT              _at_ BAT1_MemBase+0x6C;
XWORD   BAT1_THROT_UPT              _at_ BAT1_MemBase+0x6E;
//-----------------------------------------------------------------------------
#define ACBT_MemBase                0x0570
XBYTE   xEC_PowerSource             _at_ ACBT_MemBase+0x00;
XBYTE   PowerSource                 _at_ ACBT_MemBase+0x01;
XBYTE   Debounce_ACin               _at_ ACBT_MemBase+0x02;
XBYTE   Debounce_Bt1In              _at_ ACBT_MemBase+0x03;
XBYTE   Debounce_Bt2In              _at_ ACBT_MemBase+0x04;
XBYTE   SendBatEventTimer           _at_ ACBT_MemBase+0x05;
XBYTE   SendACiEventTimer           _at_ ACBT_MemBase+0x06;
XBYTE   PowPgmScan                  _at_ ACBT_MemBase+0x07;

XBYTE   SMBA_FloatingTimer          _at_ ACBT_MemBase+0x09;
XBYTE   BatteryDetectStep           _at_ ACBT_MemBase+0x0A;
XBYTE   BatteryDetectRetry          _at_ ACBT_MemBase+0x0B;
XWORD   wBatteryDetectTmr           _at_ ACBT_MemBase+0x0C;
XBYTE   EventTestTimer              _at_ ACBT_MemBase+0x0E;
XBYTE   EventTestNumber             _at_ ACBT_MemBase+0x0F;
//-----------------------------------------------------------------------------
#define Thermal_MemBase             0x0580

XBYTE   SkinTripFlag                _at_ BAT1_MemBase+0x94;

XBYTE   xEC_Sensor_TSHT_New         _at_ BAT1_MemBase+0x98;
XBYTE   xEC_Sensor_TSLT_New         _at_ BAT1_MemBase+0x99;
XBYTE   xEC_Sensor_TSHT_Send        _at_ BAT1_MemBase+0x9A;
XBYTE   xEC_Sensor_TSLT_Send        _at_ BAT1_MemBase+0x9B;

//-----------------------------------------------------------------------------
#define CPUT_MemBase                0x05D0
XBYTE   xEC_CPUT_HiLimit            _at_ CPUT_MemBase+0x00;
XBYTE   xEC_CPUT_LoLimit            _at_ CPUT_MemBase+0x01;
XBYTE   xEC_CPUT_EventTimer         _at_ CPUT_MemBase+0x02;
XBYTE   xEC_CPUT_SendEvent          _at_ CPUT_MemBase+0x03;

//-----------------------------------------------------------------------------
#define PWDM_MemBase                0x05E0
XWORD   wPowerSavingDelay           _at_ PWDM_MemBase+0x00;
XBYTE   PowerSavingCount            _at_ PWDM_MemBase+0x02;

XWORD   BAT1_ChargingCurrentLast    _at_ PWDM_MemBase+0x06;
XWORD   USBC_ChargingCurrentLast    _at_ PWDM_MemBase+0x08;
XWORD   USBC_InputCurrent           _at_ PWDM_MemBase+0x0A;
XWORD   USBC_ChargingCurrent        _at_ PWDM_MemBase+0x0C;
XWORD   USBC_ChargingVoltage        _at_ PWDM_MemBase+0x0E;
//-----------------------------------------------------------------------------
#define CHGR_MemBase                0x05F0
XWORD   CHGR_ChargerOption          _at_ CHGR_MemBase+0x00;
XWORD   CHGR_InputCurrent           _at_ CHGR_MemBase+0x02;
XWORD   CHGR_ChargingCurrent        _at_ CHGR_MemBase+0x04;
XWORD   CHGR_ChargingVoltage        _at_ CHGR_MemBase+0x06;
XWORD   CHGR_ManufacturerID         _at_ CHGR_MemBase+0x08;
XWORD   CHGR_DeviceID               _at_ CHGR_MemBase+0x0A;
XWORD   CHGR_ChargerREG3E           _at_ CHGR_MemBase+0x0C;
XBYTE   WakeUpChargeTimer           _at_ CHGR_MemBase+0x0E;
XBYTE   SW_DN                       _at_ CHGR_MemBase+0x0F;
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
/* 256 bytes SPI read/write buffer */
XBYTE   SPIBuffer[256]              _at_ (OEMRAM8+0x00);
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0900 ~ 0x09FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
XBYTE   P80_RAM_9[256]		_at_ 0x0900;

/* Cache DMA for Windows Flash */
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0A00 ~ 0x0AFF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
XBYTE   EJ898A_DEBUG_A[256]         _at_ 0x0A00;
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0B00 ~ 0x0BFF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
XBYTE   EJ898A_DEBUG_B[256]         _at_ 0x0B00;
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0C00 ~ 0x0CFF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
XBYTE   EJ898A_RAM_C[256]           _at_ 0x0C00;
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0D00 ~ 0x0DFF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
XBYTE   EJ898A_RAM_D[256]           _at_ 0x0D00;
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0E00 ~ 0x0EFF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
/* [X] IT8527E */
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0F00 ~ 0x0FFF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
/* [X] IT8527E */
//-----------------------------------------------------------------------------

XBYTE	P80_RAM_F[256]			_at_ 0x0F00;

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* BRAM                   (0x2200 ~ 0x22FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* FUNCTION CALL AREA ********************************************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - Clear_Memory_Range
 * @function - Clear Memory Range
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Clear_Memory_Range(WORD nAddr, WORD nSize)
{
    Tmp_XPntr = (unsigned int *)nAddr;
    for (ITempW01 = 0; ITempW01 <= nSize; ITempW01++)
    {
        *Tmp_XPntr = 0;
        Tmp_XPntr++;
    }
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_MEMORY.C */
