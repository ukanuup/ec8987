/*-----------------------------------------------------------------------------
 * @file     | OEM_GPIO.C
 * ----------+-----------------------------------------------------------------
 * @function | GPIO initialize & configuration
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
//#define

//-----------------------------------------------------------------------------
/* asInitGPIOReg */
//-----------------------------------------------------------------------------
const sInitGPIOReg code asInitGPIOReg[] =
{
    { &GCR,     GCR_Init            },
    { &GCR1,    GCR1_Init           },
    { &GCR2,    GCR2_Init           },
    { &GCR22,   GCR22_Init          },

    { &GPDRA,   PortA_Init          },
    { &GPDRB,   PortB_Init          },
    { &GPDRC,   PortC_Init          },
    { &GPDRD,   PortD_Init          },
    { &GPDRE,   PortE_Init          },
    { &GPDRF,   PortF_Init          },
    { &GPDRG,   PortG_Init          },
    { &GPDRH,   PortH_Init          },
    { &GPDRJ,   PortJ_Init          },

    { &GPCRA0,  PortA0_Ctrl         },
    { &GPCRA1,  PortA1_Ctrl         },
    //{ &GPCRA2,  PortA2_Ctrl       },
    //{ &GPCRA3,  PortA3_Ctrl       },
    //{ &GPCRA4,  PortA4_Ctrl       },
    //{ &GPCRA5,  PortA5_Ctrl       },
    //{ &GPCRA6,  PortA6_Ctrl       },
    //{ &GPCRA7,  PortA7_Ctrl       },

    { &GPCRB0,  PortB0_Ctrl         },
    { &GPCRB1,  PortB1_Ctrl         },
    //{ &GPCRB2,  PortB2_Ctrl       },
    { &GPCRB3,  PortB3_Ctrl         },
    { &GPCRB4,  PortB4_Ctrl         },
    { &GPCRB5,  PortB5_Ctrl         },
    { &GPCRB6,  PortB6_Ctrl         },
    //{ &GPCRB7,  PortB7_Ctrl       },

    { &GPCRC0,  PortC0_Ctrl         },
    { &GPCRC1,  PortC1_Ctrl         },
    { &GPCRC2,  PortC2_Ctrl         },
    //{ &GPCRC3,  PortC3_Ctrl       },
    //{ &GPCRC4,  PortC4_Ctrl       },
    //{ &GPCRC5,  PortC5_Ctrl       },
    //{ &GPCRC6,  PortC6_Ctrl       },
    //{ &GPCRC7,  PortC7_Ctrl       },

    { &GPCRD0,  PortD0_Ctrl         },
    //{ &GPCRD1,  PortD1_Ctrl       },
    { &GPCRD2,  PortD2_Ctrl         },
    //{ &GPCRD3,  PortD3_Ctrl       },
    //{ &GPCRD4,  PortD4_Ctrl       },
    { &GPCRD5,  PortD5_Ctrl         },
    { &GPCRD6,  PortD6_Ctrl         },
    //{ &GPCRD7,  PortD7_Ctrl       },

    { &GPCRE0,  PortE0_Ctrl         },
    //{ &GPCRE1,  PortE1_Ctrl       },
    //{ &GPCRE2,  PortE2_Ctrl       },
    //{ &GPCRE3,  PortE3_Ctrl       },
    { &GPCRE4,  PortE4_Ctrl         },
    //{ &GPCRE5,  PortE5_Ctrl       },
    //{ &GPCRE6,  PortE6_Ctrl       },
    { &GPCRE7,  PortE7_Ctrl         },

    //{ &GPCRF0,  PortF0_Ctrl       },
    //{ &GPCRF1,  PortF1_Ctrl       },
    { &GPCRF2,  PortF2_Ctrl         },
    { &GPCRF3,  PortF3_Ctrl         },
    //{ &GPCRF4,  PortF4_Ctrl       },
    //{ &GPCRF5,  PortF5_Ctrl       },
    { &GPCRF6,  PortF6_Ctrl         },
    { &GPCRF7,  PortF7_Ctrl         },

    //{ &GPCRG0,  PortG0_Ctrl       },
    { &GPCRG1,  PortG1_Ctrl         },
    { &GPCRG2,  PortG2_Ctrl         },
    { &GPCRG3,  PortG3_Ctrl         },
    { &GPCRG4,  PortG4_Ctrl         },
    { &GPCRG5,  PortG5_Ctrl         },
    { &GPCRG6,  PortG6_Ctrl         },
    { &GPCRG7,  PortG7_Ctrl         },

    { &GPCRH0,  PortH0_Ctrl         },
    { &GPCRH1,  PortH1_Ctrl         },
    { &GPCRH2,  PortH2_Ctrl         },
    //{ &GPCRH3,  PortH3_Ctrl       },
    //{ &GPCRH4,  PortH4_Ctrl       },
    //{ &GPCRH5,  PortH5_Ctrl       },
    //{ &GPCRH6,  PortH6_Ctrl       },

    { &GPCRI0,  PortI0_Ctrl         },
    { &GPCRI1,  PortI1_Ctrl         },
    { &GPCRI2,  PortI2_Ctrl         },
    { &GPCRI3,  PortI3_Ctrl         },
    //{ &GPCRI4,  PortI4_Ctrl       },
    //{ &GPCRI5,  PortI5_Ctrl       },
    //{ &GPCRI6,  PortI6_Ctrl       },
    //{ &GPCRI7,  PortI7_Ctrl       },

    //{ &GPCRJ0,  PortJ0_Ctrl       },
    //{ &GPCRJ1,  PortJ1_Ctrl       },
    //{ &GPCRJ2,  PortJ2_Ctrl       },
    { &GPCRJ3,  PortJ3_Ctrl         },
    //{ &GPCRJ4,  PortJ4_Ctrl       },
    //{ &GPCRJ5,  PortJ5_Ctrl       },
    { &KSOHGCTRL,   (BIT3+BIT4)     },
    { &KSOHGOEN,    (BIT3+BIT4)     },

};
/*-----------------------------------------------------------------------------
 * @subroutine - Init_GPIO
 * @function - Power up GPIO configuration
 * @Upstream - By call (Init)
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Init_GPIO(void)
{
    ITempB01 = 0;
    while (ITempB01 < (sizeof(asInitGPIOReg) / sizeof(sInitGPIOReg)))
    {
        *asInitGPIOReg[ITempB01].reg = asInitGPIOReg[ITempB01].value;
        ITempB01++;
    }
}

//----------------------------------------------------------------------------
// Hook function of SCI high
//----------------------------------------------------------------------------
void Hook_SCION(void)
{
    EC_SCI_LO();
}

//----------------------------------------------------------------------------
// Hook function of SCI low
//----------------------------------------------------------------------------
void Hook_SCIOFF(void)
{
    EC_SCI_HI();
}

//----------------------------------------------------------------------------
// Hook function of SMI high
//----------------------------------------------------------------------------
void Hook_SMION(void)
{
    EC_SMI_LO();
}

//----------------------------------------------------------------------------
// Hook function of SMI low
//----------------------------------------------------------------------------
void Hook_SMIOFF(void)
{
    EC_SMI_HI();
}

//----------------------------------------------------------------------------
// Hook function of A20 high
//----------------------------------------------------------------------------
void Hook_A20ON(void)
{
    GATEA20_HI();
}

//----------------------------------------------------------------------------
// Hook function of A20 low
//----------------------------------------------------------------------------
void Hook_A20OFF(void)
{
    GATEA20_LO();
}

//----------------------------------------------------------------------------
// Hook function of keyboard reset low
//----------------------------------------------------------------------------
void Hook_KBRSTON(void)
{
    KBRST_LO();
}

//----------------------------------------------------------------------------
// Hook function of keyboard reset high
//----------------------------------------------------------------------------
void Hook_KBRSTOFF(void)
{
    KBRST_HI();
}

//----------------------------------------------------------------------------
// Hook function of NUM LED ON
//----------------------------------------------------------------------------
void Hook_NUMLED_ON(void)
{
    KB_NUMLED_ON();
}

//----------------------------------------------------------------------------
// Hook function of NUM LED OFF
//----------------------------------------------------------------------------
void Hook_NUMLED_OFF(void)
{
    KB_NUMLED_OFF();
}

//----------------------------------------------------------------------------
// Hook function of CAP LED ON
//----------------------------------------------------------------------------
void Hook_CAPLED_ON(void)
{
    KB_CAPLED_ON();
}

//----------------------------------------------------------------------------
// Hook function of CAP LED OFF
//----------------------------------------------------------------------------
void Hook_CAPLED_OFF(void)
{
    KB_CAPLED_OFF();
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_GPIO.C */