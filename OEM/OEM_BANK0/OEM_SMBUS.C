/*-----------------------------------------------------------------------------
 * @file     | OEM_SMBUS.C
 *-----------+-----------------------------------------------------------------
 * @function | OEM SMBus Data Service
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2015, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>


/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/
#define DEBUG_EJ898A_USB_PD             TRUE
#define SUPPORT_EJ898A_EEPROM_HOTFIX    FALSE
#define SUPPORT_EJ898A_PD_ADAPTER       TRUE
#define SUPPORT_EJ898A_PR_SWAP          TRUE

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_EJ898A_USB_PD
#define EJ898A_RamDebug(x)      RamDebug(x)
#else
#define EJ898A_RamDebug(x)      {}
#endif
//-----------------------------------------------------------------------------
#if SUPPORT_TYPE_C_SMBUS_B
#define _SMB_TYPE_C             _SMB_CH1
#else
#define _SMB_TYPE_C             _SMB_CH0
#endif
//-----------------------------------------------------------------------------


/*-----------------------------------------------------------------------------
 * @subroutine - Hook_GetSMBusReadBlockByteCount
 * @function - [rblk_bcis] the byte count of read smbus read block protocol
 * @Upstream - CORE_SMBUS.C
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Hook_GetSMBusReadBlockByteCount(BYTE rblk_bc)
{

}


/*-----------------------------------------------------------------------------
 * @subroutine - SMB_DataToMem
 * @function - SMBus data move to Memory
 * @upstream - SMBus_Channel_C() -> service_5mS_A
 * @input    - SMBX_ID, SMBX_MEMADR, SMBX_CTL, D0REG_X, D1REG_X
 * @return   - TRUE: All data finished
 *             FALSE: More data request (ex:block read)
 * @note     - None
 *---------------------------------------------------------------------------*/
