/*-----------------------------------------------------------------------------
 * @file     | OEM_FLASH.C
 *-----------+-----------------------------------------------------------------
 * @function | SPI Flash & Programming
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
#define SUPPORT_PORT64_RAMCODE_CMD      TRUE
#define SUPPORT_PORT66_RAMCODE_CMD      TRUE
#define SUPPORT_PORT6C_RAMCODE_CMD      FALSE

/*-----------------------------------------------------------------------------
 * @subroutine - SetLPCClockFreeRun
 * @function - Set LPC Clock Free Run
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SetLPCClockFreeRun(void)
{
#if SUPPORT_GPH0_CLKRUN
    GPCRH0 = OUTPUT;
    CLEAR_MASK(GPDRH, BIT(0));
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - LPC_RamCode
 * @function - LPC RamCode for none HSPI mode
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void LPC_RamCode(void)
{
    RamcodeCmd = 0x00;

    SET_MASK(SMECCS, HOSTWA);   // LPC Host write allow

#if SUPPORT_PORT64_RAMCODE_CMD
    if (RamCodePort == 0x64)
    {
        KBHIKDOR = 0xFA;
    }
#endif
#if SUPPORT_PORT66_RAMCODE_CMD
    if (RamCodePort == 0x66)
    {
        PM1DO = 0xFA;
    }
#endif
#if SUPPORT_PORT6C_RAMCODE_CMD
    else if (RamCodePort == 0x6C)
    {
        PM2DO = 0xFA;
    }
#endif
    while (1)
    {
        ITempB02++;
#if SUPPORT_PORT64_RAMCODE_CMD
        if (RamCodePort == 0x64)
        {
            if (IS_MASK_CLEAR(KBHISR, IBF)) { continue; }
            if (IS_MASK_CLEAR(KBHISR, C_D)) { continue; }
            RamcodeCmd = KBHIDIR;
        }
#endif
#if SUPPORT_PORT66_RAMCODE_CMD
        if (RamCodePort == 0x66)
        {
            if (IS_MASK_CLEAR(PM1STS, P_IBF)) { continue; }
            if (IS_MASK_CLEAR(PM1STS, P_C_D)) { continue; }
            RamcodeCmd = PM1DI;
        }
#endif
#if SUPPORT_PORT6C_RAMCODE_CMD
        else if (RamCodePort == 0x6C)
        {
            if (IS_MASK_CLEAR(PM2STS, P_IBF)) { continue; }
            if (IS_MASK_CLEAR(PM2STS, P_C_D)) { continue; }
            RamcodeCmd = PM2DI;
        }
#endif
        if ((RamcodeCmd == 0x55) || (RamcodeCmd == 0x8E))
        {
            PM1DO = 0xFA;
            WinFlashMark = 0x33;
            break;
        }
        else if ((RamcodeCmd == 0xAF) || IS_PCH_SLP_S3_LO() ||
                    IS_PCH_SLP_S4_LO())
        {
            WDTRST = 1;         // Reset watch dog timer
            WDTEB = 1;          // Enable watch dog
            while (1);          // Wait for watch dog time-out
        }
#if 0
        else if (RamcodeCmd == 0xD7)    // For AMI BIOS
        {
            CLEAR_MASK(SMECCS, HOSTWA); // Host write not allow
            _nop_();
            _nop_();
            SET_MASK(SMECCS, HOSTWA);   // Host write allow
        }
#endif
    }

    CLEAR_MASK(SMECCS, HOSTWA); // Host write not allow

    _nop_();
    _nop_();
    _nop_();
    _nop_();

#if SUPPORT_GPH0_CLKRUN
    GPCRH0 = ALT;
#endif
    main();
}

/*-----------------------------------------------------------------------------
 * @subroutine - RamProgram
 * @function - Scratch rom for Ram Program
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void RamProgram(BYTE useport)
{
    SetLPCClockFreeRun();
    RamCodePort = useport;
    DisableAllInterrupt();

    Tmp_XPntr = 0x700;

#if HSPI_DefferingMode
    /* Disable HSPI interrupt */
    CLEAR_MASK(IER7, Int_DeferredSPI);
