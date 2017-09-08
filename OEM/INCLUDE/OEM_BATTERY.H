/*-----------------------------------------------------------------------------
 * @file     | OEM_BATTERY.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_BATTERY.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef BATTERY_H
#define BATTERY_H


/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/
typedef struct PDdata
{
    XBYTE   *databyte0;
    XBYTE   *databyte1;
    XBYTE   *databyte2;
    XBYTE   *databyte3;
} PD_data;
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void PollSmartBattery(void);
extern void PollSmartCharger(void);
extern void Adapter_Detection(void);
extern void Battery_Detection(void);

extern void Update_ACPI_BIF1(void);
extern void Update_ACPI_BST1(void);
extern void Update_ACPI_Battery(void);
extern void SCI_PowerEvent(void);

extern void Charger_Hook1SecTimer(void);

//-----------------------------------------------------------------------------
extern void USB_TypeC_Adapter_Charging(void);


//-----------------------------------------------------------------------------
#endif  //BATTERY_H
/*-----------------------------------------------------------------------------
 * End of OEM_BATTERY.H */
