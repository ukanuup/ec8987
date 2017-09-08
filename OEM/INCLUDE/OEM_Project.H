/*-----------------------------------------------------------------------------
 * @file     | OEM_PROJECT.H
 * ----------+-----------------------------------------------------------------
 * @function | Project function selection.
 * ----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2015, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_Project_H
#define OEM_Project_H

//*****************************************************************************
/* EC Firmware OEM Version */
//*****************************************************************************
/* String */
#define _BUILD_MUFG     "ITE Tech. Inc. $"
#define _BUILD_MODEL    "Intel SKL-Y-MRD$"
#define _BUILD_GUEST    "Intel$"
#define _BUILD_BOARD    "A0$"
#define _BUILD_ECVER    "V3.0A.19$"//030A0F_TC5->030A11_TA2
/* Values */
#define _EC_MAIN_VER    0x03    //= MAIN Version
#define _EC_SUB_VER     0x0A    //= SUB Version
#define _EC_TEST_VER    0x19    //= TEST Version
#define _EC_CODING_VER  0x00    //= CODING Version 

//*****************************************************************************
/* OEM Configuration */
//*****************************************************************************
#define ITE_CHIP_SPI_eFLASH     TRUE
#define SUPPORT_PECI            TRUE
#define SUPPORT_PECI_CS_MODE    TRUE
#define SUPPORT_BATTERY_IN      FALSE
#define SUPPORT_SMART_BATTERY   TRUE
#define SUPPORT_BATT_FAKE_INFO  FALSE
#define SUPPORT_SMART_CHARGER   TRUE
#define SUPPORT_FAN_CONTROL     FALSE
#define SUPPORT_FAN1_TACH       FALSE
#define SUPPORT_FAN2_TACH       FALSE
#define SUPPORT_LID_SWITCH      TRUE
#define SUPPORT_VIBRATE_MOTOR   FALSE
#define SUPPORT_WDT             FALSE
#define SUPPORT_KEYBOARD_SCAN   FALSE
#define SUPPORT_SMB_SLAVE_A     FALSE
#define SUPPORT_TYPE_C_SMBUS_B  TRUE
#define SUPPORT_SMBUS_B_100KHz  TRUE
#define SUPPORT_USB_TYPE_C_PD   TRUE
#define SUPPORT_TYPE_C_DD_EVENT TRUE
#define SupportLowPowerLED      TRUE
#define Support_Resend_DD		TRUE
#define Support_CombinationKey	TRUE
#define Support_PWRDOWN_SLPS3_INT TRUE
#define Support_MRD_NOREWORK 	TRUE
#define	Support_RTC_hang25_wakeup	TRUE//if 6c port send 04 ,then 4s check slp_s3/s4 low,if not(hang25), forece shutdown.(ecspace 43 == 6A :os is longruntest)
#define SupportP80_Restore		FALSE

//*****************************************************************************
/* Power Management Configuration */
//*****************************************************************************
#define SUPPORT_POWER_SAVING    FALSE
#define SUPPORT_S3_DEEPSLEEP    FALSE
#define _ENTER_SLEEP_TIMER      500

//*****************************************************************************
/* Kernel Configuration */
//*****************************************************************************
#define SUPPORT_SERVICE_PS2     FALSE
#define SUPPORT_SERVICE_KBSCAN  FALSE
#define SUPPORT_MIRROR_ONCE     TRUE

//*****************************************************************************
/* Test Switch (Need setting FALSE before release build) */
//*****************************************************************************
#define SUPPORT_VIRTUAL_BST     FALSE

//*****************************************************************************
/* GPIO Special Function */
//*****************************************************************************
#define SUPPORT_PWRSW_RESET     TRUE   //GPE.4
#define SUPPORT_GPH0_CLKRUN     FALSE
#define SUPPORT_GPB0B1_UART     FALSE
#define SUPPORT_GPD2_PLTRST     FALSE

//*****************************************************************************
/* Watchdog */
//*****************************************************************************
#define SUPPORT_MCU_WDT_RESET   FALSE   // Internal MCU Watchdog
#define SUPPORT_EXT1_WDT_RESET  FALSE
#define SET_WDT_TIMER           8       // 8Sec

//*****************************************************************************
/* HSPI interface */
//*****************************************************************************
#define HSPI                    FALSE   // support HSPI function
#define HSPI_QOFR               FALSE   // HSPI Quad Enable
#define HSPI_DefferingMode      FALSE   // HSPI is deffering mode
/* OEM SPI Spaces Configuration */
#define HSPI_ECCodeRomAddrH     0x00    // EC code space is 0x19xxxx

//*****************************************************************************
/* SIO Base address select 0x00:2E/2F 0x01:4E/4F 0x02:User define */
//*****************************************************************************
#define Init_BADR               0x01    // 00:2E.2F 01:4E.4F 02:SWCBAH
#define Init_SWCBAHR            0x00    // I/O Port High Byte
#define Init_SWCBALR            0x4E    // I/O Port Low  Byte
#define Init_I2EC               0x43    // Enable I2EC R/W & Port80 Decode

//*****************************************************************************
/* Kernel code feature */
//*****************************************************************************
#define ITE_CHIP_858X           FALSE
#define SUPPORT_EC_RAM2K        TRUE    //IT8527E:FALSE
#define CrystalFree_Support     TRUE
#define KB_FnStickKey           FALSE   // True : for Fn stick key function
#define ExternMatrixGPO         FALSE   // True : using GPO Pin scan keyboard

//*****************************************************************************
/* PS2 interface */
//*****************************************************************************
/* Note : If TouchPad_only is set, remeber to call
          PowerOffClearTPPendingData() function in power off sequnce
          include (S3, S4, and S5)¡C
*/
#define TouchPad_only           TRUE    // True : Only PS/2 touch pad device
#define Hook_ECACKMouseDriver

//*****************************************************************************
/* Switch to Switch */
//*****************************************************************************
#if TouchPad_only
#define MultiplexedModes        FALSE   // 0 : Not support multiplexed mode.
#define PS2IFHotPlugHotSwap     FALSE   // 1 : Support hot-plug, hot-swap
/* Support "Hook_DisableInternalTB" for EC on/off touchpad */
//#define Hook_Func_DisableTP
#else
#define MultiplexedModes        TRUE    // 1 : Support multiplexed modes.
#define PS2IFHotPlugHotSwap     FALSE   // Not Support hot-plug, hot-swap
#endif

/* ITE EC Function Setting and selection */
#if CrystalFree_Support
#define EC_Signature_Flag       0x94    // for 8518 crystal free
#else
#define EC_Signature_Flag       0xA5    // external crystal
#endif

/* HSPI interface */
#if HSPI
#define Init_FMSSR              0x0E    // 0x1F 16M Bytes Share Rom for HSPI
#else
#define Init_FMSSR              0x1F    // 0x1F 2M Bytes Share Rom
#endif

//*****************************************************************************
/* UART debug interface
   Timer 2 baudrate = Fosc / 32 / (0x10000-RCAP2)¡C */
//*****************************************************************************
#ifdef UART_Debug
// 57600 bps------------------------
#define R2HV                    0xFF
#define R2LV                    0xFB
// 57600 bps------------------------
#endif

//-----------------------------------------------------------------------------
#endif  //OEM_Project_H
/*-----------------------------------------------------------------------------
 * End of OEM_Project.H */
