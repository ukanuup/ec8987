/*-----------------------------------------------------------------------------
 * @file     | OEM_LED.C
 *-----------+-----------------------------------------------------------------
 * @function | Process LED indicator control
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
#define PWRLED_LEN          6


 /*-----------------------------------------------------------------------------
 * @subroutine - OEM_Write_Leds
 * @function - Write to SCROLL LOCK, NUM LOCK, CAPS LOCK, and any custom LEDs
 *             (including an "Fn" key LED).
 * @Upstream - By call
 * @input    - data (LED_ON bit) = Data to write to the LEDs
 *             bit 0 - SCROLL, Scroll Lock
 *             bit 1 - NUM,    Num Lock
 *             bit 2 - CAPS,   Caps Lock
 *             bit 3 - OVL,    Fn LED
 *             bit 4 - LED4,   Undefined
 *             bit 5 - LED5,   Undefined
 *             bit 6 - LED6,   Undefined
 *             bit 7 - LED7,   Undefined
 * @return   - None
 * @note     - Updates Led_Data variable and calls send_leds if appropriate.
 *---------------------------------------------------------------------------*/
void OEM_Write_Leds(BYTE data_byte)
{
    Led_Data = data_byte;
#if 0
    //-------------------------------------------------------------------------
    if (data_byte & BIT1)
    {
        Hook_NUMLED_ON();
    }
    else
    {
        Hook_NUMLED_OFF();
    }
    //-------------------------------------------------------------------------
    if (data_byte & BIT2)
    {
        Hook_CAPLED_ON();
    }
    else
    {
        Hook_CAPLED_OFF();
    }
    //-------------------------------------------------------------------------
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - LED_ControlCenter
 * @function - LED_ControlCenter
 * @upstream - Hook_Timer100msEventA
 * @input    -
 * @return   -
 * @note     -
 *---------------------------------------------------------------------------*/
void LED_ControlCenter(void)
{

    //------------------------------------------------------------------------
    //if((IS_PCH_SLP_S4_HI())|(IS_PCH_SLP_S3_HI())|(IS_PLT_RST_HI()))
    if((IS_PCH_SLP_S4_HI())&&(IS_PCH_SLP_S3_HI()))
        {
            if(IS_SLP_S0_N_HI())
                {
                S5_STATE_FLG = 0;
                if(IS_CHG_LED_OFF())//if power on, led blinking ....robert20150626
                    {
                        CHG_LED_ON();
                    }
                else
                    {
                        CHG_LED_OFF();
                    }
                }
            else
                {
                    S5_STATE_FLG = 1;
                }

        }
    else
        {
            CHG_LED_OFF();//Power off, led off ...robert20150626
            S5_STATE_FLG = 0;
        }

    //-------------------------------------------------------------------------
    //if (IS_ADAPTER_OUT())
    //{
    //    CHG_LED_OFF();
        //CHG_DONE_LED_OFF();
    //    return;
    //}
    //-------------------------------------------------------------------------
    //if (IS_BATTERY1_OUT())
    //{
    //    CHG_LED_OFF();
        //CHG_DONE_LED_OFF();
    //    return;
    //}
    //-------------------------------------------------------------------------
    //if (IS_MASK_SET(xEC_Bt1State, F_BAT1_CHARGING))
    //{
    //    CHG_LED_ON();
        //CHG_DONE_LED_OFF();
    //}
    //else
    //{
    //    CHG_LED_OFF();
        //CHG_DONE_LED_ON();
    //}
    //-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
const WORD code PowerLEDPattern[]=
{
    //--------------------------------------------------------------------------
    //  S0      S3      S4      S5      index4  index5
    //--------------------------------------------------------------------------
        0xFFFF, 0x5555, 0x4444, 0x0000, 0x0000, 0x0000,     //  Power LED1
        0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x5555, 0x0101,     //  test LED2  //bbbb for led function20150908
};

//----------------------------------------------------------------------------
// Turn on/off LEDs according to machine status.
// Executed once per 1 sec
// for example:
//       ->BIT14
//      1010101010101010
//      0101010101010101
//                <-BIT3
//----------------------------------------------------------------------------
void ProcessLED(void)
{
#if SupportLowPowerLED
        BYTE bat_index, pwr_index;

        LED_FLASH_CNT <<= 1;
        if(LED_FLASH_CNT == 0)  LED_FLASH_CNT=0x0001;

        /* Power LED control method */
                pwr_index=1;                // red



        if((IS_MASK_SET(xEC_Bt1State, F_ACPI_CHARGING)) ||
			(IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_LEGACY_5V_ADAPTER)) ||
            (IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_IS_5V_ADAPTER)))
            {
                pwr_index=5;    //charge blinking
            }

        if (IS_MASK_CLEAR(PowerSource, F_AC_ON_LINE))
            {
                pwr_index=0;
                if(SystemIsS0)
                {
                    if((BAT1_RelativeStateOfChgL <= 10)&&
                            (IS_MASK_CLEAR(SystemFlag1, F_ACPI_MODE)))
                            pwr_index=5;//charge blinking
                }
                else
                {
                    if((BAT1_RelativeStateOfChgL <= 3))
                        {
                            if(BAT1_Low_ShutdownCount > 0)
                            {
                                BAT1_Low_ShutdownCount --;
                                if(BAT1_Low_ShutdownCount > 30)
                                pwr_index=4;//fast blinking
                                else
                                pwr_index=5;//charge blinking
                                //if(BAT1_Low_ShutdownCount == 0)
                                 //   EC_PWR_LATCH_LO();
                            }
                        }
                }
            }
        if(LED_OFF_CNT > 0)
        {
            pwr_index=4;//fast blinking
            LED_OFF_CNT --;
        }

        //RamDebug(0x77);
        //RamDebug(pwr_index);
        if(PowerLEDPattern[PWRLED_LEN+pwr_index] & LED_FLASH_CNT)
        {
            CHG_LED_ON();
        }
        else
        {
            CHG_LED_OFF();
        }

        /* Battery LED control method */
        bat_index = 0x03;           // pre-set battery out


        /*if(BattLEDPattern[bat_index] & LED_FLASH_CNT)
        {
            BATLED1_ON();
        }
        else
        {
            BATLED1_OFF();
        }

        if(BattLEDPattern[BATLED_LEN+bat_index] & LED_FLASH_CNT)
        {
            BATLED2_ON();
        }
        else
        {
            BATLED2_OFF();
        }*/
    }


