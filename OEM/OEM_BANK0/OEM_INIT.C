/*-----------------------------------------------------------------------------
 * @file     | OEM_INIT.C
 * ----------+-----------------------------------------------------------------
 * @function | OEM Initialize
 * ----------+-----------------------------------------------------------------
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


/*-----------------------------------------------------------------------------
 * @subroutine - Oem_StartUp
 * @function - Oem_StartUp
 * @upstream - hook from STARTUP.A51
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_StartUp(void)
{
    if (IS_MASK_CLEAR(GPDRD,BIT(5)) && IS_MASK_CLEAR(GPDRC,BIT(0)) &&
        IS_MASK_CLEAR(GPDRE,BIT(4)))
    {
        //FLHCTRL3R = 0x18;
        FLHCTRL3R = 0x28;   //bella20150907
        #if 1
        ETWCFG   = 0x20;
        EWDCNTLR = 0x01;    // for 1ms counter
        EWDKEYR = 0x5A;     // External WDTreset not match
        #endif
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Init_WDT
 * @function - The function of init. WDT registers
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Init_WDT(void)
{
#if SUPPORT_EXT1_WDT_RESET
    EWDCNTLHR = 0;
    EWDCNTLLR = SET_WDT_TIMER;
    ETWCFG = EWDKEYEN+LET1CNTL+LET1PS+LETWCFG;
#endif

#if SUPPORT_MCU_WDT_RESET
    CKCON = 0xC0;       //1/9.2MHz*2^26=7.3sec
    WDTCON = 0x03;      //Enable internal watchdog
#endif

#if SUPPORT_PWRSW_RESET
    GCR10 = PWRSW_WDT2_12S;
    //GCR8 |= PWSW2EN;
    //GCR9 |= PWSWDTGPEN;
    GCR9 |= PWSW2EN2;
    SET_MASK(GCR8, BIT4);  // enable 8s EC reset 
#endif
}

#if 0
/*-----------------------------------------------------------------------------
 * @subroutine - Init_PWM_Regs
 * @function - The function of init. SMBus Regs
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
const sREG_INIT_DEF code Init_PWM_table[] =
{
    /* PWM Initialization */
    { &ZTIER,       0x00    },  // Disable (Init required)

    { &PCFSR,       0x0B    },  // Using EC Clock 9.2MHz base for all
    { &CLK6MSEL,    0x00    },

    { &C0CPRS,      0x01    },  // 00: F = 23 KHz Prescaler 0
    { &CTR,         0xC8    },

    { &C4CPRS,      0x34    },  // 01: F = 1 KHZ Prescaler 1
    { &C4MCPRS,     0x00    },
    { &CTR1,        0xFF    },

    { &C6CPRS,      0x01    },  // 10: Auto Dimm
    { &C6MCPRS,     0x00    },
    { &CTR2,        0xFF    },

    { &C7CPRS,      0xD8    },  // 11: F = 200Hz
    { &C7MCPRS,     0x04    },
    { &CTR3,        0x28    },

    /* === PCSSGH ===   === PCSSGL ===  */
    /* PA7,PA6,PA5,PA4  PA3,PA2,PA1,PA0 */
    /* 00  00  00  00   00  00  00  00  */
    { &PCSSGH,      0x00    },  // PA7..PA4
    { &PCSSGL,      0x0C    },  // PA3..PA0
#if 0
    { &PWM0LCR1,    0x35    },
    { &PWM0LCR2,    0x22    },
    { &PWM1LCR1,    0x35    },
    { &PWM1LCR2,    0x22    },
#endif
    { &ZTIER,       0x02    },  // PWM Clock Enable
    { &DCR1,        0x00    },  // Default
    { &DCR2,        0x00    },  // Default
    { &DCR3,        0x00    },  // Default
    { &DCR4,        0x00    },  // Default

};
//-----------------------------------------------------------------------------
void Init_PWM(void)
{
    ITempB01 = 0;
    while (ITempB01 < (sizeof(Init_PWM_table) / sizeof(sREG_INIT_DEF)))
    {
        Tmp_XPntr = Init_PWM_table[ITempB01].address;
        *Tmp_XPntr = Init_PWM_table[ITempB01].initdata;
        ITempB01++;
    }
}
#endif

