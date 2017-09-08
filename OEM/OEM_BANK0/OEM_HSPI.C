/*-----------------------------------------------------------------------------
 * @file     | OEM_HSPI.C
 *-----------+-----------------------------------------------------------------
 * @function | Host SPI Shared Process
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



/*-----------------------------------------------------------------------------
 * @subroutine - Init_HSPI
 * @function - Init Disable HSPI interface pins
 * @Upstream - By call (Init)
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Init_HSPI(void)
{
#if HSPI
    /* Disable HSPI Pins */
    GPCRH3 = INPUT;
    GPCRH4 = INPUT;
    GPCRH5 = INPUT;
    GPCRH6 = INPUT;
    /* Reset SPI */
    SET_MASK(RSTC4, RSPI);
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Enable_HSPI
 * @function - Enable HSPI interface
 * @Upstream - By call (Init)
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Enable_HSPI(void)
{

}

/*-----------------------------------------------------------------------------
 * @subroutine - Disable_HSPI
 * @function - Disable HSPI interface
 * @Upstream - By call (Init)
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Disable_HSPI(void)
{
#if HSPI_DefferingMode
    CLEAR_MASK(IER7, Int_DeferredSPI);  // Disable HSPI interrupt
    ISR7 = Int_DeferredSPI;         // W/C interrupt status
    //HCTRL2R = 0x80;
#endif

    HCTRL2R = 0x00;

    GPCRH3 = INPUT;                 // Set input mode
    GPCRH4 = INPUT;                 // Set input mode
    GPCRH5 = INPUT;                 // Set input mode
    GPCRH6 = INPUT;                 // Set input mode
#if HSPI_QOFR
    GPCRG1 = INPUT;
    GPCRG6 = INPUT;
    GPCRJ0 = INPUT;
    GPCRJ1 = INPUT;
#endif
    SET_MASK(RSTC4, RSPI);          // Reset SPI
}


/*-----------------------------------------------------------------------------
 * @subroutine - HSPI_RamCode
 * @function - HSPI RamCode Service
 * @Upstream - By call (Init)
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
#if HSPI
//-----------------------------------------------------------------------------
#pragma ot(8, SPEED)
//-----------------------------------------------------------------------------
void HSPI_RamCode(void)
{
    return;
    HINSTC1 = DISSV + DISS + ENDPI + ENDEI; // Allow instruction
    //HINSTC1 = (DISSV+DISS);       // Allow instruction
    ISR7 = Int_DeferredSPI;         // W/C interrupt status

    HSPI_FPT_timeout = 0x00;
    TR0 = 0;                        // Disable timer 0
    ET0 = 0;                        // Disable timer0 interrupt
    TH0 = T_HSPI_ISRTime >> 8;      // set timer0 counter xx ms
    TL0 = T_HSPI_ISRTime;           // set timer0 counter xx ms
    TF0 = 0;                        // clear overflow flag
    TR0 = 1;                        // enable timer0

    while (!TF0)                    // if isn't time out
    {
        if (IS_MASK_SET(ISR7, Int_DeferredSPI)) // Check HSPI isr
        {
            if (DSADR2 == HSPI_ECCodeRomAddrH) // EC code space
            {
                HINSTC1 = DISSV + DISS + ENDPI + ENDEI; // Allow instruction
                //HINSTC1 = (DISSV+DISS);       // Allow instruction
                ISR7 = Int_DeferredSPI;         // W/C interrupt status

                TH0 = T_HSPI_ISRTime >> 8;      // set timer1 counter xx ms
                TL0 = T_HSPI_ISRTime;           // set timer1 counter xx ms
                TF0 = 0;                        // clear overflow flag

        while (1)
        {
            if (IS_MASK_SET(ISR7, Int_DeferredSPI))
            {
                        HINSTC1 = DISSV + DISS + ENDPI + ENDEI; // Allow instruction
                        //HINSTC1 = (DISSV+DISS);     // Allow instruction
                ISR7 = Int_DeferredSPI;     // W/C interrupt status

                        TH0 = T_HSPI_ISRTime >> 8;  // set timer1 counter xx ms
                        TL0 = T_HSPI_ISRTime;       // set timer1 counter xx ms
                        TF0 = 0;
                HSPI_FPT_timeout = 0x00;
                continue;
            }

                    if (TF0)
            {
                        if (++HSPI_FPT_timeout >= 35)  // 3 sec EC auto wake up from ram code.
                {
                    HSPI_FPT_timeout = 0xFF;
                    break;
                }
                        TH0 = T_HSPI_ISRTime >> 8;      // set timer1 counter xx ms
                        TL0 = T_HSPI_ISRTime;           // set timer1 counter xx ms
                        TF0 = 0;                        // clear overflow flag
            }
        }

        WinFlashMark = 0x33;
                TR0 = 0;                // disable timer1
                TF0 = 0;                // clear overflow flag
                ET0 = 1;                // Enable timer1 interrupt

                MainFucnLow = 0x00;     // Set main function low return vector
                MainFucnHigh = 0x02;    // Set main function high return vector
        #pragma asm
                CLR     PSW.3
                CLR     PSW.4           // IRam bank 0
                PUSH    05EH            // Push main function low return vector
                PUSH    05FH            // Push main function high return vector
                RETI                    // Return to main function 0x200
        #pragma endasm
    }

            HINSTC1 = DISSV + DISS + ENDPI + ENDEI; // Allow instruction
            //HINSTC1 = (DISSV+DISS);         // Allow instruction
        ISR7 = Int_DeferredSPI;             // W/C interrupt status

            TH0 = T_HSPI_ISRTime >> 8;  // set timer1 counter xx ms
            TL0 = T_HSPI_ISRTime;       // set timer1 counter xx ms
            TF0 = 0;
        }
    }

    TR0 = 0;                // disable timer1
    TF0 = 0;                // clear overflow flag
    ET0 = 1;                // Enable timer1 interrupt

    TL0 = Timer_1ms;        // Reload timer
    TH0 = Timer_1ms >> 8;   // 1ms
    TR0 = 1;                // Start timer0 running
    ET0 = 1;                // Enable timer0 interrupt
    F_Service_MS_1 = 1;     // Request 1 mS timer service.
}

#pragma ot(8, SPEED)
/*-----------------------------------------------------------------------------
 * @subroutine - HSPI_CmdRamCode
 * @function - HSPI CmdRamCode via command service
 * @Upstream - By call (Init)
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void HSPI_CmdRamCode(void)
{
    RamcodeCmd = 0x00;
    if (RamCodePort == 0x64)
    {
        KBHIKDOR = 0xFA;
    }
    if (RamCodePort == 0x66)
    {
        PM1DO = 0xFA;
    }
#if 0
    if (RamCodePort == 0x6C)
    {
        PM2DO = 0xFA;
    }
#endif
    while (1)
    {
        ITempB01++;
#if HSPI_DefferingMode
        if(IS_MASK_SET(ISR7, Int_DeferredSPI))
        {
            HINSTC1 = DISSV + DISS + ENDPI + ENDEI; // Allow instruction
            //HINSTC1 = (DISSV+DISS);   // Allow instruction
            ISR7 = Int_DeferredSPI;     // W/C interrupt status
        }
        #endif
        if(RamCodePort==0x64)
        {
            if (IS_MASK_CLEAR(KBHISR, IBF)) { continue; }
            if (IS_MASK_CLEAR(KBHISR, C_D))
            {
                RamcodeCmd = KBHIDIR;
                continue;
            }
            else
            {
                RamcodeCmd = KBHIDIR;
            }
        }
        else if (RamCodePort == 0x66)
        {
            if (IS_MASK_CLEAR(PM1STS, P_IBF)) { continue; }
            if (IS_MASK_CLEAR(PM1STS, P_C_D))
            {
                RamcodeCmd = PM1DI;
                continue;
            }
            else
            {
                RamcodeCmd = PM1DI;
            }
        }
#if 0
        else if (RamCodePort == 0x6C)
        {
            if (IS_MASK_CLEAR(PM2STS, P_IBF)) { continue; }
            if (IS_MASK_CLEAR(PM2STS, P_C_D))
            {
                RamcodeCmd = PM2DI;
                continue;
            }
            else
            {
                RamcodeCmd = PM2DI;
            }
            }
#endif
        if ((RamcodeCmd == 0x55) || (RamcodeCmd == 0xB5))
        {
            WinFlashMark = 0x33;
            break;
        }
        else if ((RamcodeCmd == 0xAF) || IS_PCH_SLP_S3_LO() ||
                    IS_PCH_SLP_S4_LO())
        {
            HCTRL2R = 0x00;
            CLEAR_MASK(IER7, Int_DeferredSPI);  // Disable HSPI interrupt
            ISR7 = Int_DeferredSPI; // W/C interrupt status
            GPCRH3 = INPUT;         // Set input mode
            GPCRH4 = INPUT;         // Set input mode
            GPCRH5 = INPUT;         // Set input mode
            GPCRH6 = INPUT;         // Set input mode
            SET_MASK(RSTC4, RSPI);  // Reset SPI

            WDTRST = 1;             // Reset watch dog timer
            WDTEB = 1;              // Enable watch dog
            while (1);              // Wait for watch dog time-out
        }
    }

    _nop_();
    _nop_();
    _nop_();
    _nop_();

#if SUPPORT_GPH0_CLKRUN
    GPCRH0 = ALT;
#endif

    #pragma asm
    EXTRN CODE (main)
    LJMP    main
    #pragma endasm

}
//----------------------------------------------------------------------------
#endif  //HSPI

/*-----------------------------------------------------------------------------
 * @subroutine - ChangePLLFrequency
 * @function - Changing PLL frequency function
 * @Upstream - By call (Init)
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void ChangePLLFrequency(BYTE newseting)
{
    if (newseting != PLLFREQR)
    {
        PLLFREQR = newseting;
        PLLCTRL = 1;
        DisableAllInterrupt();
        PCON = 2;   // enter sleep mode
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - ChangeHSRSMode
 * @function - Changing SPI flash read mode
 * @Upstream - By call (Init)
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void ChangeSPIFlashReadMode(BYTE Mode)
{
    BYTE    restore;

    restore = FLHCTRL1R;
    CLEAR_MASK(restore, SPIFR0 + SPIFR1);

    switch(Mode)
    {
        case SPIReadMode_0:
            break;

        case SPIReadMode_1:
            SET_MASK(restore, SPIFR0);
            break;

        case SPIReadMode_2:
            SET_MASK(restore, SPIFR1);
            break;

        case SPIReadMode_3:
            SET_MASK(restore, (SPIFR0 + SPIFR1));
            break;

        default:
            break;
    }
    FLHCTRL1R = restore;
}

/*-----------------------------------------------------------------------------
 * @subroutine - ChangeHSRSMode
 * @function - Changing HSPI requestmode
 * @Upstream - By call (Init)
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void ChangeHSRSMode(BYTE Mode)
{
    BYTE    restore;

    restore = 0x00;

    switch (Mode)
    {
        case HSPI_RequestSelection_0:
            break;

        case HSPI_RequestSelection_1:
            SET_MASK(restore, BIT3);
            break;

        case HSPI_RequestSelection_2:
            SET_MASK(restore, BIT4);
            break;

        case HSPI_RequestSelection_3:
            SET_MASK(restore, (BIT3 + BIT4));
            break;

        default:
            break;
    }

    HSPICTRL2R = restore+BIT2;
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_HSPI.C */