#else
    //Tmp_code_pointer = (void *)HSPI_CmdRamCode;
    Tmp_code_pointer = (void *)LPC_RamCode;
#endif

    for (ITempB01 = 0; ITempB01 < 255; ITempB01++)
    {
        *Tmp_XPntr = *Tmp_code_pointer;
        Tmp_XPntr++;
        Tmp_code_pointer++;
    }
    /* Enable scatch ROM */
    SET_MASK(FBCFG, SSMC);

    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();

    RamCode();
}


#if SUPPORT_MIRROR_ONCE

#pragma ot(7, SIZE)
void Do_SPI_Write_1Byte(XBYTE *DataPointer,BYTE Addr2,BYTE Addr1,BYTE Addr0)
{
    SPIDataPointer = DataPointer;
    SPIAddrCycle[0] = Addr2;
    SPIAddrCycle[1] = Addr1;
    SPIAddrCycle[2] = Addr0;
    DisableAllInterrupt();                      // Disable all interrupt
    LoadSPIFucnToRam(SPI_Write_1Byte);          // Load function to ram
    SET_MASK(FBCFG,SSMC);                       // enable scatch ROM
    FuncAt_0xFE00();                           // do function in extern ram 0x600
    CLEAR_MASK(FBCFG,SSMC);                    // disable scatch ROM
    EnableAllInterrupt();                      // Enable all interrupt

}

#pragma ot(7, SIZE)
BYTE Read_flash_Byte(BYTE FA2,BYTE FA1,BYTE FA0)
{
    ECINDAR3 = 0;
    ECINDAR2 = FA2;
    ECINDAR1 = FA1;
    ECINDAR0 = FA0;
    return ECINDDR;
}

//-----------------------------------------------------------------------------
// The function of SPI read 256 bytes
//-----------------------------------------------------------------------------
void SPI_Write_1Byte(void)
{
    ECINDAR3 = 0x0F;
    ECINDAR2 = 0xFF;
    ECINDAR0 = 0x00;                                // FFFFExx = 0xFF

    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                                     // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_ReadStatus;    // Read Status Register
    while(1)                                           // waiting spi free
    {
        if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        }
    }

    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                                 // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_BYTEProgram;   // Send Program One Data Byte command

    ECINDDR = SPIAddrCycle[0];      // For 256 bytes function limite
    ECINDDR = SPIAddrCycle[1];
    ECINDDR = SPIAddrCycle[2];

    SPIIndex = 0x00;

    ECINDDR = *SPIDataPointer;

    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                                     // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_ReadStatus;    // Read Status Register
    while(1)                                           // waiting spi free
    {
        if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        }
    }

    ECINDAR3 = 0x00;                      // Exit follow mode
    ECINDAR2 = 0x00;                           //
}

