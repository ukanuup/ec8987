/*-----------------------------------------------------------------------------
 * @file     | OEM_BATTERY.C
 *-----------+-----------------------------------------------------------------
 * @function | Battery and Charger control
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2015, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>


/*-----------------------------------------------------------------------------
 * Local Parameter Definition
 *---------------------------------------------------------------------------*/
#define DEBUG_BATTERY           FALSE


/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_BATTERY
#define Battery_RamDebug(x)     RamDebug(x)
#else
#define Battery_RamDebug(x)     {}
#endif


/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/
#define _AC1_IN_DEBOUNCE        3//500 X 1 //40 X 
#define _BAT_IN_DEBOUNCE        8
#define _SMB_BATT1_ADDR         0x16    // Smart Battery
#define _SMB_CHGRA_ADDR         0x12    // Smart Charger


//-----------------------------------------------------------------------------
#if SUPPORT_SMART_BATTERY
//*****************************************************************************
/* Smart Battery Table */
//*****************************************************************************
const sRSmbusStruct code _SMB_BATT1_INIT_TBL[] =
{
    {_SMB_RD_WORD, _CMD_ManufacturerAccess,     &BAT1_ManufacturerAccess    },
    {_SMB_RD_WORD, _CMD_Temperature,            &BAT1_Temperature           },
    {_SMB_RD_WORD, _CMD_BatteryMode,            &BAT1_BatteryMode           },
    {_SMB_RD_WORD, _CMD_Voltage,                &BAT1_Voltage               },
    {_SMB_RD_WORD, _CMD_Current,                &BAT1_Current               },
    {_SMB_RD_WORD, _CMD_AverageCurrent,         &BAT1_AverageCurrent        },
    {_SMB_RD_WORD, _CMD_MaxError,               &BAT1_MaxError              },
    {_SMB_RD_WORD, _CMD_RelativeStateOfCharge,  &BAT1_RelativeStateOfChg    },
    {_SMB_RD_WORD, _CMD_AbsoluteStateOfCharge,  &BAT1_AbsoluteOfCharge      },
    {_SMB_RD_WORD, _CMD_RemainingCapacity,      &BAT1_RemainingCapacity     },
    {_SMB_RD_WORD, _CMD_FullChargeCapacity,     &BAT1_FullChargeCapacity    },
    {_SMB_RD_WORD, _CMD_ChargingCurrent,        &BAT1_ChargingCurrent       },
    {_SMB_RD_WORD, _CMD_ChargingVoltage,        &BAT1_ChargingVoltage       },
    {_SMB_RD_WORD, _CMD_BatteryStatus,          &BAT1_BatteryStatus         },
    {_SMB_RD_WORD, _CMD_CycleCount,             &BAT1_CycleCount            },
    {_SMB_RD_WORD, _CMD_DesignCapacity,         &BAT1_DesignCapacity        },
    {_SMB_RD_WORD, _CMD_DesignVoltage,          &BAT1_DesignVoltage         },
    {_SMB_RD_WORD, _CMD_SpecificationInfo,      &BAT1_SpecificationInfo     },
    {_SMB_RD_WORD, _CMD_ManufactureDate,        &BAT1_ManufactureDate       },
    {_SMB_RD_WORD, _CMD_SerialNumber,           &BAT1_SerialNumber          },
    {_SMB_RD_BLCK, _CMD_ManufacturerName,       &BAT1_ManufacturerName      },
    {_SMB_RD_BLCK, _CMD_DeviceName,             &BAT1_DeviceName            },
    {_SMB_RD_BLCK, _CMD_DeviceChemistry,        &BAT1_DeviceChemistry       },
    {_SMB_RD_BLCK, _CMD_ManufacturerData,       &BAT1_ManufacturerData      },
};
//-----------------------------------------------------------------------------
const sRSmbusStruct code _SMB_BATT1_POLL_TBL[] =
{
    {_SMB_RD_WORD, _CMD_ChargingCurrent,        &BAT1_ChargingCurrent       },
    {_SMB_RD_WORD, _CMD_ChargingVoltage,        &BAT1_ChargingVoltage       },
    {_SMB_RD_WORD, _CMD_Temperature,            &BAT1_Temperature           },
    {_SMB_RD_WORD, _CMD_Voltage,                &BAT1_Voltage               },
    {_SMB_RD_WORD, _CMD_Current,                &BAT1_Current               },
    {_SMB_RD_WORD, _CMD_AverageCurrent,         &BAT1_AverageCurrent        },
    {_SMB_RD_WORD, _CMD_RelativeStateOfCharge,  &BAT1_RelativeStateOfChg    },
    {_SMB_RD_WORD, _CMD_RemainingCapacity,      &BAT1_RemainingCapacity     },
    {_SMB_RD_WORD, _CMD_FullChargeCapacity,     &BAT1_FullChargeCapacity    },
    {_SMB_RD_WORD, _CMD_BatteryStatus,          &BAT1_BatteryStatus         },
};
//*****************************************************************************
/* Smart Charger Table */
//*****************************************************************************
const sRSmbusStruct code _SMB_CHGRA_INIT_TBL[] =
{
    {_SMB_RD_WORD, _CMD_ChargerManufacturerID,  &CHGR_ManufacturerID        },
    {_SMB_RD_WORD, _CMD_ChargerDeviceID,        &CHGR_DeviceID              },
    {_SMB_WR_WORD, _CMD_ChargerOption,          &CHGR_ChargerOption         },
    {_SMB_WR_WORD, _CMD_ChargingVoltage,        &CHGR_ChargingVoltage       },
    {_SMB_WR_WORD, _CMD_MinSystemVoltage,       &CHGR_ChargerREG3E          },
    {_SMB_WR_WORD, _CMD_ChargerInputCurrent,    &CHGR_InputCurrent          },
    {_SMB_WR_WORD, _CMD_ChargingCurrent,        &CHGR_ChargingCurrent       },
};
//-----------------------------------------------------------------------------
const sRSmbusStruct code _SMB_CHGRA_POLL_TBL[]=
{
    {_SMB_WR_WORD, _CMD_ChargerOption,          &CHGR_ChargerOption         },
    {_SMB_WR_WORD, _CMD_ChargingVoltage,        &CHGR_ChargingVoltage       },
    {_SMB_WR_WORD, _CMD_MinSystemVoltage,       &CHGR_ChargerREG3E          },
    {_SMB_WR_WORD, _CMD_ChargerInputCurrent,    &CHGR_InputCurrent          },
    {_SMB_WR_WORD, _CMD_ChargingCurrent,        &CHGR_ChargingCurrent       },
#if 0   /* SUPPORT READ BACK CHECK */
    {_SMB_RD_WORD, _CMD_ChargerOption,          &CHGR_ChargerOption2        },
    {_SMB_RD_WORD, _CMD_ChargerInputCurrent,    &CHGR_InputCurrent2         },
    {_SMB_RD_WORD, _CMD_ChargingCurrent,        &CHGR_ChargingCurrent2      },
    {_SMB_RD_WORD, _CMD_ChargingVoltage,        &CHGR_ChargingVoltage2      }
#endif
};
//*****************************************************************************
#define _SIZE_SMB_BATT1_INIT        (sizeof(_SMB_BATT1_INIT_TBL) / 4)
#define _SIZE_SMB_BATT1_POLL        (sizeof(_SMB_BATT1_POLL_TBL) / 4)
#define _SIZE_SMB_CHGRA_INIT        (sizeof(_SMB_CHGRA_INIT_TBL) / 4)
#define _SIZE_SMB_CHGRA_POLL        (sizeof(_SMB_CHGRA_POLL_TBL) / 4)
//*****************************************************************************

