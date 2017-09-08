/*-----------------------------------------------------------------------------
 * @file     | B0_SMBUS.H
 *-----------+-----------------------------------------------------------------
 * @function | B0_SMBUS.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef B0_SMBUS_H
#define B0_SMBUS_H


/*-----------------------------------------------------------------------------
 * Devices Address Definition
 *---------------------------------------------------------------------------*/
#define _I2C_EJ898A_Addr            0xC0
#define _I2C_EEPROM_Addr            0xA0


/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
#define _SMB_CH0                    0x00
#define _SMB_CH1                    0x01
#define _SMB_CH2                    0x02
#define _SMB_CH3                    0x03
#define _SMBA_CHN                   0x00
#define _SMBB_CHN                   0x04
#define _SMBC_CHN                   0x08
#define _SMBD_CHN                   0x0C
#define _SMB_DEV0                   0x00
#define _SMB_DEV1                   0x01
#define _SMB_DEV2                   0x02
#define _SMB_DEV3                   0x03
#define _SMB_ON                     0x01
#define _SMB_OFF                    0x00
#define _SMBC_CHN2                  0x0F
//-----------------------------------------------------------------------------
#define _SMB_QK_BYTE                0x40
#define _SMB_TX_BYTE                0x44
#define _SMB_RX_BYTE                0x45
#define _SMB_RD_BYTE                0x48
#define _SMB_WR_BYTE                0x49
#define _SMB_RD_WORD                0x4C
#define _SMB_WR_WORD                0x4D
#define _SMB_RD_BLCK                0x54
#define _SMB_WR_BLCK                0x55
//-----------------------------------------------------------------------------
#define _SMbusEXT                   0x1C    // Extend command
#define _SMBusPEC                   0x01
#define _SMBusNoPEC                 0x00
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * Reference Smart Battery Data Specification
 * The following definition summarizes the Smart Battery command set.
 *---------------------------------------------------------------------------*/
#define _SMB_BatteryAddr            0x16
#define _CMD_ManufacturerAccess     0x00
#define _CMD_RemainingCapacityAlarm 0x01
#define _CMD_RemainingTimeAlarm     0x02
#define _CMD_BatteryMode            0x03
#define _CMD_AtRate                 0x04
#define _CMD_AtRateTimeToFull       0x05
#define _CMD_AtRateTimeToEmpty      0x06
#define _CMD_AtRateOK               0x07
#define _CMD_Temperature            0x08
#define _CMD_Voltage                0x09
#define _CMD_Current                0x0A
#define _CMD_AverageCurrent         0x0B
#define _CMD_MaxError               0x0C
#define _CMD_RelativeStateOfCharge  0x0D
#define _CMD_AbsoluteStateOfCharge  0x0E
#define _CMD_RemainingCapacity      0x0F
#define _CMD_FullChargeCapacity     0x10
#define _CMD_RunTimeToEmpty         0x11
#define _CMD_AverageTimeToEmpty     0x12
#define _CMD_AverageTimeToFull      0x13
#define _CMD_ChargingCurrent        0x14
#define _CMD_ChargingVoltage        0x15
#define _CMD_BatteryStatus          0x16
#define _CMD_CycleCount             0x17
#define _CMD_DesignCapacity         0x18
#define _CMD_DesignVoltage          0x19
#define _CMD_SpecificationInfo      0x1A
#define _CMD_ManufactureDate        0x1B
#define _CMD_SerialNumber           0x1C
#define _CMD_ManufacturerName       0x20
#define _CMD_DeviceName             0x21
#define _CMD_DeviceChemistry        0x22
#define _CMD_ManufacturerData       0x23
#define _CMD_OptionalMfgFunction5   0x2F
#define _CMD_OptionalMfgFunction4   0x3C
#define _CMD_OptionalMfgFunction3   0x3D
#define _CMD_OptionalMfgFunction2   0x3E
#define _CMD_OptionalMfgFunction1   0x3F

#define _CMD_Cell_4                 0x3C
#define _CMD_Cell_3                 0x3D
#define _CMD_Cell_2                 0x3E
#define _CMD_Cell_1                 0x3F
#define _CMD_ManufacturerInfo       0x70