void FSPIRomWriteEnable(void)
{
    ECINDAR3 = 0x4F;
    ECINDAR2 = 0xFF;
    ECINDAR0 = 0x00;                // FFFFExx = 0xFF
    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                 // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_ReadStatus;    // Read Status Register
    while(1)                        // waiting spi free
    {
        if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        }
    }
    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                 // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_WREN;          // Write enable
    if(SPIID==SSTID)
    {
        ECINDAR1 = 0xFE;
        ECINDDR = 0xFF;             // SCE# high level
        ECINDAR1 = 0xFD;
        ECINDDR = SPICmd_EWSR;      // Enable Write Status Register
    }
    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                 // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_ReadStatus;    // Read Status Register
    while(1)                        // waiting spi free
    {
        if((ECINDDR&(SPIStatus_WEL+SPIStatus_BUSY))==0x02) // Check write enable and spi not busy
        {
            break;
        }
    }
    ECINDAR3 = 0x00;                //Exit follow mode
    ECINDAR2 = 0x00;
}
void FSPIRomWriteDisable(void)
{
    ECINDAR3 = 0x4F;
    ECINDAR2 = 0xFF;
    ECINDAR0 = 0x00;                // FFFFExx = 0xFF
    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                 // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_ReadStatus;    // Read Status Register
    while(1)                        // waiting spi free
    {
        if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        }
    }
    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                 // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_WRDI;          // Write disable
    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                 // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_ReadStatus;    // Read Status Register
    while(1)                        // waiting spi free
    {
        if((ECINDDR&(SPIStatus_WEL+SPIStatus_BUSY))==0x00) // Check write disable and spi not busy
        {
            break;
        }
    }
    ECINDAR3 = 0x00;                //Exit follow mode
    ECINDAR2 = 0x00;
}
void Eflash_Write_1Byte(void)
{
    ECINDAR3 = 0x4F;
    ECINDAR2 = 0xFF;
    ECINDAR0 = 0x00;                                // FFFFExx = 0xFF
    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                                     // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_ReadStatus;                     // Read Status Register
    while(1)                                           // waiting spi free
    {
        if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        }
    }
    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                                 // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_BYTEProgram;   // Send Program One Data Byte command
    ECINDDR = SPIAddrCycle[0];      // For 256 bytes function limite
    ECINDDR = SPIAddrCycle[1];
    ECINDDR = SPIAddrCycle[2];
    SPIIndex = 0x00;
    ECINDDR = SPIBuffer[0];
    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                                     // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_ReadStatus;    // Read Status Register
    while(1)                                           // waiting spi free
    {
        if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        }
    }
    ECINDAR3 = 0x00;                      // Exit follow mode
    ECINDAR2 = 0x00;                           //
}
BYTE Read_Eflash_Byte(BYTE FA2,BYTE FA1,BYTE FA0)
{
    ECINDAR3 = 0x40; // 0
    ECINDAR2 = FA2;
    ECINDAR1 = FA1;
    ECINDAR0 = FA0;
    return ECINDDR;
}
#pragma ot(7, speed)
void Do_Eflash_Write_1Byte(BYTE OneByte,BYTE Addr2,BYTE Addr1,BYTE Addr0)
{
    SPIBuffer[0] = OneByte;
    SPIAddrCycle[0] = Addr2;
    SPIAddrCycle[1] = Addr1;
    SPIAddrCycle[2] = Addr0;
    DisableAllInterrupt();                      // Disable all interrupt
    LoadSPIFucnToRam(FSPIRomWriteEnable);
    SET_MASK(FBCFG,SSMC);               // enable scatch ROM
    FuncAt_0xFE00();                    // do function in extern ram 0x600
    EnableAllInterrupt();               // Enable all interrupt
    CLEAR_MASK(FBCFG,SSMC);                    // disable scatch ROM
    LoadSPIFucnToRam(Eflash_Write_1Byte);       // Load function to ram
    SET_MASK(FBCFG,SSMC);                       // enable scatch ROM
    FuncAt_0xFE00();                           // do function in extern ram 0x600
    EnableAllInterrupt();               // Enable all interrupt
    CLEAR_MASK(FBCFG,SSMC);                    // disable scatch ROM
    LoadSPIFucnToRam(FSPIRomWriteDisable);          // Load function to ram
    SET_MASK(FBCFG,SSMC);                       // enable scatch ROM
    FuncAt_0xFE00();                           // do function in extern ram 0x600
    EnableAllInterrupt();               // Enable all interrupt
    CLEAR_MASK(FBCFG,SSMC);                    // disable scatch ROM
}

#pragma ot(7, speed)
void Erase_Eflash_1K(BYTE EraseCmd,BYTE FA2,BYTE FA1,BYTE FA0)
{

    DisableAllInterrupt();                      // Disable all interrupt
    LoadSPIFucnToRam(FSPIRomWriteEnable);
    SET_MASK(FBCFG,SSMC);               // enable scatch ROM
    FuncAt_0xFE00();                    // do function in extern ram 0x600

    SPIAEraseCmd = EraseCmd;
    SPIAddrCycle[0] = FA2;
    SPIAddrCycle[1] = FA1;
    SPIAddrCycle[2] = FA0;

    DisableAllInterrupt();          // Disable all interrupt
    LoadSPIFucnToRam(SPI_Erase);    // Load function to ram
    SET_MASK(FBCFG,SSMC);           // enable scatch ROM
    FuncAt_0xFE00();                // do function in extern ram 0x600

    CLEAR_MASK(FBCFG,SSMC);                    // disable scatch ROM
    LoadSPIFucnToRam(FSPIRomWriteDisable);          // Load function to ram
    SET_MASK(FBCFG,SSMC);                       // enable scatch ROM
    FuncAt_0xFE00();                           // do function in extern ram 0x600
    CLEAR_MASK(FBCFG,SSMC);                    // disable scatch ROM

}