bit SMB_DataToMem(BYTE SMBX_ID, WORD SMBX_MEMADR,
                    BYTE SMBX_CTL, BYTE D0REG_X, BYTE D1REG_X)
{
    BYTE    SMB_BLK_DAT;

    //-------------------------------------------------------------------------
    Tmp_XPntr = 0;
    Tmp_XPntr += SMBX_MEMADR;
    //-------------------------------------------------------------------------
    /* Read Byte/Word Data */
    if (SMBX_CTL == _SMB_RD_WORD)
    {
        *Tmp_XPntr = D1REG_X;
        Tmp_XPntr++;
        *Tmp_XPntr = D0REG_X;
        return TRUE;
    }
    if (SMBX_CTL == _SMB_RD_BYTE)
    {
        *Tmp_XPntr = D0REG_X;
        return TRUE;
    }
    //-------------------------------------------------------------------------
    if (SMBX_CTL != _SMB_RD_BLCK)
    {
        return TRUE;
    }
    //-------------------------------------------------------------------------
    /* Read Block Data */
    SMBX_ID &= 0x0C;    //Get Channel ID
    //-------------------------------------------------------------------------
    if (SMBX_ID == _SMBA_CHN)
    {
        SMB_BLK_DAT = HOBDB_A;
        if (SMBA_BYTE_CNT == 0)
        {
            SMBA_BYTE_CNT = D0REG_X;
            if (SMBA_BYTE_CNT > 32)
            {
                SMBA_BYTE_CNT = 32;
            }
        }
        *Tmp_XPntr = SMB_BLK_DAT;
        SMBA_DEV_MEM++;
        SMBA_BYTE_CNT--;
        if (SMBA_BYTE_CNT > 0)
        {
            if (SMBA_BYTE_CNT == 1)
            {
                HOCTL_A |= 0x20;
            }
            return FALSE;
        }
        return TRUE;
    }
    //-------------------------------------------------------------------------
    if (SMBX_ID == _SMBB_CHN)
    {
        SMB_BLK_DAT = HOBDB_B;
        if (SMBB_BYTE_CNT == 0)
        {
            SMBB_BYTE_CNT = D0REG_X;
            if (SMBB_BYTE_CNT > 32)
            {
                SMBB_BYTE_CNT = 32;
            }
        }
        *Tmp_XPntr = SMB_BLK_DAT;
        SMBB_DEV_MEM++;
        SMBB_BYTE_CNT--;
        if (SMBB_BYTE_CNT > 0)
        {
            if (SMBB_BYTE_CNT == 1)
            {
                HOCTL_B |= 0x20;
            }
            return FALSE;
        }
        return TRUE;
    }
    //-------------------------------------------------------------------------
    if (SMBX_ID == _SMBC_CHN)
    {
        SMB_BLK_DAT = HOBDB_C;
        if (SMBC_BYTE_CNT == 0)
        {
            SMBC_BYTE_CNT = D0REG_X;
            if (SMBC_BYTE_CNT > 32)
            {
                SMBC_BYTE_CNT = 32;
            }
        }
        *Tmp_XPntr = SMB_BLK_DAT;
        SMBC_DEV_MEM++;
        SMBC_BYTE_CNT--;
        if (SMBC_BYTE_CNT > 0)
        {
            if (SMBC_BYTE_CNT == 1)
            {
                HOCTL_C |= 0x20;
            }
            return FALSE;
        }
        return TRUE;
    }
    //-------------------------------------------------------------------------
    if (SMBX_ID == _SMBD_CHN)
    {
        SMB_BLK_DAT = HOBDB_D;
        if (SMBD_BYTE_CNT == 0)
        {
            SMBD_BYTE_CNT = D0REG_X;
            if (SMBD_BYTE_CNT > 32)
            {
                SMBD_BYTE_CNT = 32;
            }
        }
        *Tmp_XPntr = SMB_BLK_DAT;
        SMBD_DEV_MEM++;
        SMBD_BYTE_CNT--;
        if (SMBD_BYTE_CNT > 0)
        {
            if (SMBD_BYTE_CNT == 1)
            {
                HOCTL_D |= 0x20;
            }
            return FALSE;
        }
        return TRUE;
    }
    //-------------------------------------------------------------------------
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - SMBA_SetToRegs
 * @function - SMBusA registers control
 * @upstream - By call
 * @input    - SMBA_DEVX_ADDR, SMBX_ID
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SMBA_SetToRegs(BYTE SMBA_DEVX_ADDR, BYTE DEVX_ID)
{
    /* EC I2C Registers control. */
    HOCMD_A  = SMBA_CHN_CMD;
    TRASLA_A = SMBA_DEVX_ADDR;

    if (SMBA_CHN_CTL == _SMB_WR_WORD)
    {
        Tmp_XPntr = (unsigned int*)SMBA_DEV_MEM;
        D1REG_A = *Tmp_XPntr;
        Tmp_XPntr++;
        D0REG_A = *Tmp_XPntr;
    }
    else if (SMBA_CHN_CTL == _SMB_WR_BYTE)
    {
        Tmp_XPntr = (unsigned int*)SMBA_DEV_MEM;
        D0REG_A = *Tmp_XPntr;
    }
    /* Read or write direction. */
    if ((SMBA_CHN_CTL & 0x01) == 0)
    {
        TRASLA_A |= 0x01;
    }
    /* Start transimition. */
    HOCTL_A = (SMBA_CHN_CTL & 0xFC);
    SMBA_CHN_STS = (F_SMB_BUSY + _SMBA_CHN + DEVX_ID);
    SMBA_BYTE_CNT = 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - SMBB_SetToRegs
 * @function - SMBusB registers control
 * @upstream - By call
 * @input    - SMBB_DEVX_ADDR, SMBX_ID
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SMBB_SetToRegs(BYTE SMBB_DEVX_ADDR, BYTE DEVX_ID)
{
    /* EC I2C Registers control. */
    HOCMD_B  = SMBB_CHN_CMD;
    TRASLA_B = SMBB_DEVX_ADDR;

    if (SMBB_CHN_CTL == _SMB_WR_WORD)
    {
        Tmp_XPntr = (unsigned int*)SMBB_DEV_MEM;
        D1REG_B = *Tmp_XPntr;
        Tmp_XPntr++;
        D0REG_B = *Tmp_XPntr;
    }
    else if (SMBB_CHN_CTL == _SMB_WR_BYTE)
    {
        Tmp_XPntr = (unsigned int*)SMBB_DEV_MEM;
        D0REG_B = *Tmp_XPntr;
    }
    /* Read or write direction. */
    if ((SMBB_CHN_CTL & 0x01) == 0)
    {
        TRASLA_B |= 0x01;
    }
    /* Start transimition. */
    HOCTL_B = (SMBB_CHN_CTL & 0xFC);
    SMBB_CHN_STS = (F_SMB_BUSY + _SMBB_CHN + DEVX_ID);
    SMBB_BYTE_CNT = 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - SMBC_SetToRegs
 * @function - SMBusC registers control
 * @upstream - By call
 * @input    - SMBC_DEVX_ADDR, SMBX_ID
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SMBC_SetToRegs(BYTE SMBC_DEVX_ADDR, BYTE DEVX_ID)
{
    /* EC I2C Registers control. */
    HOCMD_C  = SMBC_CHN_CMD;
    TRASLA_C = SMBC_DEVX_ADDR;
    Tmp_XPntr = 0;
    if (SMBC_CHN_CTL == _SMB_WR_WORD)
    {
        Tmp_XPntr += SMBC_DEV_MEM;
        D1REG_C = *Tmp_XPntr;
        Tmp_XPntr++;
        D0REG_C = *Tmp_XPntr;
    }
    else if (SMBC_CHN_CTL == _SMB_WR_BYTE)
    {
        Tmp_XPntr += SMBC_DEV_MEM;
        D0REG_C = *Tmp_XPntr;
    }
    /* Read or write direction. */
    if ((SMBC_CHN_CTL & 0x01) == 0)
    {
        TRASLA_C |= 0x01;
    }
    /* Start transimition. */
    HOCTL_C = (SMBC_CHN_CTL & 0xFC);
    SMBC_CHN_STS = (F_SMB_BUSY + _SMBC_CHN + DEVX_ID);
    SMBC_BYTE_CNT = 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - SMBusA_ScanCenter
 * @function - SMBusA_ScanCenter();     //GPB.3_SMCLK0, GPB.4_SMDAT0
 * @upstream - Hook_Timer5msEvent
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SMBusA_ScanCenter(void)
{
    //-------------------------------------------------------------------------
    /* Check & Process Channel-1 data in. */
    //-------------------------------------------------------------------------
    if (SMBA_CHN_STS & F_SMB_BUSY)
    {
        if (((HOSTA_A & 0x1C) > 0) || (SMBA_CHN_TIMER > 20))
        {
            /* SMBus timeout or error. */
            if (SMBA_ERR_STS[SMBA_CHN_STS & 0x03] < 0xFF)
            {
                SMBA_ERR_STS[SMBA_CHN_STS & 0x03]++;
            }
            /* Clear H/W I2C Status */
            HOSTA_A = 0xFF;
            SMBA_CHN_STS = 0;
            SMBA_CHN_TIMER = 0;

        }
        else if ((HOSTA_A & 0x82) > 0)
        {
            /* SMBus Data in. */
            if (SMB_DataToMem((SMBA_CHN_STS & 0x0F), SMBA_DEV_MEM,
                            SMBA_CHN_CTL, D0REG_A, D1REG_A))
            {
                SMBA_CHN_STS = 0;
                SMBA_CHN_TIMER = 0;
            }
            SMBA_ERR_STS[SMBA_CHN_STS & 0x03] = 0;
            /* SMBus Data-In Counter */
            if (SMBA_DAT_CNT[SMBA_CHN_STS & 0x0F] < 255)
            {
                SMBA_DAT_CNT[SMBA_CHN_STS & 0x0F] += 1;
            }
            /* Clear H/W I2C Status */
            HOSTA_A = 0xFF;
        }
        else
        {
            SMBA_CHN_TIMER++;
        }
        return;
    }
    //-------------------------------------------------------------------------
    /* Device Service Hook. */
    //-------------------------------------------------------------------------
	//TESTSMBUSNODELAY================================================================
    if((IS_ADAPTER_IN())&&
		(IS_MASK_CLEAR(DBG2_EJ898A_STATUS,I2C_AC_ChargeNoDealy)))
    	{
			if(!(SMBA_DEV1_STS & F_DEV_INIT))
		    	{
				if (SMBA_DEV1_DLY > 0)
					{
						SMBA_DEV1_DLY--;
					}
					else
					{
						PollSmartCharger();
					}
				}
			else
				{
				SMBA_DEV1_DLY = 0;
				SMBA_DEV1_DIR = 0;
				SET_MASK(DBG2_EJ898A_STATUS,I2C_AC_ChargeNoDealy);
				}
    	}
	if(IS_ADAPTER_OUT())
		CLEAR_MASK(DBG2_EJ898A_STATUS,I2C_AC_ChargeNoDealy);
	//TESTSMBUSNODELAY=END==============================================================
    //-------------------------------------------------------------------------
    /* USB PD EJ898A need floating SMBus after power up */
    if (SMBA_FloatingTimer > 0)
    {
        SMBA_CHN_STS = 0;
        SMBA_DEV2_DLY = 0;
        return;
    }
    //-------------------------------------------------------------------------
#if 1   //SUPPORT_USB_TYPE_C_PD
    /* USB Type-C PD controller Service */
    if (SMBA_DEV2_DLY > 0)
    {
        SMBA_DEV2_DLY--;
    }
    else
    {
        if (Service_USB_TypeC_PD())
        {
            /* Next Loop Keep Service */
            SMBA_DEV2_DLY = 0;
            return;
        }
        else if (SMBA_DEV2_DLY == 0)
        {
            SMBA_DEV2_DLY = 25;
        }
        return;
    }
#endif
    //-------------------------------------------------------------------------
#if SUPPORT_SMART_CHARGER
    /* Smart Charger Service */
    if (SMBA_DEV1_DLY > 0)
    {
#if 0
        /* Fro quickly update ChargingCurrent when request are changed. */
        if (USBC_ChargingCurrent != USBC_ChargingCurrentLast)
        {
            USBC_ChargingCurrentLast = USBC_ChargingCurrent;
            SMBA_DEV1_DLY = 0;
        }
        else if (BAT1_ChargingCurrent != BAT1_ChargingCurrentLast)
        {
            BAT1_ChargingCurrentLast = BAT1_ChargingCurrent;
            SMBA_DEV1_DLY = 0;
        }
        else
        {
            SMBA_DEV1_DLY--;
        }
#else
        SMBA_DEV1_DLY--;
#endif
    }
    else
    {
        PollSmartCharger();
        if (SMBA_DEV1_DLY == 0)
        {
            SMBA_DEV1_DLY = 5;
        }
        if (IS_USBPD_INT_N_HI())
        {
            SMBA_DEV2_DLY = 0;
        }
        return;
    }
#endif
    //-------------------------------------------------------------------------
    /* Smart Battery Service */
    if (SMBA_DEV0_DLY > 0)
    {
        SMBA_DEV0_DLY--;
    }
    else
    {
        if (IS_MASK_SET(SMBA_DEV0_STS, F_DEV_ON_LINE))
        {
#if SUPPORT_SMART_BATTERY
            PollSmartBattery();
#endif
            if (SMBA_DEV0_DLY == 0)
            {
                SMBA_DEV0_DLY = 5;
            }
        }
    }
    //-------------------------------------------------------------------------
    if (IS_USBPD_INT_N_HI())
    {
        SMBA_DEV2_DLY = 0;
    }
    //-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// USB TYPE C SERVICE PROGRAM
// CHIP: ETRON EJ898A
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - Clear_EJ898A_INT_event
 * @function - Clear_EJ898A_INT_event
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Clear_EJ898A_INT_event(void)
{
    EJ898A_READ_PD_REG_P1(0x0C);
    ITempB03 = USB_PD_REG_P1[0x0C];
    ITempB03 &= (0xFF-BIT1);
    GPCRI2 = INPUT;
    EJ898A_WRITE_PD_REG_P1(0x0C, ITempB03);
    /* Clear all interrupt event. */
    EJ898A_WRITE_PD_REG_P0(0x0E, 0xFF); //(0xFF-BIT5));  // Clear Interrupt event
    EJ898A_WRITE_PD_REG_P0(0x10, 0xFF);         // Clear Interrupt event
    EJ898A_WRITE_PD_REG_P0(0x11, 0xFF);         // Clear Interrupt event
    EJ898A_WRITE_PD_REG_P0(0xDE, 0x17);         // Clear Interrupt event
    EJ898A_WRITE_PD_REG_P1(0x10, 0xFF);         // Clear Interrupt event
    EJ898A_WRITE_PD_REG_P1(0x11, 0xFF);         // Clear Interrupt event
    EJ898A_WRITE_PD_REG_P1(0x12, 0x01);         // Clear Interrupt event
    EJ898A_WRITE_PD_REG_P1(0x21, 0xDF);
    //EJ898A_WRITE_PD_REG_P0(0x9A, 0x02);
#if SUPPORT_EJ898A_PD_ADAPTER
    EJ898A_WRITE_PD_REG_P0(0x34, 0x96);
#endif
    I2C_EJ898A_ATTENCTION_LOCK = 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Clear_EJ898A_Status
 * @function - Clear_EJ898A_Status
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Clear_EJ898A_Status(void)
{
    /* Clear all process */
    Clear_Memory_Range(0x0100,0xEF);
    Clear_Memory_Range(0x0200,0xAF);
    I2C_EJ898A_FLAG = F_CABLE_DICONNECTED;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Process_PD_REG_80DDH
 * @function - Process_PD_REG_80DDH
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Process_PD_REG_80DDH(void)
{
#if 0
    if (USB_PD_REG_P0[0xDD] & BIT3)
    {
        if ((USB_PD_REG_P0[0xDD] & BIT6) != (xEC_USB_PD_STS_DD & BIT6))
        {
            /* If USB_PD_STS changed then send SCI_DD */
            WriteSCI_Buffer(0xDD);
            EJ898A_RamDebug(0xDD);
        }
    }
    xEC_USB_PD_STS_DD = USB_PD_REG_P0[0xDD];
#else
    if((USB_PD_REG_P0[0xDD] & BIT3) != (xEC_USB_PD_STS_DD & BIT3))
    {
        /* If USB_PD_STS changed then send SCI_DD */
        WriteSCI_Buffer(0xDD);
        EJ898A_RamDebug(0xDD);
    }
    xEC_USB_PD_STS_DD = USB_PD_REG_P0[0xDD];
    I2C_EJ898A_LAST_REG_DDH = USB_PD_REG_P0[0xDD];
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Process_PD_REG_800EH
 * @function - Process_PD_REG_800EH
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Process_PD_REG_800EH(void)
{
    if (USB_PD_REG_P0[0x0E] & F_CABLE_CONNECTED)
    {
        EJ898A_READ_PD_REG_P0(0xDD);
        Process_PD_REG_80DDH();
        EJ898A_WRITE_PD_REG_P0(0x0E, F_CABLE_CONNECTED);
        if (USB_PD_REG_P0[0xDD] & BIT3)
        {
            SET_MASK(I2C_EJ898A_FLAG, F_CABLE_CONNECTED);
            CLEAR_MASK(I2C_EJ898A_FLAG, F_CABLE_DICONNECTED);
            EJ898A_WRITE_PD_REG_P0(0xD0, 0xD7);
            EJ898A_RamDebug(0xC1);
            EJ898A_RamDebug(0xC1);
        }
        else
        {
            EJ898A_RamDebug(0xC2);
        }
    }
    else if (USB_PD_REG_P0[0x0E] & F_CABLE_DICONNECTED)
    {
        EJ898A_READ_PD_REG_P0(0xDD);
        Process_PD_REG_80DDH();
        EJ898A_WRITE_PD_REG_P0(0x0E, F_CABLE_DICONNECTED);
        if (!(USB_PD_REG_P0[0xDD] & BIT3))
        {
            CLEAR_MASK(I2C_EJ898A_FLAG, F_CABLE_CONNECTED);
            SET_MASK(I2C_EJ898A_FLAG, F_CABLE_DICONNECTED);
            USBC_ChargingCurrent = 0;
            USBC_ChargingVoltage = 0;
            EJ898A_WRITE_PD_REG_P0(0xD0, 0xC7);
            EJ898A_RamDebug(0xC0);
            EJ898A_RamDebug(0xC0);
        }
        else
        {
            EJ898A_RamDebug(0xC3);
        }
        Clear_EJ898A_INT_event();
        Clear_EJ898A_Status();
        //xEC_TYPEC_POUT_EN = 0x00;
        //EC_TYPEC_POUT_EN_LO();
    }
    else if (USB_PD_REG_P0[0x0E] & BIT3)
    {
        I2C_EJ898A_RX_DR_SWAP = 1;
        EJ898A_RamDebug(0xD1);
    }
    //else if (USB_PD_REG_P0[0x0E] & BIT4)
    //{
    //    I2C_EJ898A_VCONN_SWAP = 1;
    //    EJ898A_RamDebug(0x30);
    //    //EJ898A_Received_VCONN_SWAP();
    //}
}

/*-----------------------------------------------------------------------------
 * @subroutine - Polling_EJ898A_VBUS_Voltage
 * @function - Polling_EJ898A_VBUS_Voltage
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Polling_EJ898A_VBUS_Voltage(void)
{
    EJ898A_READ_PD_REG_P0(0x7D);
    ITempB03 = USB_PD_REG_P0[0x7D];
    ITempW01 = (WORD)(ITempB03 * 92);   //92 is better
    wEJ898A_VBUS_Voltage = ITempW01;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Polling_EJ898A_Register
 * @function - Polling_EJ898A_Register
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
BYTE Polling_EJ898A_Register(void)
{
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_POLLING2 > 10)
    {
        I2C_EJ898A_POLLING2 = 0;
        Polling_EJ898A_VBUS_Voltage();
        return FALSE;
    }
    //-------------------------------------------------------------------------
    // High Priority Polling
    if (I2C_EJ898A_POLLING1 == 0)
    {
        EJ898A_READ_PD_REG_P0(0x0E);
        if (I2C_EJ898A_ERROR == 0)
        {
            Process_PD_REG_800EH();
        }
        if (IS_MASK_SET(I2C_EJ898A_FLAG, F_CABLE_CONNECTED))
        {
            I2C_EJ898A_POLLING1 = 2;
                        I2C_EJ898A_POLLING2 = 0;
        }
        else
        {
            I2C_EJ898A_POLLING1 = 1;
        }
        return FALSE;
    }
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_POLLING1 == 1)
    {
        EJ898A_READ_PD_REG_P0(0xDD);
        Process_PD_REG_80DDH();
        if (USB_PD_REG_P0[0xDD] & BIT3)
        {
            I2C_EJ898A_FLAG = F_CABLE_CONNECTED;
            I2C_EJ898A_POLLING1 = 2;
        }
        else
        {
            I2C_EJ898A_POLLING1 = 0;
                        I2C_EJ898A_POLLING2++;
        }
        return FALSE;
    }
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_POLLING1 == 2)
    {
#if SUPPORT_EJ898A_PR_SWAP
        EJ898A_READ_PD_REG_P0(0x10);
        if (USB_PD_REG_P0[0x10] & BIT4)
        {
            // Clear Interrupt event
            EJ898A_WRITE_PD_REG_P0(0x10, BIT4);
            I2C_EJ898A_RX_PR_SWAP = 1;
            //CLEAR_MASK(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER);
            I2C_EJ898A_PR_SWAP_DELAY = 0;
            I2C_EJ898A_PD_HI_DELAY = 0;
            wEJ898A_I2C_EJ898A_DELAY = 0;
            EJ898A_RamDebug(0xB1);
            DisableSmartCharger();
            I2C_EJ898A_POLLING1 = 3;
            return TRUE;
        }
#endif  //SUPPORT_EJ898A_PR_SWAP
        I2C_EJ898A_POLLING1 = 3;
        return FALSE;
    }
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_POLLING1 == 3)
    {
        EJ898A_READ_PD_REG_P1(0x10);
        if (USB_PD_REG_P1[0x10] & BIT2)
        {
            I2C_EJ898A_POLLING1 = 3;
            I2C_EJ898A_DISCOVER_MODE = 1;
            EJ898A_RamDebug(0xF3);
            return TRUE;
        }
        if (USB_PD_REG_P1[0x10] & BIT3)
        {
            I2C_EJ898A_POLLING1 = 0;
            I2C_EJ898A_DP_AB_DELAY = 0;
            I2C_EJ898A_DP_STATUS_INT = 1;
            EJ898A_RamDebug(0xF1);
            return TRUE;
        }
        if (USB_PD_REG_P1[0x10] & BIT5)
        {
            I2C_EJ898A_POLLING1 = 0;
            I2C_EJ898A_ATTENCTION_INT = 1;
            EJ898A_RamDebug(0xA1);
            return TRUE;
        }
        I2C_EJ898A_POLLING1 = 4;
        return FALSE;
    }
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_POLLING1 == 4)
    {
        EJ898A_READ_PD_REG_P0(0x08);
        if (USB_PD_REG_P0[0x08] & BIT4)
        {
            I2C_EJ898A_POLLING1 = 5;
        }
        else
        {
            I2C_EJ898A_POLLING1 = 99;
        }
        return FALSE;
    }
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_POLLING1 == 5)
    {
        EJ898A_WRITE_PD_REG_P0(0x9A, 0x06);
        I2C_EJ898A_POLLING1 = 6;
        return FALSE;
    }
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_POLLING1 == 6)
    {
        EJ898A_READ_PD_REG_P0(0x6C);
        if (USB_PD_REG_P0[0x6C] & BIT1)
        {
            I2C_EJ898A_POLLING1 = 8;
            //EJ898A_RamDebug(0x1C);
        }
        else
        {
            I2C_EJ898A_POLLING1 = 7;
        }
        return FALSE;
    }
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_POLLING1 == 7)
    {
        EJ898A_WRITE_PD_REG_P0(0x9A, 0x02);
        I2C_EJ898A_POLLING1 = 99;
        return FALSE;
    }
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_POLLING1 == 8)
    {
        EJ898A_READ_PD_REG_P0(0x4F);
        if ((USB_PD_REG_P0[0x4F] & 0x0F) == 0x0B)
        {
            EJ898A_RamDebug(0x4F);
            EJ898A_RamDebug(USB_PD_REG_P0[0x4F]);
            EJ898A_RamDebug(0x1D);
            EJ898A_WRITE_PD_REG_P0(0x4C, 0x08);
            EJ898A_WRITE_PD_REG_P0(0x4D, 0x3C);
            EJ898A_WRITE_PD_REG_P0(0x9A, 0x02);
            I2C_EJ898A_POLLING1 = 99;
        }
        else
        {
            I2C_EJ898A_POLLING1 = 7;
        }
        return FALSE;
    }
    //-------------------------------------------------------------------------
#if SUPPORT_EJ898A_PD_ADAPTER
    if (IS_MASK_CLEAR(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER))
    {
        EJ898A_READ_PD_REG_P0(0x08);
        if (USB_PD_REG_P0[0x08] & BIT1)
        {
            I2C_EJ898A_PD_HI_DELAY = 0;
            if (I2C_EJ898A_PR_SWAP_DELAY < 200)
            {
                I2C_EJ898A_PR_SWAP_DELAY++;
            }
            else
            {
                I2C_EJ898A_PR_SWAP_DELAY = 0;
                SET_MASK(I2C_EJ898A_FLAG, F_MRD_IS_SOURCE);
                SET_MASK(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER);
                EJ898A_RamDebug(0x08);
                EJ898A_RamDebug(USB_PD_REG_P0[0x08]);
                //xEC_TYPEC_POUT_EN = 0x01;
                //EC_TYPEC_POUT_EN_HI();
            }
        }
        else
        {
            if (I2C_EJ898A_PD_HI_DELAY < 20)
            {
                I2C_EJ898A_PD_HI_DELAY++;
            }
            else
            {
                CLEAR_MASK(I2C_EJ898A_FLAG, F_MRD_IS_SOURCE);
                //EJ898A_RamDebug(0xD8);
                //EJ898A_RamDebug(I2C_EJ898A_PR_SWAP_DELAY);
                EJ898A_RamDebug(0x08);
                EJ898A_RamDebug(USB_PD_REG_P0[0x08]);
                I2C_EJ898A_PR_SWAP_DELAY = 0;
                //xEC_TYPEC_POUT_EN = 0x00;
                //EC_TYPEC_POUT_EN_LO();
                I2C_EJ898A_PD_CONTRACT_HI = 1;
                EJ898A_RamDebug(0xE1);
            }
        }
        return TRUE;
    }
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_POLLING1 == 99)
    {
        if (I2C_EJ898A_PD_RECHECK_05 > 0)
        {
            I2C_EJ898A_PD_RECHECK_05--;
            EJ898A_READ_PD_REG_P0(0x05);
            EJ898A_RamDebug(0x5A);
            EJ898A_RamDebug(USB_PD_REG_P0[0x05]);
            if (USB_PD_REG_P0[0x05] & BIT6)
            {
                CLEAR_MASK(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER);
                I2C_EJ898A_PD_RECHECK_05 = 0;
            }
        }
        I2C_EJ898A_POLLING1 = 0xFF;
        return FALSE;
    }
    //-------------------------------------------------------------------------
#endif  //SUPPORT_EJ898A_PD_ADAPTER
    //-------------------------------------------------------------------------
    Polling_EJ898A_VBUS_Voltage();
    I2C_EJ898A_POLLING1 = 0;
    //-------------------------------------------------------------------------
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_Write_To_eFlash
 * @function - EJ898A_Write_To_eFlash (0xF000-0xF1FF)
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EJ898A_Write_To_eFlash(void)
{
    Do_SPI_Write_Status(SPIStatus_UnlockAll);
    // Sector Erase, 1K bytes
    Do_SPI_Write_Enable();
    Do_SPI_Erase(SPICmd_SectorErase, 0x00, 0xF0, 0x00);
    Do_SPI_Write_Disable();

    Do_SPI_Write_Enable();
    Do_SPI_Write_256Bytes(&EJ898A_RAM_C[0], 0x00, 0xF0, 0x00);
    Do_SPI_Write_Disable();

    Do_SPI_Write_Enable();
    Do_SPI_Write_256Bytes(&EJ898A_RAM_D[0], 0x00, 0xF1, 0x00);
    Do_SPI_Write_Disable();
}

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_READ_REGISTER
 * @function - I2C read EJ898A register
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EJ898A_READ_REGISTER(void)
{
    if (I2C_WriteStream(_SMB_TYPE_C,
                        _I2C_EJ898A_Addr,
                        &I2C_EJ898A_OFFSET[0],
                        2))
    {
        if (I2C_ReadStream(_SMB_TYPE_C,
                            _I2C_EJ898A_Addr,
                            &I2C_EJ898A_DATA[0],
                            1))
        {
            I2C_EJ898A_ERROR = 0;
            return;
        }
    }
    I2C_EJ898A_ERROR++;
}
//-----------------------------------------------------------------------------
void EJ898A_READ_PD_REG_P0(BYTE OFFSET)
{
    I2C_EJ898A_OFFSET[0] = 0x80;
    I2C_EJ898A_OFFSET[1] = OFFSET;
    if (I2C_WriteStream(_SMB_TYPE_C,
                        _I2C_EJ898A_Addr,
                        &I2C_EJ898A_OFFSET[0],
                        2))
    {
        if (I2C_ReadStream(_SMB_TYPE_C,
                            _I2C_EJ898A_Addr,
                            &I2C_EJ898A_DATA[0],
                            1))
        {
            USB_PD_REG_P0[OFFSET] = I2C_EJ898A_DATA[0];
            I2C_EJ898A_ERROR = 0;
            return;
        }
    }
    I2C_EJ898A_ERROR++;
}
//-----------------------------------------------------------------------------
void EJ898A_READ_PD_REG_P1(BYTE OFFSET)
{
    I2C_EJ898A_OFFSET[0] = 0x81;
    I2C_EJ898A_OFFSET[1] = OFFSET;
    if (I2C_WriteStream(_SMB_TYPE_C,
                        _I2C_EJ898A_Addr,
                        &I2C_EJ898A_OFFSET[0],
                        2))
    {
        if (I2C_ReadStream(_SMB_TYPE_C,
                            _I2C_EJ898A_Addr,
                            &I2C_EJ898A_DATA[0],
                            1))
        {
            USB_PD_REG_P1[OFFSET] = I2C_EJ898A_DATA[0];
            I2C_EJ898A_ERROR = 0;
            return;
        }
    }
    I2C_EJ898A_ERROR++;
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_WRITE_REGISTER
 * @function - I2C write EJ898A register
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EJ898A_WRITE_REGISTER(void)
{
    if (I2C_WriteStream(_SMB_TYPE_C,
                        _I2C_EJ898A_Addr,
                        &I2C_EJ898A_OFFSET[0],
                        3))
    {
        I2C_EJ898A_ERROR = 0;
        return;
    }
    I2C_EJ898A_ERROR++;
}
//-----------------------------------------------------------------------------
void EJ898A_WRITE_PD_REG_P0(BYTE OFFSET, BYTE PDATA)
{
    I2C_EJ898A_OFFSET[0] = 0x80;
    I2C_EJ898A_OFFSET[1] = OFFSET;
    I2C_EJ898A_DATA[0] = PDATA;
    if (I2C_WriteStream(_SMB_TYPE_C,
                        _I2C_EJ898A_Addr,
                        &I2C_EJ898A_OFFSET[0],
                        3))
    {
            USB_PD_REG_P0[OFFSET] = PDATA;
            I2C_EJ898A_ERROR = 0;
            return;
    }
    I2C_EJ898A_ERROR++;
}
//-----------------------------------------------------------------------------
void EJ898A_WRITE_PD_REG_P1(BYTE OFFSET, BYTE PDATA)
{
    I2C_EJ898A_OFFSET[0] = 0x81;
    I2C_EJ898A_OFFSET[1] = OFFSET;
    I2C_EJ898A_DATA[0] = PDATA;
    if (I2C_WriteStream(_SMB_TYPE_C,
                        _I2C_EJ898A_Addr,
                        &I2C_EJ898A_OFFSET[0],
                        3))
    {
            USB_PD_REG_P0[OFFSET] = PDATA;
            I2C_EJ898A_ERROR = 0;
            return;
    }
    I2C_EJ898A_ERROR++;
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_Page1_Debug
 * @function - EJ898A_Page1_Debug
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EJ898A_Page1_Debug(void)
{
    I2C_EJ898A_OFFSET[0] = 0x80;
    I2C_EJ898A_OFFSET[1] = DBG1_EJ898A_CMD;
    //-------------------------------------------------------------------------
    if (DBG1_EJ898A_START == 0x01)      //READ OP.
    {
        EJ898A_READ_REGISTER();
        if (I2C_EJ898A_ERROR == 0)
        {
            DBG1_EJ898A_DATA = I2C_EJ898A_DATA[0];
            ITempB05 = DBG1_EJ898A_CMD;
            USB_PD_REG_P0[ITempB05] = I2C_EJ898A_DATA[0];
        }
    }
    if (DBG1_EJ898A_START == 0x02)      //WRITE OP.
    {
        I2C_EJ898A_DATA[0] = DBG1_EJ898A_DATA;
        EJ898A_WRITE_REGISTER();
        DBG1_EJ898A_START = 0x01;
        return;
    }
    //-------------------------------------------------------------------------
    DBG1_EJ898A_START = 0x00;
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_Page2_Debug
 * @function - EJ898A_Page2_Debug
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EJ898A_Page2_Debug(void)
{
    I2C_EJ898A_OFFSET[0] = 0x81;
    I2C_EJ898A_OFFSET[1] = DBG2_EJ898A_CMD;
    //-------------------------------------------------------------------------
    if (DBG2_EJ898A_START == 0x01)
    {
        EJ898A_READ_REGISTER();
        if (I2C_EJ898A_ERROR == 0)
        {
            DBG2_EJ898A_DATA = I2C_EJ898A_DATA[0];
            ITempB05 = DBG2_EJ898A_CMD;
            USB_PD_REG_P1[ITempB05] = I2C_EJ898A_DATA[0];
        }
    }
    if (DBG2_EJ898A_START == 0x02)
    {
        I2C_EJ898A_DATA[0] = DBG2_EJ898A_DATA;
        EJ898A_WRITE_REGISTER();
        DBG2_EJ898A_START = 0x01;
        return;
    }
    //-------------------------------------------------------------------------
    DBG2_EJ898A_START = 0x00;
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *-----------+-----------------------------------------------------------------
 * @function | MRD TYPE-C CONTROL FLOW
 *-----------+-----------------------------------------------------------------
 * @chip     | Etron EJ898A
 * @version  | Kernel-14.4
 * @author   | OEM
 * @note     | Copyright(c)2010-2015, ITE Tech. Inc. All rights reserved.
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_Received_PR_Swap
 * @function - EJ898A_Received_PR_Swap
 * @Upstream -
 * @input    - None
 * @return   - None
 * @note     -
 *---------------------------------------------------------------------------*/
void EJ898A_Received_PR_Swap(void)
{
    if (I2C_EJ898A_RX_PR_SWAP == 1)
    {
        EJ898A_READ_PD_REG_P0(0x0A);
        if (USB_PD_REG_P0[0x0A] & BIT1)
        {
            /* ~300ms */
            wEJ898A_I2C_EJ898A_DELAY = 0;
            if (I2C_EJ898A_PR_SWAP_DELAY < 150)
            {
                I2C_EJ898A_PR_SWAP_DELAY++;
            }
            else
            {
                I2C_EJ898A_PR_SWAP_DELAY = 0;
                I2C_EJ898A_RX_PR_SWAP = 2;
            }
        }
        else
        {
            /* ~800ms */
            I2C_EJ898A_PR_SWAP_DELAY = 0;
            if (wEJ898A_I2C_EJ898A_DELAY < 400)
            {
                wEJ898A_I2C_EJ898A_DELAY++;
            }
            else
            {
                /* Issue "Soft reset" */
                //EJ898A_WRITE_PD_REG_P0(0x05, 0xE4);
                EJ898A_READ_PD_REG_P0(0xD3);
                ITempB03 = USB_PD_REG_P0[0xD3];
                ITempB03 |= BIT5;
                EJ898A_WRITE_PD_REG_P0(0xD3, ITempB03);
                EJ898A_RamDebug(0xD3);
                EJ898A_RamDebug(0x4E);
                I2C_EJ898A_PD_HI_DELAY = 0;
                I2C_EJ898A_RX_PR_SWAP = 0;
            }
        }
        return;
    }
    if (I2C_EJ898A_RX_PR_SWAP == 2)
    {
        EJ898A_READ_PD_REG_P0(0x08);
        EJ898A_RamDebug(0x08);
        EJ898A_RamDebug(USB_PD_REG_P0[0x08]);
        if (USB_PD_REG_P0[0x08] & BIT1)
        {
            SET_MASK(I2C_EJ898A_FLAG, F_MRD_IS_SOURCE);
            SET_MASK(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER);
            EJ898A_RamDebug(0x4D);
            I2C_EJ898A_RX_PR_SWAP = 3;
        }
        else
        {
            //CLEAR_MASK(I2C_EJ898A_FLAG, F_MRD_IS_SOURCE);
            //CLEAR_MASK(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER);
            //EJ898A_RamDebug(0xAC);
            //EJ898A_RamDebug(0x44);
            EJ898A_RamDebug(0x70);
            I2C_EJ898A_RX_PR_SWAP = 7;
        }
        I2C_EJ898A_PR_SWAP_DELAY = 0;
        I2C_EJ898A_PD_HI_DELAY = 0;
        return;
    }
    if (I2C_EJ898A_RX_PR_SWAP == 3)
    {
        I2C_EJ898A_RX_PR_SWAP = 99;
        /* Check "Apple ID" event */
        EJ898A_READ_PD_REG_P1(0x2C);
        if (USB_PD_REG_P1[0x2C] == 0xAC)
        {
            EJ898A_READ_PD_REG_P1(0x2D);
            if (USB_PD_REG_P1[0x2D] == 0x05)
            {
                I2C_EJ898A_RX_PR_SWAP = 4;
                I2C_EJ898A_PR_SWAP_RETRY = 0;
            }
            EJ898A_RamDebug(0x2C);
            EJ898A_RamDebug(USB_PD_REG_P1[0x2C]);
            EJ898A_RamDebug(0x2D);
            EJ898A_RamDebug(USB_PD_REG_P1[0x2D]);
        }
        else
        {
            EJ898A_RamDebug(0x2C);
            EJ898A_RamDebug(USB_PD_REG_P1[0x2C]);
        }
        return;
    }
    if (I2C_EJ898A_RX_PR_SWAP == 4)
    {
        EJ898A_READ_PD_REG_P0(0xD3);
        ITempB03 = USB_PD_REG_P0[0xD3];
        ITempB03 |= BIT5;
        EJ898A_WRITE_PD_REG_P0(0xD3, ITempB03);
        EJ898A_RamDebug(0xD3);
        //EJ898A_WRITE_PD_REG_P0(0xD3, ITempB03);
        //EJ898A_RamDebug(0xD3);
        I2C_EJ898A_PR_SWAP_DELAY = 0;
        I2C_EJ898A_RX_PR_SWAP = 5;
        return;
    }
    if (I2C_EJ898A_RX_PR_SWAP == 5)
    {
        EJ898A_READ_PD_REG_P0(0xDD);
        if ((USB_PD_REG_P0[0xDD] & BIT3) == 0)
        {
            EJ898A_RamDebug(0xDD);
            EJ898A_RamDebug(USB_PD_REG_P0[0xDD]);
            EJ898A_RamDebug(0xDA);
            I2C_EJ898A_RX_PR_SWAP = 99;
            return;
        }
        else
        {
            I2C_EJ898A_PR_SWAP_DELAY++;
            if (I2C_EJ898A_PR_SWAP_DELAY > 75)
            {
                EJ898A_RamDebug(0xDD);
                EJ898A_RamDebug(USB_PD_REG_P0[0xDD]);
                EJ898A_RamDebug(0xDB);
                I2C_EJ898A_RX_PR_SWAP = 6;
                I2C_EJ898A_PR_SWAP_DELAY = 0;
            }
        }
        return;
    }
    if (I2C_EJ898A_RX_PR_SWAP == 6)
    {
        EJ898A_READ_PD_REG_P0(0xD3);
        ITempB03 = USB_PD_REG_P0[0xD3];
        ITempB03 |= BIT5;
        EJ898A_WRITE_PD_REG_P0(0xD3, ITempB03);
        EJ898A_RamDebug(0xD3);
        //I2C_EJ898A_RX_PR_SWAP = 99;
        I2C_EJ898A_PR_SWAP_DELAY = 0;
        if (I2C_EJ898A_PR_SWAP_RETRY < 20)
        {
            I2C_EJ898A_PR_SWAP_RETRY++;
            I2C_EJ898A_RX_PR_SWAP = 5;
        }
        else
        {
            I2C_EJ898A_RX_PR_SWAP = 99;
        }
        return;
    }
    if (I2C_EJ898A_RX_PR_SWAP == 7)
    {
        EJ898A_READ_PD_REG_P0(0x7D);
        if (USB_PD_REG_P0[0x7D] >= 0x25)
        {
            EJ898A_RamDebug(0x7D);
            EJ898A_RamDebug(USB_PD_REG_P0[0x7D]);
            CLEAR_MASK(I2C_EJ898A_FLAG, F_MRD_IS_SOURCE);
            CLEAR_MASK(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER);
            EJ898A_RamDebug(0xAC);
            EJ898A_RamDebug(0x44);
            I2C_EJ898A_RX_PR_SWAP = 99;
        }
        else
        {
            if (I2C_EJ898A_PR_SWAP_DELAY < 150)
            {
                I2C_EJ898A_PR_SWAP_DELAY++;
            }
            else
            {
                EJ898A_READ_PD_REG_P0(0xD3);
                ITempB03 = USB_PD_REG_P0[0xD3];
                ITempB03 |= BIT5;
                EJ898A_WRITE_PD_REG_P0(0xD3, ITempB03);
                I2C_EJ898A_RX_PR_SWAP = 99;
                EJ898A_RamDebug(0x71);
            }
        }
        return;
    }
    EJ898A_RamDebug(0xEF);
    I2C_EJ898A_RX_PR_SWAP = 0;
    I2C_EJ898A_PR_SWAP_DELAY = 0;
    I2C_EJ898A_PD_HI_DELAY = 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_Received_VCONN_SWAP
 * @function - EJ898A_Received_VCONN_SWAP
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note
 *---------------------------------------------------------------------------*/
void EJ898A_Received_VCONN_SWAP(void)
{
    if (I2C_EJ898A_VCONN_SWAP < 100)
    {
        EJ898A_READ_PD_REG_P0(0xDD);
        Process_PD_REG_80DDH();
        EJ898A_READ_PD_REG_P0(0x08);
        //---------------------------------------------------------------------
        if ((USB_PD_REG_P0[0xDD] & BIT6) == 0)
        {
            EJ898A_RamDebug(0xDD);
            EJ898A_RamDebug(USB_PD_REG_P0[0xDD]);
            EJ898A_RamDebug(0x08);
            EJ898A_RamDebug(USB_PD_REG_P0[0x08]);
            /* EC help EJ898A reply "Wait message" */
            EJ898A_WRITE_PD_REG_P0(0x04, 0x21);
            I2C_EJ898A_VCONN_SWAP = 0;
            EJ898A_WRITE_PD_REG_P0(0x0E, BIT4);
            EJ898A_RamDebug(0x3F);
        }
        else
        {
            //if (I2C_EJ898A_VCONN_SWAP < 100)
            //{
            //    I2C_EJ898A_VCONN_SWAP++;
            //    return;
            //}
            EJ898A_RamDebug(0xDD);
            EJ898A_RamDebug(USB_PD_REG_P0[0xDD]);
            EJ898A_RamDebug(0x08);
            EJ898A_RamDebug(USB_PD_REG_P0[0x08]);
            EJ898A_WRITE_PD_REG_P0(0x0E, BIT4);
            I2C_EJ898A_VCONN_SWAP = 0;
            EJ898A_RamDebug(0x3E);
            return;
        }
        return;
        //---------------------------------------------------------------------
    }
    I2C_EJ898A_VCONN_SWAP = 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_Received_DR_Swap
 * @function - EJ898A_Received_DR_Swap
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - START: INT Pin Lo->Hi => Read REG_0E Bit=1 =>
 *             Keep Current REG_DD => Send ACK REG04 Write 0x09 =>
 *             Read REG_DD Check Bit6 swap => Changed(1) No Change (2)
 *             (1) Clear REG_0E write 0xFF.
 *             (2) Read REG_10 BIT6=1 Reject exit, 15msec READ_DDH if
 *                 still no change abort.
 *---------------------------------------------------------------------------*/
void EJ898A_Received_DR_Swap(void)
{
    //_STEP[01]----------------------------------------------------------------
    if (I2C_EJ898A_RX_DR_SWAP == 1)
    {
        EJ898A_READ_PD_REG_P0(0x0E);    //Check again
        if (USB_PD_REG_P0[0x0E] & BIT3)
        {
            I2C_EJ898A_RX_DR_SWAP = 2;
            EJ898A_RamDebug(0xD2);
        }
        else
        {
            I2C_EJ898A_STEP = 0;
            I2C_EJ898A_RX_DR_SWAP = 0;
            EJ898A_RamDebug(0xDE);
        }
        return;
    }
    //_STEP[02]----------------------------------------------------------------
    if (I2C_EJ898A_RX_DR_SWAP == 2)
    {
        /* EC help EJ898A reply "Accept message" */
        EJ898A_WRITE_PD_REG_P0(0x04, 0x09);
        I2C_EJ898A_RX_DR_SWAP = 3;
        EJ898A_RamDebug(0xD3);
        return;
    }
    //_STEP[03]----------------------------------------------------------------
    if (I2C_EJ898A_RX_DR_SWAP == 3)
    {
        EJ898A_READ_PD_REG_P0(0xDD);
        Process_PD_REG_80DDH();
        if ((USB_PD_REG_P0[0xDD] & BIT6) !=
            (I2C_EJ898A_LAST_REG_DDH & BIT6))
        {
            I2C_EJ898A_LAST_REG_DDH = USB_PD_REG_P0[0xDD];
            I2C_EJ898A_RX_DR_SWAP = 0xFF;
            EJ898A_RamDebug(0xDE);
        }
        else
        {
            I2C_EJ898A_RX_DR_SWAP = 4;
            EJ898A_RamDebug(0xD4);
        }
        return;
    }
    //------------------------------------------------------------------------
    //_EXIT
    //CLEAR_MASK(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER);
    EJ898A_WRITE_PD_REG_P0(0x0E, BIT3);
    I2C_EJ898A_RX_DR_SWAP = 0;
    //If USB_PD_STS changed, send SCI_DD
    //WriteSCI_Buffer(0xDD);
    EJ898A_RamDebug(0xDF);
    //------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_DP_STATUS_INT
 * @function - EJ898A_DP_STATUS_INT
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EJ898A_DP_STATUS_INT(void)
{
    //_STEP[01]----------------------------------------------------------------
    if (I2C_EJ898A_DP_STATUS_INT == 1)
    {
        EJ898A_READ_PD_REG_P1(0x10);
        if (USB_PD_REG_P1[0x10] & BIT6)
        {
            I2C_EJ898A_POLLING1 = 0;
            I2C_EJ898A_DP_STATUS_INT = 2;
            EJ898A_RamDebug(0xF1);
            return;
        }
        I2C_EJ898A_DP_AB_DELAY++;
        if (I2C_EJ898A_DP_AB_DELAY > 12)
        {
            I2C_EJ898A_DP_AB_DELAY = 0;
#if 1
            EJ898A_WRITE_PD_REG_P1(0x20, 0x30);
            EJ898A_WRITE_PD_REG_P1(0x20, 0x00);
#endif
            // Clear Interrupt event
            EJ898A_WRITE_PD_REG_P1(0x10, 0x48);
            if (USB_PD_REG_P1[0x10] & BIT5)
            {
                I2C_EJ898A_POLLING1 = 0;
                I2C_EJ898A_DP_STATUS_INT = 0;
                I2C_EJ898A_ATTENCTION_INT = 1;
                EJ898A_RamDebug(0xB5);
            }
            else
            {
                I2C_EJ898A_POLLING1 = 0;
                I2C_EJ898A_DP_STATUS_INT = 0;
                EJ898A_RamDebug(0xB6);
            }
        }
        return;
    }
    //_STEP[02]----------------------------------------------------------------
    if (I2C_EJ898A_DP_STATUS_INT == 2)
    {
        EJ898A_READ_PD_REG_P1(0x12);
        if (USB_PD_REG_P1[0x12] == 0x01)
        {
            EJ898A_READ_PD_REG_P1(0x1A);
            if (USB_PD_REG_P1[0x1A] == 0x05)
            {
                /* Reply "DP_configuration" */
                EJ898A_WRITE_PD_REG_P1(0x20, 0x80);
                /* Clear Enter mode & Status update INT */
                EJ898A_WRITE_PD_REG_P1(0x10, 0x48);
                I2C_EJ898A_DP_STATUS_INT = 0;
                EJ898A_RamDebug(0x05);
                EJ898A_RamDebug(0x12);
                EJ898A_RamDebug(0x1A);
                return;
            }
            else if (USB_PD_REG_P1[0x1A] == 0x04)
            {
                /* Reply "DP_configuration" */
                EJ898A_WRITE_PD_REG_P1(0x20, 0x80);
                EJ898A_WRITE_PD_REG_P1(0x20, 0x31); /* TD4+ */
                EJ898A_WRITE_PD_REG_P1(0x20, 0x00); /* TD4+ */
                /* Clear Enter mode & Status update INT */
                EJ898A_WRITE_PD_REG_P1(0x10, 0x48);
                I2C_EJ898A_DP_STATUS_INT = 0;
                EJ898A_RamDebug(0x04);
                EJ898A_RamDebug(0x12);
                EJ898A_RamDebug(0x1A);
                return;
            }
        }
        EJ898A_RamDebug(0xBA);
        I2C_EJ898A_DP_STATUS_INT = 3;
        return;
    }
    //_STEP[03]----------------------------------------------------------------
    if (I2C_EJ898A_DP_STATUS_INT == 3)
    {
        /* Check Staus update VDO & DP_configuration */
        EJ898A_READ_PD_REG_P1(0x78);
        if ((USB_PD_REG_P1[0x78] & 0x03) == 0x00)
        {
            /* Reply "DP_Configuration" */
            EJ898A_WRITE_PD_REG_P1(0x20, 0x31); /* TDF+ */
            EJ898A_WRITE_PD_REG_P1(0x20, 0x00); /* TDF+ */
            I2C_EJ898A_DP_STATUS_INT = 5;
            EJ898A_RamDebug(0xF9);
            return;
        }
        else if (USB_PD_REG_P1[0x78] & BIT7)
        {
            EJ898A_READ_PD_REG_P1(0x1B);
            if (USB_PD_REG_P1[0x1B] & BIT1)
            {
                I2C_EJ898A_DP_STATUS_INT = 4;
                EJ898A_RamDebug(0xF2);
                return;
            }
        }
        //---------------------------------------------------------------------
        /* Clear Enter mode & Status update INT */
        EJ898A_WRITE_PD_REG_P1(0x10, 0x48);
        //---------------------------------------------------------------------
        if (USB_PD_REG_P1[0x10] & BIT5)
        {
            I2C_EJ898A_POLLING1 = 0;
            I2C_EJ898A_ATTENCTION_INT = 1;
            I2C_EJ898A_DP_STATUS_INT = 0;
            EJ898A_RamDebug(0xF8);
        }
        else
        {
            I2C_EJ898A_DP_STATUS_INT = 0;
            EJ898A_RamDebug(0xFF);
        }
        //---------------------------------------------------------------------
        return;
    }
    //_STEP[04]----------------------------------------------------------------
    if (I2C_EJ898A_DP_STATUS_INT == 4)
    {
        //---------------------------------------------------------------------
        EJ898A_READ_PD_REG_P1(0x0C);
        ITempB03 = USB_PD_REG_P1[0x0C];
        ITempB03 |= BIT1;
        EJ898A_WRITE_PD_REG_P1(0x0C, ITempB03);
        //---------------------------------------------------------------------
        /* EC let EC_HPD be "High" */
        if (GPCRI2 != (OUTPUT+PULL_UP))
        {
            GPCRI2 = OUTPUT+PULL_UP;
        }
        EC_HPD_OUT_HI();
        //---------------------------------------------------------------------
        I2C_EJ898A_DP_STATUS_INT = 5;
        EJ898A_RamDebug(0xF3);
        return;
    }
    //_STEP[05]----------------------------------------------------------------
    if (I2C_EJ898A_DP_STATUS_INT == 5)
    {
        //---------------------------------------------------------------------
        /* Clear Enter mode & Status update INT */
        EJ898A_WRITE_PD_REG_P1(0x10, 0x48);
        //---------------------------------------------------------------------
        I2C_EJ898A_DP_STATUS_INT = 0;
        EJ898A_RamDebug(0xFF);
        return;
    }
    //-------------------------------------------------------------------------
    I2C_EJ898A_DP_STATUS_INT = 0;
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_Attenction_INT
 * @function - EJ898A_Attenction_INT
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EJ898A_Attenction_INT(void)
{
    //_STEP[01]----------------------------------------------------------------
    if (I2C_EJ898A_ATTENCTION_INT == 1)
    {
        EJ898A_WRITE_PD_REG_P0(0x9A, 0x06);
        I2C_EJ898A_ATTENCTION_INT = 2;
        EJ898A_RamDebug(0xA2);
        return;
    }
    //_STEP[02]----------------------------------------------------------------
    if (I2C_EJ898A_ATTENCTION_INT == 2)
    {
        EJ898A_READ_PD_REG_P0(0x55);
        //---------------------------------------------------------------------
        EJ898A_RamDebug(0x55);
        EJ898A_RamDebug(USB_PD_REG_P0[0x55]);
        //---------------------------------------------------------------------
        if (USB_PD_REG_P0[0x55] & BIT0)
        {
            I2C_EJ898A_ATTENCTION_INT = 10;
            EJ898A_RamDebug(0xA3);
        }
        else
        {
            I2C_EJ898A_ATTENCTION_INT = 20;
            EJ898A_RamDebug(0xA4);
        }
        return;
    }
    /*************************************************************************/
    //_STEP[10]----------------------------------------------------------------
    /*************************************************************************/
    if (I2C_EJ898A_ATTENCTION_INT == 10)
    {
        EJ898A_READ_PD_REG_P1(0x0C);
        ITempB03 = USB_PD_REG_P1[0x0C];
        ITempB03 |= BIT1;
        EJ898A_WRITE_PD_REG_P1(0x0C, ITempB03);
        //---------------------------------------------------------------------
        if (GPCRI2 != (OUTPUT+PULL_UP))
        {
            GPCRI2 = OUTPUT+PULL_UP;
        }
        EA = 0;
        EC_HPD_OUT_LO();
        for (ITempB01 = 0; ITempB01 < 33; ITempB01++)
        {
            WNCKR = 0x00;   //15.26us
            WNCKR = 0x00;   //15.26us
        }
        EC_HPD_OUT_HI();
        //---------------------------------------------------------------------
        EJ898A_WRITE_PD_REG_P0(0x9A, 0x02);
        EJ898A_WRITE_PD_REG_P1(0x10, BIT5);
        I2C_EJ898A_ATTENCTION_INT = 0;
        EJ898A_RamDebug(0x10);
        EJ898A_RamDebug(0xAF);
        return;
    }
    /*************************************************************************/
    //_STEP[20]----------------------------------------------------------------
    /*************************************************************************/
    if (I2C_EJ898A_ATTENCTION_INT == 20)
    {
        EJ898A_READ_PD_REG_P0(0x54);
        //---------------------------------------------------------------------
        EJ898A_RamDebug(0x54);
        EJ898A_RamDebug(USB_PD_REG_P0[0x54]);
        //---------------------------------------------------------------------
        if ((USB_PD_REG_P0[0x54] & BIT5) || (USB_PD_REG_P0[0x54] & BIT6))
        {
            I2C_EJ898A_ATTENCTION_INT = 30;
            EJ898A_RamDebug(0xA5);
            return;
        }
        //---------------------------------------------------------------------
        if ((USB_PD_REG_P0[0x54] & BIT7))
        {
#if 0
            I2C_EJ898A_ATTENCTION_INT = 22;
#else
            I2C_EJ898A_ATTENCTION_INT = 40;
#endif
            EJ898A_RamDebug(0xA6);
            return;
        }
        //---------------------------------------------------------------------
        I2C_EJ898A_ATTENCTION_INT = 23;
        EJ898A_RamDebug(0xA7);
        return;
    }
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_ATTENCTION_INT == 21)
    {
        EJ898A_READ_PD_REG_P0(0x54);
        //---------------------------------------------------------------------
        EJ898A_RamDebug(0x54);
        EJ898A_RamDebug(USB_PD_REG_P0[0x54]);
        //---------------------------------------------------------------------
        if ((USB_PD_REG_P0[0x54] & BIT7))
        {
#if 0
            I2C_EJ898A_ATTENCTION_INT = 22;
#else
            I2C_EJ898A_ATTENCTION_INT = 40;
#endif
            EJ898A_RamDebug(0xA8);
            return;
        }
        I2C_EJ898A_ATTENCTION_INT = 23;
        EJ898A_RamDebug(0xA9);
        return;
    }
    //-------------------------------------------------------------------------
#if 0
    if (I2C_EJ898A_ATTENCTION_INT == 22)
    {
        EJ898A_READ_PD_REG_P1(0x1B);
        //---------------------------------------------------------------------
        EJ898A_RamDebug(0x1B);
        EJ898A_RamDebug(USB_PD_REG_P1[0x1B]);
        //---------------------------------------------------------------------
        if ((USB_PD_REG_P1[0x1B] & BIT1))
        {
            I2C_EJ898A_ATTENCTION_INT = 40;
            EJ898A_RamDebug(0xAA);
            return;
        }
        I2C_EJ898A_ATTENCTION_INT = 30;
        EJ898A_RamDebug(0xAB);
        return;
    }
#endif
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_ATTENCTION_INT == 23)
    {
        EJ898A_READ_PD_REG_P1(0x1B);
        //---------------------------------------------------------------------
        EJ898A_RamDebug(0x1B);
        EJ898A_RamDebug(USB_PD_REG_P1[0x1B]);
        //---------------------------------------------------------------------
        if ((USB_PD_REG_P1[0x1B] & BIT1))
        {
            I2C_EJ898A_ATTENCTION_INT = 50;
            EJ898A_RamDebug(0xAC);
            return;
        }
        I2C_EJ898A_ATTENCTION_INT = 30;
        EJ898A_RamDebug(0xAD);
        return;
    }
    /*************************************************************************/
    //_STEP[30]----------------------------------------------------------------
    /*************************************************************************/
    if (I2C_EJ898A_ATTENCTION_INT == 30)
    {
        //---------------------------------------------------------------------
        EJ898A_WRITE_PD_REG_P1(0x21, 0xF0);
        //---------------------------------------------------------------------
        I2C_EJ898A_ATTENCTION_DLY = 20;
        I2C_EJ898A_ATTENCTION_INT = 99;
        EJ898A_RamDebug(0xAE);
        return;
    }
    /*************************************************************************/
    //_STEP[40]----------------------------------------------------------------
    /*************************************************************************/
    if (I2C_EJ898A_ATTENCTION_INT == 40)
    {
        EJ898A_READ_PD_REG_P1(0x0C);
        ITempB03 = USB_PD_REG_P1[0x0C];
        ITempB03 |= BIT1;
        EJ898A_WRITE_PD_REG_P1(0x0C, ITempB03);
        GPCRI2 = OUTPUT+PULL_UP;
        EC_HPD_OUT_HI();
        I2C_EJ898A_ATTENCTION_INT = 0;
        EJ898A_WRITE_PD_REG_P0(0x9A, 0x02);
        EJ898A_WRITE_PD_REG_P1(0x10, BIT5);
        EJ898A_RamDebug(0x40);
        EJ898A_RamDebug(0xAF);
        return;
    }
    /*************************************************************************/
    //_STEP[50]----------------------------------------------------------------
    /*************************************************************************/
    if (I2C_EJ898A_ATTENCTION_INT == 50)
    {
        EJ898A_READ_PD_REG_P1(0x0C);
        ITempB03 = USB_PD_REG_P1[0x0C];
        ITempB03 |= BIT1;
        EJ898A_WRITE_PD_REG_P1(0x0C, ITempB03);
        GPCRI2 = OUTPUT+PULL_UP;
        EC_HPD_OUT_LO();
        I2C_EJ898A_ATTENCTION_INT = 0;
        EJ898A_WRITE_PD_REG_P0(0x9A, 0x02);
        EJ898A_WRITE_PD_REG_P1(0x10, BIT5);
        EJ898A_RamDebug(0x50);
        EJ898A_RamDebug(0xAF);
        return;
    }
    /*************************************************************************/
    //_EXIT
    /*************************************************************************/
    if (I2C_EJ898A_ATTENCTION_DLY > 0)
    {
        I2C_EJ898A_ATTENCTION_DLY = 0;
        return;
    }
    EJ898A_WRITE_PD_REG_P0(0x9A, 0x02);
    EJ898A_WRITE_PD_REG_P1(0x10, BIT5);
    EJ898A_WRITE_PD_REG_P1(0x21, 0xD0);
    EJ898A_READ_PD_REG_P1(0x0C);
    ITempB03 = USB_PD_REG_P1[0x0C];
    ITempB03 &= (0xFF-BIT1);
    GPCRI2 = INPUT;
    EJ898A_WRITE_PD_REG_P1(0x0C, ITempB03);
    /* END OF ATTENCTION SERVICE*/
    I2C_EJ898A_ATTENCTION_INT = 0;
    EJ898A_RamDebug(0x99);
    EJ898A_RamDebug(0xAF);
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_Discover_Mode
 * @function - EJ898A_Discover_Mode
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EJ898A_Discover_Mode(void)
{
    if (I2C_EJ898A_DISCOVER_MODE == 1)
    {
        EJ898A_READ_PD_REG_P1(0x5C);
        ITempB03 = USB_PD_REG_P1[0x5C];
        ITempB03 &= (~BIT6);
        EJ898A_WRITE_PD_REG_P1(0x5C, ITempB03);
        I2C_EJ898A_DISCOVER_MODE = 2;
        EJ898A_RamDebug(0xF4);
        return;
    }
    if (I2C_EJ898A_DISCOVER_MODE == 2)
    {
        I2C_EJ898A_DISCOVER_MODE = 99;
        EJ898A_READ_PD_REG_P1(0x2C);
        EJ898A_RamDebug(0x2C);
        EJ898A_RamDebug(USB_PD_REG_P1[0x2C]);
        if (USB_PD_REG_P1[0x2C] == 0x4E)
        {
            EJ898A_READ_PD_REG_P1(0x2D);
            EJ898A_RamDebug(0x2D);
            EJ898A_RamDebug(USB_PD_REG_P1[0x2D]);
            if (USB_PD_REG_P1[0x2D] == 0x1E)
            {
                I2C_EJ898A_DISCOVER_MODE = 3;
                EJ898A_RamDebug(0xF5);
            }
        }
        return;
    }
    if (I2C_EJ898A_DISCOVER_MODE == 3)
    {
        EJ898A_WRITE_PD_REG_P0(0xD2, 0x59);
        EJ898A_RamDebug(0xF6);
        I2C_EJ898A_DISCOVER_MODE = 99;
        return;
    }
    /* Clear "Discover mode INT" */
    EJ898A_WRITE_PD_REG_P1(0x10, BIT2);
    I2C_EJ898A_DISCOVER_MODE = 0;
    EJ898A_RamDebug(0xF7);
}

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_PD_Contract_Hi
 * @function - EJ898A_PD_Contract_Hi
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
const sEJ898PDDataStruct code _EJ898A_PD_DATA_TBL[] =
{
    { 0x00, 0x00, 0x00, 0x00 },
    { 0x50, 0x51, 0x52, 0x53 },
    { 0x54, 0x55, 0x56, 0x57 },
    { 0x58, 0x59, 0x5A, 0x5B },
    { 0x5C, 0x5D, 0x5E, 0x5F },
    { 0x60, 0x61, 0x62, 0x63 },
    { 0x64, 0x65, 0x66, 0x67 },
    { 0x68, 0x69, 0x6A, 0x6B },
};
//-----------------------------------------------------------------------------
void EJ898A_PD_Contract_Hi(void)
{
    //_STEP[01]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 1)
    {
        I2C_EJ898A_PDC_COUNTER = 0;
        I2C_EJ898A_PD_CONTRACT_HI = 2;
        EJ898A_RamDebug(0xE2);
        return;
    }
    //_STEP[02]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 2)
    {
        EJ898A_READ_PD_REG_P0(0x05);
        if (USB_PD_REG_P0[0x05] & BIT6)
        {
            //I2C_EJ898A_PD_CONTRACT_HI = 8;
            I2C_EJ898A_PDC_DELAY = 0;
            I2C_EJ898A_PD_CONTRACT_HI = 21;
            EJ898A_RamDebug(0xE3);
        }
        else
        {
            I2C_EJ898A_PD_CONTRACT_HI = 3;
            I2C_EJ898A_PDC_DELAY = 0;
            EJ898A_RamDebug(0xE4);
        }
        return;
    }
    //_STEP[021]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 21)
    {
        I2C_EJ898A_PDC_DELAY++;
        /* Check "DR_Swap" event*/
        if (I2C_EJ898A_PDC_DELAY < 12)
        {
            EJ898A_READ_PD_REG_P0(0x0E);
            if (USB_PD_REG_P0[0x0E] & BIT3)
            {
                /* EC help EJ898A reply "Accept message" */
                EJ898A_WRITE_PD_REG_P0(0x04, 0x09);
                /* Check DR_Role */
                EJ898A_READ_PD_REG_P0(0xDD);
                Process_PD_REG_80DDH();
                /* Clear "DR_Swap" INT */
                EJ898A_WRITE_PD_REG_P0(0x0E, 0x08);
                I2C_EJ898A_PD_CONTRACT_HI = 8;
                EJ898A_RamDebug(0x45);
                return;
            }
        }
        else
        {
            /* Clear "DR_Swap" INT */
            EJ898A_WRITE_PD_REG_P0(0x0E, 0x08);
            I2C_EJ898A_PD_CONTRACT_HI = 8;
            EJ898A_RamDebug(0x44);
            return;
        }
        return;
    }
    //_STEP[03]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 3)
    {
        if (I2C_EJ898A_PDC_DELAY < 25)
        {
            I2C_EJ898A_PDC_DELAY++;
        }
        else
        {
            I2C_EJ898A_PDC_COUNTER++;
            if (I2C_EJ898A_PDC_COUNTER > 20)
            {
                //I2C_EJ898A_PD_CONTRACT_HI = 5;
                I2C_EJ898A_PD_CONTRACT_HI = 4;
                EJ898A_RamDebug(0xE5);
            }
            else
            {
                I2C_EJ898A_PD_CONTRACT_HI = 2;
                EJ898A_RamDebug(0xE6);
            }
        }
        return;
    }
    //_STEP[04]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 4)
    {
        /* Check "VCONN_Swap" */
        EJ898A_READ_PD_REG_P0(0x0E);
        if (USB_PD_REG_P0[0x0E] & BIT4)
        {
            I2C_EJ898A_PDC_DELAY = 0;
            I2C_EJ898A_PD_CONTRACT_HI = 41;
            EJ898A_RamDebug(0x41);
            return;
        }
        I2C_EJ898A_PD_CONTRACT_HI = 5;
        EJ898A_RamDebug(0xE7);
        return;
    }
    //_STEP[04]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 41)
    {
        I2C_EJ898A_PDC_DELAY++;
        /* Check "DR_Swap" event */
        if (I2C_EJ898A_PDC_DELAY < 12)
        {
            EJ898A_READ_PD_REG_P0(0x0E);
            if (USB_PD_REG_P0[0x0E] & BIT3)
            {
                /* EC help EJ898A reply "Accept message" */
                EJ898A_WRITE_PD_REG_P0(0x04, 0x09);
                /* Check DR_Role */
                EJ898A_READ_PD_REG_P0(0xDD);
                Process_PD_REG_80DDH();
                /* Clear "VCONN_Swap & DR_Swap" INT */
                EJ898A_WRITE_PD_REG_P0(0x0E, 0x18);
                I2C_EJ898A_PD_CONTRACT_HI = 5;
                EJ898A_RamDebug(0x43);
                return;
            }
        }
        else
        {
            /* Clear "VCONN_Swap & DR_Swap" INT */
            EJ898A_WRITE_PD_REG_P0(0x0E, 0x18);
            I2C_EJ898A_PD_CONTRACT_HI = 5;
            EJ898A_RamDebug(0x42);
            return;
        }
        return;
    }
    //_STEP[05]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 5)
    {
        EJ898A_READ_PD_REG_P0(0x4F);
        EJ898A_RamDebug(0x4F);
        EJ898A_RamDebug(USB_PD_REG_P0[0x4F]);
        //---------------------------------------------------------------------
        /* Check PD mismatch */
        if (USB_PD_REG_P0[0x4F] & BIT2)
        {
            I2C_EJ898A_PD_CONTRACT_HI = 8;
            EJ898A_RamDebug(0xE8);
        }
        else
        {
            /* Non-PD Power source VBUS=5V */
            I2C_EJ898A_PD_CONTRACT_HI = 0;
            I2C_EJ898A_PD_CONTRACT_LO = 1;
            EJ898A_RamDebug(0x11);
        }
        return;
    }
    //_STEP[08]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 8)
    {
        CLEAR_MASK(I2C_EJ898A_FLAG, F_PD_STOP_CHARGING);
        EJ898A_READ_PD_REG_P0(0x09);    //[6:4] RCV_PDO_NUM
        ITempB03 = (USB_PD_REG_P0[0x09] >> 4) & 0x07;
        //---------------------------------------------------------------------
        /* Check RCV_PDO_NUM */
        if (ITempB03 == 0x00)
        {
            SET_MASK(I2C_EJ898A_FLAG, F_PD_STOP_CHARGING);
        }
        I2C_EJ898A_RCV_PDO_NUM = (ITempB03 * 4) + 0x50;
        I2C_EJ898A_RCV_PDO_DIR = 0x50;
        I2C_EJ898A_PD_CONTRACT_HI = 9;
        EJ898A_RamDebug(0xE9);
        return;
    }
    //_STEP[09]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 9)
    {
        /* Save PDO Profile to EC RAM */
        if (I2C_EJ898A_RCV_PDO_DIR >= I2C_EJ898A_RCV_PDO_NUM)
        {
            I2C_EJ898A_PD_CONTRACT_HI = 10;
            EJ898A_RamDebug(0xEA);
        }
        else
        {
            EJ898A_READ_PD_REG_P0(I2C_EJ898A_RCV_PDO_DIR);
            I2C_EJ898A_RCV_PDO_DIR++;
        }
        EJ898A_RamDebug(0xD0);
        return;
    }
    //_STEP[10]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 10)
    {
        EJ898A_READ_PD_REG_P0(0x4F);
        /* Check EJ898A request which profile */
        ITempB03 = (USB_PD_REG_P0[0x4F] >> 4) & 0x07;
        if (ITempB03 == 0x00)
        {
            SET_MASK(I2C_EJ898A_FLAG, F_PD_STOP_CHARGING);
        }
        I2C_EJ898A_TPD_SNK_RDO = ITempB03;
        I2C_EJ898A_PD_CONTRACT_HI = 11;
        EJ898A_RamDebug(0xEB);
        return;
    }
    //_STEP[11]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 11)
    {
        //---------------------------------------------------------------------
        ITempB03 = I2C_EJ898A_TPD_SNK_RDO;
        ITempB04 = _EJ898A_PD_DATA_TBL[ITempB03].data0;
        I2C_EJ898A_PDO_DATA0 = USB_PD_REG_P0[ITempB04];
        ITempB04 = _EJ898A_PD_DATA_TBL[ITempB03].data1;
        I2C_EJ898A_PDO_DATA1 = USB_PD_REG_P0[ITempB04];
        ITempB04 = _EJ898A_PD_DATA_TBL[ITempB03].data2;
        I2C_EJ898A_PDO_DATA2 = USB_PD_REG_P0[ITempB04];
        ITempB04 = _EJ898A_PD_DATA_TBL[ITempB03].data3;
        I2C_EJ898A_PDO_DATA3 = USB_PD_REG_P0[ITempB04];
        //---------------------------------------------------------------------
        /* EJ898A request how many current */
        EJ898A_READ_PD_REG_P0(0x4C);
        EJ898A_READ_PD_REG_P0(0x4D);
        //---------------------------------------------------------------------
        wEJ898A_RDO_Current = (WORD)((USB_PD_REG_P0[0x4D] << 8) +
                                    USB_PD_REG_P0[0x4C]);
        wEJ898A_RDO_Current = (wEJ898A_RDO_Current & 0x03FF) * 10;
        //---------------------------------------------------------------------
        I2C_EJ898A_PD_CONTRACT_HI = 12;
        EJ898A_RamDebug(0xEC);
        return;
    }
    //_STEP[12]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 12)
    {
        //---------------------------------------------------------------------
        wEJ898A_PDO_Select_Voltage = ((WORD)(I2C_EJ898A_PDO_DATA2 << 6)) +
                                        ((WORD)(I2C_EJ898A_PDO_DATA1 >> 2));
        wEJ898A_PDO_Select_Voltage = (wEJ898A_PDO_Select_Voltage & 0x03FF) * 50;
        wEJ898A_PDO_Sel_V_m10 = wEJ898A_PDO_Select_Voltage / 100;
        //---------------------------------------------------------------------
        /* Check then partner's current capability */
        wEJ898A_PDO_Select_Current = (WORD)((I2C_EJ898A_PDO_DATA1 << 8) +
                                        I2C_EJ898A_PDO_DATA0);
        wEJ898A_PDO_Sel_I_m10 = (wEJ898A_PDO_Select_Current & 0x03FF) / 10;
        wEJ898A_PDO_Select_Current = (wEJ898A_PDO_Select_Current & 0x03FF) * 10;
        //---------------------------------------------------------------------
        if (wEJ898A_PDO_Select_Voltage > 11000)
        {
            //-----------------------------------------------------------------
            /* ChargingVoltage */
            USBC_ChargingVoltage = 8400;
            //-----------------------------------------------------------------
            /* InputCurrent */
            if (wEJ898A_PDO_Select_Current > 2000)
            {
                USBC_InputCurrent = 2000;
                wEJ898A_PDO_Sel_I_m10 = 20;
            }
            else
            {
                USBC_InputCurrent = wEJ898A_PDO_Select_Current;
            }
            //-----------------------------------------------------------------
            /* ChargingCurrent */
            USBC_ChargingCurrent = 80 * wEJ898A_PDO_Sel_V_m10;
            USBC_ChargingCurrent = USBC_ChargingCurrent / 84;
            USBC_ChargingCurrent = USBC_ChargingCurrent * wEJ898A_PDO_Sel_I_m10;
            if (USBC_ChargingCurrent > 2000)
            {
                USBC_ChargingCurrent = 2000;
            }
            //-----------------------------------------------------------------
        }
        else
        {
            //-----------------------------------------------------------------
            /* ChargingVoltage */
            USBC_ChargingVoltage = 8400;
            //-----------------------------------------------------------------
            /* InputCurrent */
            USBC_InputCurrent = 8 * wEJ898A_PDO_Sel_V_m10;
            USBC_InputCurrent = USBC_InputCurrent * wEJ898A_PDO_Sel_I_m10;
            USBC_InputCurrent = USBC_InputCurrent / 11;
            if (USBC_InputCurrent > 2000)
            {
                USBC_InputCurrent = 2000;
            }
            //-----------------------------------------------------------------
            /* ChargingCurrent */
            USBC_ChargingCurrent = USBC_InputCurrent / 84;
            USBC_ChargingCurrent = USBC_ChargingCurrent * 88;
            if (USBC_ChargingCurrent > 2000)
            {
                USBC_ChargingCurrent = 2000;
            }
            //-----------------------------------------------------------------
        }
        //---------------------------------------------------------------------
        /* Calculate PDO Watt. */
        wEJ898A_PDO_Sel_W_m10 = wEJ898A_PDO_Sel_V_m10 * wEJ898A_PDO_Sel_I_m10;
        I2C_EJ898A_PD_WATT = wEJ898A_PDO_Sel_W_m10 / 100;
        //---------------------------------------------------------------------
        I2C_EJ898A_PD_CONTRACT_HI = 13;
        EJ898A_RamDebug(0xED);
        return;
    }
    //_STEP[13]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 13)
    {
        if (wEJ898A_PDO_Select_Current >= 2000)
        {
            /* Incease current to 2A */
            EJ898A_WRITE_PD_REG_P0(0x34, 0xC8);
            EJ898A_RamDebug(0x34);
            EJ898A_RamDebug(0xC8);
            I2C_EJ898A_PD_CONTRACT_HI = 200;    //2A
            return;
        }
        else if (wEJ898A_PDO_Select_Current == 1500)
        {
            I2C_EJ898A_PD_CONTRACT_HI = 150;    //1.5A
            EJ898A_RamDebug(0x15);
            return;
        }
        else
        {
            I2C_EJ898A_PD_CONTRACT_HI = 50;     //Request mode
            EJ898A_RamDebug(0x50);
        }
        return;
    }
    /*************************************************************************/
    //_STEP[50]---------------------------------------------------------------
    /*************************************************************************/
    if (I2C_EJ898A_PD_CONTRACT_HI == 50)
    {
        wEJ898A_Max_PDO_Voltage = 0;
        I2C_EJ898A_REQ_DIR = 1;
        I2C_EJ898A_PD_CONTRACT_HI = 51;
        EJ898A_RamDebug(0x51);
        return;
    }
    //_STEP[51]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 51)
    {
        //---------------------------------------------------------------------
        ITempB03 = I2C_EJ898A_REQ_DIR;
        ITempB04 = _EJ898A_PD_DATA_TBL[ITempB03].data0;
        I2C_EJ898A_PDO_DATA0 = USB_PD_REG_P0[ITempB04];
        ITempB04 = _EJ898A_PD_DATA_TBL[ITempB03].data1;
        I2C_EJ898A_PDO_DATA1 = USB_PD_REG_P0[ITempB04];
        ITempB04 = _EJ898A_PD_DATA_TBL[ITempB03].data2;
        I2C_EJ898A_PDO_DATA2 = USB_PD_REG_P0[ITempB04];
        ITempB04 = _EJ898A_PD_DATA_TBL[ITempB03].data3;
        I2C_EJ898A_PDO_DATA3 = USB_PD_REG_P0[ITempB04];
        //---------------------------------------------------------------------
        ITempW01 = (WORD)((I2C_EJ898A_PDO_DATA1 << 8) + I2C_EJ898A_PDO_DATA0);
        ITempW01 = (ITempW01 & 0x03FF);
        //---------------------------------------------------------------------
        ITempW02 = ((WORD)(I2C_EJ898A_PDO_DATA2 << 6)) +
                                        ((WORD)(I2C_EJ898A_PDO_DATA1 >> 2));
        ITempW02 = (ITempW02 & 0x03FF) * 50;
        //---------------------------------------------------------------------
        if (ITempW02 > wEJ898A_Max_PDO_Voltage)
        {
            wEJ898A_Max_PDO_Voltage = ITempW02;
            wEJ898A_Request_Current = ITempW01;
        }
        //---------------------------------------------------------------------
        I2C_EJ898A_PD_CONTRACT_HI = 52;
        EJ898A_RamDebug(0x52);
        return;
    }
    //_STEP[52]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 52)
    {
        if (I2C_EJ898A_REQ_DIR >= 7)
        {
            I2C_EJ898A_PD_CONTRACT_HI = 56;
            EJ898A_RamDebug(0x53);
            return;
        }
        I2C_EJ898A_REQ_DIR++;
        I2C_EJ898A_PD_CONTRACT_HI = 51;
        EJ898A_RamDebug(0x51);
        return;
    }
    //_STEP[56]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 56)
    {
        ITempB01 = (wEJ898A_Request_Current & 0xFF);
        EJ898A_WRITE_PD_REG_P0(0x34, ITempB01);
        //---------------------------------------------------------------------
        EJ898A_RamDebug(0x34);
        EJ898A_RamDebug(ITempB01);
        //---------------------------------------------------------------------
        I2C_EJ898A_PD_CONTRACT_HI = 57;
        EJ898A_RamDebug(0x57);
        return;
    }
    //_STEP[57]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 57)
    {
        /* Get remote capacity */
        EJ898A_READ_PD_REG_P0(0x05);
        ITempB03 = USB_PD_REG_P0[0x05];
        ITempB03 |= BIT3;
        EJ898A_WRITE_PD_REG_P0(0x05, ITempB03);
        I2C_EJ898A_PD_CONTRACT_HI = 59;
        EJ898A_RamDebug(0x58);
        return;
    }
    //_STEP[59]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 59)
    {
        //---------------------------------------------------------------------
        /* EJ898A request how many current */
        EJ898A_READ_PD_REG_P0(0x4C);
        EJ898A_READ_PD_REG_P0(0x4D);
        //---------------------------------------------------------------------
        wEJ898A_RDO_Current = (WORD)((USB_PD_REG_P0[0x4D] << 8) +
                                    USB_PD_REG_P0[0x4C]);
        wEJ898A_RDO_Current = (wEJ898A_RDO_Current & 0x03FF) * 10;
        //---------------------------------------------------------------------
#if 0
        USBC_ChargingCurrent = wEJ898A_RDO_Current;
        USBC_ChargingVoltage = 8400;    //8400mV
        USBC_InputCurrent = USBC_ChargingCurrent;
        if (USBC_ChargingCurrent > 2048)
        {
            USBC_InputCurrent = 2048;
        }
#endif
        //---------------------------------------------------------------------
        /* Set flags */
        CLEAR_MASK(I2C_EJ898A_FLAG, F_PD_IS_5V_ADAPTER);
        SET_MASK(I2C_EJ898A_FLAG, F_PD_ADAPTER_IN);
        SET_MASK(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER);
        SMBA_DEV1_DLY = 10;
        //---------------------------------------------------------------------
        /* End of Contract Hi */
        I2C_EJ898A_PD_CONTRACT_HI = 0;
        EJ898A_RamDebug(0x59);
        EJ898A_RamDebug(0x5F);
        return;
    }
    /*************************************************************************/
    //_STEP[150]---------------------------------------------------------------
    /*************************************************************************/
    if (I2C_EJ898A_PD_CONTRACT_HI == 150)
    {
        //USBC_InputCurrent = 1500;
        //USBC_ChargingCurrent = 1500;    //1500mA
        //USBC_ChargingVoltage = 8400;    //8400mV
        //---------------------------------------------------------------------
        /* Set flags */
        CLEAR_MASK(I2C_EJ898A_FLAG, F_PD_IS_5V_ADAPTER);
        SET_MASK(I2C_EJ898A_FLAG, F_PD_ADAPTER_IN);
        SET_MASK(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER);
        SMBA_DEV1_DLY = 10;
        //---------------------------------------------------------------------
        /* End of Contract Hi */
        I2C_EJ898A_PD_CONTRACT_HI = 0;
        EJ898A_RamDebug(0x15);
        EJ898A_RamDebug(0x9F);
        return;
    }
    /*************************************************************************/
    //_STEP[200]---------------------------------------------------------------
    /*************************************************************************/
    if (I2C_EJ898A_PD_CONTRACT_HI == 200)
    {
        /* Get remote capacity */
        EJ898A_READ_PD_REG_P0(0x05);
        ITempB03 = USB_PD_REG_P0[0x05];
        ITempB03 |= BIT3;
        EJ898A_WRITE_PD_REG_P0(0x05, ITempB03);
        I2C_EJ898A_PD_CONTRACT_HI = 201;
        EJ898A_RamDebug(0x21);
        return;
    }
    //_STEP[201]---------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 201)
    {
        EJ898A_READ_PD_REG_P0(0x4C);
        EJ898A_READ_PD_REG_P0(0x4D);
        //---------------------------------------------------------------------
        wEJ898A_RDO_Current = (WORD)((USB_PD_REG_P0[0x4D] << 8) +
                                    USB_PD_REG_P0[0x4C]);
        wEJ898A_RDO_Current = (wEJ898A_RDO_Current & 0x03FF) * 10;
        //---------------------------------------------------------------------
        I2C_EJ898A_PD_CONTRACT_HI = 202;
        EJ898A_RamDebug(0x22);
        return;
    }
    //_STEP[201]---------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_HI == 202)
    {
        //USBC_InputCurrent = 2048;
        //USBC_ChargingCurrent = 2048;
        //USBC_ChargingVoltage = 8400;
        //---------------------------------------------------------------------
        /* Set flags */
        CLEAR_MASK(I2C_EJ898A_FLAG, F_PD_IS_5V_ADAPTER);
        SET_MASK(I2C_EJ898A_FLAG, F_PD_ADAPTER_IN);
        SET_MASK(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER);
        SMBA_DEV1_DLY = 10;
        //---------------------------------------------------------------------
        /* End of Contract Hi */
        I2C_EJ898A_PD_CONTRACT_HI = 0;
        EJ898A_RamDebug(0x20);
        EJ898A_RamDebug(0x2F);
        return;
    }
    //-------------------------------------------------------------------------
    SET_MASK(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER);
    /* End of Contract Hi */
    I2C_EJ898A_PD_CONTRACT_HI = 0;
    EJ898A_RamDebug(0xEE);
    EJ898A_RamDebug(0x2F);
    return;
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_PD_Contract_Lo
 * @function - EJ898A_PD_Contract_Lo
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EJ898A_PD_Contract_Lo(void)
{
    //_STEP[01]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_LO == 1)
    {
        CLEAR_MASK(I2C_EJ898A_FLAG, F_PD_STOP_CHARGING);
        EJ898A_READ_PD_REG_P0(0x08);
        if (USB_PD_REG_P0[0x08] & BIT1)
        {
            SET_MASK(I2C_EJ898A_FLAG, F_PD_STOP_CHARGING);
        }
        I2C_EJ898A_PD_CONTRACT_LO = 2;
        EJ898A_RamDebug(0x12);
        return;
    }
    //_STEP[02]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_LO == 2)
    {
        EJ898A_READ_PD_REG_P0(0x7D);
        I2C_EJ898A_PD_CONTRACT_LO = 3;
        EJ898A_RamDebug(0x13);
        return;
    }
    //_STEP[03]----------------------------------------------------------------
    if (I2C_EJ898A_PD_CONTRACT_LO == 3)
    {
        //---------------------------------------------------------------------
        ITempB03 = USB_PD_REG_P0[0x7D];
        ITempW01 = (WORD)(ITempB03 * 92);
        wEJ898A_VBUS_Voltage = ITempW01;
        //---------------------------------------------------------------------
        USBC_ChargingVoltage = 8400;
        USBC_InputCurrent = 192;
        USBC_ChargingCurrent = 200;
        /*set flags*/
        SET_MASK(I2C_EJ898A_FLAG, F_PD_IS_5V_ADAPTER);
        SET_MASK(I2C_EJ898A_FLAG, F_PD_LEGACY_5V_ADAPTER);
        SET_MASK(I2C_EJ898A_FLAG, F_PD_ADAPTER_IN);
        SMBA_DEV1_DLY = 0;
        SET_MASK(DBG2_EJ898A_STATUS,I2C_EJ898_SET_5V);
        EJ898A_RamDebug(0x14);
        //---------------------------------------------------------------------
        I2C_EJ898A_PD_CONTRACT_LO = 9;
        return;
    }
    /*************************************************************************/
    //_FINISHED
    /*************************************************************************/
    I2C_EJ898A_PD_RECHECK_05 = 5;
    I2C_EJ898A_PD_CONTRACT_LO = 0;
    SET_MASK(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER);
    EJ898A_RamDebug(0x1F);
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - Service_USB_TypeC_PD
 * @function - Service_USB_TypeC_PD
 * @Upstream - By call
 * @input    - None
 * @return   - 1:Kepp USB Service Loop   0:Next I2C/SMBus Device
 * @note     - None
 *---------------------------------------------------------------------------*/
BYTE Service_USB_TypeC_PD(void)
{
    //-------------------------------------------------------------------------
    /* EJ898A Debug Mode Group */
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_DEBUG > 0x80)
    {
        SMBA_CHN_STS = 0;
        //---------------------------------------------------------------------
        if (I2C_EJ898A_DEBUG == 0xDB)   //I2C_EJ898A_DEBUG:029F
        {
#if SUPPORT_TYPE_C_SMBUS_B
            GPCRC1 = INPUT;
            GPCRC2 = INPUT;
#else
            GPCRB3 = INPUT;
            GPCRB4 = INPUT;
#endif
            return  TRUE;
        }
        //---------------------------------------------------------------------
        if (I2C_EJ898A_DEBUG == 0xDD)   //I2C_EJ898A_DEBUG:029F
        {
            EJ898A_Read_EEPROM();
            I2C_EJ898A_DEBUG = 0x00;
            return  TRUE;
        }
        //---------------------------------------------------------------------
        if (I2C_EJ898A_DEBUG == 0xDE)
        {
            ECIndirectFastRead(0x00, 0xF0, 0x00,
                        SPI_selection_internal, 512, &EJ898A_RAM_C[0]);
            I2C_EJ898A_DEBUG = 0x00;
            return  TRUE;
        }
        //---------------------------------------------------------------------
        if (I2C_EJ898A_DEBUG == 0xDF)
        {
            EJ898A_Write_To_eFlash();
            I2C_EJ898A_DEBUG = 0x00;
            return  TRUE;
        }
        //---------------------------------------------------------------------
        if (I2C_EJ898A_DEBUG == 0xBB)
        {
            EJ898A_Write_EEPROM();
            I2C_EJ898A_DEBUG = 0x00;
            return  TRUE;
        }
        //---------------------------------------------------------------------
        if (I2C_EJ898A_DEBUG == 0xCC)
        {
            EJ898A_Clear_EEPROM();
            I2C_EJ898A_DEBUG = 0x00;
            return  TRUE;
        }
        //---------------------------------------------------------------------
    }
    //-------------------------------------------------------------------------
    /* Exit I2C Floating Mode Check */
    //-------------------------------------------------------------------------
    if (GPCRB3 == INPUT)
    {
        GPCRB3 = ALT;
        GPCRB4 = ALT;
        return  TRUE;
    }
#if SUPPORT_TYPE_C_SMBUS_B
    if (GPCRC1 == INPUT)
    {
        GPCRC1 = ALT;
        GPCRC2 = ALT;
    }
#endif
    //-------------------------------------------------------------------------
    /* Initial EJ898A  (Get version and check) */
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_INITIAL == 0)
    {
        EJ898A_Initialize();
        return TRUE;
    }
    //-------------------------------------------------------------------------
    /* Debug Utility EJ898A  */
    //-------------------------------------------------------------------------
    if (DBG1_EJ898A_START > 0)
    {
        EJ898A_Page1_Debug();
        return TRUE;
    }
    //-------------------------------------------------------------------------
    if (DBG2_EJ898A_START > 0)
    {
        EJ898A_Page2_Debug();
        return TRUE;
    }
    //-------------------------------------------------------------------------
    /* 0x44 Skip EJ898A runtime service */
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_DEBUG == 0x44)
    {
        return FALSE;
    }
    //-------------------------------------------------------------------------
    /* EJ898A runtime service */
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_VCONN_SWAP > 0)
    {
        EJ898A_Received_VCONN_SWAP();
        return TRUE;
    }
    if (I2C_EJ898A_RX_DR_SWAP > 0)
    {
        EJ898A_Received_DR_Swap();
        return TRUE;
    }
    if (I2C_EJ898A_RX_PR_SWAP > 0)
    {
        EJ898A_Received_PR_Swap();
        return TRUE;
    }
    if (I2C_EJ898A_DP_STATUS_INT > 0)
    {
        EJ898A_DP_STATUS_INT();
        return TRUE;
    }
    if (I2C_EJ898A_ATTENCTION_INT > 0)
    {
        EJ898A_Attenction_INT();
        return TRUE;
    }
    if (I2C_EJ898A_DISCOVER_MODE > 0)
    {
        EJ898A_Discover_Mode();
        return TRUE;
    }
    //-------------------------------------------------------------------------
    if (IS_MASK_CLEAR(I2C_EJ898A_FLAG, F_INIT_PD_ADAPTER))
    {
        if (I2C_EJ898A_PD_CONTRACT_HI > 0)
        {
            EJ898A_PD_Contract_Hi();
            return TRUE;
        }
        if (I2C_EJ898A_PD_CONTRACT_LO > 0)
        {
            EJ898A_PD_Contract_Lo();
            return TRUE;
        }
    }
    //-------------------------------------------------------------------------
    if (Polling_EJ898A_Register())
    {
        return TRUE;
    }
    //-------------------------------------------------------------------------
    return FALSE;
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - Initial_EJ898A_Registers
 * @function - Initial_EJ898A_Registers
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Initial_EJ898A_Registers(void)
{
#if SUPPORT_EJ898A_EEPROM_HOTFIX    /* Patch EJ898A Load EEPROM noise */
    EJ898A_WRITE_PD_REG_P1(0x02, 0x01);
    EJ898A_WRITE_PD_REG_P1(0x03, 0xFF);
    EJ898A_WRITE_PD_REG_P1(0x04, 0x4D);
    EJ898A_WRITE_PD_REG_P1(0x05, 0x3F);
    EJ898A_WRITE_PD_REG_P1(0x06, 0x3F);
    EJ898A_WRITE_PD_REG_P1(0x07, 0x00);
    EJ898A_WRITE_PD_REG_P1(0x08, 0xFF);
    EJ898A_WRITE_PD_REG_P1(0x09, 0xFF);
    EJ898A_WRITE_PD_REG_P1(0x0A, 0xFF);
    EJ898A_WRITE_PD_REG_P1(0x0B, 0xFF);
    EJ898A_WRITE_PD_REG_P1(0x0C, 0x2D);
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_Initialize
 * @function - Process EJ898A_Initialize
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EJ898A_Initialize(void)
{
    //-------------------------------------------------------------------------
    /* Get EJ898A EEPROM version */
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_GET_VER_OK < 3)
    {
        I2C_EJ898A_NEW_VER = EJ898A_RAM_D[0xFB];
        I2C_EJ898A_OFFSET[0] = 0x01;
        I2C_EJ898A_OFFSET[1] = 0xFB;
        if (I2C_WriteStream(_SMB_TYPE_C,
                            _I2C_EEPROM_Addr,
                            &I2C_EJ898A_OFFSET[0],
                            2))
        {
            if (I2C_ReadStream(_SMB_TYPE_C,
                                _I2C_EEPROM_Addr,
                                &EJ898A_DEBUG_B[0xFB],
                                2))
            {
                xEC_EJ898A_FW_VERSION = EJ898A_DEBUG_B[0xFB];
                xEC_EJ898A_FW_VERSION2 = EJ898A_DEBUG_B[0xFC];
                I2C_EJ898A_EEPROM_VER = xEC_EJ898A_FW_VERSION;
                I2C_EJ898A_GET_VER_OK = 0x07;
            }
        }
        else
        {
                xEC_EJ898A_FW_VERSION = 0xFF;
                I2C_EJ898A_GET_VER_OK++;
                SMBA_FloatingTimer = 5;     //100ms x 5 =  500 mSec
        }
        return;
    }
    //-------------------------------------------------------------------------
    /* Check EJ898A EEPROM update Mode */
    //-------------------------------------------------------------------------
    if (I2C_EJ898A_GET_VER_OK == 0x07)
    {
            if ((xEC_EJ898A_FW_VERSION != EJ898A_RAM_D[0xFB]) ||
                (xEC_EJ898A_FW_VERSION2 != EJ898A_RAM_D[0xFC]))
            {
                EJ898A_Write_EEPROM();
                if (I2C_EJ898A_ERROR == 0)
                {
                    I2C_EJ898A_INITIAL = 0xA1;  // PASS 0xA1: Update EEPROM
                }
                else
                {
                    I2C_EJ898A_INITIAL = 0xE1;  // Can't Write EEPROM
                }
            }
            else
            {
                I2C_EJ898A_INITIAL = 0xA0;  // PASS 0xA0: No update EEPROM
                Initial_EJ898A_Registers();
            }
            return;
    }
    else
    {
        /* Here retry process if EEPROM no any data (for SMT) */
        if (I2C_EJ898A_RETRY < 2)
        {
            I2C_EJ898A_RETRY++;
            SMBA_FloatingTimer = 100;   //100ms x 100 =  10 sec
            I2C_EJ898A_INITIAL = 0x00;  //Retry
            I2C_EJ898A_GET_VER_OK = 0;
        }
        else
        {
            I2C_EJ898A_INITIAL = 0xE0;  // Can't Get EEPROM Version
        }
    }
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - Read_EJ898A_EEPROM
 * @function - I2C read EJ898A EEPROM
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EJ898A_Read_EEPROM(void)
{
    //-------------------------------------------------------------------------
    I2C_EJ898A_OFFSET[0] = 0x00;
    I2C_EJ898A_OFFSET[1] = 0x00;
    if (I2C_WriteStream(_SMB_TYPE_C,
                        _I2C_EEPROM_Addr,
                        &I2C_EJ898A_OFFSET[0],
                        2))
    {
        if (I2C_ReadStream(_SMB_TYPE_C,
                            _I2C_EEPROM_Addr,
                            &EJ898A_DEBUG_A[0],
                            256))
        {
            I2C_EJ898A_ERROR = 0;
        }
        else
        {
            I2C_EJ898A_ERROR++;
        }
    }
    else
    {
        I2C_EJ898A_ERROR++;
    }
    //-------------------------------------------------------------------------
    I2C_EJ898A_OFFSET[0] = 0x01;
    I2C_EJ898A_OFFSET[1] = 0x00;
    if (I2C_WriteStream(_SMB_TYPE_C,
                        _I2C_EEPROM_Addr,
                        &I2C_EJ898A_OFFSET[0],
                        2))
    {
        if (I2C_ReadStream(_SMB_TYPE_C,
                            _I2C_EEPROM_Addr,
                            &EJ898A_DEBUG_B[0],
                            256))
        {
            ;
        }
        else
        {
            I2C_EJ898A_ERROR++;
        }
    }
    else
    {
        I2C_EJ898A_ERROR++;
    }
    //-------------------------------------------------------------------------
    xEC_EJ898A_ERROR = I2C_EJ898A_ERROR;
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_Write_EEPROM
 * @function - I2C write EJ898A EEPROM
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EJ898A_Write_EEPROM(void)
{
    I2C_EJ898A_ERROR = 0;
    I2C_EJ898A_NEED_REBOOT = 0xFF;
    xEC_EJ898A_NEED_REBOOT = 0xFF;
    I2C_EJ898A_OFFSET[0] = 0x00;
    I2C_EJ898A_OFFSET[1] = 0x00;
    while(1)
    {
        ITempB05 = I2C_EJ898A_OFFSET[1];
        if (I2C_EJ898A_OFFSET[0] == 0)
        {
            for (ITempB06 = 2; ITempB06 < 34; ITempB06++)
            {
                EJ898A_DEBUG_A[ITempB06] = EJ898A_RAM_C[ITempB05];
                ITempB05++;
            }
        }
        else
        {
            for (ITempB06 = 2; ITempB06 < 34; ITempB06++)
            {
                EJ898A_DEBUG_A[ITempB06] = EJ898A_RAM_D[ITempB05];
                ITempB05++;
            }
        }
        EJ898A_DEBUG_A[0] = I2C_EJ898A_OFFSET[0];
        EJ898A_DEBUG_A[1] = I2C_EJ898A_OFFSET[1];

        if (I2C_WriteStream(_SMB_TYPE_C,
                            _I2C_EEPROM_Addr,
                            &EJ898A_DEBUG_A[0],
                            34))
        {
            ;
        }
        else
        {
            I2C_EJ898A_ERROR++;
            break;
        }

        Delay1MS(20);
        I2C_EJ898A_OFFSET[1] += 32;
        if (I2C_EJ898A_OFFSET[1] == 0x00)
        {
            I2C_EJ898A_OFFSET[0]++;
            if (I2C_EJ898A_OFFSET[0] >= 2)
            {
                I2C_EJ898A_NEED_REBOOT = 0x01;
                xEC_EJ898A_NEED_REBOOT = 0x01;
                break;
            }
        }
    }
    //-------------------------------------------------------------------------
    xEC_EJ898A_ERROR = I2C_EJ898A_ERROR;
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - EJ898A_Clear_EEPROM
 * @function - I2C clear EJ898A EEPROM
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EJ898A_Clear_EEPROM(void)
{
    I2C_EJ898A_ERROR = 0;
    I2C_EJ898A_NEED_REBOOT = 0xFF;
    xEC_EJ898A_NEED_REBOOT = 0xFF;
    I2C_EJ898A_OFFSET[0] = 0x00;
    I2C_EJ898A_OFFSET[1] = 0x00;
    while(1)
    {
            ITempB05 = I2C_EJ898A_OFFSET[1];
            if (I2C_EJ898A_OFFSET[0] == 0)
            {
                for (ITempB06 = 2; ITempB06 < 34; ITempB06++)
                {
                    EJ898A_DEBUG_A[ITempB06] = 0xFF;
                    ITempB05++;
                }
            }
            else
            {
                for (ITempB06 = 2; ITempB06 < 34; ITempB06++)
                {
                    EJ898A_DEBUG_A[ITempB06] = 0xFF;
                    ITempB05++;
                }
            }
            EJ898A_DEBUG_A[0] = I2C_EJ898A_OFFSET[0];
            EJ898A_DEBUG_A[1] = I2C_EJ898A_OFFSET[1];

            if (I2C_WriteStream(_SMB_TYPE_C,
                                _I2C_EEPROM_Addr,
                                &EJ898A_DEBUG_A[0],
                                34))
            {
                ;
            }
            else
            {
                break;
            }
            Delay1MS(20);
            I2C_EJ898A_OFFSET[1] += 32;
            if (I2C_EJ898A_OFFSET[1] == 0x00)
            {
                I2C_EJ898A_OFFSET[0]++;
                if (I2C_EJ898A_OFFSET[0] >= 2)
                {
                    I2C_EJ898A_NEED_REBOOT = 0x01;
                    xEC_EJ898A_NEED_REBOOT = 0x01;
                    break;
                }
            }
    }
    //-------------------------------------------------------------------------
    xEC_EJ898A_ERROR = I2C_EJ898A_ERROR;
    //-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of B0_SMBUS.C */
