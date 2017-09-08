/*-----------------------------------------------------------------------------
 * @file     | OEM_PECI.C
 *-----------+-----------------------------------------------------------------
 * @function | Process CPU PECI
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2014, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/*-----------------------------------------------------------------------------
 * Local Parameter Definition
 *---------------------------------------------------------------------------*/
#define SUPPORT_PECI_SUBROUTINE     FALSE
#define SUPPORT_PECI_POWER_CTRL     FALSE
#define SUPPORT_SOFTWARE_AWFCS      FALSE
//#define SUPPORT_PECI              TRUE


//-----------------------------------------------------------------------------
#if SUPPORT_PECI
/*-----------------------------------------------------------------------------
 * @subroutine - Init_PECI
 * @function - Init_PECI
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
#if 0
void Init_PECI(void)
{

}
#endif

/*-----------------------------------------------------------------------------
 * @subroutine - Service_PECI_Data
 * @function - Service_PECI_Data
 * @upstream - Hook_Timer10msEventB
 * @input    - None
 * @return   - None
 * @note     - Max:~38us,
 *---------------------------------------------------------------------------*/
void Service_PECI_Data(void)
{
    BYTE    i;

    if (PECI_FLAG & F_PECI_BUSY)
    {
        if ((HOSTAR & 0xEC) != 0)
        {
            /* Error Bit */
            PECI_ERRCNT++;
            PECI_ERRSTS = HOSTAR;
#if SUPPORT_PECI_CS_MODE
            HOCTLR = 0x08;
#else
            HOCTLR = 0x00;  /* PECI_HostDisable */
#endif
            HOSTAR = 0xFE;  /* ResetPECIStatus  */
            CLEAR_MASK(PECI_FLAG, F_PECI_BUSY);
        }
        else if (IS_MASK_SET(HOSTAR, FINISH))
        {
            PECI_ERRSTS = HOSTAR;
            Tmp_XPntr = (unsigned int *)PECI_MEMADR;
            for (i = 0x00; i < HORDLR; i++)
            {
                *Tmp_XPntr = HORDDR;
                Tmp_XPntr++;
            }
#if SUPPORT_PECI_CS_MODE
            HOCTLR = 0x08;
#else
            HOCTLR = 0x00;  /* PECI_HostDisable */
#endif
            HOSTAR = 0xFE;  /* ResetPECIStatus  */

            CLEAR_MASK(PECI_FLAG, F_PECI_BUSY);
            PECI_FLAG |= F_PECI_UPDATED;

            if (PECI_CMD == _PECI_CMD_GetDIB)
            {
                PECI_FLAG |= F_PECI_INIT;
            }
            if (PECI_CMD == _PECI_CMD_GetTemp)
            {
                Calc_CPU_Temperature();
            }
        }
        else
        {
            PECI_TIMER++;
#if 0 //SUPPORT_PECI_CS_MODE
            if(CS_2C_CMD_PULL != 1 )
                {
                    if (PECI_TIMER > 200)

                    {
                        PECI_TIMER = 0;
                        PECI_OVTCT++;
                        HOCTLR = 0x08;  /* PECI_HostDisable */
                        HOSTAR = 0xFE;  /* ResetPECIStatus  */
                        CLEAR_MASK(PECI_FLAG, F_PECI_BUSY);
                    }
                }
            else
                {
                if (PECI_TIMER > 0)
                        PECI_TIMER = 0;
                        PECI_OVTCT++;
                        HOCTLR = 0x08;  /* PECI_HostDisable */
                        HOSTAR = 0xFE;  /* ResetPECIStatus  */
                        CLEAR_MASK(PECI_FLAG, F_PECI_BUSY);
                }
#else
            if (PECI_TIMER > 200)
            {
                PECI_TIMER = 0;
                PECI_OVTCT++;
                HOCTLR = 0x00;  /* PECI_HostDisable */
                HOSTAR = 0xFE;  /* ResetPECIStatus  */
                CLEAR_MASK(PECI_FLAG, F_PECI_BUSY);
            }
#endif
        }
        return;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Service_PECI_Command
 * @function - Service_PECI_Command
 * @upstream - Hook_Timer100msEventA
 * @input    - None
 * @return   - None
 * @note     - Max:~33us,
 *---------------------------------------------------------------------------*/
void Service_PECI_Command(void)
{
    //-------------------------------------------------------------------------
    if (SysPowState != _SYSTEM_S0)
    {
        PECI_FLAG = 0;
        return;
    }
    //-------------------------------------------------------------------------
    if (PECI_DELAY > 0)
    {
        PECI_DELAY--;
        return;
    }
    if (PECI_FLAG & F_PECI_BUSY)
    {
        return;
    }
    //-------------------------------------------------------------------------
#if SUPPORT_PECI_CS_MODE
            HOCTLR = 0x08;
#else
            HOCTLR = 0x00;  /* PECI_HostDisable */
#endif
    HOSTAR = 0xFE;      /* ResetPECIStatus  */
    /* PECI_HostEnable(); */
    HOCTLR = (FIFOCLR + FCSERR_ABT + PECIHEN + CONCTRL);
    if (!(PECI_FLAG & F_PECI_INIT))
    {
        HOTRADDR = _PECI_CPU_ADDR;
        HOWRLR = 0x01;
        HORDLR = 0x08;
        PECI_CMD = _PECI_CMD_GetDIB;
        PECI_MEMADR = &PECI_GetDIB[0];
    }
#if SUPPORT_PECI_POWER_CTRL
    else if (!(PECI_FLAG & F_PECI_INIT2))
    {
        PECI_FLAG |= F_PECI_INIT2;
        PECI_ReadPowerUnit();
    }
    else if (!(PECI_FLAG & F_PECI_INIT3))
    {
        PECI_FLAG |= F_PECI_INIT3;
        PECI_WritePowerLimit2(15);      /* Example */
        PECI_WritePowerLimit1(13, 20);  /* Example 13Watt, 20sec */
    }
    else if (!(PECI_FLAG & F_PECI_INIT4))
    {
        PECI_FLAG |= F_PECI_INIT4;
        PECI_ReadPowerLimit1();
        PECI_ReadPowerLimit2();
    }
#endif
    else
    {
        if (PECI_RdPkgCfg_Idx16[2] == 0x00)
        {
            HOTRADDR = _PECI_CPU_ADDR;
            HOWRLR = 0x05;
            HORDLR = 0x05;
            PECI_CMD = _PECI_CMD_RdPkgConfig;
            PECI_MEMADR = &PECI_RdPkgCfg_Idx16_CC;
        }
        else
        {
            HOTRADDR = _PECI_CPU_ADDR;
            HOWRLR = 0x01;
            HORDLR = 0x02;
            PECI_CMD = _PECI_CMD_GetTemp;
            PECI_MEMADR = &PECI_GetTemp[0];
        }
    }
    HOCMDR = PECI_CMD;

    if (PECI_CMD == _PECI_CMD_RdPkgConfig)
    {
        HOWRDR = 0x02;
        HOWRDR = 16;
        HOWRDR = 0x00;
        HOWRDR = 0x00;
    }
    HOCTLR |= START;    /* PECI_HostControl(START) */
    PECI_TIMER = 0;
#if SUPPORT_PECI_CS_MODE
    if(CS_2C_CMD_PULL != 1 )
    PECI_DELAY = 50;     /* 5 x 100ms = 0.5sec */
    else
    PECI_DELAY = 800;   //bbbbb
#else
    PECI_DELAY = 5;     /* 5 x 100ms = 0.5sec */
#endif
    PECI_FLAG |= F_PECI_BUSY;
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - Calc_CPU_Temperature
 * @function - Calc_CPU_Temperature
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Calc_CPU_Temperature(void)
{
    if (PECI_FLAG & F_PECI_UPDATED)
    {
        CLEAR_MASK(PECI_FLAG, F_PECI_UPDATED);
        //---------------------------------------------------------------------
        ITempW01 = (PECI_GetTemp[1] << 8) + PECI_GetTemp[0];
        ITempW01 = (~ITempW01) + 1;     /* 2's complement */
        ITempB05 = ITempW01 >> 6;       /* 1/64 degrees centigrade */
        if (Processor_Tj_max == 0)
        {
            PECI_CPU_T = 100 - ITempB05;
            //CPU_Shutdown_T = 100;
            //SCI_Shutdown_T = 95;
        }
        else
        {
            //CPU_Shutdown_T = Processor_Tj_max + 3;
            //SCI_Shutdown_T = Processor_Tj_max + 0;
            if ((ITempB05 & 0x80) == 0x00)
            {
                PECI_CPU_T = Processor_Tj_max - ITempB05;
            }
            else
            {
                ITempB05 = (~ITempB05);
                PECI_CPU_T = Processor_Tj_max + ITempB05;
            }
        }
    }
}
#endif
//-----------------------------------------------------------------------------

#if SUPPORT_PECI_SUBROUTINE
/*-----------------------------------------------------------------------------
 * @subroutine - PECI_CheckHostBusy
 * @function - Check PECI interface busy or not
 * @upstream - By call
 * @input    - None
 * @return   - 0 : 30 ms time out,  1 : OK
 * @note     - None
 *---------------------------------------------------------------------------*/
BYTE PECI_CheckHostBusy(void)
{
    /* Init TimeOut Timer for PECI access */
    SettingTimer1(Timer_30ms);

    while (!TF1)
    {
        if (IS_MASK_CLEAR(HOSTAR, HOBY))
        {
            TR1 = 0;
            TF1 = 0;
            ET1 = 1;
            break;
        }
    }

    if (TF1)
    {
        TR1 = 0;
        TF1 = 0;
        ET1 = 1;
        return(0);
    }
    return(1);
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_CheckHostFinish
 * @function - Check PECI interface finish or not
 * @upstream - By call
 * @input    - None
 * @return   - 0 : time-out or error
 * @note     - None
 *---------------------------------------------------------------------------*/
BYTE PECI_CheckHostFinish(void)
{
    BYTE    error, status, result;

    error = 0x04;   /* Preset error */

    /* Init TimeOut Timer for PECI access */
    SettingTimer1(Timer_30ms);

    while (!TF1)
    {
        status = HOSTAR;

        if (status != 0x00)
        {
            if (IS_MASK_SET(status, FINISH))
            {
                error = 0x00;
                break;
            }
            else if (IS_MASK_SET(status, RD_FCS_ERR))
            {
                error = 0x01;
                break;
            }
            else if (IS_MASK_SET(status, WR_FCS_ERR))
            {
                error = 0x01;
                break;
            }
            else if (IS_MASK_SET(status, EXTERR))
            {
                SET_MASK(RSTC4, RPECI);  /* Reset PECI interface */
                error = 0x02;
                break;
            }
            else if (IS_MASK_SET(status, BUSERR))
            {
                SET_MASK(RSTC4, RPECI);  /* Reset PECI interface */
                error = 0x02;
                break;
            }
            else if (IS_MASK_SET(status, TEMPERR))
            {
                error = 0x03;
                break;
            }
        }
    }

    if (error != 0x00)
    {
        result = 0x00;    /* Error */
    }
    else
    {
        result = 0x01;    /* Finish */
    }

    TR1 = 0;
    TF1 = 0;
    ET1 = 1;

    return(result);
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_CalcCRC8
 * @function - CRC-8 polynomial
 * @upstream - By call
 * @input    - sourcebyte
 * @return   - PECI_CRC8
 * @note     - None
 *---------------------------------------------------------------------------*/
void PECI_CalcCRC8(BYTE sourcebyte)
{
#if SUPPORT_SOFTWARE_AWFCS
    BYTE    temp;

    PECI_CRC8 ^= sourcebyte;
    temp = PECI_CRC8;

    if (IS_MASK_CLEAR(temp, BIT7))
    {
        temp = temp << 1;
        PECI_CRC8 ^= temp;
    }
    else
    {
        temp = temp << 1;
        PECI_CRC8 ^= 0x09;
        PECI_CRC8 ^= temp;
    }

    if (IS_MASK_CLEAR(temp, BIT7))
    {
        temp = temp << 1;
        PECI_CRC8 ^= temp;
    }
    else
    {
        temp = temp << 1;
        PECI_CRC8 ^= 0x07;
        PECI_CRC8 ^= temp;
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_WrPkgConfig
 * @function - Write to the package configuration space (PCS) within the
 *             processor
 * @upstream - Hook_Timer10msEventB
 * @input    - (1) addr : The address of processor
 *             (2) *ReadData : the start address of variable to save data
 *             (3) Domain : 0 or 1?
 *                          0 : Domain 0, 1 : Domain 1?
 *             (4) Retry   0 or 1
 *             (5) Index
 *             (6) LSB of parameter
 *             (7) MSB of parameter
 *             (8) ReadLen read length 2 or 3 or 5
 *             (9) WriteLen write length 5
 *
 * @return   - 1 : done     0 : error
 * @note     - None
 *---------------------------------------------------------------------------*/
BYTE PECI_RdPkgConfig(BYTE addr, XBYTE *ReadData, BYTE Domain, BYTE Retry,
        BYTE Index, BYTE LSB, BYTE MSB, BYTE ReadLen, BYTE WriteLen)
{
    BYTE    done, loop;

    done = 0x00;

    /* PECI_HostEnable(); */
    HOCTLR = (FIFOCLR + FCSERR_ABT + PECIHEN + CONCTRL);
    HOTRADDR = addr;
    HOWRLR = WriteLen;
    HORDLR = ReadLen;

    if (Domain < 2)
    {
        HOCMDR = _PECI_CMD_RdPkgConfig + Domain;
    }
    else
    {
        HOCMDR = _PECI_CMD_RdPkgConfig;
    }

    if (Retry < 2)
    {
        HOWRDR = (_PECI_HostID << 1) + Retry;
    }
    else
    {
        HOWRDR = (_PECI_HostID << 1);
    }

    HOWRDR = Index;
    HOWRDR = LSB;
    HOWRDR = MSB;

    if (PECI_CheckHostBusy())
    {
        HOCTLR |= START;    /* PECI_HostControl(START); */
        if (PECI_CheckHostFinish())
        {
            if (HORDLR != 0x00)
            {
                for (loop = 0; loop < HORDLR; loop++)
                {
                    if (loop == 0x00)
                    {
                        PECI_CompletionCode = HORDDR;
                    }
                    else
                    {
                        *(ReadData + loop - 1) = HORDDR;
                    }
                }

                if (PECI_CompletionCode == _PECI_CC_Valid)
                {
                    done = 0x01;
                }
                else
                {
                    done = 0x00;
                }
            }
            else
            {
                done = 0x00;
            }
        }
    }

    HOCTLR = 0x00;  /* PECI_HostDisable */
    HOSTAR = 0xFE;  /* ResetPECIStatus  */
    return(done);
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_WrPkgConfig
 * @function - Write to the package configuration space (PCS) within the
 *             processor
 * @upstream - Hook_Timer10msEventB
 * @input    - (1) addr : The address of processor
 *             (2) *WriteData : the start address of variable to wirte data
 *             (3) Domain : 0 or 1?
 *                           0 : Domain 0, 1 : Domain 1?
 *             (4) Retry   0 or 1
 *             (5) Index
 *             (6) LSB of parameter
 *             (7) MSB of parameter
 *             (8) ReadLen read length 1
 *             (9) WriteLen write length 0x07 or 0x08 or 0x0A
 *
 * @return   - 1 : done     0 : error
 * @note     - None
 *---------------------------------------------------------------------------*/
BYTE PECI_WrPkgConfig(BYTE addr, XBYTE *WriteData, BYTE Domain, BYTE Retry,
        BYTE Index, BYTE LSB, BYTE MSB, BYTE ReadLen, BYTE WriteLen)
{
    BYTE    done, loop;

    done = 0x00;

    PECI_CompletionCode = 0x00;

    /* PECI_HostEnable(); */
    HOCTLR = (FIFOCLR + FCSERR_ABT + PECIHEN + CONCTRL);

#if SUPPORT_SOFTWARE_AWFCS
    PECI_CRC8 = 0x00;
#else
    /* PECI_HostControl(AWFCS_EN); */
    HOCTLR |= AWFCS_EN;
#endif

    HOTRADDR = addr;
    PECI_CalcCRC8(addr);
    HOWRLR = WriteLen;
    PECI_CalcCRC8(WriteLen);
    HORDLR = ReadLen;
    PECI_CalcCRC8(ReadLen);

    if (Domain < 2)
    {
        HOCMDR = (_PECI_CMD_WrPkgConfig + Domain);
        PECI_CalcCRC8(_PECI_CMD_WrPkgConfig + Domain);
    }
    else
    {
        HOCMDR = _PECI_CMD_WrPkgConfig;
        PECI_CalcCRC8(_PECI_CMD_WrPkgConfig);
    }

    if (Retry < 2)
    {
        HOWRDR = (_PECI_HostID << 1) + Retry;
        PECI_CalcCRC8((_PECI_HostID << 1) + Retry);
    }
    else
    {
        HOWRDR = (_PECI_HostID << 1);
        PECI_CalcCRC8(_PECI_HostID << 1);
    }

    HOWRDR = Index;
    PECI_CalcCRC8(Index);
    HOWRDR = LSB;
    PECI_CalcCRC8(LSB);
    HOWRDR = MSB;
    PECI_CalcCRC8(MSB);

    for (loop = 0; loop < (WriteLen - 6); loop++)
    {
        HOWRDR = *(WriteData + loop);
        PECI_CalcCRC8(*(WriteData + loop));
    }

#if SUPPORT_SOFTWARE_AWFCS
    /* Inverted MSb of preliminary FCS reslut */
    PECI_CRC8 ^= 0x80;
    HOWRDR = PECI_CRC8;
#endif

    if (PECI_CheckHostBusy())
    {
        HOCTLR |= START;    /* PECI_HostControl(START) */

        if (PECI_CheckHostFinish())
        {
            PECI_CompletionCode = HORDDR;

            if (PECI_CompletionCode == _PECI_CC_Valid)
            {
                done = 0x01;
            }
            else
            {
                done = 0x00;
            }
        }
    }

    HOCTLR = 0x00;  /* PECI_HostDisable */
    HOSTAR = 0xFE;  /* ResetPECIStatus  */
    return(done);
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_RdIAMSR
 * @function - Read to Model Specific Registers function
 * @upstream - Hook_Timer10msEventB
 * @input    - (1) addr : The address of processor
 *             (2) *ReadData : the start address of variable to save data
 *             (3) Domain : 0 or 1?
 *                          0 : Domain 0, 1 : Domain 1?
 *             (4) Retry   0 or 1
 *             (5) ProcessorID
 *             (6) LSB of parameter
 *             (7) MSB of parameter
 *             (8) ReadLen read length 0x02 or 0x03 or 0x05 or 0x09
 *             (9) WriteLen write length 0x05
 *
 * @return   - 1 : done     0 : error
 * @note     - None
 *---------------------------------------------------------------------------*/
BYTE PECI_RdIAMSR(BYTE addr, XBYTE *ReadData, BYTE Domain, BYTE Retry,
        BYTE ProcessorID, BYTE LSB, BYTE MSB, BYTE ReadLen, BYTE WriteLen)
{
    BYTE    done, loop;

    done = 0x00;

    /* PECI_HostEnable(); */
    HOCTLR = (FIFOCLR + FCSERR_ABT + PECIHEN + CONCTRL);
    HOTRADDR = addr;
    HOWRLR = WriteLen;
    HORDLR = ReadLen;

    if (Domain < 2)
    {
        HOCMDR = (_PECI_CMD_RdIAMSR + Domain);
    }
    else
    {
        HOCMDR = _PECI_CMD_RdIAMSR;
    }

    if (Retry < 2)
    {
        HOWRDR = (_PECI_HostID << 1) + Retry;
    }
    else
    {
        HOWRDR = (_PECI_HostID << 1);
    }

    HOWRDR = ProcessorID;
    HOWRDR = LSB;
    HOWRDR = MSB;

    if (PECI_CheckHostBusy())
    {
        HOCTLR |= START;    /* PECI_HostControl(START) */

        if (PECI_CheckHostFinish())
        {
            for (loop = 0; loop < HORDLR; loop++)
            {
                if (loop == 0x00)
                {
                    PECI_CompletionCode = HORDDR;
                }
                else
                {
                    *(ReadData + loop - 1) = HORDDR;
                }
            }

            if (PECI_CompletionCode == _PECI_CC_Valid)
            {
                done = 0x01;
            }
            else
            {
                done = 0x00;
            }
        }
    }

    HOCTLR = 0x00;  /* PECI_HostDisable */
    HOSTAR = 0xFE;  /* ResetPECIStatus  */

    return(done);
}
#endif  //SUPPORT_PECI_SUBROUTINE
//-----------------------------------------------------------------------------


#if SUPPORT_PECI_POWER_CTRL
/*-----------------------------------------------------------------------------
 * @subroutine - PECI_ReadPowerUnit
 * @function - The function of PECI3.0 Package read power unit
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void PECI_ReadPowerUnit(void)
{
    if (PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_ReadBuffer, _PECI_Domain_0,
                            0, _PECI_Index_PPSH, 0, 0, 5, 5))
    {
        PECI_PowerUnit = (PECI_ReadBuffer[0] & 0x0F);    /* Bit[3:0] */
        PECI_EnergyUnit = (PECI_ReadBuffer[1] & 0x1F);   /* Bit[12:8] */
        PECI_TimeUnit = (PECI_ReadBuffer[2] & 0x0F);     /* Bit[19:16] */
        PECI_UnitPower = 1 << PECI_PowerUnit;
    }
    else
    {
        PECI_PowerUnit = 0;
        PECI_EnergyUnit = 0;
        PECI_TimeUnit = 0;
        PECI_UnitPower = 0;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_ReadPowerLimit1
 * @function - The function of PECI3.0 Package read power limit 1
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void PECI_ReadPowerLimit1(void)
{
    if (PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_ReadBuffer, _PECI_Domain_0,
                            0, _PECI_Index_PPL1, 0, 0, 5, 5))
    {
        PECI_PowerLimit1 = (PECI_ReadBuffer[0] +
                ((PECI_ReadBuffer[1] & 0x7F) * 256)) / PECI_UnitPower;
    }
    else
    {
        PECI_PowerLimit1 = 0xFF;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_ReadPowerLimit2
 * @function - The function of PECI3.0 Package read power limit 2
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void PECI_ReadPowerLimit2(void)
{
    if (PECI_RdPkgConfig(_PECI_CPU_ADDR, &PECI_ReadBuffer, _PECI_Domain_0,
                            0, _PECI_Index_PPL2, 0, 0, 5, 5))
    {
        PECI_PowerLimit2 = (PECI_ReadBuffer[0]) / PECI_UnitPower;
    }
    else
    {
        PECI_PowerLimit2 = 0xFF;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_WritePowerLimit1
 * @function - The function of PECI3.0 Package write power limit 1
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void PECI_WritePowerLimit1(BYTE SettingWatts, BYTE SettingTimer)
{
    WORD    wTEMP;

    wTEMP = (PECI_UnitPower * SettingWatts);
    PECI_WriteBuffer[0] = wTEMP;
    PECI_WriteBuffer[1] = (wTEMP >> 8) | 0x80;

    wTEMP = ((1 << PECI_TimeUnit) * SettingTimer);
    PECI_WriteBuffer[2] = wTEMP;
    PECI_WriteBuffer[3] = 0;

    if (PECI_WrPkgConfig(_PECI_CPU_ADDR, &PECI_WriteBuffer, _PECI_Domain_0,
                            0, _PECI_Index_PPL1, 0, 0, 1, 10))
    {
        ;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - PECI_WritePowerLimit2
 * @function - The function of PECI3.0 Package write power limit 2
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void PECI_WritePowerLimit2(BYTE SettingWatts)
{
    WORD    wTEMP;

    wTEMP = (PECI_UnitPower * SettingWatts);
    PECI_WriteBuffer[0] = wTEMP;
    PECI_WriteBuffer[1] = (wTEMP >> 8) | 0x80;
    PECI_WriteBuffer[2] = 0;
    PECI_WriteBuffer[3] = 0;

    if (PECI_WrPkgConfig(_PECI_CPU_ADDR, &PECI_WriteBuffer, _PECI_Domain_0,
                            0, _PECI_Index_PPL2, 0, 0, 1, 10))
    {
        ;
    }
}
//-----------------------------------------------------------------------------
#endif  //SUPPORT_PECI_POWER_CTRL
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_PECI.C */