/*#pragma ot(7, speed)
void Do_Eflash_Write_16byte_Sign(BYTE *BytePointer,BYTE Addr2,BYTE Addr1,BYTE Addr0)
{

    EFLASHDataPointer= BytePointer;
    SPIBuffer[0x0D] = 0x7F;                 //mirror Size 128KB
    SPIAddrCycle[0] = Addr2;
    SPIAddrCycle[1] = Addr1;
    SPIAddrCycle[2] = Addr0;
    DisableAllInterrupt();                  // Disable all interrupt
    LoadSPIFucnToRam(FSPIRomWriteEnable);
    SET_MASK(FBCFG,SSMC);               // enable scatch ROM
    FuncAt_0xFE00();                    // do function in extern ram 0x600
    CLEAR_MASK(FBCFG,SSMC);                    // disable scatch ROM
    LoadSPIFucnToRam(Eflash_Write_16Byte);          // Load function to ram
    SET_MASK(FBCFG,SSMC);                       // enable scatch ROM
    FuncAt_0xFE00();                           // do function in extern ram 0x600
    CLEAR_MASK(FBCFG,SSMC);                    // disable scatch ROM
    LoadSPIFucnToRam(FSPIRomWriteDisable);          // Load function to ram
    SET_MASK(FBCFG,SSMC);                       // enable scatch ROM
    FuncAt_0xFE00();                           // do function in extern ram 0x600
    CLEAR_MASK(FBCFG,SSMC);                    // disable scatch ROM
}

#if 0
#pragma ot(8, speed)
void FSCEHighLevel( BYTE SpiCmd )
{
    ECINDAR3 = 0x4F;        //0xFF        // Enter follow mode
    ECINDAR2 = 0xFF;
    ECINDAR1 = 0xFE;
    ECINDAR0 = 0x00;
    ECINDDR  = 0xFF;        // SCE# high level
    ECINDDR  = 0xFF;        // SCE# high level
    ECINDAR1 = 0xFD;        // Address:FD00h
    ECINDDR  = SpiCmd;      // SPI Command
}
#pragma ot(8, speed)
void FSPIRomCheckBusy(void)
{
    while(1)
    {
        FSCEHighLevel( 0x05 );  // Read Status Reg (05h)
        if( ~ECINDDR & 0x01 )
        {
            break;
        }
    }
}
#pragma ot(8, speed)
void Write_Eflash_1Byte(BYTE FA2,BYTE FA1,BYTE FA0,BYTE OneByte)
{
    FSPIRomWriteEnable();
    FSCEHighLevel(0x02);    // Others Page program
    ECINDDR = FA2;            // A2
    ECINDDR = FA1;            // A1
    ECINDDR = FA0;            // A0
    ECINDDR = OneByte;
    FSPIRomCheckBusy();
    FSPIRomWriteDisable();
}
#pragma ot(8, speed)
BYTE Erase_Eflash_1K(BYTE FA2,BYTE FA1,BYTE FA0)
{
    FSPIRomWriteEnable();
    FSCEHighLevel( 0xD7 );  // erase command 0x20:Sector 0xD8:Block
    ECINDDR = FA2;        // A2
    ECINDDR = FA1;        // A1
    ECINDDR = FA0;        // A0
    FSPIRomCheckBusy();
    FSPIRomWriteDisable();
    return (0x01);
}
void Copy_Eflash_1K(BYTE SFA2,BYTE SFA1,BYTE SFA0, BYTE DFA2, BYTE DFA1, BYTE DFA0)
{
}
BYTE Read_Eflash_Byte(BYTE FA2,BYTE FA1,BYTE FA0)
{
    ECINDAR3 = 0x40; // 0
    ECINDAR2 = FA2;
    ECINDAR1 = FA1;
    ECINDAR0 = FA0;
    return ECINDDR;
}
#endif
*/
#endif

