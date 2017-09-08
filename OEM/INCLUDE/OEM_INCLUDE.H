/*-----------------------------------------------------------------------------
 * @file     | OEM_INCLUDE.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_INCLUDE.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_INCLUDE_H
#define OEM_INCLUDE_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
//----------------------------------------------------------------------------
// OEM Bank0
//----------------------------------------------------------------------------
#include <OEM_GPIO.H>
#include <OEM_Project.H>
#include <OEM_INIT.H>
#include <OEM_MAIN.H>
#include <OEM_LED.H>
#include <OEM_FAN.H>
#include <OEM_BATTERY.H>
#include <OEM_MEMORY.H>
#include <OEM_POWER.H>
#include <OEM_EVENT.H>
#include <OEM_SMBUS.H>
#include <OEM_SCANTABS.H>
#include <OEM_ADC.H>
#include <OEM_MMB.H>
#include <OEM_ACPI.H>
#include <OEM_CIR.H>
#include <OEM_FLASH.H>
#include <OEM_HOSTIF.H>
#include <OEM_6064.H>
#include <OEM_MailBox.H>
#include <OEM_Ver.H>
#include <OEM_LCD.H>
#include <OEM_PM4.H>
#include <OEM_PECI.H>
#include <OEM_PM3.H>
#include <OEM_LPC.H>
#include <OEM_SPI.H>
#include <OEM_IRQ.H>
#include <OEM_PM2.H>
#include <OEM_PS2.H>
#include <OEM_SPI.H>
#include <OEM_LPC.H>
#include <OEM_TIME.H>
#include <OEM_Timer.H>
#include <OEM_HSPI.H>
#include <OEM_ASM.H>
#include <OEM_Debug.H>
#include <OEM_ECPDM.H>

//----------------------------------------------------------------------------
// OEM Bank1
//----------------------------------------------------------------------------
#include <OEM_BANK1_Func.H>

//----------------------------------------------------------------------------
// OEM Bank2
//----------------------------------------------------------------------------
#include <OEM_BANK2_Func.H>

//----------------------------------------------------------------------------
// OEM Ban3
//----------------------------------------------------------------------------
#include <OEM_BANK3_Func.H>

//-----------------------------------------------------------------------------
#endif  //OEM_INCLUDE_H
/*-----------------------------------------------------------------------------
 * End of OEM_INCLUDE.H */