/*-----------------------------------------------------------------------------
 * Reference Smart Charger Specification
 *---------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
/* The bq24715/7 supports seven battery-charger commands */
/*
  0x12 ChargeOption() Read or Write
       Charger Options Control Default E144H
  0x14 ChargeCurrent() Read or Write
       7-Bit Charge Current Setting Default 0mA,64mA Step Range:128mA~8.128A
  0x15 MaxChargeVoltage() Read or Write
       11-Bit Charge Voltage Setting Default 2S-9V, 3S-13.5V, 4S-17.4V...
  0x3E MinSystemVoltage() Read or Write
       6-Bit Minimum System Voltage Setting Default 2S-6.144V, 3S-9.216V...
  0x3F InputCurrent() Read or Write
       7-Bit Input Current Setting Default 3.2A,64mA Step,Range:128mA-8.064A
  0xFE ManufacturerID() Read Only Manufacturer ID: 0x0040H
  0xFF DeviceID() Read Only Device ID 0x0010H (715) 0x0012H (717)
*/
#define _CMD_ChargerOption          0x12
#define _CMD_ChargerMinSysVoltage   0x3E
#define _CMD_ChargerInputCurrent    0x3F
#define _CMD_ChargerManufacturerID  0xFE
#define _CMD_ChargerDeviceID        0xFF
#define _CMD_ChargerREG3E           0x3E
#define _CMD_MinSystemVoltage       0x3E

/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/
typedef struct RSmbusStruct
{
    BYTE    address;
    BYTE    cmd;
    XBYTE   *smbdata;

} sRSmbusStruct;
//-----------------------------------------------------------------------------
typedef struct EJ898PollStruct
{
    BYTE    Page;
    BYTE    Offset;

} sEJ898PollStruct;
//-----------------------------------------------------------------------------
typedef struct EJ898PDDataStruct
{
    BYTE    data0;
    BYTE    data1;
    BYTE    data2;
    BYTE    data3;

} sEJ898PDDataStruct;
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Hook_GetSMBusReadBlockByteCount(BYTE rblk_bc);
extern bit SMB_DataToMem(BYTE SMBX_ID, WORD SMBX_MEMADR,
                            BYTE SMBX_CTL, BYTE D0REG_X, BYTE D1REG_X);
extern void SMBA_SetToRegs(BYTE SMBA_DEVX_ADDR, BYTE DEVX_ID);
extern void SMBB_SetToRegs(BYTE SMBB_DEVX_ADDR, BYTE DEVX_ID);
extern void SMBC_SetToRegs(BYTE SMBC_DEVX_ADDR, BYTE DEVX_ID);

extern void SMBusA_ScanCenter(void);
extern void SMBusB_ScanCenter(void);

extern BYTE Service_USB_TypeC_PD(void);

extern void EJ898A_Initialize(void);
extern void EJ898A_Write_To_eFlash(void);

extern void EJ898A_Read_EEPROM(void);
extern void EJ898A_Write_EEPROM(void);
extern void EJ898A_Clear_EEPROM(void);
extern void EJ898A_Version_EEPROM(void);

extern void EJ898A_READ_REGISTER(void);
extern void EJ898A_READ_PD_REG_P0(BYTE OFFSET);
extern void EJ898A_READ_PD_REG_P1(BYTE OFFSET);

extern void EJ898A_WRITE_REGISTER(void);
extern void EJ898A_WRITE_PD_REG_P0(BYTE OFFSET, BYTE PDATA);

extern BYTE Polling_EJ898A_Register(void);
extern void Service_PD_REG_P0(BYTE cmd);
extern void EJ898A_WRITE_PD_REG_P1(BYTE OFFSET, BYTE PDATA);
extern void EJ898A_Received_VCONN_SWAP(void);

extern void DisableSmartCharger(void);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//-----------------------------------------------------------------------------
#endif  //B0_SMBUS_H
/*-----------------------------------------------------------------------------
 * End of B0_SMBUS.H */
