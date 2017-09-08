/*-----------------------------------------------------------------------------
 * @file     | OEM_PS2.C
 *-----------+-----------------------------------------------------------------
 * @function | PS/2 port function
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
#define DEBUG_OEM_PS2           FALSE
#define CHECK_TP_ID_ELANTECH    FALSE
#define CHECK_TP_ID_SYNAPTICS   TRUE
#define CHECK_TP_ID_AVC         TRUE
#define CHECK_TP_ID_SENTELIC    TRUE

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_OEM_PS2
#define OemPS2_RamDebug(x)   RamDebug(x)
#else
#define OemPS2_RamDebug(x)   {}
#endif
//-----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// To define "Hook_ECACKMouseDriver" is necessary
// If define "Hook_ECACKMouseDriver" EC firmware need Respond mouse driver
//  via Hook_ECRespondtoMouseDriver function
// ----------------------------------------------------------------------------
void Hook_ECRespondtoMouseDriver(BYTE mscmd)
{
#if 0
    AUXData_To_Host_nWait(0xFA, 0xFF);

    if (KBHIData == 0xFF)
    {
        AUXData_To_Host_nWait(0xAA, 0xFF);
        AUXData_To_Host_nWait(0x00, 0xFF);
    }
#endif
}

// ----------------------------------------------------------------------------
// Hook kernel service_ps2 function
// ----------------------------------------------------------------------------
void Hook_service_ps2(BYTE ps2_channel, BYTE ps2_data)
{

}

// ----------------------------------------------------------------------------
// Disable port 0 ( send 0xF5 command to device)
// ----------------------------------------------------------------------------
void Hook_DisablePS2Port_0(void)
{
    DisablePS2Port_0();
}

// ----------------------------------------------------------------------------
// Disable port 1 ( send 0xF5 command to device)
// ----------------------------------------------------------------------------
void Hook_DisablePS2Port_1(void)
{
    DisablePS2Port_1();
}

// ----------------------------------------------------------------------------
// Disable port 2 ( send 0xF5 command to device)
// ----------------------------------------------------------------------------
void Hook_DisablePS2Port_2(void)
{
    DisablePS2Port_2();
}

// ----------------------------------------------------------------------------
// Enable port 0 ( send 0xF4 command to device)
// ----------------------------------------------------------------------------
void Hook_EnablePS2Port_0(void)
{
    EnablePS2Port_0();
}

// ----------------------------------------------------------------------------
// Enable port 1 ( send 0xF4 command to device)
// ----------------------------------------------------------------------------
void Hook_EnablePS2Port_1(void)
{
    EnablePS2Port_1();
}

// ----------------------------------------------------------------------------
// Enable port 0 ( send 0xF4 command to device)
// ----------------------------------------------------------------------------
void Hook_EnablePS2Port_2(void)
{
    EnablePS2Port_2();
}

// ----------------------------------------------------------------------------
// Hook_TPOnlyLowLevelFunc
// ----------------------------------------------------------------------------
void Hook_TPOnlyLowLevelFunc(void)
{

}
// ----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_PS2.C */