/*-----------------------------------------------------------------------------
 * @subroutine - ITE_WinFlash
 * @function - ITE WinFlash
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - Run after CacheDma
 *---------------------------------------------------------------------------*/
void ITE_WinFlash(void)
{
#pragma asm
;;;;;--------------------------------------------------------------------------
    MOV     A, #33H
    MOV     DPTR, #1511H            ;PM2DO
    MOVX    @DPTR, A
    MOV     R3, #00H
;;;;;--------------------------------------------------------------------------
_LOOP_WINFLASH:
#if 1
    MOV     DPTR, #1F06H
    MOV     A, #20H
    MOVX    @DPTR, A
#endif
    INC     65H
    MOV     DPTR, #1500H            ;PM1STS
    MOVX    A, @DPTR
    JB      ACC.1, _P6266_IBF       ;PM1STS.P_IBF
    JMP     _WIN_FLASH
;;;;;--------------------------------------------------------------------------
_P6266_IBF:
    JB      ACC.3, _P66_COMMAND     ;PM1STS.P_C_D
    JMP     _P62_DATA
_P66_COMMAND:
    MOV     2FH, #00H               ;BIT:7FH-78H
    MOV     DPTR, #1504H            ;PM1DI
    MOVX    A, @DPTR
    MOV     2EH, A                  ;BIT:77H-70H
    JB      72H,_P66_CMD_84
    JB      71H,_P66_CMD_823
    JMP     _PULSE_SCI
;;;;;--------------------------------------------------------------------------
_P66_CMD_823:
    MOV     C, ACC.0
    CPL     C
    MOV     DPTR, #1500H            ;PM1STS
    MOVX    A, @DPTR
    MOV     ACC.4, C                ;BURST
    MOVX    A, @DPTR
    MOV     A, #90H
    JNC     _OUTPUT_P62
    JMP     _PULSE_SCI
;;;;;--------------------------------------------------------------------------
_P66_CMD_84:
    MOV     DPTR, #1501H            ;PM1DO
    CLR     A
    MOVX    @DPTR, A
;;;;;
    MOV     DPTR, #1500H            ;PM1STS
    MOVX    A, @DPTR
    CLR     ACC.5                   ;PM1STS.SCIEVT = 0
    MOVX    @DPTR, A
;;;;;
    JMP     _PULSE_SCI
;;;;;--------------------------------------------------------------------------
_OUTPUT_P62:
    MOV     DPTR, #1501H            ;PM1DO
    MOVX    @DPTR, A
;;;;;
_PULSE_SCI:
    MOV     DPTR, #1604H            ;PM1STS
    MOVX    A, @DPTR
    CLR     ACC.3
    MOVX    @DPTR, A
;;;;;
    MOV     DPTR, #200BH            ;WNCKR
    CLR     A
    MOVX    @DPTR, A
;;;;;
    MOV     DPTR, #1604H            ;PM1STS
    MOVX    A, @DPTR
    SETB    ACC.3
    MOVX    @DPTR, A
_EXIT_SCI:
    JMP     _WIN_FLASH
;;;;;--------------------------------------------------------------------------
_P62_DATA:  ;[R3]<--[R2]<--PM1DI
    MOV     DPTR, #1504H            ;PM1DI
    MOVX    A, @DPTR
    JNB     70H,_P66_CMD80
    JB      78H,_P66_CMD81
    MOV     R2, A
    SETB    78H
    JMP     _PULSE_SCI
;;;;;--------------------------------------------------------------------------
_P66_CMD81:
    MOV     DPH, #04H               ;EC_SPACE=0400H-04FFH
    MOV     DPL, R2
    MOVX    @DPTR, A
    JMP     _PULSE_SCI
;;;;;--------------------------------------------------------------------------
_P66_CMD80:
    MOV     DPH, #04H               ;EC_SPACE=0400H-04FFH
    MOV     DPL, A
    MOVX    A, @DPTR
    JMP     _OUTPUT_P62
;;;;;--------------------------------------------------------------------------
_WIN_FLASH:
    MOV     DPTR, #130AH            ;KBHIDIR
    MOVX    A, @DPTR
;;;;;
    MOV     DPTR, #1510H            ;PM2STS
    MOVX    A, @DPTR
    JB      ACC.1, _P686C_IBF       ;PM2STS.P_IBF
    JMP     _LOOP_WINFLASH
;;;;;--------------------------------------------------------------------------
_P686C_IBF:
    JB      ACC.3, _P6C_COMMAND     ;PM2STS.P_C_D
    MOV     DPTR, #1514H            ;PM2DI
    MOVX    A, @DPTR
    JMP     _LOOP_WINFLASH
_P6C_COMMAND:
    MOV     DPTR, #1514H            ;PM2DI
    MOVX    A, @DPTR
    CJNE    R3, #01H, _J0_P6C_CMD
    MOV     R3, #00H
    MOV     DPTR, #103FH            ;ECINDDR
    MOVX    @DPTR, A
    JMP     _LOOP_WINFLASH
;;;;;--------------------------------------------------------------------------
_J0_P6C_CMD:
    CJNE    A, #01H,_J1_P6C_CMD
;;;;;--------------------------------------------------------------------------
_P6C_CMD01:
    MOV     A, #0FH
    MOV     DPTR, #103EH            ;ECINDAR3
    MOVX    @DPTR, A

    MOV     A, #0FFH
    MOV     DPTR, #103DH            ;ECINDAR2
    MOVX    @DPTR, A

    MOV     A, #0FEH
    MOV     DPTR, #103CH            ;ECINDAR1
    MOVX    @DPTR, A

    CLR     A
    MOV     DPTR, #103BH            ;ECINDAR0
    MOVX    @DPTR, A
    MOV     DPTR, #103FH            ;ECINDDR
    MOVX    @DPTR, A
    INC     66H                     ;DEBUG COUNTER
    LJMP    _LOOP_WINFLASH
_J1_P6C_CMD:
    CJNE    A, #02H,_J2_P6C_CMD
;;;;;--------------------------------------------------------------------------
_P6C_CMD02:
    MOV     A, #0FDH
    MOV     DPTR, #103CH            ;ECINDAR1
    MOVX    @DPTR, A
    MOV     R3, #01H
    INC     67H                     ;DEBUG COUNTER
    LJMP    _LOOP_WINFLASH
_J2_P6C_CMD:
    CJNE    A, #03H,_J3_P6C_CMD
;;;;;--------------------------------------------------------------------------
_P6C_CMD03:
    MOV     R3, #01H
    INC     68H
    LJMP    _LOOP_WINFLASH
_J3_P6C_CMD:
    CJNE    A, #04H,_J4_P6C_CMD
;;;;;--------------------------------------------------------------------------
_P6C_CMD04:
    MOV     DPTR, #103FH            ;ECINDDR
    MOVX    A, @DPTR
    MOV     DPTR, #1511H            ;PM2DO
    MOVX    @DPTR, A
    INC     69H
    LJMP    _LOOP_WINFLASH
_J4_P6C_CMD:
    CJNE    A, #05H,_J5_P6C_CMD
;;;;;--------------------------------------------------------------------------
_P6C_CMD05:
    CLR     A
    MOV     DPTR, #103EH            ;ECINDAR3
    MOVX    @DPTR, A
    MOV     DPTR, #103DH            ;ECINDAR2
    MOVX    @DPTR, A
    INC     6AH
    LJMP    _LOOP_WINFLASH
_J5_P6C_CMD:
;;;;;
_JX_P6C_CMD:
    CJNE    A, #0FCH,_JL_P6C_CMD
;;;;;--------------------------------------------------------------------------
_P6C_CMD_FC:
    JMP     _EXIT_FLASH
_JL_P6C_CMD:
    LJMP    _LOOP_WINFLASH
;;;;;--------------------------------------------------------------------------
_EXIT_FLASH:
    MOV     DPTR, #0045H            ;WinFlashMark
    MOV     A, #33H
    MOVX    @DPTR, A
    LJMP    200H                    ;main()
;;;;;--------------------------------------------------------------------------
#pragma endasm
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_FLASH.C */