#else

        BYTE bat_index, pwr_index;

        LED_FLASH_CNT <<= 1;
        if(LED_FLASH_CNT == 0)  LED_FLASH_CNT=0x0001;

        /* Power LED control method */
        pwr_index=0;                // pre-set S0
        if(SystemIsS0)              // pre-set S3
        {
            pwr_index=5;
        }
        if((SystemIsS0) && (IS_SLP_S0_N_LO()))// (S5_STATE_FLG == 0x01)
        {
            pwr_index=4;
        }
        if(SystemIsS5)              // pre-set S5
        {
            pwr_index=3;
        }
        if(SystemIsS4)              // pre-set S4
        {
            pwr_index=2;
        }
        if(SystemIsS3)              // pre-set S3
        {
            pwr_index=1;
        }

        /*if(PowerLEDPattern[pwr_index] & LED_FLASH_CNT)    // setup power LED
        {
            CHG_LED_ON();
        }
        else
        {
            CHG_LED_OFF();
        }*/
        if(PowerLEDPattern[PWRLED_LEN+pwr_index] & LED_FLASH_CNT)
        {
            CHG_LED_ON();
        }
        else
        {
            CHG_LED_OFF();
        }

        /* Battery LED control method */
        bat_index = 0x03;           // pre-set battery out


        /*if(BattLEDPattern[bat_index] & LED_FLASH_CNT)
        {
            BATLED1_ON();
        }
        else
        {
            BATLED1_OFF();
        }

        if(BattLEDPattern[BATLED_LEN+bat_index] & LED_FLASH_CNT)
        {
            BATLED2_ON();
        }
        else
        {
            BATLED2_OFF();
        }*/
    }
#endif


//----------------------------------------------------------------------------
// The function of turning on all LED
//----------------------------------------------------------------------------
void TurnOnAllLED(void)
{

}

/*-----------------------------------------------------------------------------
 * End of OEM_LED.C */
