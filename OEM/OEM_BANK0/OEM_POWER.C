/*-----------------------------------------------------------------------------
 * @file     | OEM_POWER.C
 *-----------+-----------------------------------------------------------------
 * @function | System power sequence control
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
#define DEBUG_POWERSTEP             FALSE
#define SUPPORT_AUTO_S3             FALSE
#define SUPPORT_CHECK_TIMEOUT       FALSE

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_POWERSTEP
#define Power_RamDebug(x)           RamDebug(x)
#else
#define Power_RamDebug(x)           {}
#endif

/*-----------------------------------------------------------------------------
 * @subroutine - PF_XXXXXXX
 * @function - Hook for power sequence control I/O
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* PUBLIC PF_XXXXXX Power Function  ******************************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
void PF_PowerSwitchOFF(void)
{
    //-------------------------------------------------------------------------
    if (IS_EC_PWRSW_UP())
    {
        if (wLockPWRBTN > 0)
        {
            wLockPWRBTN--;
        }
        CLEAR_MASK(PowSwFlag, F_PSW_WAIT_UP);
        PowSwDownTimer = 0;
        PCH_PWRBTN_HI();
        return;
    }
    PCH_PWRBTN_LO();
    //-------------------------------------------------------------------------
    // PowerSwitch Down
    //-------------------------------------------------------------------------
    if (IS_MASK_SET(PowSwFlag, F_PSW_WAIT_UP))
    {
        return;
    }
    //-------------------------------------------------------------------------
    if (PowSwDownTimer < 550)
    {
        PowSwDownTimer++;
    }
    else
    {
        PowSwDownTimer = 0;
        SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
        Oem_TriggerPowerOff(1);
    }
    //-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
BYTE PF_CHECK_TIMEOUT2(WORD OVER_T)
{
    PowSeqWait++;
    if (PowSeqWait > OVER_T)
    {
        PowSeqWait = 0;
        return (1);
    }
    return (0);
}
//-----------------------------------------------------------------------------
BYTE PF_CHECK_TIMEOUT(WORD OVER_T)
{
#if SUPPORT_CHECK_TIMEOUT
    PowSeqWait++;
    if (PowSeqWait > OVER_T)
    {
        PowSeqWait = 0;
        return (1);
    }
    return (0);
#else
    PF_PowerSwitchOFF();
    return (0);
#endif
}
//-----------------------------------------------------------------------------
void PF_HSPI_ON(void)
{
#ifdef HSPI
#if HSPI
    /* Enable HSPI interface if HSPI is supported */
    Enable_HSPI();