/*-----------------------------------------------------------------------------
 * @subroutine - PollSmartBattery
 * @function - Process SMBus Smart Battery Data
 * @upstream - SMBus_Channel_C() -> service_5mS_A
 * @input    - None
 * @return   - None
 * @note     - GPB.4_SMCLK2, GPB.5_SMDAT2
 *---------------------------------------------------------------------------*/
void PollSmartBattery(void)
{
#if SUPPORT_BATT_FAKE_INFO
    if ((BAT1_RemainingCapacity == 0) || (BAT1_FullChargeCapacity == 0))
    {
        BAT1_Temperature = 2730+333;
        BAT1_Voltage = 8123;
        BAT1_Current = 1000;
        BAT1_AverageCurrent = 1000;
        BAT1_RelativeStateOfChgL = 66;
        BAT1_RemainingCapacity = 2000;
        BAT1_FullChargeCapacity  = 3000;
        BAT1_ChargingCurrent = 1500;
        BAT1_ChargingVoltage = 8400;
        BAT1_CycleCount = 99;
        BAT1_DesignCapacity = 3200;
        BAT1_DesignVoltage = 8400;
    }
    SMBA_DEV0_DLY = 500;    //5ms x 500 = 2.5 sec (per loop)
#else
    if (!(SMBA_DEV0_STS & F_DEV_INIT))
    {
        /* Initial read all battery information. */
        if (SMBA_DEV0_DIR >= _SIZE_SMB_BATT1_INIT)
        {
#if 0
            SMBA_DEV0_DIR = 0;
            SMBA_DEV0_STS |= F_DEV_INIT;
            PowerSource |= F_BAT1_PRESENT;
            /* TODO: Here Check Data Failed Retry */
            // Example:
            //if ((BAT1_DesignVoltage == 0) ||
            //    (BAT1_FullChargeCapacity == 0) ||
            //    (BAT1_DeviceChemistry == 0))
            //{
            //    SMBA_DEV0_STS = 0;
            //    return;
            //}
            //Hook_SmartBatteryInitOK();
#else
            if ((BAT1_DesignVoltage == 0) || (BAT1_DeviceChemistry == 0) ||
                (BAT1_FullChargeCapacity == 0))
            {
                SMBA_DEV0_STS &= F_DEV_ON_LINE;
                SMBA_DEV0_DIR = 0;
            }
            else
            {
                SMBA_DEV0_DIR = 0;
                SMBA_DEV0_STS |= F_DEV_INIT;
                PowerSource |= F_BAT1_PRESENT;
                //Hook_SmartBatteryInitOK();
            }
            return;
#endif
        }
        SMBA_CHN_CTL = _SMB_BATT1_INIT_TBL[SMBA_DEV0_DIR].address;
        SMBA_CHN_CMD = _SMB_BATT1_INIT_TBL[SMBA_DEV0_DIR].cmd;
        SMBA_DEV_MEM = _SMB_BATT1_INIT_TBL[SMBA_DEV0_DIR].smbdata;
    }
    else
    {
        /* Update SMBus device dynamic data. */
        if (SMBA_DEV0_DIR >= _SIZE_SMB_BATT1_POLL)
        {
            SMBA_DEV0_DIR = 0;
            SMBA_DEV0_STS |= F_DEV_UPDATED;
            SMBA_DEV0_DLY = 800;    //5ms x 800 = 4 sec (per loop)
            /* TODO: Here check data one loop */
            // :
        }
        SMBA_CHN_CTL = _SMB_BATT1_POLL_TBL[SMBA_DEV0_DIR].address;
        SMBA_CHN_CMD = _SMB_BATT1_POLL_TBL[SMBA_DEV0_DIR].cmd;
        SMBA_DEV_MEM = _SMB_BATT1_POLL_TBL[SMBA_DEV0_DIR].smbdata;
    }
    SMBA_DEV0_DIR++;
    SMBA_SetToRegs(_SMB_BATT1_ADDR, _SMB_DEV0);
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - DisableSmartCharger
 * @function - Process SMBus Smart Charger disable
 * @upstream - SMBus_Channel_A() -> service_5mS_A
 * @input    - None
 * @return   - None
 * @note     -  
 *---------------------------------------------------------------------------*/
void DisableSmartCharger(void)
{
#if 1
    I2C_EJ898A_OFFSET[0] = _CMD_ChargerOption;
    I2C_EJ898A_OFFSET[1] = 0x5F;
    I2C_EJ898A_OFFSET[2] = 0x66;
	I2C_WriteStream(_SMB_CH0,
                   	_SMB_CHGRA_ADDR,
                    &I2C_EJ898A_OFFSET[0],
                    3);
	SMBA_DEV1_DLY = 3000;
    //RamDebug(0xDC);
   // RamDebug(0xAA);
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Battery_Protection
 * @function - Battery_Protection
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *        		* * * * * * Alarm Bits * * * * *
 *         		0x8000 OVER_CHARGED_ALARM
 *         		0x4000 TERMINATE_CHARGE_ALARM
 *         		0x2000 Reserved
 *         		0x1000 OVER_TEMP_ALARM
 *         		0x0800 TERMINATE_DISCHARGE_ALARM
 *         		0x0400 Reserved
 *         		0x0200 REMAINING_CAPACITY_ALARM
 *         		0x0100 REMAINING_TIME_ALARM
 *         		* * * * * * Status Bits * * * * *
 *        		0x0080 INITIALIZED
 *         		0x0040 DISCHARGING
 *         		0x0020 FULLY_CHARGED
 *         		0x0010 FULLY_DISCHARGED
 *         		* * * * * * Error Code * * * * *
 * 				0x0000-0x000f Reserved for error codes
 *---------------------------------------------------------------------------*/
void Battery_Protection(void)
{
#if 0 
    /* Normal Charge Protection (Suggestion) */
    BAT1_BatteryStatus2 |= (BAT1_BatteryStatus & 0xD020);
    if (BAT1_BatteryStatus2 > 0)
    {
        if ((BAT1_BatteryStatus2 & 0xD000) > 0)
        {
            CHGR_ChargingCurrent = 0;
        }
        else if (BAT1_BatteryStatus & 0x0020)
        {
            CHGR_ChargingCurrent = 0;
        }
        else if (BAT1_RelativeStateOfChgL > 98)
        {
            CHGR_ChargingCurrent = 0;
        }
        else
        {
            BAT1_BatteryStatus2 = 0;
        }
    }
#else
	/* Only Fully Charged Process */
    BAT1_BatteryStatus2 |= (BAT1_BatteryStatus & 0x0020);
    if (BAT1_BatteryStatus2 > 0)
    {
        if( (BAT1_BatteryStatus & 0x0020)&&(BAT1_RelativeStateOfChgL == 0x64))
        {
            CHGR_ChargingCurrent = 0;
        }
        //else if (BAT1_RelativeStateOfChgL > 98)
        //{
         //   CHGR_ChargingCurrent = 0;
        //}
        else
        {
            BAT1_BatteryStatus2 = 0;
        }
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - PollSmartCharger
 * @function - Process SMBus Smart Charger Data
 * @upstream - SMBus_Channel_C() -> service_5mS_A
 * @input    - None
 * @return   - None
 * @note     - GPB.4_SMCLK2, GPB.5_SMDAT2
 *---------------------------------------------------------------------------*/
void PollSmartCharger(void)
{
#if 0
    /*TEST MODE */
    //CHGR_ChargerOption = 0xE144;
    //CHGR_ChargerREG3E = 0x1800;
    //CHGR_InputCurrent = 0x07C0;
    //CHGR_ChargingCurrent = 500;     //200mA
    //CHGR_ChargingVoltage = 8400;    //8400mV
#else
    //-------------------------------------------------------------------------
    //CHGR_ChargerOption = 0x665F;  /* The config with set the switching   */
                                    /* frequency to 1Mhz, and disable      */
                                    /* charging. */
    //CHGR_ChargerREG3E = 0x2000;
    //CHGR_ChargingCurrent = 2000;  /* [07D0] Intel request fixed charging */
                                    /* current, change Input current only. */
    CHGR_ChargingVoltage = 8400;    /* [20D0] 8400mV */
    //-------------------------------------------------------------------------
    if (IS_AC_OK_LOW())    //GPH.1
    {
        if (IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_LEGACY_5V_ADAPTER))
        {
            CHGR_ChargerOption = 0x665E;
            CHGR_InputCurrent = 192;
            CHGR_ChargingCurrent = 200; //[REG3F]
            CHGR_ChargerREG3E = 0x1770;
        }
        else
        {
            CHGR_ChargerOption = 0x665F;
            CHGR_InputCurrent = 2048;
            CHGR_ChargerREG3E = 0x1770;
            CHGR_ChargingCurrent = 0x07D1;  //[REG3F]
        }
    }
    else
    {
        if (IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_ADAPTER_IN))
        {
            if (IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_LEGACY_5V_ADAPTER))
            {
                CHGR_ChargerOption = 0x665E;
                CHGR_InputCurrent = 192;
                CHGR_ChargingCurrent = 200;	//[REG3F]
                CHGR_ChargerREG3E = 0x1770;

            }
            else if (IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_IS_5V_ADAPTER))
            {
                CHGR_ChargerOption = 0x665E;
                CHGR_InputCurrent = USBC_InputCurrent;
                CHGR_ChargingCurrent = USBC_ChargingCurrent;	//[REG3F]
                CHGR_ChargerREG3E = 0x1770;
            }
            else
            {
                /* Real PD Adapter (PDO) */
                CHGR_ChargerOption = 0x665E;
                CHGR_InputCurrent = USBC_InputCurrent;
                CHGR_ChargingCurrent = USBC_ChargingCurrent;	//[REG3F]
                CHGR_ChargerREG3E = 0x1770;
            }
        }
        else
        {
            /* Reserved */
			//if (wEJ898A_VBUS_Voltage > 0)
			//{
            //	/* From None RP 5V Adapter (No Connection Flag) */
            //	CHGR_ChargerOption = 0x665E;
            //	CHGR_InputCurrent = 192;
            //	CHGR_ChargingCurrent = 192;  //[REG3F]
            //	CHGR_ChargerREG3E = 0x1770;
			//}
			//else
			//{
            	/* From DC Jack Power */
            	CHGR_ChargerOption = 0x665E;
            	CHGR_InputCurrent = 0x07D0;
            	CHGR_ChargingCurrent = 0x07D0;  //[REG3F]
            	CHGR_ChargerREG3E = 0x1770;
			//}
			#if !Support_MRD_NOREWORK
			if(IS_ADP_SEL_L())//reserve for typeC leacgy 5V
				{
				CHGR_ChargerOption = 0x665E;
                CHGR_InputCurrent = 192;
                CHGR_ChargingCurrent = 200;	//[REG3F]
                CHGR_ChargerREG3E = 0x1770;
				SMBA_DEV1_DLY = 10;

				}
			#endif
				
        }

        if (BAT1_Voltage == 0)
        {
            CHGR_ChargerOption = 0x665F;
            CHGR_InputCurrent = 2048;
            CHGR_ChargerREG3E = 0x2000;
            CHGR_ChargingCurrent = 0;			//[REG3F]
        }
        else if (BAT1_Voltage < 6500)
        {
            CHGR_ChargerREG3E = 0x1770;
        }

#if !Support_MRD_NOREWORK
			if((IS_ADAPTER_IN())&& (IS_ADP_SEL_L())
				&& (IS_MASK_CLEAR(PowerSource, F_BAT1_PRESENT)))
				{
				CHGR_ChargerOption = 0x665F;
				CHGR_ChargingVoltage = 8400;
				CHGR_ChargerREG3E = 0x2000;
				}
			else if((IS_ADAPTER_IN())&& (IS_ADP_SEL_H())
				&& (IS_MASK_SET(PowerSource, F_BAT1_PRESENT)))
				{
				CHGR_ChargerOption = 0x665E;
				CHGR_ChargingVoltage = 8400;
				CHGR_InputCurrent=0x0800;//InputCurrent() or 3F = 0x0800;
				CHGR_ChargingCurrent = 0x0800;
				CHGR_ChargerREG3E = 0x1770;
				}

#endif
		if((DBG2_EJ898A_STATUS&0x03)==0x01)
		{
		SET_MASK(DBG2_EJ898A_STATUS,I2C_EJ898A_ChargeNoDealy);
		SMBA_DEV1_DLY = 0;
		SMBA_DEV1_DIR = 0;
		}
		
    }
    //------------------------------------------------------------------------
#endif
    //-------------------------------------------------------------------------
	Battery_Protection();
    //-------------------------------------------------------------------------
    if (!(SMBA_DEV1_STS & F_DEV_INIT))
    {
        CHGR_ChargingCurrent = 0;
        /* Initial read all battery information. */
        if (SMBA_DEV1_DIR >= _SIZE_SMB_CHGRA_INIT)
        {
            SMBA_DEV1_DIR = 0;
            SMBA_DEV1_STS |= (F_DEV_INIT + F_DEV_READY);
            /* TODO: Here Check Data Failed Retry */
            // :
        }
        SMBA_CHN_CTL = _SMB_CHGRA_INIT_TBL[SMBA_DEV1_DIR].address;
        SMBA_CHN_CMD = _SMB_CHGRA_INIT_TBL[SMBA_DEV1_DIR].cmd;
        SMBA_DEV_MEM = _SMB_CHGRA_INIT_TBL[SMBA_DEV1_DIR].smbdata;
    }
    else
    {
        /* Update SMBus device dynamic data. */
        if (SMBA_DEV1_DIR >= _SIZE_SMB_CHGRA_POLL)
        {
            SMBA_DEV1_DIR = 0;
            SMBA_DEV1_STS |= F_DEV_UPDATED;
            /* Polling Speed */
			if(IS_MASK_SET(DBG2_EJ898A_STATUS,I2C_EJ898A_ChargeNoDealy))
				{
				SMBA_DEV1_DLY=2;
				DBG2_EJ898A_STATUS = 0;
				//RamDebug(0x99);
				}
			else
				{
	            SMBA_DEV1_DLY = 3000;    //5ms x 3000 = 15 sec (per loop)
				}
	           //BAT1_ChargePauseTimer = 0x77;
	            /* TODO: Here check data one loop */
	            // :
	    }
        else
        {
            SMBA_DEV1_DLY = 2;
        }

        SMBA_CHN_CTL = _SMB_CHGRA_POLL_TBL[SMBA_DEV1_DIR].address;
        SMBA_CHN_CMD = _SMB_CHGRA_POLL_TBL[SMBA_DEV1_DIR].cmd;
        SMBA_DEV_MEM = _SMB_CHGRA_POLL_TBL[SMBA_DEV1_DIR].smbdata;
    }
    SMBA_DEV1_DIR++;
    SMBA_SetToRegs(_SMB_CHGRA_ADDR, _SMB_DEV1);
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * @subroutine - Charger_Hook1SecTimer
 * @function - Charger_Hook1SecTimer
 * @Upstream - Hook_Timer1SecEventC
 * @input    -
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Charger_Hook1SecTimer(void)
{
    if (WakeUpChargeTimer > 0)
    {
        WakeUpChargeTimer--;
    }
}
//-----------------------------------------------------------------------------
#endif  //SUPPORT_SMART_BATTERY

/*-----------------------------------------------------------------------------
 * @subroutine - Adapter_Detection
 * @function - AC-Adapter plug-in Detection
 * @Upstream - Hook_Timer50msEventA
 * @input    - GPI
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Adapter_Detection(void)
{
    if (IS_ADAPTER_IN() ||
        IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_LEGACY_5V_ADAPTER) ||
        IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_IS_5V_ADAPTER))
    {
        if (Debounce_ACin < _AC1_IN_DEBOUNCE)
        {
            Debounce_ACin++;
        }
        else
        {
            if (IS_MASK_CLEAR(PowerSource, F_AC_ON_LINE))
            {
                SET_MASK(PowerSource, F_AC_ON_LINE);
				//xEC_PowerState = PowerSource;
                WakeUpChargeTimer = 6;
				//SendACiEventTimer = 20;
				//WriteSCI_Buffer(_SCIEVT_ADAPTER);
                /* Adapter Plug-In Initialize */
                /* TODO: */
                //SET_MASK(xEC_USB_TypeCFlag, Flag_inputcurrent);
            }
        }
    }
    else
    {
        if (IS_MASK_SET(PowerSource, F_AC_ON_LINE))
        {
            CLEAR_MASK(PowerSource, F_AC_ON_LINE);
			//xEC_PowerState = PowerSource;
			//SendACiEventTimer = 20;
            //WriteSCI_Buffer(_SCIEVT_ADAPTER);
            /* Adapter Removed Initialize */
            /* TODO: */
            //SET_MASK(xEC_USB_TypeCFlag, Flag_inputcurrent);
        }
        Debounce_ACin = 0;
    }

}

