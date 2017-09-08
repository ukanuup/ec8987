/*-----------------------------------------------------------------------------
 * @file     | OEM_MAIN.C
 * ----------+-----------------------------------------------------------------
 * @function | OEM Kernel bridge link
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
#define SUPPORT_MAILBOX_5MS         0


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 1ms events
// EventId is 0 ~ 9 cycle
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer1msEvent(IBYTE EventId)
{
    //-------------------------------------------------------------------------
    // Power Status Branch
    //-------------------------------------------------------------------------
    if ((SysPowState == _SYSTEM_S0) || (SysPowState == _SYSTEM_S1))
    {
        Oem_SysPowState_S0_S1();
    }
    else if (SysPowState == _SYSTEM_S3)
    {
        Oem_SysPowState_S3();
    }
    else if ((SysPowState == _SYSTEM_S4) || (SysPowState == _SYSTEM_S5))
    {
        Oem_SysPowState_S4_S5();
        if ((IS_PCH_SLP_S4_HI())&& (IS_VCC_DDR_PWROK_HI())&&IS_PCH_SLP_S3_HI())
        {
             Set_SysPowState(_PST_S5_to_S0);
			xEC_RTC_Wakeuptimer=0;
			xEC_RTC_WakeupFlag=0;
        }
 #if Support_RTC_hang25_wakeup   
		if(xEC_RTC_Wakeuptimer>0)
			{
	    		xEC_RTC_Wakeuptimer--;
				if(xEC_RTC_Wakeuptimer==0)
				{
				   Set_SysPowState(_PST_S5_to_S0); 
				}
			}
 #endif
    }
    else if (IS_MASK_CLEAR(SysPowState, F_PST_BUSY))
    {
        Oem_SysPowState_G3();
    }
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    // System Power Control
    //-------------------------------------------------------------------------
    if (IS_MASK_SET(SysPowState, F_PST_BUSY))
    {
        Oem_SysPowSequence();   // System Power Control
    }
    else
    {
        //---------------------------------------------------------------------
        // System Battery Low Pin Control
        //---------------------------------------------------------------------
        //if (IS_ADAPTER_IN() && IS_PCH_RSMRST_HI())
        if (IS_ADAPTER_IN() && IS_PCH_RSMRST_HI())
        {
            PF_AC_PRESENT_HI();
            PM_BATLOW_HI();
        }
        else
        {
            PF_AC_PRESENT_LO();
            if (BAT1_Voltage > 6000)
            {
                PM_BATLOW_HI();
            }
            else
            {
                PM_BATLOW_LO();
            }
        }
    }
    //-------------------------------------------------------------------------
    if (EventId & 0x01)
    {
        /* Divide Timer2msEvent */
        SMBusA_ScanCenter();
    }
    //-------------------------------------------------------------------------
#if SUPPORT_MAILBOX_5MS
    if ((EventId == 1) || (EventId == 6))
    {
        /* Divide Timer5msEvent */
        //ServiceMailBoxFunction();
    }