#endif
#endif
}
//-----------------------------------------------------------------------------
void PF_HSPI_OFF(void)
{
#ifdef HSPI
#if HSPI
    Disable_HSPI();
#endif
#endif
}
//-----------------------------------------------------------------------------
void PF_PECI_ON(void)
{
#ifdef SUPPORT_PECI
#if SUPPORT_PECI
    GPCRF6 = ALT;
    GCR2 |= PECIE;      /* Enable PECI */
#endif
#endif
}
//-----------------------------------------------------------------------------
void PF_PECI_OFF(void)
{
#ifdef SUPPORT_PECI
#if SUPPORT_PECI
    GPCRF6 = INPUT;
#endif
#endif
}
//-----------------------------------------------------------------------------
void PF_INIT_SIO(void)
{
    Init_SIO();
}
//-----------------------------------------------------------------------------
void PF_INIT_PMIO(void)
{
    //GPCRB? = OUTPUT;      // SIO_A20GATE
    //GPCRB? = OUTPUT;      // SIO_RCIN#
    GPCRG2 = OUTPUT;        // EC_RUN_SCI#
    //GPCRD? = OUTPUT;      // SIO_EXT_SMI#
    EC_SCI_HI();
    //EC_SMI_HI();
    //GATEA20_HI();
    //KBRST_HI();
}
//-----------------------------------------------------------------------------
void PF_PMIO_OFF(void)
{
    //GPCRB5 = INPUT;       // SIO_A20GATE
    //GPCRB6 = INPUT;       // SIO_RCIN#
    GPCRG2 = INPUT;         // SIO_EXT_SCI#
    //GPCRD4 = INPUT;       // SIO_EXT_SMI#
}
//-----------------------------------------------------------------------------
void PF_INIT_PS2(void)
{
#if SUPPORT_SERVICE_PS2
    PS2DeviceInactive();    // For Touchpad issue
    GPCRF4 = ALT;           // PS2 interface
    GPCRF5 = ALT;
#endif
}
//-----------------------------------------------------------------------------
void PF_PS2_OFF(void)
{
#if SUPPORT_SERVICE_PS2
    GPCRF4 = OUTPUT;        // PS2 interface
    GPCRF5 = OUTPUT;
    CLEAR_MASK(GPDRF, BIT(4));
    CLEAR_MASK(GPDRF, BIT(5));

    MouseDriverIn = 0;
    SetPS2InhibitTime(InactiveTime);
#endif
}
//-----------------------------------------------------------------------------
void PF_SMBUS_ON(void)
{
    /* SMBUS-0 */
    //GPCRB3 = ALT; //P2:GPB3,GPB4 Battery
    //GPCRB4 = ALT;
}
//-----------------------------------------------------------------------------
void PF_SMBUS_OFF(void)
{
    /* SMBUS-1 */
    //GPCRC1 = INPUT;
    //GPCRC2 = INPUT;
}
//-----------------------------------------------------------------------------
void PF_RSMRST_HI(void)
{
    PCH_RSMRST_HI();
    Power_RamDebug(0xA5);
}
//-----------------------------------------------------------------------------
void PF_RSMRST_LO(void)
{
	if((xEC_ShutdownCode == 0x01)||(xEC_ShutdownCode== 0x02))
    PCH_RSMRST_LO();
}
//-----------------------------------------------------------------------------
void PF_PWRBTN_HI(void)
{
    PCH_PWRBTN_HI();
    Power_RamDebug(0xA4);
}
//-----------------------------------------------------------------------------
void PF_PWRBTN_LO(void)
{
    PCH_PWRBTN_LO();
    Power_RamDebug(0xA6);
}
//-----------------------------------------------------------------------------
void PF_GATEA20_HI(void)
{
    GATEA20_HI();
}
//-----------------------------------------------------------------------------
void PF_GATEA20_LO(void)
{
    GATEA20_LO();
}
//-----------------------------------------------------------------------------
void PF_PWROK_HI(void)
{
    //PCH_PWROK_HI();
}
//-----------------------------------------------------------------------------
void PF_PWROK_LO(void)
{
    //PCH_PWROK_LO();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* OEM PF_XXXXXX Power Wait Signal Function  *********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
BYTE PF_CHECK_SLP_S3_HI(void)
{
    if (IS_PCH_SLP_S3_HI())
    {
        return (1); /* TRUE: Next Power Function */
    }
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
BYTE PF_CHECK_SLP_S3_LO(void)//ROBERT 20150630
{
    if (IS_PCH_SLP_S3_LO())
    {
        return (1); /* TRUE: Next Power Function */
    }
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
BYTE PF_CHECK_SLP_S4_HI(void)
{
    if (IS_PCH_SLP_S4_HI())
    {
    	Forece_Shutdown_timer = 0;
        return (1); /* TRUE: Next Power Function */
    }
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}

BYTE PF_CHECK_SLP_S4_LO(void)//ROBERT 20150630
{
    if (IS_PCH_SLP_S4_LO())
    {
        return (1); /* TRUE: Next Power Function */
    }
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
BYTE PF_CHECK_SLP_S5_HI(void)
{
    if (IS_PCH_SLP_S5_HI())
    {
        return (1); /* TRUE: Next Power Function */
    }
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
BYTE PF_CHK_V5P0A_PGOOD_HI(void)
{
    if (IS_V5P0A_PGOOD_HI())
    {
        return (1); /* TRUE: Next Power Function */
    }
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
BYTE PF_CHK_PCH_PWROK_HI(void)
{
    if (IS_PCH_PWROK_HI())
    {
        return (1); /* TRUE: Next Power Function */
    }
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}

void PF_PCH_PWROK_HI(void)
{
	PCH_PWROK_HI();
	GPCRF7=INPUT;
	
}
//-----------------------------------------------------------------------------
BYTE PF_CHK_VCC_DDR_PWROK_HI(void)
{
    if (IS_VCC_DDR_PWROK_HI())
    {
        return (1); /* TRUE: Next Power Function */
    }
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------
BYTE PF_CHK_SUS_PWR_DN_ACK_HI(void)
{
    if (IS_SLP_S0_N_HI())
    {
        return (1); /* TRUE: Next Power Function */
    }
    if ((PF_CHECK_TIMEOUT(1000)) != 0)
    {
        PowerOnFailed = 1;
        return (1);
    }
    return (0);     /* FALSE: Continues Waiting */
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* OEM PF_XXXXXX Power Function  *********************************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
void PF_AC_PRESENT_HI(void)
{
    //KSOHGDMRR |= BIT3;    //KSO11
    KSOH1 |= BIT3;
}
//-----------------------------------------------------------------------------
void PF_AC_PRESENT_LO(void)
{
    //KSOHGDMRR &= (~BIT3); //KSO11
    KSOH1 &= (~BIT3);
}
//-----------------------------------------------------------------------------
void PF_CHK_AC_PRESENT(void)
{
    if (IS_ADAPTER_IN())
    {
        PF_AC_PRESENT_HI();
    }
    else
    {
        PF_AC_PRESENT_LO();
    }
    /* TEST */
    //PF_AC_PRESENT_HI();
}
//-----------------------------------------------------------------------------
void PF_VIBRATOR_ON(void)
{
    //KSOHGDMRR |= BIT4;    //KSO12
    //KSOH1 |= BIT4;
}
//-----------------------------------------------------------------------------
void PF_VIBRATOR_OFF(void)
{
    //KSOHGDMRR &= (~BIT4); //KSO12
    //KSOH1 &= (~BIT4);
    ViberatorTimer = 0;
}
//-----------------------------------------------------------------------------
void PF_PM_BATLOW_HI(void)
{
    PM_BATLOW_HI();
}
//-----------------------------------------------------------------------------
void PF_PM_BATLOW_LO(void)
{
    PM_BATLOW_LO();
}
//-----------------------------------------------------------------------------
void PF_EC_PWR_LATCH_HI(void)
{
    EC_PWR_LATCH_HI();
    Power_RamDebug(0xA2);
}
//-----------------------------------------------------------------------------
void PF_EC_PWR_LATCH_LO(void)
{
	if(xEC_ShutdownCode == 0x01)
    EC_PWR_LATCH_LO();
}
//-----------------------------------------------------------------------------
void PF_EC_PROCHOT_HI(void)
{
    EC_PROCHOT_HI();
}
//-----------------------------------------------------------------------------
void PF_EC_PROCHOT_LO(void)
{
    EC_PROCHOT_LO();
    Power_RamDebug(0xA7);
}
//-----------------------------------------------------------------------------
void PF_SLP_SX_N_HI(void)
{
    SLP_SX_N_HI();
}
//-----------------------------------------------------------------------------
void PF_SLP_SX_N_LO(void)
{
    SLP_SX_N_LO();
}
//-----------------------------------------------------------------------------
void PF_EC_SYS_PWROK_HI(void)
{
    EC_SYS_PWROK_HI();
    Power_RamDebug(0xAB);
}
//-----------------------------------------------------------------------------
void PF_EC_SYS_PWROK_LO(void)
{
    EC_SYS_PWROK_LO();
}
//-----------------------------------------------------------------------------
void PF_ALLSYSPWRGD_HI(void)
{
    //KSOHGDMRR |= BIT4;    //KSO12
    KSOH1 |= BIT4;
    Power_RamDebug(0xA9);
}
//-----------------------------------------------------------------------------
void PF_ALLSYSPWRGD_LO(void)
{
    //KSOHGDMRR &= (~BIT4); //KSO12
    KSOH1 &= (~BIT4); //ALLSYSPWRGD
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * @subroutine - CheckResetSource
 * @function - CheckResetSource
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void CheckResetSource(void)
{

}

/*-----------------------------------------------------------------------------
 * @subroutine - SystemWarmBoot
 * @function - SystemWarmBoot
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SystemWarmBoot(void)
{

}

/*-----------------------------------------------------------------------------
 * @subroutine - INIT_COMMON_OFF
 * @function - INIT_COMMON_S3S4S5
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void INIT_COMMON_OFF(void)
{
    SysPowState = _SYSTEM_S5;
    //EC_TYPEC_POUT_EN_HI();//robert 20150801
    DLY_S3_S4 = 8;
	#if Support_RTC_hang25_wakeup
	Forece_Shutdown_timer = 0;
	
	if(xEC_RTC_SupportFlag == 0x6A)
		{
		//xEC_RTC_test_counter++;
		}
	else
		{
		xEC_RTC_test_counter = 0;
		Clear_Memory_Range(0x0E00,0xFF);
		}
	#endif
    //-------------------------------------------------------------------------
    /* GPIO FUNCTION POWER OFF */
    //-------------------------------------------------------------------------
    PF_PECI_OFF();
#if SUPPORT_GPD2_PLTRST
    GPCRD2 = INPUT;     //PLTRST#
#endif
#if SUPPORT_GPB0B1_UART
    GPCRB0 = INPUT;     //UART1_RXD
    GPCRB1 = INPUT;     //UART1_TXD
    GCR1 &= (~BIT(0));
#endif
    GPCRI0 = INPUT;
    GPCRI1 = INPUT;
    SPCTRL1 &= (~BIT7);
    //-------------------------------------------------------------------------
    /* PROCESS PUBLIC INITIALIZE FOR POWER OFF */
    //-------------------------------------------------------------------------
    CLEAR_MASK(KBHISR, SYSF);
    Ccb42_SYS_FLAG = 0;
#if TouchPad_only
    PowerOffClearTPPendingData();
#endif
    ClearSCIEvent();
    SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
    //-------------------------------------------------------------------------
    /* OEM PLATFORM INITIALIZE FOR POWER OFF */
    //-------------------------------------------------------------------------
    Reload_EC_Ver();	
    CLEAR_MASK(SystemFlag1, F_ACPI_MODE);
#if SupportLowPowerLED
    LED_OFF_CNT = 10;
#endif
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - INIT_COMMON_ON
 * @function - INIT_COMMON_ON
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void INIT_COMMON_ON(void)
{
    SysPowState = _SYSTEM_S0;
	//I2C_DD_Resend = 8;
    GPCRH0 = 0x00;//bbbbb
    //-------------------------------------------------------------------------
    /* GPIO FUNCTION POWER ON */
    //-------------------------------------------------------------------------
#if SUPPORT_GPD2_PLTRST
    GPCRD2 = ALT;       //PLTRST#
#endif
#if SUPPORT_GPB0B1_UART
    GPCRB0 = ALT;       //UART1_RXD
    GPCRB1 = ALT;       //UART1_TXD
    GCR1 |= (~BIT(0));
#endif
    //GPCRI0 = ALT;
    //GPCRI1 = ALT;
    SPCTRL1 |= (BIT7);
    //-------------------------------------------------------------------------
    /* PROCESS PUBLIC INITIALIZE FOR POWER ON */
    //-------------------------------------------------------------------------
    ClearSCIEvent();
    CLEAR_MASK(KBHISR, SYSF);
    SET_MASK(KBHISR, KEYL);
    SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
    Ccb42_SYS_FLAG = 0;
#if TouchPad_only
    PowerOffClearTPPendingData();
#endif
    //-------------------------------------------------------------------------
    /* OEM PLATFORM INITIALIZE FOR POWER ON */
    //-------------------------------------------------------------------------
    //SET_MASK(SystemFlag1, F_ACPI_MODE);
    	SET_MASK(xEC_LID_STATUS,F_LID_STA);
	//------------------------------------------------------------------------
#if Support_PWRDOWN_SLPS3_INT
	WUEMR10 = BIT2;//GPF2 failing-edge-INT103
	//WUEMR11 = BIT1;//GPB6 failing-edge-INT110

	WUESR10 = BIT2;
	//WUESR11 = BIT1;
	
	SET_MASK(IER12, Int_WKO98);//INT103 GPF2
	//SET_MASK(IER13, Int_WKO105);//INT110 GPB6
#endif
	xEC_ShutdownCode=0;
    //-------------------------------------------------------------------------
	
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - GO_INIT_S0
 * @function - GO_INIT_S0
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void GO_INIT_S0(void)
{
    INIT_COMMON_ON();
#if SupportLowPowerLED
    LED_OFF_CNT = 10;
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - GO_INIT_S3_TO_S0
 * @function - GO_INIT_S3_TO_S0
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void GO_INIT_S3_TO_S0(void)
{
    INIT_COMMON_ON();
}
/*-----------------------------------------------------------------------------
 * @subroutine - GO_INIT_S3
 * @function - GO_INIT_S3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void GO_INIT_S3(void)
{
    EC_SYS_PWROK_LO(); //bbbbb
    KSOH1 &= (~BIT4); //ALLSYSPWRGD
    SLP_SX_N_LO();

    INIT_COMMON_OFF();
    SysPowState = _SYSTEM_S3;
}

/*-----------------------------------------------------------------------------
 * @subroutine - GO_INIT_S5
 * @function - GO_INIT_S5
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void GO_INIT_S5(void)
{
    INIT_COMMON_OFF();
	GPCRF7=OUTPUT;
	PCH_PWROK_LO();
	
   // CLEAR_MASK(SystemFlag1, F_ACPI_MODE);
}

/*-----------------------------------------------------------------------------
 * @subroutine - GO_INIT_G3
 * @function - GO_INIT_G3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void GO_INIT_G3(void)
{
    SysPowState = _SYSTEM_G3;
    INIT_COMMON_OFF();
}

/*-----------------------------------------------------------------------------
 * @table - sSEQ_S5_to_S0
 *
 *---------------------------------------------------------------------------*/
const sPowerSEQ code sSEQ_S5_to_S0[] =
{
    /* Function                   Delay   Wait   */
    /* Hook                       x 1ms   status */
    { 0x0000,                       0,      0,  },  /* Dummy Require */
    { PF_EC_PWR_LATCH_HI,          10,      0,  },  /* (6) EC->PW */
    { PF_CHK_V5P0A_PGOOD_HI,        0,      1,  },  /* (7) PW->EC */
    { PF_PM_BATLOW_HI,              0,      0,  },
    { PF_PWRBTN_HI,                 0,      0,  },
    { PF_RSMRST_HI,                20,      0,  },  /* (8) EC->PCH */
    { PF_CHK_SUS_PWR_DN_ACK_HI,    90,      1,  },  /* (9) PW->EC */
    { PF_CHK_AC_PRESENT,           20,      0,  },  /* (9b) EC->PW */
    { PF_PWRBTN_LO,                20,      0,  },  /* (11) EC->PCH */
    { PF_EC_PROCHOT_LO,             0,      0,  },
    { PF_VIBRATOR_OFF,              0,      0,  },
    //{ PF_CHECK_SLP_S5_HI,         0,      1,  },
    { PF_CHECK_SLP_S4_HI,           0,      1,  },  /* (12) PCH->EC */
    { PF_CHECK_SLP_S3_HI,           0,      1,  },  /* (13) PCH->EC */
    { PF_PWRBTN_HI,                 0,      0,  },
    { PF_INIT_PMIO,                 0,      0,  },
    { PF_CHK_VCC_DDR_PWROK_HI,    	0,      1,  },  /* (14) PW->EC */
    { PF_SLP_SX_N_HI,             	1,      0,  },  /* (15) EC->PW */
    { PF_ALLSYSPWRGD_HI,            1,      0,  },  /* (15a) EC->PW */
    { PF_INIT_SIO,                  0,      0,  },
	{ PF_PCH_PWROK_HI,				0,		0,	},
    { PF_CHK_PCH_PWROK_HI,          0,      1,  },  /* (16) PW->EC */
    { PF_PECI_ON,                   0,      0,  },
    { PF_SMBUS_ON,                 99,      0,  },
    { PF_EC_SYS_PWROK_HI,           0,      0,  },  /* (17) EC->SYS */
    { GO_INIT_S0,                   0,      0,  },  /* Sequence End */
};
/*-----------------------------------------------------------------------------
 * @table - sSEQ_S0_to_S5
 *
 *---------------------------------------------------------------------------*/
const sPowerSEQ code sSEQ_S0_to_S5[] =
{
    /* Function                   Delay   Wait   */
    /* Hook                       x 1ms   status */
    { 0x0000,                       0,      0,  },  /* Dummy Require */
    { PF_SLP_SX_N_LO,               0,      0,  },
    { PF_ALLSYSPWRGD_LO,            0,      0,  }, //ROBERT 20150707
    { PF_EC_SYS_PWROK_LO,           0,      0,  },
    { PF_EC_PROCHOT_LO,             0,      0,  },
    { PF_VIBRATOR_OFF,              0,      0,  },
    { PF_PECI_OFF,                  0,      0,  },
    { PF_PMIO_OFF,                  0,      0,  },
    { PF_SMBUS_OFF,                 0,      0,  },
    { PF_PM_BATLOW_LO,              0,      0,  },
    { PF_RSMRST_LO,                 0,      0,  },
    { PF_PWRBTN_HI,                20,      0,  },
    { PF_AC_PRESENT_LO,             0,      0,  },
    { PF_EC_PWR_LATCH_LO,           0,      0,  },
    { GO_INIT_S5,                   0,      0,  },  /* Sequence End */

};
/*-----------------------------------------------------------------------------
 * @table - sSEQ_S0_to_S3
 *
 *---------------------------------------------------------------------------*/
const sPowerSEQ code sSEQ_S0_to_S3[] =
{
    /* Function                   Delay   Wait   */
    /* Hook                       x 1ms   status */
    { 0x0000,                       0,      0,  },  /* Dummy Require */
   // { PF_EC_SYS_PWROK_LO,           5,      0,  },
   // { PF_SLP_SX_N_LO,               0,      0,  },
   // { PF_ALLSYSPWRGD_LO,            0,      0,  },//bbbbb
    { PF_VIBRATOR_OFF,              0,      0,  },
    { GO_INIT_S3,                   0,      0,  },  /* Sequence End */
};
/*-----------------------------------------------------------------------------
 * @table - sSEQ_S3_to_S0
 *
 *---------------------------------------------------------------------------*/
const sPowerSEQ code sSEQ_S3_to_S0[] =
{
    /* Function                   Delay   Wait   */
    /* Hook                       x 1ms   status */
    { 0x0000,                       0,      0,  },  /* Dummy Require */
    { PF_CHK_VCC_DDR_PWROK_HI,      0,      1,  },
    { PF_CHK_SUS_PWR_DN_ACK_HI,     0,      1,  },
    { PF_SLP_SX_N_HI,               1,      0,  },
    { PF_ALLSYSPWRGD_HI,            0,      1,  },//bbbbb
    { PF_CHK_PCH_PWROK_HI,          0,      1,  },
    { PF_PECI_ON,                   0,      0,  },
    { PF_SMBUS_ON,                 99,      0,  },
    { PF_EC_SYS_PWROK_HI,           0,      0,  },
    { PF_VIBRATOR_OFF,              0,      0,  },
    { GO_INIT_S3_TO_S0,             0,      0,  },  /* Sequence End */

};
/*-----------------------------------------------------------------------------
 * @table - sSEQ_S5_to_G3
 *
 *---------------------------------------------------------------------------*/
const sPowerSEQ code sSEQ_S5_to_G3[] =
{
    /* Function                   Delay   Wait   */
    /* Hook                       x 1ms   status */
    { 0x0000,                       0,      0,  },  /* Dummy Require */

    { GO_INIT_G3,                   0,      0,  },  /* Sequence End */
};
/*-----------------------------------------------------------------------------
 * @table - sSEQ_G3_to_S5
 *
 *---------------------------------------------------------------------------*/
const sPowerSEQ code sSEQ_G3_to_S5[] =
{
    /* Function                   Delay   Wait   */
    /* Hook                       x 1ms   status */
    { 0x0000,                       0,      0,  },  /* Dummy Require */

    { GO_INIT_S5,                   0,      0,  },  /* Sequence End */
};
/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PST_G3_to_S5
 * @function - Oem_PST_G3_to_S5
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_PST_G3_to_S5(void)
{
    while (CtrlPowStep < (sizeof(sSEQ_G3_to_S5) / sizeof(sPowerSEQ)))
    {
        if (sSEQ_S5_to_G3[CtrlPowStep].checkstatus == 0x00)
        {
            (sSEQ_S5_to_G3[CtrlPowStep].func)();
            PowSeqDelay = sSEQ_S5_to_G3[CtrlPowStep].delay;
            CtrlPowStep++;
            PowSeqWait = 0;
            if (PowSeqDelay != 0x00)
            {
                break;
            }
        }
        else
        {
            if ((sSEQ_S5_to_G3[CtrlPowStep].func)())
            {
                PowSeqWait = 0;
                PowSeqDelay = sSEQ_S5_to_G3[CtrlPowStep].delay;
                CtrlPowStep++;
            }
            break;
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PST_S5_to_G3
 * @function - Oem_PST_S5_to_G3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_PST_S5_to_G3(void)
{
    while (CtrlPowStep < (sizeof(sSEQ_S5_to_G3) / sizeof(sPowerSEQ)))
    {
        if (sSEQ_S5_to_G3[CtrlPowStep].checkstatus == 0x00)
        {
            (sSEQ_S5_to_G3[CtrlPowStep].func)();
            PowSeqDelay = sSEQ_S5_to_G3[CtrlPowStep].delay;
            CtrlPowStep++;
            PowSeqWait = 0;
            if (PowSeqDelay != 0x00)
            {
                break;
            }
        }
        else
        {
            if ((sSEQ_S5_to_G3[CtrlPowStep].func)())
            {
                /* Check Status Pass */
                PowSeqWait = 0;
                PowSeqDelay = sSEQ_S5_to_G3[CtrlPowStep].delay;
                CtrlPowStep++;
            }
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PST_S5_to_S0
 * @function - Oem_PST_S5_to_S0
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_PST_S5_to_S0(void)
{
    while (CtrlPowStep < (sizeof(sSEQ_S5_to_S0) / sizeof(sPowerSEQ)))
    {
        if (sSEQ_S5_to_S0[CtrlPowStep].checkstatus == 0x00)
        {
            (sSEQ_S5_to_S0[CtrlPowStep].func)();
            PowSeqDelay = sSEQ_S5_to_S0[CtrlPowStep].delay;;
            CtrlPowStep++;
            PowSeqWait = 0;
            if (PowSeqDelay != 0x00)
            {
                break;
            }
        }
        else
        {
            if ((sSEQ_S5_to_S0[CtrlPowStep].func)())
            {
                PowSeqWait = 0;
                PowSeqDelay = sSEQ_S5_to_S0[CtrlPowStep].delay;
                CtrlPowStep++;
            }
            break;
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PST_S0_to_S5
 * @function - Oem_PST_S0_to_S5
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_PST_S0_to_S5(void)
{
    while (CtrlPowStep < (sizeof(sSEQ_S0_to_S5) / sizeof(sPowerSEQ)))
    {
        if (sSEQ_S0_to_S5[CtrlPowStep].checkstatus == 0x00)
        {
            (sSEQ_S0_to_S5[CtrlPowStep].func)();
            PowSeqDelay = sSEQ_S0_to_S5[CtrlPowStep].delay;
            CtrlPowStep++;
            PowSeqWait = 0;
            if (PowSeqDelay != 0x00)
            {
                break;
            }
        }
        else
        {
            if ((sSEQ_S0_to_S5[CtrlPowStep].func)())
            {
                PowSeqWait = 0;
                PowSeqDelay = sSEQ_S0_to_S5[CtrlPowStep].delay;
                CtrlPowStep++;
            }
            break;
        }
    }
    //DLY_S3_S4 = 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PST_S0_to_S3
 * @function - Oem_PST_S0_to_S3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_PST_S0_to_S3(void)
{
    while (CtrlPowStep < (sizeof(sSEQ_S0_to_S3) / sizeof(sPowerSEQ)))
    {
        if (sSEQ_S0_to_S3[CtrlPowStep].checkstatus == 0x00)
        {
            (sSEQ_S0_to_S3[CtrlPowStep].func)();
            PowSeqDelay = sSEQ_S0_to_S3[CtrlPowStep].delay;
            CtrlPowStep++;
            PowSeqWait = 0;
            if (PowSeqDelay != 0x00)
            {
                break;
            }
        }
        else
        {
            if ((sSEQ_S0_to_S3[CtrlPowStep].func)())
            {
                PowSeqDelay = sSEQ_S0_to_S3[CtrlPowStep].delay;
                CtrlPowStep++;
            }
            break;
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PST_S3_to_S0
 * @function - Oem_PST_S3_to_S0
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_PST_S3_to_S0(void)
{
    while (CtrlPowStep < (sizeof(sSEQ_S3_to_S0) / sizeof(sPowerSEQ)))
    {
        if (sSEQ_S3_to_S0[CtrlPowStep].checkstatus == 0x00)
        {
            (sSEQ_S3_to_S0[CtrlPowStep].func)();
            PowSeqDelay = sSEQ_S3_to_S0[CtrlPowStep].delay;
            CtrlPowStep++;
            PowSeqWait = 0;
            if (PowSeqDelay != 0x00)
            {
                break;
            }
        }
        else
        {
            if ((sSEQ_S3_to_S0[CtrlPowStep].func)())
            {
                PowSeqDelay = sSEQ_S3_to_S0[CtrlPowStep].delay;
                CtrlPowStep++;
            }
            break;
        }
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_SpecialPowOnSequence
 * @function - Oem_SpecialPowOnSequence
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_SpecialPowOnSequence(void)
{
    SLP_SX_N_HI();
    //EC_TYPEC_POUT_EN_LO();
    USBC_LoopTimer = 0;
    while(1)
    {
        if (F_Service_MS_1)
        {
            F_Service_MS_1 = 0;
            if (SysPowState == _PST_S5_to_S0)
            {
                Oem_PST_S5_to_S0();
                if (PowSeqDelay != 0x00)
                {
                    Power_RamDebug(0xDE);
                    Power_RamDebug(PowSeqDelay);
                    break;
                }
            }
            else if (SysPowState == _PST_S3_to_S0)
            {
                Oem_PST_S3_to_S0();
            }
            USBC_LoopTimer++;
        }
        if ((SysPowState == _SYSTEM_S0) &&
            (USBC_LoopTimer > 200))
        {
            break;
        }
    }
    /* Change to Master Mode */
    Init_SMBus();
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_SysPowSequence
 * @function - Oem_SysPowSequence
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_SysPowSequence(void)
{
    /*-----------------------------------------------------------------------*/
    // POWER SWQUENCE QUICKLY TIMING
    /*-----------------------------------------------------------------------*/
     if ((SysPowState == _PST_S5_to_S0) || (SysPowState == _PST_S3_to_S0))
    {
       /* if (IS_VCC_DDR_PWROK_HI() && IS_PCH_SLP_S3_HI() &&
            IS_SLP_S0_N_HI())
        {
            Power_RamDebug(0xCC);
            Power_RamDebug(CtrlPowStep);
            Oem_SpecialPowOnSequence();
            return;
        }*/
        if(IS_PCH_SLP_S3_HI())
			SLP_SX_N_HI();
    }
    /*-----------------------------------------------------------------------*/
    // POWER SWQUENCE DELAY
    /*-----------------------------------------------------------------------*/
    if (PowSeqDelay != 0x00)
    {
        PowSeqDelay--;              //1m Sec count base

        if (PowSeqDelay != 0x00)
        {
            return;
        }
    }
    /*-----------------------------------------------------------------------*/
    // POWER SWQUENCE STEP
    /*-----------------------------------------------------------------------*/
    switch (SysPowState)
    {
        //---------------------------------------------------------------------
    case _PST_G3_to_S5:     // Power State Transitions: G3 -> S5
        Oem_PST_G3_to_S5();
        break;
        //---------------------------------------------------------------------
    case _PST_S5_to_S0:     // Power State Transitions: S5 -> S0
        Oem_PST_S5_to_S0();
        break;
        //---------------------------------------------------------------------
    case _PST_S0_to_S3:     // Power State Transitions: S0 -> S3
        Oem_PST_S0_to_S3();
        break;
        //---------------------------------------------------------------------
    case _PST_S3_to_S0:     // Power State Transitions: S3 -> S0
        Oem_PST_S3_to_S0();
        break;
        //---------------------------------------------------------------------
    case _PST_S0_to_S5:     // Power State Transitions: S0 -> S5
        Oem_PST_S0_to_S5();
        break;
        //---------------------------------------------------------------------
    case _PST_S5_to_G3:     // Power State Transitions: S5 -> G3
        Oem_PST_S5_to_G3();
        break;
        //---------------------------------------------------------------------
    default:
        SysPowState = 0;
        return;
        //---------------------------------------------------------------------
    }
    /*-----------------------------------------------------------------------*/
}

/*-----------------------------------------------------------------------------
 * @subroutine - Set_SysPowState
 * @function - Set_SysPowState
 * @upstream - By call
 * @input    - SetValue
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Set_SysPowState(BYTE SetValue)
{
    CtrlPowStep = 1;
    PowSeqDelay = 0;
    SysPowState = SetValue;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_TriggerPowerOn
 * @function - Oem_TriggerPowerOn
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_TriggerPowerOn(void)
{
    Set_SysPowState(_PST_S5_to_S0);
    PowerOnFailed = 0;
    SMBA_DEV1_DLY = 3000;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_TriggerPowerOff
 * @function - Oem_TriggerPowerOff
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_TriggerPowerOff(BYTE ShutdownCode)
{
    xEC_ShutdownCode = ShutdownCode;
    Set_SysPowState(_PST_S0_to_S5);
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_PowSwToPWRBTN
 * @function - Oem_PowSwToPWRBTN
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_PowSwToPWRBTN(void)
{
#if Support_CombinationKey
	if(SysPowState == _SYSTEM_S0)
	   {
	   if(DebounceGPI3 > 0)
	   {
		 if (IS_EC_PWRSW_UP())
		{
		PowSwDownTimer=0;
		wLockPWRBTN = 0;
		}
	   return;
	   }
	   
	   if (DebounceGPI6 > 0)
	   {
		   if (IS_EC_PWRSW_UP())
		   {
			   if (DebounceGPI6 == 10)
			   e0_prefix_code(0x71, BREAK_EVENT); //del key
			   if (DebounceGPI6 == 5)
			   e0_prefix_code(0x14, BREAK_EVENT); //Control key
			   if (DebounceGPI6 == 1)
			   e0_prefix_code(0x11, BREAK_EVENT); //alt key
				DebounceGPI6 --;
				PowSwDownTimer=0;
				wLockPWRBTN = 0;
		   }
		   return;
	   }
	   }
#endif
    //-------------------------------------------------------------------------
    if (IS_EC_PWRSW_UP())
    {
        if (wLockPWRBTN > 0)
        {
            wLockPWRBTN--;
        }
        PCH_PWRBTN_HI();
        CLEAR_MASK(PowSwFlag, F_PSW_WAIT_UP);
        PowSwDownTimer = 0;
        return;
    }
    //-------------------------------------------------------------------------
    // PowerSwitch Down
    //-------------------------------------------------------------------------
    if (IS_MASK_SET(PowSwFlag, F_PSW_WAIT_UP))
    {
        return;
    }
    //-------------------------------------------------------------------------
    PCH_PWRBTN_LO();
    if (PowSwDownTimer < 5500)
    {
        PowSwDownTimer++;
    }
    else
    {
        PowSwDownTimer = 0;
        SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
        Oem_TriggerPowerOff(1);
    }
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_G3S5_PowSwitch
 * @function - Oem_G3S5_PowSwitch
 * @upstream - Oem_SysPowState_G3->Hook_Timer10msEventA
 * @input    -
 * @return   -
 * @note     -
 *---------------------------------------------------------------------------*/
void Oem_G3S5_PowSwitch(void)
{
    //-------------------------------------------------------------------------
    if (IS_EC_PWRSW_UP())
    {
        if (PowSwLockTimer > 0)
        {
            PowSwLockTimer--;
            return;
        }
        PowSwDebounce = 0;
        PowSwDownTimer = 0;
        CLEAR_MASK(PowSwFlag, F_PSW_WAIT_UP);
		CLEAR_MASK(MISC_EVENT,EC_RESET_PW);
        return;
    }
    //dead battery detect---------------------------------------------------------
    /*if (IS_MASK_SET(PowerSource, F_AC_ON_LINE))
        {
          if( BAT1_Voltage < 6400)
            {
                SET_MASK(PowerSource,F_BAT1_CRITICAL);
            }
          else
            {
                CLEAR_MASK(PowerSource,F_BAT1_CRITICAL);
            }
        }
        */
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    AutoBootTimer = 0;
    SetAutoBootTimer = 0;
    //-------------------------------------------------------------------------
    if (IS_MASK_SET(PowSwFlag, F_PSW_WAIT_UP))
    {
        return;
    }
	//if (IS_MASK_SET(MISC_EVENT,EC_RESET_PW))
	//{
	//	return;
	//}
    //-------------------------------------------------------------------------
    if (PowSwLockTimer > 0)
    {
        PowSwLockTimer--;
        return;
    }
    //-------------------------------------------------------------------------
    if (PowSwDebounce < 50)
    {
        PowSwDebounce++;
    }
    else
    {
        PowSwDownTimer++;
#if 0//SupportLowPowerLED
        if(SMBA_FloatingTimer > 0)
        {
            return;
        }
#endif
        if (PowSwDownTimer > 2000)
        {
#if SupportLowPowerLED
             //if((BAT1_RelativeStateOfChgL > 64)&&
            //(IS_MASK_CLEAR(PowerSource, F_AC_ON_LINE)))
            if((BAT1_RelativeStateOfChgL < 4)&&IS_ADAPTER_OUT())
                {
                PowSwDownTimer = 0;
                PowSwDebounce = 0;
                SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
                BAT1_Low_ShutdownCount = 54;
                DLY_S3_S4 = 6;
                }
            else
                {
				 PowSwDownTimer = 0;
                PowSwDebounce = 0;
                SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
                Oem_TriggerPowerOn();
                }
#else

                PowSwDownTimer = 0;
                PowSwDebounce = 0;
                SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
                Oem_TriggerPowerOn();

#endif
        }
    }
    //-------------------------------------------------------------------------
}

#if 0
/*-----------------------------------------------------------------------------
 * @subroutine - Oem_S5_PowSwitch
 * @function - Oem_S5_PowSwitch
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_S5_PowSwitch(void)
{
    //-------------------------------------------------------------------------
#if SUPPORT_LID_SWITCH
    if (IS_LID_SW_CLOSE())
    {
        return;
    }
#endif
    //-------------------------------------------------------------------------
    if (IS_EC_PWRSW_UP())
    {
        if (PowSwLockTimer > 0)
        {
            PowSwLockTimer--;
            return;
        }
        PowSwDebounce = 0;
        PowSwDownTimer = 0;
        CLEAR_MASK(PowSwFlag, F_PSW_WAIT_UP);
        return;
    }
    //-------------------------------------------------------------------------
    AutoBootTimer = 0;
    SetAutoBootTimer = 0;
    //-------------------------------------------------------------------------
    if (IS_MASK_SET(PowSwFlag, F_PSW_WAIT_UP))
    {
        return;
    }
    //-------------------------------------------------------------------------
    if (PowSwLockTimer > 0)
    {
        PowSwLockTimer--;
        return;
    }
    //-------------------------------------------------------------------------
    if (PowSwDebounce < 5)
    {
        PowSwDebounce++;
    }
    else
    {
        PowSwDownTimer++;
        if (PowSwDownTimer > 200)
        {
            PowSwDownTimer = 0;
            PowSwDebounce = 0;
            SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
            Oem_TriggerPowerOn();
        }
    }
    //-------------------------------------------------------------------------
}
#endif

#if 0
/*-----------------------------------------------------------------------------
 * @subroutine - Oem_AutoBoot
 * @function - Automatic Power on (Test Utility)
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_AutoBoot(void)
{
    if ((SysPowState == _SYSTEM_S0) || (SetAutoBootTimer == 0))
    {
        return;
    }
    if (AutoBootTimer == 0)
    {
        AutoBootTimer = SetAutoBootTimer;
    }
    else
    {
        AutoBootTimer--;
        if (AutoBootTimer == 0)
        {
            PowSwDebounce = 0;
            PowSwDownTimer = 0;
            SET_MASK(PowSwFlag, F_PSW_WAIT_UP);
            if (SysPowState == _SYSTEM_S5)
            {
                Oem_TriggerPowerOn();
            }
            else if (SysPowState == _SYSTEM_S3)
            {
                if (IS_PCH_SLP_S3_LO())
                {
                    PCH_PWRBTN_LO();
                    DelayXms(20);
                    PCH_PWRBTN_HI();
                }
            }
        }
    }
}
#endif

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_SysPowState_S0_S1
 * @function - Oem_SysPowState_S0_S1
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_SysPowState_S0_S1(void)
{
#if 1
    Oem_PowSwToPWRBTN();
    if ((IS_PCH_SLP_S3_LO())&& (IS_PCH_SLP_S4_HI()))
    {
        Set_SysPowState(_PST_S0_to_S3);
    }
    else if ((IS_PCH_SLP_S4_LO()) && (IS_VCC_DDR_PWROK_LO())&&(IS_PCH_SLP_S3_LO()))
    {
        Set_SysPowState(_PST_S0_to_S5);
    }
#endif
#if Support_RTC_hang25_wakeup
	if(IS_PCH_SLP_S3_HI()||IS_PCH_SLP_S4_HI())
			{
			if(Forece_Shutdown_timer > 0)
				{
				Forece_Shutdown_timer--;
				if(Forece_Shutdown_timer==0)
					{
						if(xEC_RTC_WakeupFlag == 0x6A)
						{
							xEC_RTC_Wakeuptimer = 60000;
							xEC_RTC_WakeupFlag=0;
							xEC_RTC_lastwakeup_counter_H=xEC_RTC_test_counter;
							//RamDebugh25(xEC_RTC_lastwakeup_counter_L);
							//RamDebugh25(xEC_RTC_lastwakeup_counter_H);
							xEC_RTC_lastwakeup_counter_H=0;
							xEC_RTC_lastwakeup_counter_L=0;
						}
						Oem_TriggerPowerOff(2);
						xEC_Forece_Shutdown_counter++;

					}
				}
			}

#endif

}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_SysPowState_S3
 * @function - Oem_SysPowState_S3
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_SysPowState_S3(void)
{
    Oem_PowSwToPWRBTN();

    if (IS_PCH_SLP_S3_HI())
    {
        Set_SysPowState(_PST_S3_to_S0);
    }
    else if ((IS_PCH_SLP_S3_LO()) && (IS_PCH_SLP_S4_LO()) &&
            (IS_VCC_DDR_PWROK_LO()))
    {
            Set_SysPowState(_PST_S0_to_S5);
    }

}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_SysPowState_S4_S5
 * @function - Oem_SysPowState_S4_S5
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Oem_SysPowState_S4_S5(void)
{
	if ((IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_ADAPTER_IN)) && (IS_MASK_CLEAR(PowerSource, F_BAT1_PRESENT)))
	{
		if ((I2C_EJ898A_PD_WATT < 10)&&
		(IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_LEGACY_5V_ADAPTER) || (IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_IS_5V_ADAPTER))))
			{
				return;
			}
		if((BAT1_Voltage > 0) && (BAT1_Voltage <= 7200))
			{
				return;
			}

		if (IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_LEGACY_5V_ADAPTER))
			{
				return;
			}
	}

    if (SMBA_DEV1_STS & F_DEV_INIT)
    {
        Oem_G3S5_PowSwitch();
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Oem_SysPowState_G3
 * @function - Oem_SysPowState_G3
 * @upstream -
 * @input    -
 * @return   -
 * @note     -
 *---------------------------------------------------------------------------*/
void Oem_SysPowState_G3(void)
{
	if ((IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_ADAPTER_IN)) && (IS_MASK_CLEAR(PowerSource, F_BAT1_PRESENT)))
	{
		if ((I2C_EJ898A_PD_WATT < 10)&&
		(IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_LEGACY_5V_ADAPTER) || (IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_IS_5V_ADAPTER))))
			{
				return;
			}
		if((BAT1_Voltage > 0) && (BAT1_Voltage <= 7200))
			{
				return;
			}

		if (IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_LEGACY_5V_ADAPTER))
			{
				return;
			}
	}
    if (SMBA_DEV1_STS & F_DEV_INIT)
    {
        Oem_G3S5_PowSwitch();
    }
}
//-----------------------------------------------------------------------------

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
#if SUPPORT_POWER_SAVING
//-----------------------------------------------------------------------------
// Sleep / Wakeup Init register table
//-----------------------------------------------------------------------------
const sInitSleepWakeReg code InitSleepWakeTBL[] =
{
    //----------------------------------------------------
    /* Switch GPIO Mode for Power Saving                */
    /* GPIO         Entry               Exit            */
#if 0 /* Need Check if open SUPPORT_POWER_SAVING */
    { &GPCRA0,      INPUT,              OUTPUT          },
    { &GPCRA1,      INPUT,              OUTPUT          },
    { &GPCRB0,      INPUT,              OUTPUT          },
    { &GPCRB1,      INPUT,              OUTPUT          },
    { &GPCRB3,      INPUT,              INPUT           },
    { &GPCRB4,      INPUT,              INPUT           },
    { &GPCRB5,      INPUT,              OUTPUT          },
    { &GPCRC1,      INPUT,              ALT             },
    { &GPCRC2,      INPUT,              ALT             },
    { &GPCRE0,      INPUT,              INPUT           },
    { &GPCRE4,      ALT,                INPUT           },
    { &GPCRE7,      INPUT,              OUTPUT          },
    { &GPCRF3,      INPUT,              INPUT           },
    { &GPCRF7,      INPUT,              INPUT           },
    { &GPCRG2,      INPUT,              INPUT           },
    { &GPCRG6,      INPUT,              OUTPUT          },
    //----------------------------------------------------
    { &GPDRA,       0x00,               0x00,           },
    { &GPDRB,       0x00,               0x00,           },
    { &GPDRC,       0x00,               0x00,           },
    { &GPDRD,       0x00,               0x00,           },
    { &GPDRE,       0x00,               0x00,           },
    { &GPDRF,       0x00,               0x00,           },
    { &GPDRG,       0x04,               0x04,           },
#endif
    //----------------------------------------------------
    /* Switch Special Function Mode for Power Saving    */
    { &ADCCFG,      0x00,               0x00            },
    { &DACPWRDN,    0x1F,               0x1F            },
    { &ZTIER,       0x00,               0x00            },
    { &KSOL,        0x00,               0x00            },
    { &KSOH1,       0x00,               0x00            },
    //----------------------------------------------------
    /* Wake-Up Edge Mode Register Setting               */
    //{ &WUEMR1,    0x00,               0x00            },
    { &WUEMR2,      0x20,     0x00            },
    //----------------------------------------------------
    /* Wake-Up Sense Register Clear                     */
    { &WUESR1,      0xFF,               0xFF            },
    { &WUESR2,      0xFF,               0xFF            },
    { &WUESR3,      0xFF,               0xFF            },
    { &WUESR4,      0xFF,               0xFF            },
    { &WUESR6,      0xFF,               0xFF            },
    { &WUESR7,      0xFF,               0xFF            },
    { &WUESR8,      0xFF,               0xFF            },
    { &WUESR9,      0xFF,               0xFF            },
    { &WUESR10,     0xFF,               0xFF            },
    { &WUESR11,     0xFF,               0xFF            },
    { &WUESR12,     0xFF,               0xFF            },
    { &WUESR13,     0xFF,               0xFF            },
    { &WUESR14,     0xFF,               0xFF            },
    //----------------------------------------------------
    /* Wake-Up Enable Register Setting                  */
    //{ &WUENR1,    _SET_EN_WUENR1,     _SET_WK_WUENR1  },
    //{ &WUENR3,    _SET_EN_WUENR3,     _SET_WK_WUENR3  },
    //{ &WUENR4,    _SET_EN_WUENR4,     _SET_WK_WUENR4  },
    //----------------------------------------------------
    /* Interrupt Edge/Level-Triggered Mode Setting      */
    //{ &IELMR0,    0x00,               0x00            },
    //{ &IELMR1,    0x00,               0x00            },
    //----------------------------------------------------
    /* Interrupt Polarity Register Setting              */
    //{ &IPOLR0,    0x00,               0x00            },
    //{ &IPOLR1,    0x00,               0x00            },
    //{ &IPOLR2,    0x00,               0x00            },
    //{ &IPOLR3,    0x00,               0x00            },
    //{ &IPOLR4,    0x00,               0x00            },
    //{ &IPOLR5,    0x00,               0x00            },
    //{ &IPOLR6,    0x00,               0x00            },
    //{ &IPOLR7,    0x00,               0x00            },
    //{ &IPOLR8,    0x00,               0x00            },
    //{ &IPOLR9,    0x00,               0x00            },
    //----------------------------------------------------
    /* Clear Interrupt Status Register                  */
    { &ISR0,        0xFF,               0xFF            },
    { &ISR1,        0xFF,               0xFF            },
    { &ISR2,        0xFF,               0xFF            },
    { &ISR3,        0xFF,               0xFF            },
    { &ISR4,        0xFF,               0xFF            },
    { &ISR5,        0xFF,               0xFF            },
    { &ISR6,        0xFF,               0xFF            },
    { &ISR7,        0xFF,               0xFF            },
    { &ISR8,        0xFF,               0xFF            },
    { &ISR9,        0xFF,               0xFF            },
    { &ISR10,       0xFF,               0xFF            },
    { &ISR11,       0xFF,               0xFF            },
    { &ISR12,       0xFF,               0xFF            },
    { &ISR13,       0xFF,               0xFF            },
    { &ISR14,       0xFF,               0xFF            },
    { &ISR15,       0xFF,               0xFF            },
    { &ISR16,       0xFF,               0xFF            },
    { &ISR17,       0xFF,               0xFF            },
    { &ISR18,       0xFF,               0xFF            },
    { &ISR19,       0xFF,               0xFF            },
    //----------------------------------------------------
    /* Interrupt Enable Register Settin                 */
    { &IER0,        _SET_EN_IER0,       _SET_WK_IER0    },  //INT7..0
    { &IER1,        _SET_EN_IER1,       _SET_WK_IER1    },  //INT15..8
    { &IER2,        _SET_EN_IER2,       _SET_WK_IER2    },  //INT23..16
    { &IER3,        _SET_EN_IER3,       _SET_WK_IER3    },  //INT31..24
    { &IER4,        _SET_EN_IER4,       _SET_WK_IER4    },  //INT39..32
    { &IER5,        _SET_EN_IER5,       _SET_WK_IER5    },  //INT47..40
    { &IER6,        _SET_EN_IER6,       _SET_WK_IER6    },  //INT55..48
    { &IER7,        _SET_EN_IER7,       _SET_WK_IER7    },  //INT63..56
    { &IER8,        _SET_EN_IER8,       _SET_WK_IER8    },  //INT71..64
    { &IER9,        _SET_EN_IER9,       _SET_WK_IER9    },  //INT79..72
    { &IER10,       _SET_EN_IER10,      _SET_WK_IER10   },
    { &IER11,       _SET_EN_IER11,      _SET_WK_IER11   },
    { &IER12,       _SET_EN_IER12,      _SET_WK_IER12   },
    { &IER13,       _SET_EN_IER13,      _SET_WK_IER13   },
    { &IER14,       _SET_EN_IER14,      _SET_WK_IER14   },
    { &IER15,       _SET_EN_IER15,      _SET_WK_IER15   },
    { &IER16,       _SET_EN_IER16,      _SET_WK_IER16   },
    { &IER17,       _SET_EN_IER17,      _SET_WK_IER17   },
    { &IER18,       _SET_EN_IER18,      _SET_WK_IER18   },
    //----------------------------------------------------
};
/*-----------------------------------------------------------------------------
 * @subroutine - InitEnterPowerDown
 * @function - InitEnterPowerDown
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void InitEnterPowerDown(void)
{
    BYTE    i;

    i = 0;
    while (i < (sizeof(InitSleepWakeTBL) / 4))
    {
        *InitSleepWakeTBL[i].reg = InitSleepWakeTBL[i].entrysleep;
        i++;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - InitWakeFromDeepSleep
 * @function - InitWakeFromDeepSleep
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void InitWakeFromPowerDown(void)
{
    BYTE    i;

    i = 0;
    while (i < (sizeof(InitSleepWakeTBL) / 4))
    {
        *InitSleepWakeTBL[i].reg = InitSleepWakeTBL[i].exitsleep;
        i++;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - EnterPowerSaving
 * @function - Enter Power Saving
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void EnterPowerSaving(void)
{
    F_MCU_POWERDOWN = 1;
    //-------------------------------------------------------------------------
#if SUPPORT_EXT1_WDT_RESET
    EWDCNTLHR = 0;
    EWDCNTLLR = 240;    //4 min.
#endif
    //-------------------------------------------------------------------------
#if SUPPORT_MCU_WDT_RESET
    /* Disable internal watchdog */
    WDTCON = 0x00;
#endif
    //-------------------------------------------------------------------------
#if 0   /* External Timer 2 Wake up */
    //CLEAR_MASK(IER7, eINT_58);
    //ISR7 = eINT_58;
    ET2PSR = ET_SOURCE_32768Hz;
    /* 10000h = 65536/32768 = 2S */
    ET2CNTLH2R = 5;    /* 10s */
    ET2CNTLHR = 0x00;
    ET2CNTLLR = 0x00;
#endif
    //-------------------------------------------------------------------------
    InitEnterPowerDown();
    _nop_();
    _nop_();
    EA = 1;         /* Enable global interrupt */
#if 1               /* Deep Sleep(For Max. Power Saving */
    PLLCTRL = 0x01;
    PCON = 0x02;    /* MCU into Sleep (Deep Sleep) mode. */
#else
    PLLCTRL = 0x03;
    _nop_();
    PCON = 0x02;    /* MCU into DeepDoze Mode */
#endif
    /* Wake-up Delay */
    _nop_();        /* 1st // Repeat "nop" eight times immediately */
    _nop_();        /* 2nd // for internal bus turn-around. */
    _nop_();        /* 3rd */
    _nop_();        /* 4th */
    _nop_();        /* 5th */
    _nop_();        /* 6th */
    _nop_();        /* 7th */
    _nop_();        /* 8th */
    F_MCU_POWERDOWN = 0;
    PLLCTRL = 1;
    InitWakeFromPowerDown();
    //-------------------------------------------------------------------------
#if SUPPORT_MCU_WDT_RESET
    /* 1/9.2MHz*2^26=7.3sec */
    CKCON = 0xC0;
    /* Enable internal watchdog */
    WDTCON = 0x03;
#endif
    //-------------------------------------------------------------------------
    Init_GPIO();
#if SUPPORT_KEYBOARD_SCAN
    Enable_Any_Key_Irq();   // Enable Keyboard
#endif
    Init_Timers();
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - CheckPowerSaving
 * @function - Check Power Saving
 * @upstream - 10ms
 * @input    - None
 * @return   - 1: Enter Power Saving, 0: Reject
 * @note     - None
 *---------------------------------------------------------------------------*/
BYTE CheckPowerSaving(void)
{
    if ((IS_ADAPTER_IN()) || (SysPowState == _SYSTEM_S0))
    {
        /* Skip Deep-Sleep if Adapter On-Line */
       wPowerSavingDelay = _ENTER_SLEEP_TIMER;    /* 10 sec Deep-Sleep timer */
        return (0);
    }
#if 0
    /* Here is battery mode and system none S0 */
#if (SUPPORT_S3_DEEPSLEEP == FALSE)
    if (SysPowState == _SYSTEM_S3)
    {
        wPowerSavingDelay = _ENTER_SLEEP_TIMER;    /* 10 sec Deep-Sleep timer */
        return (0);
    }
#endif
#endif
    /* Count down entry timer */
    if (wPowerSavingDelay > 0)
    {
        wPowerSavingDelay--;
        return (0);
    }
    wPowerSavingDelay = 500;    /* Preset wake-up 500mSec */
    PowerSavingCount++;
    return (1);
}
//-----------------------------------------------------------------------------
#endif  //SUPPORT_POWER_SAVING
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_POWER.C */
