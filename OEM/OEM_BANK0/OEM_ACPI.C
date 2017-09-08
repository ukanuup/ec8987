/*-----------------------------------------------------------------------------
 * @file     | OEM_ACPI.C
 *-----------+-----------------------------------------------------------------
 * @function | OEM ACPI control method process
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2014, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/
#define DEBUG_EC6266            FALSE
#define DEBUG_SCIEVT            FALSE
#define DEBUG_DISABLE_SCIEVT    FALSE

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_EC6266
#define EC6266_RamDebug(x)      RamDebug(x)
#else
#define EC6266_RamDebug(x)      {}
#endif
#if DEBUG_SCIEVT
#define SCIEVT_RamDebug(x)      RamDebug(x)
#else
#define SCIEVT_RamDebug(x)      {}
#endif
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * @subroutine - SCI_EventCenter
 * @function - SCI_EventCenter
 * @upstream - Hook_Timer50msEventC
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SCI_EventCenter(void)
{
#if DEBUG_DISABLE_SCIEVT
    return;
#endif
    if (SCIEVT_DELAY != 0)
    {
        SCIEVT_DELAY--;
        return;
    }
	
    if (SysPowState != _SYSTEM_S0)
    {
        return;
    }
    if (SCIEVT_OUT != 0)
    {
        if (IS_MASK_SET(SystemFlag1, F_ACPI_MODE))
        {
            OEM_ACPI_Gen_Int();
            SCIEVT_DELAY = 20;
        }
        else
        {
            /* Drop DOS mode SCI# event */
            SCIEVT_OUT = 0;
        }
        SCIEVT_OVT++;
        return;
    }
    if (SCIEVT_RIDX == SCIEVT_WIDX)
    {
        SCIEVT_WIDX = 0;
        SCIEVT_RIDX = 0;
        return;
    }
    ReadSCI_Buffer();
    if (IS_MASK_SET(SystemFlag1, F_ACPI_MODE))
    {
        OEM_ACPI_Gen_Int();
    }
    SCIEVT_DELAY = 2;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ReadSCI_Buffer
 * @function - Read SCI Event Buffer
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void ReadSCI_Buffer(void)
{
    if (SCIEVT_RIDX >= SCIEVT_WIDX)
    {
        SCIEVT_OUT = 0;
        SCIEVT_RIDX = 0;
        SCIEVT_WIDX = 0;
    }
    else
    {
        SCIEVT_OUT = SCIEVT_BUF[SCIEVT_RIDX];
        SCIEVT_LAST = SCIEVT_OUT;
        SCIEVT_RIDX++;
        SET_MASK(PM1STS, SCIEVT);
        SCIEVT_RamDebug(SCIEVT_LAST);
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - WriteSCI_Buffer
 * @function - Write SCI Event Buffer
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void WriteSCI_Buffer(BYTE SCI_NUM)
{
    if (SysPowState != _SYSTEM_S0)
    {
        return;
    }
#if 0
    if (IS_MASK_CLEAR(SystemFlag1, F_ACPI_MODE))
    {
        return;
    }
#endif
    SCIEVT_CNT++;

    if (SCIEVT_WIDX >= 7)
    {
        SCIEVT_WIDX = 7;
        SCIEVT_BUF[SCIEVT_WIDX] = SCI_NUM;
        SCIEVT_LOSE++;
    }
    else
    {
        SCIEVT_BUF[SCIEVT_WIDX] = SCI_NUM;
        SCIEVT_WIDX++;
    }
}


/*-----------------------------------------------------------------------------
 * @subroutine - Hook_62Port
 * @function - The hook function of 62 port data
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Hook_62Port(BYTE PM1_Cmd)
{
    //-------------------------------------------------------------------------
    if (PM1_Cmd == 0x58)
    {
        PM1DO = 0x00;
        PM1Data = 0x00;
        PM1DataCount = 1;
        return;
    }
    //-------------------------------------------------------------------------
    if (PM1_Cmd == 0xA2)
    {
        wECU_ADDR &= 0xFF00;
        wECU_ADDR |= PM1Data;
        EC6266_RamDebug(PM1Data);
        return;
    }
    else if (PM1_Cmd == 0xA3)
    {
        wECU_ADDR &= 0x00FF;
        wECU_ADDR |= (PM1Data << 8);
        EC6266_RamDebug(PM1Data);
        return;
    }
    else if (PM1_Cmd == 0xA5)
    {
        Tmp_XPntr = (unsigned int*)wECU_ADDR;
        *Tmp_XPntr = PM1Data;
        EC6266_RamDebug(PM1Data);
        return;
    }
    //-------------------------------------------------------------------------
    EC6266_RamDebug(0x62);
    EC6266_RamDebug(PM1Data);
    //-------------------------------------------------------------------------
#if 0
    if (PM1_Cmd == 0xAB)
    {   /* Auto cold boot timer */
        AutoBootTimer = PM1Data;
        SetAutoBootTimer = PM1Data;
    }
#endif
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_66Cmd_00_7F
 * @function - The hook function of 66 port command 00 - 7Fh
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Hook_66Cmd_00_7F(BYTE PM1_Cmd)
{
    if (PM1_Cmd == 0x58)
    {
        PM1Step = 1;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_66Cmd_90_FF
 * @function - The hook function of 66 port command 90 - FFh
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Hook_66Cmd_90_FF(BYTE PM1_Cmd)
{
    //-------------------------------------------------------------------------
    if (PM1_Cmd == 0x90)
    {
        PM1DO = 0x00;
        PM1Data = 0x00;
        PM1DataCount = 3;
        return;
    }
    //-------------------------------------------------------------------------
    if (PM1_Cmd == 0x94)
    {
    }
    //-------------------------------------------------------------------------
    PM1Step = 1;
    if (PM1_Cmd == 0xA4)
{
        Tmp_XPntr = (unsigned int*)wECU_ADDR;
        PM1Data = *Tmp_XPntr;
        PM1DO = PM1Data;
        EC6266_RamDebug(PM1Data);
    }
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_66Port
 * @function - The hook function of 66 port command.
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Hook_66Port(BYTE PM1_Cmd)
{
    BYTE    i;

    EC6266_RamDebug(0x66);
    EC6266_RamDebug(PM1_Cmd);
    //-------------------------------------------------------------------------
    if (PM1_Cmd < 0x80)
    {
        Hook_66Cmd_00_7F(PM1_Cmd);
        return;
    }
    else if (PM1_Cmd > 0x8F)
    {
        Hook_66Cmd_90_FF(PM1_Cmd);
        return;
    }
    //-------------------------------------------------------------------------
    if ((PM1_Cmd == 0x80) || (PM1_Cmd == 0x81))
    {
        if (IS_MASK_SET(SystemFlag1, F_ACPI_MODE))
        {
            if (IS_MASK_CLEAR(PM1STS, BURST))
            {
                ECCheckBurstMode = 1;
            }
        }
        return;
    }
    else if (PM1_Cmd == 0x82)
    {
        // Auto ACPI Enable
        SET_MASK(SystemFlag1, F_ACPI_MODE);
        // Burst Enable Embedded Controller, BE_EC (0x82)
        ECCheckBurstMode = 1;
        return;
    }
    else if (PM1_Cmd == 0x83)
    {
        // Burst Disable Embedded Controller, BD_EC (0x83)
        ECCheckBurstMode = 0;
        return;
    }
    else if (PM1_Cmd == 0x84)
    {
        // Query Embedded Controller, QR_EC (0x84)
        SendFromAcpi(SCIEVT_OUT);
        CLEAR_MASK(PM1STS,SCIEVT);
        SCIEVT_OUT = 0x00;
        EC6266_RamDebug(SCIEVT_OUT);
        return;
    }
    else if (PM1_Cmd == 0x86)
    {
        // Enable EC ACPI mode.
        SET_MASK(SystemFlag1, F_ACPI_MODE);
        SCIEVT_OVT = 0;
        return;
    }
    else if (PM1_Cmd == 0x87)
    {
        // Disable EC ACPI mode. (Legacy Mode)
        CLEAR_MASK(SystemFlag1, F_ACPI_MODE);
        return;
    }
    else if (PM1_Cmd == 0x8A)
    {
        PM1DO = 0x00;
        return;
    }
    else if (PM1_Cmd == 0x8F)
   {   // Set EC enter flash idle.
        RamProgram(0x66);    //OEM_FLASH.C
    }
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_ACPICommand
 * @function - Hook function of ACPI command
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Hook_ACPICommand(void)
{

}

/*-----------------------------------------------------------------------------
 * @subroutine - OEM_ACPI_Gen_Int
 * @function - Parameter "QeventSCI" only, For a pulsed SCI
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void OEM_ACPI_Gen_Int(void)
{
    DisableAllInterrupt();
    Hook_SCION();
    for (ITempB05 = 0; ITempB05 < 6; ITempB05++)
    {
        WNCKR = 0x00;   // Delay 15.26 us
    }
    Hook_SCIOFF();
    EnableAllInterrupt();
}

/*-----------------------------------------------------------------------------
 * @subroutine - ClearSCIEvent
 * @function - ClearSCIEvent
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void ClearSCIEvent(void)
{
    BYTE    i;

    for (i = 0; i < 8; i++)
    {
        SCIEVT_BUF[i] = 0x00;
    }
    SCIEVT_WIDX = 0;
    SCIEVT_RIDX = 0;
    SCIEVT_OUT = 0;
    CLEAR_MASK(PM1STS, SCIEVT);
    ECCheckBurstMode = 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_ReadMapECSpace
 * @function - Read EC Ram Space
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
BYTE Hook_ReadMapECSpace(BYTE MapIndex)
{
    EC6266_RamDebug(MapIndex);
    Tmp_XPntr = (MEM_EC_SPACE | MapIndex);
    ITempB05 = *Tmp_XPntr;
    EC6266_RamDebug(ITempB05);
    return (ITempB05);
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_WriteMapECSpace
 * @function - Write EC Ram Space
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1)
{
    EC6266_RamDebug(MapIndex);
    Tmp_XPntr = (MEM_EC_SPACE | MapIndex);
    *Tmp_XPntr = data1;
    EC6266_RamDebug(data1);
#if SUPPORT_PECI_CS_MODE
	if (MapIndex == 0x20)
	{
			if(data1 == 0x2C)
			{
				CS_2C_CMD_PULL = 1;
			}

			if(data1 == 0x2D)
			{
				CS_2C_CMD_PULL = 0;
			}
	}
#endif
#if Support_RTC_hang25_wakeup
	if (MapIndex == 0x43)
	{
			if(data1 == 0x6A)
			{
				xEC_RTC_WakeupFlag = 0x6A;
			}
	}
#endif
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_ACPI.C */