/*-----------------------------------------------------------------------------
 * @subroutine - Init_SMBus
 * @function - The function of init. SMBus Regs
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
const sREG_INIT_DEF code Init_SMBus_table[] =
{
    { &SMB4P7USL,   0x28    },  /* 100KHz */
    { &SMB4P0USH,   0x25    },
    { &SMB300NS,    0x03    },
    { &SMB250NS,    0x02    },
    { &SMB25MS,     0x19    },
    { &SMB45P3USL,  0xA5    },
    { &SMBS4P3USH,  0x01    },
    { &SMB4P7A4P0H, 0x00    },

    { &HOCTL2_A,    0x01    },
    { &HOCTL_A,     0x03    },
    { &HOCTL_A,     0x01    },
    { &HOSTA_A,     0xFF    },
    { &SCLKTS_A,    0x11    },  /* 0x11:50KHz,0x12:100KHz,0x13:400KHz */

    { &HOCTL2_B,    0x01    },
    { &HOCTL_B,     0x03    },
    { &HOCTL_B,     0x01    },
    { &HOSTA_B,     0xFF    },
#if SUPPORT_SMBUS_B_100KHz
    { &SCLKTS_B,    0x12    },  /* 0x11:50KHz,0x12:100KHz,0x13:400KHz */
#else
    { &SCLKTS_B,    0x11    },  /* 0x11:50KHz,0x12:100KHz,0x13:400KHz */
#endif
#if 0
    { &HOCTL2_C,    0x01    },
    { &HOCTL_C,     0x03    },
    { &HOCTL_C,     0x01    },
    { &HOSTA_C,     0xFF    },
    { &SCLKTS_C,    0x11    },  /* 0x11:50KHz,0x12:100KHz,0x13:400KHz */

    { &HOCTL2_D,    0x01    },
    { &HOCTL_D,     0x03    },
    { &HOCTL_D,     0x01    },
    { &HOSTA_D,     0xFF    },
    { &SCLKTS_D,    0x11    },  /* 0x11:50KHz,0x12:100KHz,0x13:400KHz */
#endif
#ifdef SUPPORT_SMB_SLAVE_A
#if SUPPORT_SMB_SLAVE_A   //Special Contrl
    { &SLVISEL,     _SMB_CH0    },
    //{ &SLVISEL,   _SMB_CH1    },
    //{ &SLVISEL,   _SMB_CH2    },
    //{ &SLVISEL,   _SMB_CH3    },
    { &HOCTL2_A,    0x21        },  // Enable SMBus Slave
    { &SICR_A,      0x03        },  // Enable slave interrupt
    { &RESLADR_A,   0x68        },  // HID slave address = 0x68
    { &RESLADR2_A,  0xF6        },  // Slave address 2 for ACPI = 0xEC
    { &HOCTL_A,     0x02        },  // Kill current host transaction
    { &HOCTL_A,     0x00        },  // Kill current host transaction
    { &HOSTA_A,     0xFF        },  // Clear all master status
    { &SLSTA_A,     0xFF        },  // Clear all slave status
    { &SCLKTS_A,    0x12        },