#endif
    //-------------------------------------------------------------------------
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 5ms events
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer5msEvent(void)
{

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 10ms events
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer10msEventA(void)
{


#if 0
    //-------------------------------------------------------------------------
    // Power Status Branch
    //-------------------------------------------------------------------------
    if ((SysPowState == _SYSTEM_S0) || (SysPowState == _SYSTEM_S1))
    {
        Oem_SysPowState_S0_S1();
    }
    else if (SysPowState == _SYSTEM_S3)
    {
        Oem_SysPowState_S3();
    }
    else if ((SysPowState == _SYSTEM_S4) || (SysPowState == _SYSTEM_S5))
    {
        Oem_SysPowState_S4_S5();
        if ((IS_PCH_SLP_S4_HI())&& (IS_VCC_DDR_PWROK_HI()))
        {
             Set_SysPowState(_PST_S5_to_S0);
        }
    }
    else if (IS_MASK_CLEAR(SysPowState, F_PST_BUSY))
    {
        Oem_SysPowState_G3();
    }
    //-------------------------------------------------------------------------
#endif
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 10ms events
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer10msEventB(void)
{
#if SUPPORT_PECI
#if SUPPORT_PECI_CS_MODE
    if (SysPowState == _SYSTEM_S0)
    {
        Service_PECI_Command();
        Service_PECI_Data();
    }
#else
    Service_PECI_Data();
#endif
#endif
    xEC_PECI_CPU_T = PECI_CPU_T;
    if (SysPowState == _SYSTEM_S0)
    	{
			if(xEC_PECI_CPU_T>=xEC_SYS_SKIN_T)
			{
				xEC_PLMX_T=xEC_PECI_CPU_T;
			}
			else
			{
				xEC_PLMX_T = xEC_SYS_SKIN_T;
			}
    	}

    //-------------------------------------------------------------------------
#if SUPPORT_VIBRATE_MOTOR
    if (ViberatorTimer > 0)
    {
        PF_VIBRATOR_ON();
        ViberatorTimer--;
    }
    else
    {
        PF_VIBRATOR_OFF();
    }
#endif
    //-------------------------------------------------------------------------
#if SUPPORT_POWER_SAVING
    if (CheckPowerSaving())
    {
        EnterPowerSaving();
    }
#endif
    //-------------------------------------------------------------------------
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 50ms events A
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer50msEventA(void)
{
   // Adapter_Detection();
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 50ms events B
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer50msEventB(void)
{
    Battery_Detection();
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 50ms events C
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer50msEventC(void)
{
    Service_GPI_Event();
    SCI_EventCenter();
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 100ms events A
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer100msEventA(void)
{
    ProcessLED();
    Process_LID_Switch();
    //-------------------------------------------------------------------------
#if SupportP80_Restore	
	P80_Save_to_eFLash();
#endif
    //-------------------------------------------------------------------------
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 100ms events B
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer100msEventB(void)
{
#if SUPPORT_PECI
#if SUPPORT_PECI_CS_MODE
#else
    Service_PECI_Command();
#endif
#endif
    SCI_PowerEvent();

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 100ms events C
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer100msEventC(void)
{
#if SUPPORT_EXT1_WDT_RESET
    EWDKEYR = 0x5C;
#endif

#if SUPPORT_MCU_WDT_RESET
    WDTCON |= 0x01;
#endif
    Scan_ADC_CH01();
    //-------------------------------------------------------------------------
    if (SMBA_FloatingTimer > 0)
    {
#if SUPPORT_TYPE_C_SMBUS_B
        GPCRC1 = INPUT;
        GPCRC2 = INPUT;
#else
        GPCRB3 = INPUT;
        GPCRB4 = INPUT;
#endif
        SMBA_FloatingTimer--;
    }
    //-------------------------------------------------------------------------
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 500ms events A
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer500msEventA(void)
{
    Get_ADC0_Thermistor();
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 500ms events B
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer500msEventB(void)
{
    Get_ADC1_Thermistor();
    //-------------------------------------------------------------------------
    if (IS_MASK_SET(xEC_Sensor_F, F_PECI_Sensor))
    {
        Service_CPU_T_Event();
    }
    //-------------------------------------------------------------------------
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 500ms events C
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer500msEventC(void)
{
	Adapter_Detection();
    Update_ACPI_Battery();
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 1sec events A
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer1SecEventA(void)
{
#if SUPPORT_FAN1_TACH
    wFan1_CurrentRPM = GetFanRPM(F1TMRR, F1TLRR);
#endif
    //-------------------------------------------------------------------------
    if (SkinTripFlag == 1)
    {
        SET_MASK(xEC_ThermalSource, F_SKIN_HOT);
        WriteSCI_Buffer(_SCIEVT_TrigPoint);
        SkinTripFlag --;
    }
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    //robert 20150911++
    //if ((SysPowState == _SYSTEM_S4) || (SysPowState == _SYSTEM_S5))
    if(IS_PCH_SLP_S5_LO()&& IS_PCH_SLP_S3_LO()&&IS_ADAPTER_OUT())
    {
        if (DLY_S3_S4 == 0)
        {
            EC_PWR_LATCH_LO();
            /*while(1)
            {
                if (IS_EC_PWRSW_DN() || IS_ADAPTER_IN())
                {
                    break;
				}
			}*/
        }
        else
        {
            DLY_S3_S4--;
        }
    }
    //-------------------------------------------------------------------------
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 1sec events B
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer1SecEventB(void)
{
#if SUPPORT_FAN2_TACH
    wFan2_CurrentRPM = GetFanRPM(F2TMRR, F2TLRR);
#endif
    //-------------------------------------------------------------------------
    /* For test and debug send SCI event. */
    if (EventTestTimer > 0)
    {
        EventTestTimer--;
        if (EventTestTimer == 0)
        {
            WriteSCI_Buffer(EventTestNumber);
            EventTestNumber = 0;
        }
    }
    //-------------------------------------------------------------------------
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook 1sec events C
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer1SecEventC(void)
{
    Charger_Hook1SecTimer();
	#if Support_Resend_DD
		if(IS_MASK_SET(SystemFlag1, F_ACPI_MODE))
			{
			xEC_USB_PD_STS_DD = USB_PD_REG_P0[0xDD];
			if(I2C_DD_Resend > 0)
				{
				I2C_DD_Resend --;
				if(I2C_DD_Resend == 0)
					{
					WriteSCI_Buffer(0xDD);
					}
				}
			
			}
#endif

	    


		if(P80_DEBUG_CODE > 4)
		{
			if(IS_PCH_SLP_S3_LO()||IS_PCH_SLP_S4_LO())
				{
					BRAM[0x3F]=0xFF;
				}

			RamDebugP80(BRAM[0x3F]);
			P80_DEBUG_CODE = 0;
		}
		else
		{
			P80_DEBUG_CODE++;
		}
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook1min events
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_Timer1MinEvent(void)
{

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// service_OEM_1
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void service_OEM_1(void)
{

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// service_OEM_2
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void service_OEM_2(void)
{

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// service_OEM_3
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void service_OEM_3(void)
{

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// service_OEM_4
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void service_OEM_4(void)
{

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook_main_service_H
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_main_service_H(void)
{
    if ((PM1DataCount > 0) && (IS_MASK_CLEAR(PM1STS, P_OBF)))
    {
        PM1DataCount--;
        PM1DO = PM1Data;
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Hook_main_service_L
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Hook_main_service_L(void)
{

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Timer event control function
// Return :
//  Only_Timer1msEvent : Only Timer1msEvent and Hook_Timer1msEvent function
//  All_TimerEvent : All timer events are OK.
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
BYTE Hook_Only_Timer1msEvent(void)
{
    //-------------------------------------------------------------------------
// Return :
//  Only_Timer1msEvent : Only Timer1msEvent and Hook_Timer1msEvent function
//  All_TimerEvent : All timer events are OK.
    //-------------------------------------------------------------------------
    return(All_TimerEvent);
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// OEM_SkipMainServiceFunc
//  Note:
//      1. Always return(0xFF|Normal_MainService) to run normal main_service
//         function.
//      2. If you don't understand the use of OEM_SkipMainServiceFunc
//         function, don't change anything.
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
BYTE OEM_SkipMainServiceFunc(void)
{
    return(Normal_MainService);
}
//-----------------------------------------------------------------------------
#if SupportP80_Restore

void P80_Write_To_eFlash(void)
{

    Do_SPI_Write_Status(SPIStatus_UnlockAll);
    // Sector Erase, 1K bytes
    Do_SPI_Write_Enable();
    Do_SPI_Erase(SPICmd_SectorErase, 0x01, 0xF0, 0x00);
    Do_SPI_Write_Disable();

    Do_SPI_Write_Enable();
    Do_SPI_Write_256Bytes(&P80_RAM_F[0], 0x01, 0xF0, 0x00);
    Do_SPI_Write_Disable();

}

void P80_Save_to_eFLash(void)
{
	if((IS_VOLUME_DOWN_DN())&&(IS_VOLUME_UP_DN()))
		{
		DebounceGPI8++;	
		if(DebounceGPI8>80)
			{
				P80_Write_To_eFlash();
			    ECIndirectFastRead(0x01, 0xF0, 0x00,
                        SPI_selection_internal, 256, &P80_RAM_9[0]);
			DebounceGPI8=0;
			}
		}
	else
		{
		DebounceGPI8 = 0;
		}

}
#endif


/*-----------------------------------------------------------------------------
 * End of OEM_MAIN.C */