/*-----------------------------------------------------------------------------
 * @subroutine - Battery_Detection
 * @function - Battery#1 plug-in Detection
 * @Upstream - Hook_Timer50msEventB
 * @input    - GPI
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Battery_Detection(void)
{
#if SUPPORT_BATTERY_IN
    if (IS_BATTERY1_IN())
    {
        if (Debounce_Bt1In < _BAT_IN_DEBOUNCE)
        {
            Debounce_Bt1In++;
        }
        else
        {
            if (IS_MASK_CLEAR(SMBA_DEV0_STS, F_DEV_ON_LINE))
            {
                SET_MASK(SMBA_DEV0_STS, F_DEV_ON_LINE);
                wPowerSavingDelay = 1000;
            }

            if (IS_MASK_CLEAR(PowerSource, F_BAT1_PRESENT))
            {
                if ((SMBA_DEV0_STS & (F_DEV_INIT+F_DEV_UPDATED)) ==
                    (F_DEV_INIT+F_DEV_UPDATED))
                {
                    SET_MASK(PowerSource, F_BAT1_PRESENT);
                }
            }
        }
    }
    else
    {
        if (SMBA_DEV0_STS != 0)
        {
            Clear_Memory_Range(BAT1_MemBase, 0x6F);
            SMBA_DEV0_STS = 0;
        }
        CLEAR_MASK(PowerSource, F_BAT1_PRESENT);
        Debounce_Bt1In = 0;
    }
#else
    //-------------------------------------------------------------------------
    if (wBatteryDetectTmr > 0)
    {
        wBatteryDetectTmr--;
        return;
    }
    if (SMBA_FloatingTimer > 0)
    {
        return;
    }
    //-------------------------------------------------------------------------
    if (BatteryDetectStep == 0)
    {
        /* Force Battery On-Line */
        //GPCRB3 = ALT;
        //GPCRB4 = ALT;
        SMBA_DEV0_STS = F_DEV_ON_LINE;
        SMBA_ERR_STS[0] = 0;
        SMBA_DEV1_DLY = 1;
        SMBA_DEV0_DIR = 0;
        WakeUpChargeTimer = 6;
        Clear_Memory_Range(BAT1_MemBase, 0x6F);
        BatteryDetectStep = 1;
        wBatteryDetectTmr = 120;        //120x50ms = 6sec
        return;
    }
    //-------------------------------------------------------------------------
    if (BatteryDetectStep == 1)
    {
        if (SMBA_ERR_STS[0] == 0)
        {
            BatteryDetectStep = 3;
            BatteryDetectRetry = 0;
        }
        else
        {
            BatteryDetectStep = 2;
            wBatteryDetectTmr = 400;    //400x50ms = 20sec
            SMBA_DEV0_STS = 0;
        }
        return;
    }
    //-------------------------------------------------------------------------
    if (BatteryDetectStep == 2)
    {
        BatteryDetectStep = 0;
        BatteryDetectRetry++;
        return;
    }
    //-------------------------------------------------------------------------
    if (BatteryDetectStep == 3)
    {
        if (SMBA_ERR_STS[0] > 32)
        {
            BatteryDetectStep = 0;
            wBatteryDetectTmr = 200 * (BatteryDetectRetry + 1); // 10sec
            SMBA_ERR_STS[0] = 0;
            Clear_Memory_Range(BAT1_MemBase, 0x6F);
            SMBA_DEV0_STS = 0;
            CLEAR_MASK(PowerSource, F_BAT1_PRESENT);
        }
        else
        {
            SET_MASK(PowerSource, F_BAT1_PRESENT);
        }
        return;
    }
    //-------------------------------------------------------------------------
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Update_ACPI_BIF1
 * @function - Update ACPI Control Method Battery Information
 * @Upstream - Update_ACPI_Battery,SCI_PowerEvent
 * @input    - Real Battery Data
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Update_ACPI_BIF1(void)
{
    xEC_Bt1DesignCapacityL = BAT1_DesignCapacity;
    xEC_Bt1DesignCapacityH = BAT1_DesignCapacity >> 8;
    xEC_Bt1FullChrgCapacityL = BAT1_FullChargeCapacity;
    xEC_Bt1FullChrgCapacityH = BAT1_FullChargeCapacity >> 8;
    xEC_Bt1DesignVoltageL = BAT1_DesignVoltage;
    xEC_Bt1DesignVoltageH = BAT1_DesignVoltage >> 8;
    xEC_Bt1SerialNumberL = BAT1_SerialNumber;
    xEC_Bt1SerialNumberH = BAT1_SerialNumber >> 8;
    xEC_Bt1TripPointL = 0x00;
    xEC_Bt1TripPointH = 0x00;
    xEC_Bt1ModelCode = 0x01;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Update_ACPI_BST
 * @function - Update ACPI Control Method Battery Status
 * @Upstream - Update_ACPI_Battery,SCI_PowerEvent
 * @input    - PowerSource
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Update_ACPI_BST1(void)
{
    //-------------------------------------------------------------------------
    xEC_Bt1RemainCapacityL = BAT1_RemainingCapacity;
    xEC_Bt1RemainCapacityH = BAT1_RemainingCapacity >> 8;
    xEC_Bt1PresentVoltageL = BAT1_Voltage;
    xEC_Bt1PresentVoltageH = BAT1_Voltage >> 8;
    xEC_BtRSOC = BAT1_RelativeStateOfChgL;
    //-------------------------------------------------------------------------
    ITempW01 = BAT1_Current;
    if (ITempW01 > 0x8000)
    {
        ITempW01 ^= 0xFFFF;
        ITempW01++;
    }
    xEC_Bt1PresentRateL = ITempW01;
    xEC_Bt1PresentRateH = ITempW01 >> 8;
    //-------------------------------------------------------------------------
    if (xEC_PowerState & F_AC_ON_LINE)
    {
        if (IS_MASK_CLEAR(xEC_PowerState, F_BAT1_PRESENT))
        {
            xEC_Bt1State = 0;
        }
        else if ((IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_LEGACY_5V_ADAPTER)) ||
                (IS_MASK_SET(I2C_EJ898A_FLAG, F_PD_IS_5V_ADAPTER)))
        {
            ITempW01 = BAT1_Current;
            if (ITempW01 == 0)
            {
                xEC_Bt1State = 0;
            }
            else if (ITempW01 > 0x8000)
            {
            #if !Support_MRD_NOREWORK
            	if(IS_ADP_SEL_L())
                xEC_Bt1State = 0;//reserved Legacy USB charger toggle between charge and discharge state
                else
			#endif
				xEC_Bt1State = F_ACPI_CHARGING;
            }
            else
            {
                xEC_Bt1State = F_ACPI_CHARGING;
            }

        }
        else if (//(BAT1_BatteryStatus & 0x0020) ||
            (BAT1_RelativeStateOfChgL >= 100)&&(BAT1_RemainingCapacity>=BAT1_FullChargeCapacity))
        {
            xEC_Bt1State = 0;
			BAT1_LockPowerOnRSOC =1;
			if(BAT1_RemainingCapacity < BAT1_LastFCC)
			 {
			 xEC_Bt1RemainCapacityL =  (BAT1_LastFCC);
			 xEC_Bt1RemainCapacityH = (BAT1_LastFCC)>>8;
			 }
        }
        else
        {
            xEC_Bt1State = F_ACPI_CHARGING;
        }
    }
    else
    {
        xEC_Bt1State = F_ACPI_DISCHRGE;
    }
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - Update_ACPI_Battery
 * @function - Update ACPI Control Method Battery
 * @Upstream - Hook_Timer500msEventC
 * @input    - PowerSource
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Update_ACPI_Battery(void)
{
    BYTE    i;
#if 0   /* TEST MODE */
    BAT1_DesignCapacity = 4000;
    BAT1_FullChargeCapacity = 4000;
    BAT1_DesignVoltage = 8400;
    BAT1_SerialNumber = 0xABCD;
    BAT1_RemainingCapacity = 3500;
    BAT1_Voltage = 8000;
    BAT1_Current = 500;
    BAT1_RelativeStateOfChgL = 87;
    SET_MASK(PowerSource, F_AC_ON_LINE);
    SET_MASK(PowerSource, F_BAT1_PRESENT);
#endif
    if (xEC_PowerState != PowerSource)
    {
        i = (xEC_PowerState ^ PowerSource);
        xEC_PowerState = PowerSource;
        Update_ACPI_BIF1();
        Update_ACPI_BST1();
#if 1   /* Process ACPI Event */
        if (i & F_AC_ON_LINE)
        {
           SendACiEventTimer = 20;
           WriteSCI_Buffer(_SCIEVT_ADAPTER);
        }
        else if (i & F_BAT1_PRESENT)
        {
            SendBatEventTimer = 5;
            BAT1_LastRSOC = BAT1_RelativeStateOfChgL;
        }
		BAT1_LastRSOC = BAT1_RelativeStateOfChgL;
		BAT1_LastFCC = BAT1_FullChargeCapacity;
		BAT1_LockPowerOnRSOC = 0;
#endif
    }
    else
    {
    	if(IS_ADAPTER_IN()&&(BAT1_LockPowerOnRSOC == 1))
		{
    		//if(BAT1_RemainingCapacity== BAT1_FullChargeCapacity)
			if (//(BAT1_BatteryStatus & 0x0020) ||
			(BAT1_RelativeStateOfChgL >= 100)&&(BAT1_RemainingCapacity>=BAT1_FullChargeCapacity))
			{return;} //disable update information to os.
			else
			{BAT1_LockPowerOnRSOC=0;}	
		}
        if (IS_MASK_SET(SMBA_DEV0_STS, F_DEV_UPDATED))
        {
            CLEAR_MASK(SMBA_DEV0_STS, F_DEV_UPDATED);
            Update_ACPI_BIF1();
            Update_ACPI_BST1();
        }
#if 0   /* TRUE: Windows can't polling battery */
        if (BAT1_LastRSOC != BAT1_RelativeStateOfChgL)
        {
            SendBatEventTimer = 5;
            BAT1_LastRSOC = BAT1_RelativeStateOfChgL;
        }
#endif
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - SCI_PowerEvent
 * @function - Adapter/Battery SCI notify event.
 * @Upstream - Hook_Timer100msEventB
 * @input    - EventAdapterOut,EventBatteryOut
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void SCI_PowerEvent(void)
{
    //-------------------------------------------------------------------------
    if (SendACiEventTimer > 0)
    {
        SendACiEventTimer--;
        if (SendACiEventTimer == 0)
        {
            Update_ACPI_BIF1();
            Update_ACPI_BST1();
            WriteSCI_Buffer(_SCIEVT_ADAPTER);
        }
        return;
    }
    //-------------------------------------------------------------------------
    if (SendBatEventTimer > 0)
    {
        SendBatEventTimer--;
        if (SendBatEventTimer == 0)
        {
            Update_ACPI_BIF1();
            Update_ACPI_BST1();
            WriteSCI_Buffer(_SCIEVT_BATTERY);
        }
        return;
    }
    //-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_BATTERY.C */