#endif
#endif
};
//-----------------------------------------------------------------------------
void Init_SMBus(void)
{
    ITempB01 = 0;
    while (ITempB01 < (sizeof(Init_SMBus_table) / sizeof(sREG_INIT_DEF)))
    {
        Tmp_XPntr = Init_SMBus_table[ITempB01].address;
        *Tmp_XPntr = Init_SMBus_table[ITempB01].initdata;
        ITempB01++;
    }
    /* SMBus Channel D Enable. */
    //GCR2 |= SMB4E;
}
//-----------------------------------------------------------------------------
void Init_ADC(void)
{
    /* Initial ADC registers */
    ADCCFG |= BIT0;
    ADCCFG |= (AINITB + DOVE + EOCE);
    VCH0CTL = 0x80;
    VCH1CTL = 0x81;
    VCH2CTL = 0x82;
    VCH3CTL = 0x83;
#ifndef ITE_CHIP_IT851X
    //VCH4CTL = (DATVAL + VCHEN); /* For IT8528E/IT858X */
    //VCH5CTL = (DATVAL + VCHEN); /* For IT8528E/IT858X */
    //VCH6CTL = (DATVAL + VCHEN); /* For IT8528E/IT858X */
    //VCH7CTL = (DATVAL + VCHEN); /* For IT8528E/IT858X */
#endif
    ADCCFG = 0;
}
/*-----------------------------------------------------------------------------
 * @subroutine - Oem_Initialization
 * @function - Initialize the registers, data variables, and oem functions
 *             after kernel init. function.
 * @upstream - hook from CORE_MAIN.C
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_Initialization(void)
{
	XBYTE RSTStatus1 ;
    BAT1_ChargePauseTimer = 0;
    //-------------------------------------------------------------------------
#if 0
#ifdef HSPI
    Init_HSPI();
#endif
#ifdef SPIReadMode
    ChangeSPIFlashReadMode(SPIReadMode);
#endif
#ifdef HSRSMode
    ChangeHSRSMode(HSRSMode);
#endif
#ifdef PLLFrequency
    ChangePLLFrequency(PLLFrequency);
#endif
    //-------------------------------------------------------------------------
#endif
    Init_Cache();
#if 0
    ET1PSR = ET_SOURCE_32768Hz;
    ET1CNTLHR = 0x80;   // 10000h = 32768/32768 = 1S
    ET1CNTLLR = 0x00;

    ET2PSR = ET_SOURCE_32768Hz;
    ET2CNTLH2R = 0x01;  // 10000h = 65536/32768 = 2S
    ET2CNTLHR = 0x00;
    ET2CNTLLR = 0x00;
#endif
    //-------------------------------------------------------------------------
    Init_GPIO();
    Init_SMBus();
    //Init_PWM();
    Init_ADC();
    /* DAC Initialization */
    DACPWRDN = 0x00;
#if SUPPORT_SERVICE_KBSCAN
    Init_Kbd();
#endif
    Init_WDT();
    Init_SIO();
    //-------------------------------------------------------------------------
    // Load I2EC Setting
    //SPCTRL1 = Init_I2EC;
    //BADRSEL = Init_BADR;
    //SWCBALR = Init_SWCBALR;
    //SWCBAHR = Init_SWCBAHR;
    //-------------------------------------------------------------------------
#if ITE_CHIP_SPI_eFLASH
    Init_EC_Indirect_Selection(SPI_selection_internal);
#else
    Init_EC_Indirect_Selection(SPI_selection_external);
#endif
    //-------------------------------------------------------------------------
#if 1   /* 1: Using Kernel Function */
    Do_SPI_Read_ID();
    SPIID = SSTID;          /* Set eFlash SPIID */
#else
    CacheDma(0, SPI_Read_ID);
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    EA = 0;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    SPI_Read_ID();
    SCRA1H = 0x03;
#endif
    //-------------------------------------------------------------------------
    /* LOAD SPI TABLE. */
    //-------------------------------------------------------------------------
    ECIndirectFastRead(0x00, 0xF0, 0x00,
                        SPI_selection_internal, 512, &EJ898A_RAM_C[0]);
#if SupportP80_Restore
    ECIndirectFastRead(0x01, 0xF0, 0x00,
                        SPI_selection_internal, 256, &P80_RAM_9[0]);
#endif
    //-------------------------------------------------------------------------
	 #if SUPPORT_PWRSW_RESET
	RSTStatus1 = SPCTRL4;
	if(IS_MASK_SET(RSTStatus1, BIT1))
	{
//		PowerOnWDT = T_EC8SHWRST;
		SPCTRL4 = 0x02;
		SET_MASK(MISC_EVENT,EC_RESET_PW);
	
	}
	#endif
	Reload_EC_Ver();
    //Update_ACPI_Battery();    /* TEST */
    //-------------------------------------------------------------------------
    Ccb42 = 0x65;
    SMBA_FloatingTimer = 10;    //100ms x 10 = 1 Sec
    DLY_S3_S4 = 8;
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - Init_ClearRam
 * @function - The function of clearing external ram for OEM code
 *             Clear external ram (0x100~0xFFF)
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Init_ClearRam(void)
{
    PORT_BYTE_PNTR byte_register_pntr;

    byte_register_pntr = 0x100;
#if SUPPORT_EC_RAM2K
    /* Clear external ram (0x100~0xFFF) */
    while (byte_register_pntr < 0x0FFF)
    {
        *byte_register_pntr = 0;
        byte_register_pntr++;
    }
#else
    /* Clear external ram (0x100~0x7FF) */
    while (byte_register_pntr < 0x0800)
    {
        *byte_register_pntr = 0;
        byte_register_pntr++;
    }
#endif
}

#if SUPPORT_EC_RAM2K
/*-----------------------------------------------------------------------------
 * @subroutine - Init_Cache
 * @function - Init. DMA for scratch sram
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
const sDMAScratchSRAM code asDMAScratchSRAM[] =   /* For 8500 Dino */
{
    /* 1024 bytes (externl ram 0x800 ~ 0xBFF) */
    {   &SCRA1H,    &SCRA1M,    &SCRA1L },
    /* 512 bytes  (externl ram 0xC00 ~ 0xDFF) */
    {   &SCRA2H,    &SCRA2M,    &SCRA2L },
    /* 256 bytes  (externl ram 0xE00 ~ 0xEFF) */
    {   &SCRA3H,    &SCRA3M,    &SCRA3L },
    /* 256 bytes  (externl ram 0xF00 ~ 0xFFF) */
    {   &SCRA4H,    &SCRA4M,    &SCRA4L }
};
//-----------------------------------------------------------------------------
void  CacheDma(BYTE sramnum, WORD addr)
{
    *asDMAScratchSRAM[sramnum].scarh = 0x80;
    /* high byte of function address */
    *asDMAScratchSRAM[sramnum].scarm = (WORD) addr >> 8;
    /* low byte of function address */
    *asDMAScratchSRAM[sramnum].scarl = (WORD) addr & 0xff;
    /* start cache dma */
    *asDMAScratchSRAM[sramnum].scarh = 0x00;
}
#endif
//-----------------------------------------------------------------------------
void Init_Cache(void)
{
#if SUPPORT_EC_RAM2K      /* Dino For 8500 no cache ram 0x800 ~ 0xFFF */

#if HSPI
#if HSPI_DefferingMode
    /* Cache to memory 0xF00 ~ 0xFFF */
    CacheDma(3, HSPI_RamCode);
#endif
#endif
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_ECExitFollowMode
 * @function - EC leaves follow mode or EC scatch ROM and jump to main function
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - Before jump to main function
 *             [WinFlashMark = 0x33;] is necessary.
 *---------------------------------------------------------------------------*/
void Hook_ECExitFollowMode(void)
{
    Init_Cache();

#if HSPI_DefferingMode
    /* Enable HSPI interrupt */
    SET_MASK(IER7, Int_DeferredSPI);
#endif
    Reload_EC_Ver();
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_ECRetunrMainFuncKeepCondition
 * @function - EC leaves follow mode or EC scatch ROM and jump to main function
 * @upstream - By call
 * @input    - None
 * @return   - 0x33 or 0x00
 * @note     - 1. Before jump to main function if want to keep EC setting
 *                [return(0x33);] is necessary.
 *             2. If you don't understand the use of
 *                Hook_ECRetunrMainFuncKeepCondition function, don't change
 *                anything.
 *             3. Always at bank0 (0x9000)
 *---------------------------------------------------------------------------*/
BYTE Hook_ECRetunrMainFuncKeepCondition(void)
{
    if (WinFlashMark == 0x33)
    {
        /* SPI Flash update */
        Hook_Setup_Scanner_Pntr();
        Reload_EC_Ver();
        return(0x33);
    }
    else
    {
        return(0x00);
    }
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_INIT.C */